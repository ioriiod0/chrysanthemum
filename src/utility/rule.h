// ======================================================================================
// File         : rule.h
// Author       : Gao Lei 
// Last Change  : 12/17/2011 | 19:15:05 PM | Saturday,December
// Description  : 
// ======================================================================================


#include <functional>


struct no_skip;
struct skip;

template <typename Iterator,typename skip_policy = skip>
struct rule
{
public:
    typedef Iterator iterator; 
    typedef std::function<bool(Iterator&,Iterator)> delegater;
    typedef std::function<bool(Iterator&,Iterator)> skiper;
public:
    template <typename Skiper>
    rule(Skiper&& s) {skiper_ = std::forward<Skiper>(s);}
public:
    bool operator() (Iterator& first,Iterator last)
    {
        if(dele_)
        {
            Iterator it;
            for(;;)
            {
                it = first;
                if(!skiper_(first,last))
                {
                    first = it;
                    break;
                }
            } 
            if(!dele_(first,last))
                return false;
            for(;;)
            {
                it = first;
                if(!skiper_(first,last))
                {
                    first = it;
                    break;
                }
            } 
        }
        return true;
    }
    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }
private:
    delegater dele_;
    skiper skiper_;
};


template <typename Iterator>
struct rule<Iterator,no_skip>
{
public:
    typedef Iterator iterator;
    typedef std::function<bool(Iterator&,Iterator)> delegater;
public:
    bool operator() (Iterator& first,Iterator last)
    {
        if(dele_)
        {
            if(!dele_(first,last))
                return false;
        }
        return true;
    }
    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }
private:
    delegater dele_;
};


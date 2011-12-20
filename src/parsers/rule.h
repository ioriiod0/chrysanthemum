// ======================================================================================
// File         : rule.h
// Author       : Gao Lei 
// Last Change  : 12/17/2011 | 19:15:05 PM | Saturday,December
// Description  : 
// ======================================================================================


#include <functional>
#include "basic_parsers.h"


struct no_skip;
struct no_context;

////////////////////Skiper & Context/////////////////
template <typename Iterator,typename Context,typename Skiper = _space>
struct rule
{
public:
    typedef Context ctx_type;
    typedef std::function<bool(Iterator&,Iterator)> delegater;

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
            if(dele_(first,last))
            {
                for(;;)
                {
                    it = first;
                    if(!skiper_(first,last))
                    {
                        first = it;
                        break;
                    }
                }
                return true;
            }
        }
        return false;
    }
    
    ctx_type& ctx()
    {
        return ctx_;
    }

    const ctx_type& ctx() const
    {
        return ctx_;
    }

    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }
private:
    delegater dele_;
    Skiper skiper_;
    ctx_type ctx_;
};

/////////////////////////no_skiper////////////////////////////
template <typename Iterator,typename Context>
struct rule<Iterator,Context,no_skip>
{
public:
    typedef Context ctx_type;
    typedef std::function<bool(Iterator&,Iterator)> delegater;
public:
    bool operator() (Iterator& first,Iterator last)
    {
        if(dele_)
        {
            if(dele_(first,last))
                return true;
        }
        return false;
    }

    ctx_type& ctx()
    {
        return ctx_;
    }

    const ctx_type& ctx() const
    {
        return ctx_;
    }
    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }
private:
    delegater dele_;
    ctx_type ctx_;
};

/////////////////////////no_context and no_skiper//////////////////
template <typename Iterator>
struct rule<Iterator,no_context,no_skip>
{
public:
    typedef std::function<bool(Iterator&,Iterator)> delegater;
public:
    bool operator() (Iterator& first,Iterator last)
    {
        if(dele_)
        {
            if(dele_(first,last))
                return true;
        }
        return false;
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

////////////////////////no_context///////////////////////////
template <typename Iterator,typename Skiper>
struct rule<Iterator,no_context,Skiper>
{
public:
    typedef std::function<bool(Iterator&,Iterator)> delegater;
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
            if(dele_(first,last))
            {
                for(;;)
                {
                    it = first;
                    if(!skiper_(first,last))
                    {
                        first = it;
                        break;
                    }
                }
                return true;
            }
        }
        return false;
    }
    
    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }
private:
    delegater dele_;
    Skiper skiper_;

};

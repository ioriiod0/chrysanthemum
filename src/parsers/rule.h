// ======================================================================================
// File         : rule.h
// Author       : Gao Lei 
// Last Change  : 12/17/2011 | 19:15:05 PM | Saturday,December
// Description  : 
// ======================================================================================


#include <functional>
#include "basic_parsers.h"

struct no_skip;


////////////////////Skiper & Context/////////////////
template <typename Iterator,typename Skiper = _space>
struct rule
{
public:
    typedef std::function<bool(Iterator&,Iterator)> delegater;
    rule(Skiper&& skiper = Skiper()):skiper_(std::forward<Skiper>(skiper)) {}

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


/////////////////////////no_skiper//////////////////
template <typename Iterator>
struct rule<Iterator,no_skip>
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



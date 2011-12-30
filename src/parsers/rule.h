// ======================================================================================
// File         : rule.h
// Author       : Gao Lei 
// Last Change  : 12/17/2011 | 19:15:05 PM | Saturday,December
// Description  : 
// ======================================================================================


#include <functional>
#include <stack>
#include "basic_parsers.h"

namespace chrysanthemum{

struct no_skip;
struct no_context;


////////////////////Skiper & Context/////////////////
template <typename Iterator,typename Context,typename Skiper = _space>
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
            new_ctx();
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
        clear_ctx();
        return false;
    }


    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }

    /////////////////////////////////
    void new_ctx()
    {
        ctxs.emplace();

    }
    void clear_ctx()
    {
        ctxs.pop();
    }

    Context& cur_ctx()
    {
        return ctxs.top();
    }

    const Context& cur_ctx() const
    {
        return ctxs.top();
    }

private:
    delegater dele_;
    Skiper skiper_;
    std::stack<Context> ctxs;

};


/////////////////////////no_skiper//////////////////
template <typename Iterator,typename Context>
struct rule<Iterator,Context,no_skip>
{
public:
    typedef std::function<bool(Iterator&,Iterator)> delegater;
public:
    bool operator() (Iterator& first,Iterator last)
    {
        if(dele_)
        {
            new_ctx();
            if(dele_(first,last))
                return true;
        }
        clear_ctx();
        return false;
    }
    /////////////////////////////////
    void new_ctx()
    {
        ctxs.emplace();

    }
    void clear_ctx()
    {
        ctxs.pop();
    }

    Context& cur_ctx()
    {
        return ctxs.top();
    }

    const Context& cur_ctx() const
    {
        return ctxs.top();
    }


    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }
private:
    delegater dele_;
    std::stack<Context> ctxs;
};


////////////////////no_context/////////////////
template <typename Iterator,typename Skiper>
struct rule<Iterator,no_context,Skiper>
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



} //end namespace

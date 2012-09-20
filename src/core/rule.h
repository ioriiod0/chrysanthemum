// ======================================================================================
// File         : rule.h
// Author       : Gao Lei
// Last Change  : 12/17/2011 | 19:15:05 PM | Saturday,December
// Description  : 
// ======================================================================================


#include <functional>
#include <stack>
#include <deque>
#include <list>
#include <vector>
#include <memory>
#include <ext/pool_allocator.h>
#include "parser_base.h"

namespace chrysanthemum{

struct no_skip;
struct no_context;


////////////////////Skiper & Context/////////////////
template <typename Scanner,typename Context,typename Skiper>
struct rule:public parser_base<rule<Scanner,Context,Skiper>>
{
public:
    typedef std::function<bool(Scanner&)> delegater;
    rule(Skiper&& skiper = Skiper()):skiper_(std::forward<Skiper>(skiper)) {}

public:
    bool operator() (Scanner& scan)
    {
        if(dele_)
        {
            new_ctx();

            Scanner save;
            for(;;)
            {
                save = scan;
                if(!skiper_(scan))
                {
                    scan = save;
                    break;
                }
            } 

            if(dele_(scan))
            {
                for(;;)
                {
                    save = scan;
                    if(!skiper_(scan))
                    {
                        scan = save;
                        break;
                    }
                }
                return true;
            }

            clear_ctx();
        }
       
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

    Context pop_ctx()
    {
        Context tmp = std::move(cur_ctx());
        clear_ctx();
        return tmp;
    }

    const Context& cur_ctx() const
    {
        return ctxs.top();
    }


private:
    delegater dele_;
    Skiper skiper_;
    // std::stack<Context,std::deque<Context,__gnu_cxx::__pool_alloc<Context> > > ctxs;
    std::stack<Context> ctxs;
};


/////////////////////////no_skiper//////////////////
template <typename Scanner,typename Context>
struct rule<Scanner,Context,no_skip>:public parser_base<rule<Scanner,Context,no_skip>>
{
public:
    typedef std::function<bool(Scanner&)> delegater;
public:
    bool operator() (Scanner& scan)
    {
        if(dele_)
        {
            new_ctx();
            if(dele_(scan))
                return true;
            clear_ctx();
        }
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

    Context pop_ctx()
    {
        Context tmp = std::move(cur_ctx());
        clear_ctx();
        return tmp;
    }

    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }

private:
    delegater dele_;
    //std::stack<Context,std::deque<Context,__gnu_cxx::__pool_alloc<Context> > > ctxs;
    std::stack<Context> ctxs;

};


////////////////////no_context/////////////////
template <typename Scanner,typename Skiper>
struct rule<Scanner,no_context,Skiper>:public parser_base<rule<Scanner,no_context,Skiper>>
{
public:
    typedef std::function<bool(Scanner&)> delegater;
    rule(Skiper&& skiper = Skiper()):skiper_(std::forward<Skiper>(skiper)) {}

public:
    bool operator() (Scanner& scan)
    {
        if(dele_)
        {
            Scanner save;
            for(;;)
            {
                save = scan;
                if(!skiper_(scan))
                {
                    scan = save;
                    break;
                }
            } 
            if(dele_(scan))
            {
                for(;;)
                {
                    save = scan;
                    if(!skiper_(scan))
                    {
                        scan = save;
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
template <typename Scanner>
struct rule<Scanner,no_context,no_skip>:public parser_base<rule<Scanner,no_context,no_skip>>
{
public:
    typedef std::function<bool(Scanner&)> delegater;
public:
    bool operator() (Scanner& scan)
    {
        if(dele_)
        {
            if(dele_(scan))
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

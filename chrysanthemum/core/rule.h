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
#include "parser_base.h"

namespace chrysanthemum{

struct no_skip;
struct no_context;


////////////////////Skiper & Context/////////////////
template <typename Scanner,typename Context,typename Skiper>
struct rule:public parser_base<rule<Scanner,Context,Skiper> >
{
public:
    typedef std::function<bool(Scanner&)> delegater;
    typedef std::function<void(Context&)> callbacker;
    rule(Skiper&& skiper = Skiper()):skiper_(std::forward<Skiper>(skiper)) {}
    ~rule() {
        if(on_error_){
            while(!ctxs.empty()) {
                on_error_(ctxs.top());
                ctxs.pop();
            }
        }
    }

public:
    bool operator() (Scanner& scan)
    {
        if(dele_)
        {
            push_ctx();
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
        Context tmp(std::move(ctxs.top()));
        if(on_pop_) {
            on_pop_(tmp);
        }
        ctxs.pop();
        return tmp;
    }

    template <typename F>
    void on_init(F&& cb) {
        on_init_ = std::forward<F>(cb);
    }

    template <typename F>
    void on_pop(F&& cb) {
        on_pop_ = std::forward<F>(cb);
    }

    template <typename F>
    void on_error(F&& cb) {
        on_error_ = std::forward<F>(cb);
    }



private:
    void push_ctx()
    {
        ctxs.emplace();
        if(on_init_){
            on_init_(ctxs.top());
        }
    }
    void clear_ctx()
    {
        if(on_error_) {
            on_error_(ctxs.top());
        }
        ctxs.pop();
    }

    callbacker on_init_;
    callbacker on_error_;
    callbacker on_pop_;
    delegater dele_;
    Skiper skiper_;
    // std::stack<Context,std::deque<Context,__gnu_cxx::__pool_alloc<Context> > > ctxs;
    std::stack<Context> ctxs;
};


/////////////////////////no_skiper//////////////////
template <typename Scanner,typename Context>
struct rule<Scanner,Context,no_skip>:public parser_base<rule<Scanner,Context,no_skip> >
{
public:
    typedef std::function<bool(Scanner&)> delegater;
    typedef std::function<void(Context&)> callbacker;
public:
    rule() {}
    ~rule() {
        if(on_error_){
            while(!ctxs.empty()) {
                on_error_(ctxs.top());
                ctxs.pop();
            }
        }
    }

    bool operator() (Scanner& scan)
    {
        if(dele_)
        {
            push_ctx();
            if(dele_(scan))
                return true;
            clear_ctx();
        }
        return false;
    }

    /////////////////////////////////
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
        Context tmp(std::move(ctxs.top()));
        if(on_pop_) {
            on_pop_(tmp);
        }
        ctxs.pop();
        return tmp;
    }

    //////////////////////////////////////
    template <typename Delegater>
    void operator%=(Delegater&& dele)
    {
        dele_ = std::forward<Delegater>(dele);
    }

    template <typename F>
    void on_init(F&& cb) {
        on_init_ = std::forward<F>(cb);
    }

    template <typename F>
    void on_pop(F&& cb) {
        on_pop_ = std::forward<F>(cb);
    }

    template <typename F>
    void on_error(F&& cb) {
        on_error_ = std::forward<F>(cb);
    }

private:
    void push_ctx()
    {
        ctxs.emplace();
        if(on_init_){
            on_init_(ctxs.top());
        }
    }
    void clear_ctx()
    {
        if(on_error_) {
            on_error_(ctxs.top());
        }
        ctxs.pop();
    }

    callbacker on_init_;
    callbacker on_error_;
    callbacker on_pop_;
    delegater dele_;
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

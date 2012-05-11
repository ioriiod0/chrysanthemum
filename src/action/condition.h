// ======================================================================================
// File         : condition.h
// Author       : Gao Lei , Qianhong Wang
// Last Change  : 12/17/2011 | 18:29:25 PM | Saturday,December
// Description  : 
// ======================================================================================
#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <tuple>
#include <functional>
#include <type_traits>
#include "../utility/meta_fuctions.h"

namespace chrysanthemum{


template <typename Condition,typename Handler>
struct if_then
{
    ////////////////////////////////////////
    if_then(Condition&& c,Handler&& h):c_(std::forward<Condition>(c)),
                        h_(std::forward<Handler>(h)) {}
    ///////////////////////////////////////
    template <typename T>
    bool operator()(const T& t)
    {
        bool ret = c_(t);
        if(ret)
            h_(t);
        return ret;
    }
    //////////////////////////////////////
    Condition c_;
    Handler h_;
    
};

template <typename Condition,typename Handler>
auto _if_then(Condition&& c,Handler&& h)
    -> if_then<Condition,Handler>
{
    return if_then<Condition,Handler>(std::forward<Condition>(c),std::forward<Handler>(h));
}

/////////////////////////////////////////////////////////////////////////

template <typename Condition,typename Handler1,typename Handler2>
struct if_else
{
    ////////////////////////////////////////
    if_else(Condition&& c,Handler1&& h1,Handler2&& h2):
                            c_(std::forward<Condition>(c)),
                            h1_(std::forward<Handler1>(h1)),
                            h2_(std::forward<Handler2>(h2)) {}
    ///////////////////////////////////////
    template <typename T>
    bool operator()(const T& t)
    {
        bool ret = c_(t);
        if(ret)
            h1_(t);
        else
            h2_(t);
        return ret;
    }
    //////////////////////////////////////
    Condition c_;
    Handler1 h1_;
    Handler2 h2_;
    
};

template <typename Condition,typename Handler1,typename Handler2>
auto _if_else(Condition&& c,Handler1&& h1,Handler2&& h2)
    -> if_else<Condition,Handler1,Handler2>
{
    return if_else<Condition,Handler1,Handler2>(std::forward<Condition>(c),
                                                std::forward<Handler1>(h1),
                                                std::forward<Handler2>(h2));
}

} //end namespace

#endif

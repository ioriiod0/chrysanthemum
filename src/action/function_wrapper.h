// ======================================================================================
// File         : function_wrapper.h
// Author       : Gao Lei 
// Last Change  : 12/17/2011 | 21:03:02 PM | Saturday,December
// Description  : 
// ======================================================================================
#ifndef __FUNCTION_WRAPPER_H__
#define __FUNCTION_WRAPPER_H__

#include <tuple>
#include <functional>
#include <type_traits>
#include "../utility/meta_fuctions.h"

namespace chrysanthemum {

template <typename Converter,typename Handler>
struct function_wrapper
{
    ///////////////////////////
    typedef typename Converter::ctx_type Arg;
    typedef std::function<bool(Arg)> Func;
    ////////////////////////////
    function_wrapper(Converter&& c,Handler&& h):c_(std::forward<Converter>(c)),
                                                  f_(std::forward<Handler>(h)) {}
    /////////////////////////////
    template <typename Iterator>
    bool operator() (Iterator first,Iterator last)
    {
        if(c_(first,last))
            return f_(c_.ctx());
        return false;
    }
    //////////////////////
    Func f_;
    Converter c_; 

};


template <typename C,typename H>
auto _wrapper(C&& c,H&& h)
    -> function_wrapper<C,H>
{
    return function_wrapper<C,H>(std::forward<C>(c),std::forward<H>(h));
}

} //end namespace
#endif


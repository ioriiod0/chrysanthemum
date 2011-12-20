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



template <typename Handler>
struct function_wrapper;


template <typename R,typename Farg>
struct function_wrapper<R(Farg)>
{
    ///////////////////////////
    typedef std::function<R(Farg)> F_type;
    typedef typename std::remove_reference<Farg>::type T1;
    typedef typename std::remove_const<T1>::type data_type;
    ////////////////////////////
    function_wrapper(const F_type& f):tuple_(data_type()),f_(f) {}
    function_wrapper(F_type&& f):tuple_(data_type()),f_(std::move(f)) {}
    /////////////////////////////
    function_wrapper(const function_wrapper& rhs):f_(rhs.f_),tuple_(rhs.tuple_) {}
    function_wrapper(function_wrapper&& rhs):f_(std::move(rhs.f_)),
                                            tuple_(std::move(rhs.tuple_)) {}
    ///////////////////////////
    template <typename Iterator>
    bool operator() (Iterator first,Iterator last)
    {
        Traits<data_type>::do_convert(first,last,tuple_);
        f_(std::get<0>(tuple_));
        return true;
    }
    //////////////////////
    F_type f_;
    std::tuple<data_type> tuple_;

};


template <typename Sig,typename U>
auto _wrapper(U&& u)
    -> function_wrapper<converter_traits,Sig>
{
    return function_wrapper<converter_traits,Sig>(std::forward<U>(u));
}

#endif


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
#include "basic_action.h"
#include "converters.h"


template <template<class> class Traits,typename Handler>
struct function_wrapper;


// template <typename Farg,template<class> class Traits,typename... Args>
// struct function_wrapper<bool(Farg),Traits,Args...>
// {
//     ///////////////////////////
//     typedef typename std::function<R(Farg)>::argument_type T1;
//     typedef typename std::remove_const<T1>::type data_type;
//     ////////////////////////////
//     template <typename U>
//     function_wrapper(U&& u,Args&&... args):
//                             f_(std::forward<U>(u)),
//                             tuple_(data_type(),std::forward<Args>(args)...){}
//     /////////////////////////////
//     function_wrapper(const function_wrapper& rhs) = default;
//     function_wrapper(function_wrapper&& rhs) = default;
//     ///////////////////////////
//     template <typename Iterator>
//     bool operator() (Iterator first,Iterator last)
//     {
//         Traits<data_type>::do_convert(first,last,tuple_);
//         return f_(std::get<0>(tuple_));
//     }
//     //////////////////////
//     std::function<bool(Farg)> f_;
//     std::tuple<data_type,Args...> tuple_;

// };

/////////////////////////////////////////////////////////////////

template <template<class> class Traits,typename R,typename Farg>
struct function_wrapper<Traits,R(Farg)>
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


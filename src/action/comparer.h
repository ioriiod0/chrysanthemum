// ======================================================================================
// File         : comparer.h
// Author       : Lei Gao 
// Last Change  : 12/17/2011 | 16:20:06 PM | Saturday,December
// Description  : 
// ======================================================================================
#ifndef __COMPARER_H__
#define __COMPARER_H__

#include <tuple>
#include <functional>
#include <type_traits>
#include "../utility/meta_fuctions.h"
#include "basic_action.h"
#include "converters.h"



template <template<class> class Traits,typename Comp,typename T,typename... Args>
struct comparer
{
    typedef typename std::remove_reference<T>::type data_type;
    ////////////////////////////////////////
    comparer(T&& t,Args&&... args):t_(std::forward<T>(t)),
                        tuple_(data_type(),std::forward<Args>(args)...) {}
    ///////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        Traits<data_type>::do_convert(first,last,tuple_);
        return comp_(std::get<0>(tuple_),t_);
    }
    ///////////////////////////////
    data_type& data()
    {
        return std::get<0>(tuple_);
    }
    const data_type& data() const
    {
        return std::get<0>(tuple_);
    }
    //////////////////////////////////////
    Comp comp_;
    T t_;
    std::tuple<data_type,Args...> tuple_;

    
};

template <typename T,typename... Args>
auto _equal_to(T&& t,Args&&... args)
    -> comparer<converter_traits,std::equal_to<T>,T,Args...>
{
    return comparer<converter_traits,std::equal_to<T>,T,Args...>(std::forward<T>(t),std::forward<Args>(args)...);
}

template <typename T,typename... Args>
auto _not_equal_to(T&& t,Args&&... args)
    -> comparer<converter_traits,std::not_equal_to<T>,T,Args...>
{
    return comparer<converter_traits,std::not_equal_to<T>,T,Args...>(std::forward<T>(t),std::forward<Args>(args)...);
}   

template <typename T,typename... Args>
auto _less_than(T&& t,Args&&... args)
    -> comparer<converter_traits,std::less<T>,T,Args...>
{
    return comparer<converter_traits,std::less<T>,T,Args...>(std::forward<T>(t),std::forward<Args>(args)...);
}

template <typename T,typename... Args>
auto _less_equal(T&& t,Args&&... args)
    -> comparer<converter_traits,std::less_equal<T>,T,Args...>
{
    return comparer<converter_traits,std::less_equal<T>,T,Args...>(std::forward<T>(t),std::forward<Args>(args)...);
}

template <typename T,typename... Args>
auto _greater_than(T&& t,Args&&... args)
    -> comparer<converter_traits,std::greater<T>,T,Args...>
{
    return comparer<converter_traits,std::greater<T>,T,Args...>(std::forward<T>(t),std::forward<Args>(args)...);
}
template <typename T,typename... Args>
auto _greater_equal(T&& t,Args&&... args)
    -> comparer<converter_traits,std::greater_equal<T>,T,Args...>
{
    return comparer<converter_traits,std::greater_equal<T>,T,Args...>(std::forward<T>(t),std::forward<Args>(args)...);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif







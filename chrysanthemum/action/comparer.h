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

namespace chrysanthemum{

template <typename T,typename Comp>
struct comparer
{
    ////////////////////////////////////////
    comparer(T&& t):t_(std::forward<T>(t)) {}
    ///////////////////////
    bool operator()(const T& t)
    {
        return comp_(t,t_);
    }
    //////////////////////////////////////
    Comp comp_;
    T t_;
};

template <typename T>
auto _equal_to(T&& t)
    -> comparer<T,std::equal_to<T>>
{
    return comparer<T,std::equal_to<T>>(std::forward<T>(t));
}

template <typename T>
auto _not_equal_to(T&& t)
    -> comparer<T,std::not_equal_to<T>>
{
    return comparer<T,std::not_equal_to<T>>(std::forward<T>(t));
}   

template <typename T>
auto _less_than(T&& t)
    -> comparer<T,std::less<T>>
{
    return comparer<T,std::less<T>>(std::forward<T>(t));
}

template <typename T>
auto _less_equal(T&& t)
    -> comparer<T,std::less_equal<T>>
{
    return comparer<T,std::less_equal<T>>(std::forward<T>(t));
}


template <typename T>
auto _greater_than(T&& t)
    -> comparer<T,std::greater<T>>
{
    return comparer<T,std::greater<T>>(std::forward<T>(t));
}

template <typename T>
auto _greater_equal(T&& t)
    -> comparer<T,std::greater_equal<T>>
{
    return comparer<T,std::greater_equal<T>>(std::forward<T>(t));
}


}//end namespace
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif







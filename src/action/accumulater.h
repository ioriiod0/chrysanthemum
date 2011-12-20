// ======================================================================================
// File         : accumulater.h
// Author       : Lei Gao 
// Last Change  : 12/15/2011 | 16:15:30 PM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __ACCUMULATER_H__
#define __ACCUMULATER_H__

#include <type_traits>
#include "../utility/meta_fuctions.h"



template <typename Sum>
struct accumulater
{
    ////////////////////////////////
    typedef typename std::remove_reference<Sum>::type data_type;
    /////////////////////////////////
    accumulater(Sum&& sum):sum_(std::forward<Sum>(sum)) {}
    ////////////////////////////////
    template <typename T>
    bool operator()(const T& t)
    {
        sum_ += t;
        return true;
    }
   
    /////////////////////////////////////
    Sum sum_; 
  

};

template <typename Sum>
auto _accumulater(Sum&& sum)
    -> accumulater<Sum>
{
    return accumulater<Sum>(std::forward<Sum>(sum));
}

#endif


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
#include "basic_action.h"
#include "converters.h"


template <template<class> class Traits,typename Sum,typename... Args>
struct accumulater
{
    ////////////////////////////////
    typedef typename std::remove_reference<Sum>::type data_type;
    /////////////////////////////////
    accumulater(Sum&& sum,Args&&... args):
                                    sum_(std::forward<Sum>(sum)),
                                    tuple_(data_type(),std::forward<Args>(args)...) {}
    ////////////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        Traits<data_type>::do_convert(first,last,tuple_);
        sum_ += std::move(std::get<0>(tuple_));
        return true;
    }
   
    ///////////////////////
    data_type& data()
    {
        return sum_;
    }
    const data_type& data() const
    {
        return sum_;
    }
    /////////////////////////////////////
    Sum sum_; 
    std::tuple<data_type,Args...> tuple_;    

};

template <typename Sum,typename... Args>
auto _accumulater(Sum&& sum,Args&&... args)
    -> accumulater<converter_traits,Sum,Args...>
{
    return accumulater<converter_traits,Sum,Args...>(std::forward<Sum>(sum),std::forward<Args>(args)...);
}

#endif


// ======================================================================================
// File         : back_inserter.h
// Author       : Lei Gao , Qianhong Wang
// Last Change  : 12/15/2011 | 16:14:25 PM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __BACK_INSERTER_H__
#define __BACK_INSERTER_H__

#include <type_traits>
#include "../utility/meta_fuctions.h"

//#include "data_holder.h"
namespace chrysanthemum{

template <typename Container>
struct back_inserter
{
    /////////////////////////////////
    back_inserter(Container&& c):c_(std::forward<Container>(c)) {}
    ////////////////////////////////
    template <typename T>
    bool operator()(const T& t)
    {
        c_.push_back(t);
        return true;
    }
   
    Container c_;


};

template <typename Container>
auto _back_inserter(Container&& c)
    -> back_inserter<Container>
{
    return back_inserter<Container>(std::forward<Container>(c));
}

} //end namespace
#endif


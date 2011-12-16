// ======================================================================================
// File         : back_inserter.h
// Author       : Lei Gao 
// Last Change  : 12/15/2011 | 16:14:25 PM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __BACK_INSERTER_H__
#define __BACK_INSERTER_H__

#include "basic_action.h"
#include "data_holder.h"


template <typename Container,typename... Args,template<class> class Traits = converter_traits>
struct back_inserter
{
    back_inserter(Container& c):c_(c) {}
    ////////////////////////////////////
    template <typename Iterator>
    bool operator() (Iterator first,Iterator last)
    {
        c_.push_back(Traits<typename Container::value_type>::do_convert(first,last,args));
        return true;
    }
    /////////////////////////////////////
    Container& c_;
    std::tuple<Args...> args;
    

};

template <typename Container,typename... Args>
auto _back_inserter(Container& c,Args&&... args)
    -> back_inserter<Container,Args...>
{
    return back_inserter<Container,Args...>(c,std::forward<Args>(args)...);
}

#endif


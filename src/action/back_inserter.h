// ======================================================================================
// File         : back_inserter.h
// Author       : Lei Gao 
// Last Change  : 12/15/2011 | 16:14:25 PM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __BACK_INSERTER_H__
#define __BACK_INSERTER_H__

#include <type_traits>
#include "../utility/meta_fuctions.h"
#include "basic_action.h"
#include "converters.h"
//#include "data_holder.h"


template <template<class> class Traits,typename Container,typename... Args>
struct back_inserter
{
    ////////////////////////////////
    typedef typename std::remove_reference<Container>::type data_type;
    typedef typename data_type::value_type value_type;
    /////////////////////////////////
    back_inserter(Container&& c,Args&&... args):
                                    c_(std::forward<Container>(c)),
                                    tuple_(value_type(),std::forward<Args>(args)...) {}
    ~back_inserter() {}
    ////////////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        Traits<value_type>::do_convert(first,last,tuple_);
        c_.push_back(std::move(std::get<0>(tuple_)));
        return true;
    }
   
    ///////////////////////
    data_type& data()
    {
        return c_;
    }
    const data_type& data() const
    {
        return c_;
    }
    /////////////////////////////////////
    Container c_;
    std::tuple<value_type,Args...> tuple_;    

};

template <typename Container,typename... Args>
auto _back_inserter(Container&& c,Args&&... args)
    -> back_inserter<converter_traits,Container,Args...>
{
    return back_inserter<converter_traits,Container,Args...>(std::forward<Container>(c),std::forward<Args>(args)...);
}

#endif


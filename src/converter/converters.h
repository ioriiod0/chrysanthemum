// ======================================================================================
// File         : action.h
// Author       : Lei Gao 
// Last Change  : 12/13/2011 | 13:32:14 PM | Tuesday,December
// Description  : 
// ======================================================================================
#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "convert_traits.h"

template <template <class> class Traits,typename T,typename... Args>
struct converter
{
    ////////////////////////
    typedef typename std::remove_reference<T>::type ctx_type;
    ////////////////////////
    converter(T&& t,Args&&... args):tuple_(std::forward<T>(t),
                                           std::forward<Args>(args)...) {}
    /////////////////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        Traits<ctx_type>::do_convert(first,last,tuple_);
        return true;
    }

    ///////////////////////
    ctx_type& ctx()
    {
        return std::get<0>(tuple_);
    }
    const ctx_type& ctx() const
    {
        return std::get<0>(tuple_);
    }

    std::tuple<T,Args...> tuple_;
};


template <typename T,typename... Args>
auto _converter(T&& t,Args&&... args)
    -> converter<converter_traits,T,Args...>
{
    return converter<converter_traits,T,Args...>(std::forward<T>(t),std::forward<Args>(args)...);
}






#endif


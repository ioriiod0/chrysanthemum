// ======================================================================================
// File         : and_p.h
// Author       : Gao Lei 
// Last Change  : 12/17/2011 | 21:30:22 PM | Saturday,December
// Description  : 
// ======================================================================================

#ifndef __and_P_H__
#define __and_P_H__


#include <type_traits>
#include <tuple>
#include "../utility/meta_fuctions.h"
#include "../utility/basic_parser.h"
#include "literal_p.h"



template <typename... Args>
class and_p:
    public basic_parser<typename std::remove_reference<typename at<0,Args...>::type>::type::iterator,
                       and_p<Args...> > 
{
public:
    typedef typename std::remove_reference<typename at<0,Args...>::type>::type::iterator Iterator;

    template <typename Tuple,typename It,std::size_t N>
    struct helper
    {
        inline static bool do_parse(Tuple& t,It& first,It last)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-N;
            if(!std::get<Idx>(t)(first,last))
                return false;
            return helper<Tuple,It,N-1>::do_parse(t,first,last);
        }
    };

    template <typename Tuple,typename It>
    struct helper<Tuple,It,1>
    {
        inline static bool do_parse(Tuple& t,It& first,It last)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-1;  
            if(!std::get<Idx>(t)(first,last))
                return false;
            return true;
        }
    };

    typedef std::tuple<Args...> tuple_type;

public:
    and_p(Args&&... args):tuple_(std::forward<Args>(args)...) {}
public:
    bool do_parse(Iterator& first,Iterator last) 
    {
       if(!helper<tuple_type,Iterator,
               std::tuple_size<tuple_type>::value>::do_parse(tuple_,first,last))
           return false;
       return true;
    }
private:
    tuple_type tuple_;
};


////////////////////////////////////////////////////////////////////////////
template <typename... Args>
auto _and(Args&&... args) -> and_p<Args...> 
{
    return and_p<Args...>(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////
template <typename T1,typename T2>
auto  operator& (T1&& t1,T2&& t2) -> and_p<T1,T2> 
{
    return and_p<T1,T2>(std::forward<T1>(t1),std::forward<T2>(t2));
}
///////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (T1&& t1,const char* str) 
    -> decltype(_and(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(str)))
{
    return _and(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(str));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (const char* str,T1&& t1) 
     -> decltype(_and(_literal<typename std::remove_reference<T1>::type::iterator>(str),std::forward<T1>(t1)))
{
    return _and(_literal<typename std::remove_reference<T1>::type::iterator>(str),
                std::forward<T1>(t1));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (T1&& t1,const std::string& str) 
     -> decltype(_and(std::forward<T1>(t1)),_literal<typename std::remove_reference<T1>::type::iterator>(str))
{
    return _and(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(str));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (const std::string& str,T1&& t1) 
     -> decltype(_and(_literal<typename std::remove_reference<T1>::type::iterator>(str),std::forward<T1>(t1)))
{
    return _and(_literal<typename std::remove_reference<T1>::type::iterator>(str),std::forward<T1>(t1));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (T1&& t1,char ch) 
     -> decltype(_and(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(ch))) 
{
    return _and(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(ch));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (char ch,T1&& t1) 
      -> decltype(_and(_literal<typename std::remove_reference<T1>::type::iterator>(ch),std::forward<T1>(t1))) 
{
    return _and(_literal<typename std::remove_reference<T1>::type::iterator>(ch),std::forward<T1>(t1));
}

#endif

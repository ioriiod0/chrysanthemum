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
#include "literal_p.h"



template <typename... Args>
class and_p 
{
public:

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
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last) 
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
inline auto _and(Args&&... args) -> and_p<Args...> 
{
    return and_p<Args...>(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////
template <typename T1,typename T2>
inline auto  operator& (T1&& t1,T2&& t2) -> and_p<T1,T2> 
{
    return and_p<T1,T2>(std::forward<T1>(t1),std::forward<T2>(t2));
}
///////////////////////////////////////////////////////////////////////////////
template <typename T1>
inline auto  operator& (T1&& t1,const char* str) 
    -> decltype(_and(std::forward<T1>(t1),_literal(str)))
{
    return _and(std::forward<T1>(t1),_literal(str));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
inline auto  operator& (const char* str,T1&& t1) 
     -> decltype(_and(_literal(str),std::forward<T1>(t1)))

{
    return _and(_literal(str),std::forward<T1>(t1));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
inline auto  operator& (T1&& t1,const std::string& str) 
     -> decltype(_and(std::forward<T1>(t1)),_literal(str))
{
    return _and(std::forward<T1>(t1),_literal(str));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
inline auto  operator& (const std::string& str,T1&& t1) 
     -> decltype(_and(_literal(str),std::forward<T1>(t1)))
{
    return _and(_literal(str),std::forward<T1>(t1));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
inline auto  operator& (T1&& t1,char ch) 
     //-> decltype(_and(std::forward<T1>(t1),_literal(ch)))
    ->and_p<T1,literal_ch_p<char>>
{
    return _and(std::forward<T1>(t1),_literal(ch));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
inline auto  operator& (char ch,T1&& t1) 
      -> and_p<literal_ch_p<char>,T1>
{
    return _and(_literal(ch),std::forward<T1>(t1));
}

#endif

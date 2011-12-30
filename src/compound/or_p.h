// ======================================================================================
// File         : or_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:13 PM | Wednesday,December
// Description  : 
// ======================================================================================


#ifndef __or_p_H__
#define __or_p_H__



#include <tuple>
#include <type_traits>
#include <string>
#include "literal_p.h"
#include "../utility/meta_fuctions.h"


namespace chrysanthemum{

template <typename... Args>
class or_p
{
public:

    template <typename Tuple,typename It,std::size_t N>
    struct helper
    {
        inline static bool do_parse(Tuple& t,It& first,It last)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-N; 
            It it = first;
            if(std::get<Idx>(t)(first,last))
            {
                //typedef typename std::tuple_element<Idx,Tuple>::type ttype;
                return true;
            }
            first = it;
            return helper<Tuple,It,N-1>::do_parse(t,first,last);
        }
    };

    template <typename Tuple,typename It>
    struct helper<Tuple,It,1>
    {
        inline static bool do_parse(Tuple& t,It& first,It last)
        { 
            const static std::size_t Idx = std::tuple_size<Tuple>::value-1; 
            It it = first;
            if(std::get<Idx>(t)(first,last))
            {
                //typedef typename std::tuple_element<Idx,Tuple>::type ttype;
                return true;
            }
            //first = it;
            return false;
        }
    };

    typedef std::tuple<Args...> tuple_type;


public:
    or_p(Args&&... args):tuple_(std::forward<Args>(args)...) {}
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



template <typename... Args>
inline auto _or(Args&&... args) -> or_p<Args...> 
{
    return or_p<Args...>(std::forward<Args>(args)...);
}


namespace ops {

template <typename T1,typename T2>
inline auto operator| (T1&& t1,T2&& t2)
    -> or_p<T1,T2>
{
    return or_p<T1,T2>(std::forward<T1>(t1),std::forward<T2>(t2));
}

template <typename T1>
inline auto operator| (T1&& t1,const char* str)
    -> or_p<T1,literal_str_p>
{
    return _or(std::forward<T1>(t1),_literal(str));
}

template <typename T1>
inline auto operator| (const char* str,T1&& t1)
    -> or_p<literal_str_p,T1>
{
    return _or(_literal(str),std::forward<T1>(t1));
}

template <typename T1>
inline auto operator| (T1&& t1,const std::string& str)
    -> or_p<T1,literal_str_p>
{
    return _or(std::forward<T1>(t1),_literal(str));
}
    
template <typename T1>
inline auto operator| (const std::string& str,T1&& t1)
    -> or_p<literal_str_p,T1>
{
    return _or(_literal(str),std::forward<T1>(t1));
}

template <typename T1>
inline auto operator| (T1&& t1,std::string&& str)
    -> or_p<T1,literal_str_p>
{
    return _or(std::forward<T1>(t1),_literal(std::move(str)));
}
    
template <typename T1>
inline auto operator| (std::string&& str,T1&& t1)
    -> or_p<literal_str_p,T1>
{
    return _or(_literal(std::move(str)),std::forward<T1>(t1));
}
    
template <typename T1>
inline auto operator| (T1&& t1,char ch)
    -> or_p<T1,literal_ch_p<char>>
{
    return _or(std::forward<T1>(t1),_literal(ch));
}
    
template <typename T1>
inline auto operator| (char ch,T1&& t1)
    -> or_p<literal_ch_p<char>,T1>
{
    return _or(_literal(ch),std::forward<T1>(t1));
}

} //end namespace ops

} //end namespace
#endif

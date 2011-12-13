// ======================================================================================
// File         : sequence_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:46:30 PM | Wednesday,December
// Description  : 
// ======================================================================================

#ifndef __SEQUENCE_P_H__
#define __SEQUENCE_P_H__


#include <type_traits>
#include <tuple>
#include "../utility/meta_fuctions.h"
#include "../utility/basic_parser.h"
#include "literal_p.h"



template <typename Iterator,typename... Args>
class squence:public basic_parser<Iterator,squence<Iterator,Args...>> 
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
    squence(Args&&... args):tuple_(std::forward<Args>(args)...) {}
    ~squence() {}
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
template <typename Iterator,typename... Args>
auto _sequence(Args&&... args) -> squence<Iterator,Args...> 
{
    return squence<Iterator,Args...>(std::forward<Args>(args)...);
}
////////////////////////////////////////////////////////////////////////////
template <typename... Args>
auto _sequence(Args&&... args) -> squence<typename std::remove_reference<typename at<0,Args...>::type>::type::iterator,Args...> 
{
    return squence<typename std::remove_reference<typename at<0,Args...>::type>::type::iterator,Args...>(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////
template <typename T1,typename T2>
auto  operator& (T1&& t1,T2&& t2) -> squence<typename std::remove_reference<T1>::type::iterator,T1,T2> 
{
    return squence<typename T1::iterator,T1,T2>(std::forward<T1>(t1),std::forward<T2>(t2));
}
///////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (T1&& t1,const char* str) 
    -> decltype(_sequence(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(str)))
{
    return _sequence(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(str));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (const char* str,T1&& t1) 
     -> decltype(_sequence(_literal<typename std::remove_reference<T1>::type::iterator>(str),std::forward<T1>(t1)))
{
    return _sequence(_literal<typename std::remove_reference<T1>::type::iterator>(str),std::forward<T1>(t1));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (T1&& t1,const std::string& str) 
     -> decltype(_sequence(std::forward<T1>(t1)),_literal<typename std::remove_reference<T1>::type::iterator>(str))
{
    return _sequence(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(str));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (const std::string& str,T1&& t1) 
     -> decltype(_sequence(_literal<typename std::remove_reference<T1>::type::iterator>(str),std::forward<T1>(t1)))
{
    return _sequence(_literal<typename std::remove_reference<T1>::type::iterator>(str),std::forward<T1>(t1));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (T1&& t1,char ch) 
     -> decltype(_sequence(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(ch))) 
{
    return _sequence(std::forward<T1>(t1),_literal<typename std::remove_reference<T1>::type::iterator>(ch));
}
// ////////////////////////////////////////////////////////////////////////////////
template <typename T1>
auto  operator& (char ch,T1&& t1) 
      -> decltype(_sequence(_literal<typename std::remove_reference<T1>::type::iterator>(ch),std::forward<T1>(t1))) 
{
    return _sequence<typename T1::iterator>(_literal<typename std::remove_reference<T1>::type::iterator>(ch),std::forward<T1>(t1));
}

#endif

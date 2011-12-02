// ======================================================================================
// File         : sequential.h
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 01:27:39 AM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __SEQUENTIAL_H__
#define __SEQUENTIAL_H__

#include <type_traits>
#include <tuple>
#include "data_holder.h"

// struct sequence_trait_shelper
// {
//     template <typename... Args>
//     static std::tuple<Args...> f(data_holder<Args>... )
//     {
//         return std::tuple<Args...>();
//     }
// };

// template <typename... Args>
// struct sequence_traits
// {
//     typedef decltype(sequence_trait_shelper::f(Args()...)) data_type;
// };

template <typename... Args>
class squence:public data_holder<std::tuple<typename std::remove_reference<Args>::type::data_type...> >
{
public:
    template <typename Tuple,typename Data_type,typename Iterator,std::size_t N>
    struct helper
    {
        static bool do_parse(std::tuple<Args...>& t,Data_type& data,Iterator& first,Iterator last)
        {
            if(!std::get<std::tuple_size<Tuple>::value-N>(t)(first,last))
                return false;
            std::get<std::tuple_size<Tuple>::value-N>(data) = std::get<std::tuple_size<Tuple>::value-N>(t).data();
            return helper<Tuple,Data_type,Iterator,N-1>::do_parse(t,data,first,last);
        }
    };

    template <typename Tuple,typename Data_type,typename Iterator>
    struct helper<Tuple,Data_type,Iterator,1>
    {
        static bool do_parse(std::tuple<Args...>& t,Data_type& data,Iterator& first,Iterator last)
        {
            if(!std::get<std::tuple_size<Tuple>::value-1>(t)(first,last))
                return false;
            std::get<std::tuple_size<Tuple>::value-1>(data) = std::get<std::tuple_size<Tuple>::value-1>(t).data();
            return true;
        }
    };

    typedef std::tuple<Args...> tuple_type;
    typedef std::tuple<typename  std::remove_reference<Args>::type::data_type...> data_type;
    typedef data_holder<data_type> data_holder_type;


public:
    squence(Args&&... args):tuple_(args...) {}
    ~squence() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last) 
    {
       if(!helper<tuple_type,data_type,Iterator,
               std::tuple_size<tuple_type>::value>::do_parse(tuple_,data_holder_type::data(),first,last))
           return false;
       data_holder_type::call_back();
       return true;
    }
    // /////////////////////////////////////////
    // template <typename CallBack>
    // squence& operator<= (const CallBack& cb)
    // {
    //     data_holder_type::call_back_function() = cb; 
    //     return *this;
    // }
    // template <typename CallBack>
    // squence& operator<= (CallBack&& cb)
    // {
    //     data_holder_type::call_back_function() = std::move(cb);
    //     return *this;
    // }
    // ////////////////////////////////////////////
private:
    tuple_type tuple_;
};

template <typename... Args>
auto _sequence(Args&&... args) -> squence<Args...> 
{
    return squence<Args...>(std::forward<Args>(args)...);
}


#endif

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
#include "../utility/data_holder.h"



template <typename... Args>
class squence:public data_holder<std::tuple<typename std::remove_reference<Args>::type::data_type...> >
{
public:
    template <typename Tuple,typename Data_type,typename Iterator,std::size_t N>
    struct helper
    {
        static bool do_parse(Tuple& t,Data_type& data,Iterator& first,Iterator last)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-N;
            if(!std::get<Idx>(t)(first,last))
                return false;
            std::get<Idx>(data) = std::get<Idx>(t).data();
            return helper<Tuple,Data_type,Iterator,N-1>::do_parse(t,data,first,last);
        }
    };

    template <typename Tuple,typename Data_type,typename Iterator>
    struct helper<Tuple,Data_type,Iterator,1>
    {
        static bool do_parse(Tuple& t,Data_type& data,Iterator& first,Iterator last)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-1;  
            if(!std::get<Idx>(t)(first,last))
                return false;
            std::get<Idx>(data) = std::get<Idx>(t).data();
            return true;
        }
    };



    typedef std::tuple<Args...> tuple_type;
    typedef std::tuple<typename  std::remove_reference<Args>::type::data_type...> data_type;
    typedef data_holder<data_type> data_holder_type;


public:
    squence(Args&&... args):tuple_(std::forward<Args>(args)...) {}
    ~squence() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last) 
    {
       if(!helper<tuple_type,data_type,Iterator,
               std::tuple_size<tuple_type>::value>::do_parse(tuple_,data_holder_type::data(),first,last))
           return false;
       return data_holder_type::call_back();
    }
private:
    tuple_type tuple_;
};

template <typename... Args>
auto _sequence(Args&&... args) -> squence<Args...> 
{
    return squence<Args...>(std::forward<Args>(args)...);
}


#endif

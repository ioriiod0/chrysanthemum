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
//#include "../utility/data_holder.h"
#include "../utility/basic_parser.h"



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

template <typename Iterator,typename... Args>
auto _sequence(Args&&... args) -> squence<Iterator,Args...> 
{
    return squence<Iterator,Args...>(std::forward<Args>(args)...);
}


#endif

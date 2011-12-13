// ======================================================================================
// File         : alternative_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:13 PM | Wednesday,December
// Description  : 
// ======================================================================================


#ifndef __ALTERNATIVE_P_H__
#define __ALTERNATIVE_P_H__



#include <tuple>
#include <type_traits>
#include <string>
#include "../utility/basic_parser.h"


template <typename Iterator,typename... Args>
class alternative_p
    :public basic_parser<Iterator,alternative_p<Iterator,Args...>>
{
    template <typename Tuple,typename It,std::size_t N>
    struct helper
    {
        inline static bool do_parse(Tuple& t,It& first,Iterator last)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-N; 
            Iterator it = first;
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
        inline static bool do_parse(Tuple& t,It& first,Iterator last)
        { 
            const static std::size_t Idx = std::tuple_size<Tuple>::value-1; 
            Iterator it = first;
            if(std::get<Idx>(t)(first,last))
            {
                //typedef typename std::tuple_element<Idx,Tuple>::type ttype;
                return true;
            }
            first = it;
            return false;
        }
    };

    typedef std::tuple<Args...> tuple_type;


public:
    alternative_p(Args&&... args):tuple_(std::forward<Args>(args)...) {}
    ~alternative_p() {}
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
auto _alternative(Args&&... args) -> alternative_p<Iterator,Args...> 
{
    return alternative_p<Iterator,Args...>(std::forward<Args>(args)...);
}

#endif

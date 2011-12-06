// ======================================================================================
// File         : alternative.h
// Author       : Gao Lei 
// Last Change  : 12/03/2011 | 00:13:30 AM | Saturday,December
// Description  : 
// ======================================================================================


#include <tuple>
#include <type_traits>
#include <string>
#include "mutiple.h"
#include "data_holder.h"



template <typename Parser>
struct alternative_data_type_traits
{
    typedef typename std::remove_reference<Parser>::type::data_type type;
};


template <typename... Args>
class alternative
    :public data_holder< mutiple<typename alternative_data_type_traits<Args>::type...> > // mutiple<typename alternative_data_type_traits<Args>::type...>
{
    template <typename Tuple,typename Data_type,typename Iterator,std::size_t N>
    struct helper
    {
        static bool do_parse(Tuple& t,Data_type& data,Iterator& first,Iterator last)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-N; 
            Iterator it = first;
            if(std::get<Idx>(t)(first,last))
            {
                //typedef typename std::tuple_element<Idx,Tuple>::type ttype;
                data.template set<Idx>(std::get<Idx>(t).data());
                return true;
            }
            first = it;
            return helper<Tuple,Data_type,Iterator,N-1>::do_parse(t,data,first,last);
        }
    };

    template <typename Tuple,typename Data_type,typename Iterator>
    struct helper<Tuple,Data_type,Iterator,1>
    {
        static bool do_parse(Tuple& t,Data_type& data,Iterator& first,Iterator last)
        { 
            const static std::size_t Idx = std::tuple_size<Tuple>::value-1; 
            Iterator it = first;
            if(std::get<Idx>(t)(first,last))
            {
                //typedef typename std::tuple_element<Idx,Tuple>::type ttype;
                data.template set<Idx>(std::get<Idx>(t).data());
                return true;
            }
            first = it;
            return false;
        }
    };

    typedef std::tuple<Args...> tuple_type;
    typedef mutiple<typename alternative_data_type_traits<Args>::type...> data_type;
    typedef data_holder<data_type> data_holder_type;


public:
    alternative(Args&&... args):tuple_(std::forward<Args>(args)...) {}
    ~alternative() {}
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

private:
    tuple_type tuple_;

};



template <typename... Args>
auto _alternative(Args&&... args) -> alternative<Args...> 
{
    return alternative<Args...>(std::forward<Args>(args)...);
}



// ======================================================================================
// File         : diference_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:09 PM | Wednesday,December
// Description  : 
// ======================================================================================


#ifndef __DIFFERENCE_P_H__
#define __DIFFERENCE_P_H__

#include <type_traits>
#include "../utility/data_holder.h"


template <typename Parser1,typename Parser2>
class difference_p:public data_holder<typename std::remove_reference<Parser1>::type::data_type>
{
public:
    typedef typename std::remove_reference<Parser1>::type::data_type data_type;
    typedef data_holder<data_type> data_holder_type; 
public:
    difference_p(Parser1&& p1,Parser2&& p2):
                parser1(std::forward<Parser1>(p1)),
                parser2(std::forward<Parser2>(p2)) {}
    ~difference_p() {}
public:
    template <typename Iterator>
    bool operator() (Iterator& first,Iterator last)
    {
        Iterator it=first;
        if(!parser2(first,last))
        {   
            first = it;
            if(parser1(first,last))
            {
                data_holder_type::data() = parser1.data();
                return data_holder_type::call_back();
            }
        }
        return false;
    }
private:
    Parser1 parser1;
    Parser2 parser2;
};

template <typename Parser1,typename Parser2>
auto _difference(Parser1&& p1,Parser2&& p2) -> difference_p<Parser1,Parser2>
{
    return difference_p<Parser1,Parser2>(std::forward<Parser1>(p1),std::forward<Parser2>(p2));
}

template <typename Parser1,typename Parser2>
auto operator- (Parser1&& p1,Parser2&& p2) -> difference_p<Parser1,Parser2>
{
    return difference_p<Parser1,Parser2>(std::forward<Parser1>(p1),std::forward<Parser2>(p2));
}


#endif


// ======================================================================================
// File         : diference_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:09 PM | Wednesday,December
// Description  : 
// ======================================================================================


#ifndef __DIFFERENCE_P_H__
#define __DIFFERENCE_P_H__

#include <type_traits>
#include "../utility/basic_parser.h"


template <typename Iterator,typename Parser1,typename Parser2>
class difference_p:public basic_parser<Iterator,difference_p<Iterator,Parser1,Parser2>>
{
public:
    difference_p(Parser1&& p1,Parser2&& p2):
                parser1(std::forward<Parser1>(p1)),
                parser2(std::forward<Parser2>(p2)) {}
    ~difference_p() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {
        Iterator it=first;
        if(!parser2(first,last))
        {   
            first = it;
            if(parser1(first,last))
            {
                return true;
            }
        }
        return false;
    }
private:
    Parser1 parser1;
    Parser2 parser2;
};

template <typename Iterator,typename Parser1,typename Parser2>
auto _difference(Parser1&& p1,Parser2&& p2) -> difference_p<Iterator,Parser1,Parser2>
{
    return difference_p<Iterator,Parser1,Parser2>(std::forward<Parser1>(p1),std::forward<Parser2>(p2));
}

template <typename Parser1,typename Parser2>
auto operator- (Parser1&& p1,Parser2&& p2) -> difference_p<typename Parser1::iterator,Parser1,Parser2>
{
    return difference_p<typename Parser1::iterator,Parser1,Parser2>(std::forward<Parser1>(p1),std::forward<Parser2>(p2));
}


#endif


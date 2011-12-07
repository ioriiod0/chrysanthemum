// ======================================================================================
// File         : list_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:17 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __LIST_P_H__
#define __LIST_P_H__

#include <vector>
#include "../utility/data_holder.h"

template <typename Parser1,typename Parser2>
class list:
    public data_holder< std::vector<typename std::remove_reference<Parser1>::type::data_type> >
{
public:
    typedef std::vector<typename std::remove_reference<Parser1>::type::data_type> data_type;
    typedef data_holder<data_type> data_holder_type;
public:
    list(Parser1&& p1,Parser2&& p2):
            parser1_(std::forward<Parser1>(p1)),
            parser2_(std::forward<Parser2>(p2)) {}
    ~list() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        /////////////////clear the data() befor parsing//////////////
        data_holder_type::data().clear();
        ///////////////////////////////////////////////////////
        if(!parser1_(first,last))
            return false;
        data_holder_type::data().push_back(parser1_.data());
        Iterator it;
        for(;;)
        {
            it = first;
            if(!parser2_(first,last) || !parser1_(first,last))
            {
                first = it;
                break;
            }
            data_holder_type::data().push_back(parser1_.data());
        }
        data_holder_type::call_back();
        return true;
    }

   private:
    Parser1 parser1_;
    Parser2 parser2_;

};


template <typename P1,typename P2>
auto _list(P1&& p1,P2&& p2) -> list<P1,P2>
{
    return list<P1,P2>(std::forward<P1>(p1),std::forward<P2>(p2));
}


#endif


// ======================================================================================
// File         : list.h
// Author       : Gao Lei 
// Last Change  : 12/03/2011 | 00:12:27 AM | Saturday,December
// Description  : 
// ======================================================================================

#include <vector>
#include "data_holder.h"

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
        parser1_.reset();
        if(!parser1_(first,last))
            return false;
        data_holder_type::data().push_back(parser1_.data());
        Iterator it;
        for(;;)
        {
            it = first;
            parser1_.reset(); //clear parser1_'s data before new parsing with it;
            parser2_.reset();
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
    void reset()
    {
        data_holder_type::data().clear();
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



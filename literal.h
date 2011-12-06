// ======================================================================================
// File         : literal.h
// Author       : Gao Lei 
// Last Change  : 12/02/2011 | 00:12:23 AM | Friday,December
// Description  : 
// ======================================================================================

#include <string>
#include "data_holder.h"


class literal:public data_holder<std::string>
{
    public:
        literal(const std::string& str) {data_ = str;}
        literal(std::string&& str) {data_ = std::move(str);}
        literal(const char* str) { data_ = str; }
        ~literal() {}

    public:
        template<typename Iterator>
        bool operator() (Iterator& first,Iterator last)
        {
            std::string::iterator it = data_.begin();
            while(first!=last && it!=data_.end())
            {
                if(*first++ != *it++)
                    return false;
            }
            if(it != data_.end())
                return false;
            call_back();
            return true;
        }
};

template <typename Arg>
auto _literal(Arg&& arg) -> literal
{
    return literal(std::forward<Arg>(arg));
}



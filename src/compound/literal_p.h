// ======================================================================================
// File         : literal_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:46 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __LITERAL_P_H__
#define __LITERAL_P_H__


#include <string>
#include "../utility/data_holder.h"


class literal_str_p:public data_holder<std::string>
{
    public:
        literal_str_p(const std::string& str) {data_ = str;}
        literal_str_p(std::string&& str) {data_ = std::move(str);}
        literal_str_p(const char* str) { data_ = str; }
        ~literal_str_p() {}

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
            return call_back();
        }
};


class literal_ch_p:public data_holder<char>
{
    public:
        literal_ch_p(char ch) {data_ = ch;}
        ~literal_ch_p() {}
    public:
        template<typename Iterator>
        bool operator() (Iterator& first,Iterator last)
        {
            if(first != last && *first++ == data_)
            {
                return call_back();
            }
            return false;
        }
};


template <typename Arg>
auto _literal(Arg&& arg) -> literal_str_p
{
    return literal_str_p(std::forward<Arg>(arg));
}

auto _literal(char ch) -> literal_ch_p
{
    return literal_ch_p(ch);
}


#endif

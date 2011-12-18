// ======================================================================================
// File         : literal_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:46 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __LITERAL_P_H__
#define __LITERAL_P_H__


#include <string>
#include <type_traits>
#include "../utility/basic_parser.h"

template <typename Iterator,typename Str_type>
class literal_str_p:public basic_parser<Iterator,literal_str_p<Iterator,Str_type>>
{
    public:
        template <typename T>
        literal_str_p(T&& t):data_(std::forward<T>(t)) {}
        ////////////////////////////////////////
        literal_str_p(const literal_str_p& rhs) = default;
        literal_str_p(literal_str_p&& rhs) = default;
        /////////////////////////////////////////
    public:
        bool do_parse(Iterator& first,Iterator last)
        {
            typename Str_type::iterator it = data_.begin();
            while(first!=last && it!=data_.end())
            {
                if(*first++ != *it++)
                    return false;
            }
            if(it != data_.end())
                return false;
            return true;
        }
    private:
        Str_type data_;
};

template <typename Iterator,typename CharT>
class literal_ch_p:public basic_parser<Iterator,literal_ch_p<Iterator,CharT>>
{
    public:
        literal_ch_p(char ch) {data_ = ch;}
    public:
        bool do_parse(Iterator& first,Iterator last)
        {
            if(first != last && *first++ == data_)
            {
                return true;
            }
            return false;
        }
    private:
        CharT data_;

};


template <typename Iterator,typename Arg>
auto _literal(Arg&& arg) -> literal_str_p<Iterator,std::string>
{
    return literal_str_p<Iterator,std::string>(std::forward<Arg>(arg));
}


template <typename Iterator>
auto _literal(char ch) -> literal_ch_p<Iterator,char>
{
    return literal_ch_p<Iterator,char>(ch);
}


#endif

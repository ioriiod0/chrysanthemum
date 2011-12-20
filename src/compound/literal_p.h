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


class literal_str_p
{
    public: 
        literal_str_p(const char* str):data_(str) {}
        literal_str_p(const std::string& str):data_(str) {}
        literal_str_p(std::string&& str):data_(std::move(str)) {}

        /////////////////////////////////////////
    public:
        template <typename Iterator>
        bool operator()(Iterator& first,Iterator last)
        {
            typename std::string::iterator it = data_.begin();
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
        std::string data_;
};

template <typename CharT>
class literal_ch_p
{
    public:
        literal_ch_p(CharT ch) {data_ = ch;}
    public:
        template <typename Iterator>
        bool operator()(Iterator& first,Iterator last)
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


inline auto _literal(const char* str) -> literal_str_p
{
    return literal_str_p(str);
}


inline auto _literal(const std::string& str) -> literal_str_p
{
    return literal_str_p(str);
}


inline auto _literal(std::string&& str) -> literal_str_p
{
    return literal_str_p(std::move(str));
}


inline auto _literal(char ch) -> literal_ch_p<char>
{
    return literal_ch_p<char>(ch);
}


#endif

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
#include "parser_base.h"

namespace chrysanthemum{

template <typename CharT>
class literal_str_p:public parser_base<literal_str_p<CharT>>
{
    public: 
        typedef CharT char_type;
        typedef std::basic_string<char_type> string_type;

        ////////////////////////////////////////////////////
        literal_str_p(const char_type* str):data_(str) {}
        literal_str_p(const string_type& str):data_(str) {}
        literal_str_p(string_type&& str):data_(std::move(str)) {}

        /////////////////////////////////////////
    public:
        template <typename Scanner>
        bool operator()(Scanner& scan)
        {
            auto it = data_.begin();
            while(!scan.at_end() && it!=data_.end())
            {
                if(scan.get_and_increase() != *it++)
                    return false;
            }
            if(it != data_.end())
                return false;
            return true;
        }
    private:
        string_type data_;
};

template <typename CharT>
class literal_ch_p:public parser_base<literal_ch_p<CharT>>
{
    public:
        typedef CharT char_type;
        //////////////////////////////
        literal_ch_p(CharT ch) {data_ = ch;}
    public:
        template <typename Scanner>
        bool operator()(Scanner& scan)
        {
            if(!scan.at_end() && scan.get_and_increase() == data_)
            {
                return true;
            }
            return false;
        }
    private:
        char_type data_;

};

template <typename CharT>
inline auto _literal(const CharT* str) 
    -> literal_str_p<CharT>
{
    return literal_str_p<CharT>(str);
}


template <typename CharT>
inline auto _literal(const std::basic_string<CharT>& str) 
    -> literal_str_p<CharT>
{
    return literal_str_p<CharT>(str);
}

template <typename CharT>
inline auto _literal(std::basic_string<CharT>&& str) 
    -> literal_str_p<CharT>
{
    return literal_str_p<CharT>(std::move(str));
}

template <typename CharT>
inline auto _literal(CharT ch) 
    -> literal_ch_p<char>
{
    return literal_ch_p<CharT>(ch);
}

} //end namespace

#endif

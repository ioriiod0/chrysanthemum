// ======================================================================================
// File         : basic_parsers.h
// Author       : Lei Gao 
// Last Change  : 12/22/2011 | 16:40:21 PM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __pS_H__
#define __pS_H__


#include <cctype>
#include <cwctype>
#include <iterator>

#include "../core/parser_base.h"

namespace chrysanthemum{


template <typename CharT>
struct character_type_traits;

template <>
struct character_type_traits<char>
{
   inline static bool isalpha(int ch)
   {
       return std::isalpha(ch);
   }
   inline static bool isalnum(int ch)
   {
       return std::isalnum(ch);
   }
   inline static bool islower(int ch)
   {
       return std::islower(ch);
   }   
   inline static bool isupper(int ch)
   {
       return std::isupper(ch);
   }   
   inline static bool isdigit(int ch)
   {
       return std::isdigit(ch);
   }   
   inline static bool isxdigit(int ch)
   {
       return std::isxdigit(ch);
   }   
   inline static bool isblank(int ch)
   {
       return (ch == 9) || (ch == 32);
   }   
   inline static bool iscntrl(int ch)
   {
       return std::iscntrl(ch);
   }   
   inline static bool isgraph(int ch)
   {
       return std::isgraph(ch);
   }   
   inline static bool isspace(int ch)
   {
       return std::isspace(ch);
   }
   inline static bool isprint(int ch)
   {
       return std::isprint(ch);
   }
   inline static bool ispunct(int ch)
   {
       return std::ispunct(ch);
   }   
  
};

template <>
struct character_type_traits<wchar_t>
{
   inline static bool isalpha(wint_t ch)
   {
       return std::iswalpha(ch);
   }
   inline static bool isalnum(wint_t ch)
   {
       return std::iswalnum(ch);
   }
   inline static bool islower(wint_t ch)
   {
       return std::iswlower(ch);
   }   
   inline static bool isupper(wint_t ch)
   {
       return std::iswupper(ch);
   }   
   inline static bool isdigit(wint_t ch)
   {
       return std::iswdigit(ch);
   }   
   inline static bool isxdigit(wint_t ch)
   {
       return std::iswxdigit(ch);
   }   
   inline static bool isblank(wint_t ch)
   {
       return (ch == 9) || (ch == 32);
   }   
   inline static bool iscntrl(wint_t ch)
   {
       return std::iswcntrl(ch);
   }   
   inline static bool isgraph(wint_t ch)
   {
       return std::iswgraph(ch);
   }   
   inline static bool isspace(wint_t ch)
   {
       return std::iswspace(ch);
   }
   inline static bool isprint(wint_t ch)
   {
       return std::iswprint(ch);
   }
   inline static bool ispunct(wint_t ch)
   {
       return std::iswpunct(ch);
   }   
  
};


struct alnum_p:public parser_base<alnum_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isalnum(*first++))
            return false;
        return true;
    }
};

struct alpha_p:public parser_base<alpha_p>
{
    
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isalpha(*first++))
            return false;
        return true;
    }  
};

struct upper_p:public parser_base<upper_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isupper(*first++))
            return false;
        return true;
    }
};


struct lower_p:public parser_base<lower_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::islower(*first++))
            return false;
        return true; 
    }
};


struct digit_p :public parser_base<digit_p>
{

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isdigit(*first++))
            return false;
        return true;
    }
 
};

struct xdigit_p:public parser_base<xdigit_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isxdigit(*first++)) 
            return false;
        return true;
    }
};

struct blank_p: public parser_base<blank_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isblank(*first++)) 
            return false;
        return true;
    }
};

struct cntrl_p:public parser_base<cntrl_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::iscntrl(*first++))
            return false;
        return true;
    }
    
};

struct graph_p:public parser_base<graph_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isgraph(*first++))
            return false;
        return true;
    }
    
};

struct space_p:public parser_base<space_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isspace(*first++))
            return false;
        return true;
    }
};

struct print_p:public parser_base<print_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::isprint(*first++))
            return false;
        return true;
    }
};


struct punct_p:public parser_base<punct_p>
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first == last || !character_type_traits<char_type>::ispunct(*first++))
            return false;
        return true;
    }
};

//////////////////////////////////////////////////
struct any_ch_p:public parser_base<any_ch_p>
{

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last)
            return false;
        if((int)*first <0 || (int)*first > 127)
            return false;
        ++first;
        return true;
    }
};


// struct oct_p
// {   
// public:
//     template <typename Iterator>
//     bool operator()(Iterator& first,Iterator last)
//     {
//         typedef typename std::iterator_traits<Iterator>::value_type char_type;
//         if(first == last)
//             return false;
//         ++first;
//         return true;
//     }
//  };


template <typename CharT,CharT Start,CharT End>
struct range_p:public parser_base<range_p<CharT,Start,End>>
{
public:
    static_assert(Start<End,"Start must less than End");

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        if(first==last)
            return false;
        if(*first<Start || *first>End)
            return false;
        ++first;
        return true;
    }

};


#define _alnum alnum_p
#define _alpha alpha_p
#define _lower lower_p
#define _upper upper_p
#define _digit digit_p
#define _xdigit xdigit_p
#define _blank blank_p
#define _cntrl cntrl_p
#define _space space_p
#define _graph graph_p
#define _print print_p
#define _punct punct_p
#define _any_ch any_ch_p
#define _range range_p


} //end namespace

#endif


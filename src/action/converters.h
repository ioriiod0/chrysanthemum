// ======================================================================================
// File         : action.h
// Author       : Lei Gao 
// Last Change  : 12/13/2011 | 13:32:14 PM | Tuesday,December
// Description  : 
// ======================================================================================
#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <cstdlib>
#include <string>
#include <tuple>
#include <type_traits>
#include "../utility/meta_fuctions.h"
#include <iterator>


namespace chrysanthemum{


template <typename CharT>
struct converter_character_type_traits;

template <>
struct converter_character_type_traits<char>
{
    inline static long strtol(const char* str,char** str_end,int base)
    {
        return strtol(str,str_end,base);
    }
    inline static long strtoul(const char* str,char** str_end,int base)
    {
        return strtoul(str,str_end,base);
    }        
    inline static long strtoll(const char* str,char** str_end,int base)
    {
        return strtoll(str,str_end,base);
    }
    inline static long strtoull(const char* str,char** str_end,int base)
    {
        return strtoull(str,str_end,base);
    }
    inline static long strtod(const char* str,char** str_end)
    {
        return strtod(str,str_end);
    }
    inline static long strtold(const char* str,char** str_end)
    {
        return strtold(str,str_end);
    }
    inline static long strtof(const char* str,char** str_end)
    {
        return strtof(str,str_end);
    }

};

template <>
struct converter_wchar_tacter_type_traits<wwchar_t_t>
{
    inline static long strtol(const wchar_t* str,wchar_t** str_end,int base)
    {
        return wcstol(str,str_end,base);
    }
    inline static long strtoul(const wchar_t* str,wchar_t** str_end,int base)
    {
        return wcstoul(str,str_end,base);
    }        
    inline static long strtoll(const wchar_t* str,wchar_t** str_end,int base)
    {
        return wcstoll(str,str_end,base);
    }
    inline static long strtoull(const wchar_t* str,wchar_t** str_end,int base)
    {
        return wcstoull(str,str_end,base);
    }
    inline static long strtod(const wchar_t* str,wchar_t** str_end)
    {
        return wcstod(str,str_end);
    }
    inline static long strtold(const wchar_t* str,wchar_t** str_end)
    {
        return wcstold(str,str_end);
    }
    inline static long strtof(const wchar_t* str,wchar_t** str_end)
    {
        return wcstof(str,str_end);
    }


};


#define STRICT_MODE_FUNC_IMPL(TYPE,FUNC,DEC) \
    template <typename Iterator> \
    bool operator()(Iterator first,Iterator last) \
    { \
        typedef typename std::iterator_traits<Iterator>::pointer pointer; \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        pointer p; \
        ctx() = converter_character_type_traits<value_type>::FUNC(&*first,&p,DEC); \
        return p == *&last; \
    } \
    template <typename Iterator> \
    inline static bool do_convert(Iterator first,Iterator last, TYPE& t) \
    { \
        typedef typename std::iterator_traits<Iterator>::pointer pointer; \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        pointer p; \
        t = converter_character_type_traits<value_type>::FUNC(&*first,&p,DEC); \
        return p == *&last; \
    } 

#define NOT_STRICT_MODE_FUNC_IMPL(TYPE,FUNC,DEC) \
    template <typename Iterator> \
    bool operator()(Iterator first,Iterator last) \
    { \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        ctx() = converter_character_type_traits<value_type>::FUNC(&*first,NULL,DEC); \
        return true; \
    } \
    template <typename Iterator> \
    inline static bool do_convert(Iterator first,Iterator last, TYPE& t) \
    { \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        t = converter_character_type_traits<value_type>::FUNC(&*first,NULL,DEC); \
        return true; \
    } 

#define STRICT_MODE_FUNC_IMPL2(TYPE,FUNC) \
    template <typename Iterator> \
    bool operator()(Iterator first,Iterator last) \
    { \
        typedef typename std::iterator_traits<Iterator>::pointer pointer; \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        pointer p; \
        ctx() = converter_character_type_traits<value_type>::FUNC(&*first,&p); \
        return p == *&last; \
    } \
    template <typename Iterator> \
    inline static bool do_convert(Iterator first,Iterator last, TYPE& t) \
    { \
        typedef typename std::iterator_traits<Iterator>::pointer pointer; \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        pointer p; \
        t = converter_character_type_traits<value_type>::FUNC(&*first,&p); \
        return p == *&last; \
    } 

#define NOT_STRICT_MODE_FUNC_IMPL2(TYPE,FUNC) \
    template <typename Iterator> \
    bool operator()(Iterator first,Iterator last) \
    { \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        ctx() = converter_character_type_traits<value_type>::FUNC(&*first,NULL); \
        return true; \
    } \
    template <typename Iterator> \
    inline static bool do_convert(Iterator first,Iterator last, TYPE& t) \
    { \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        t = converter_character_type_traits<value_type>::FUNC(&*first,NULL); \
        return true; \
    } 

struct strict_mode;
struct not_strict_mode;

template <typename T>
struct converter_base
{
    ctx_type& ctx()
    {
        return t_;
    }

    const ctx_type& ctx() const
    {
        return t_;
    }

    T t_;
};

template <typename T>
struct emplace_converter_base
{
    emplace_converter_base(T& t):t_(t) {}

    ctx_type& ctx()
    {
        return t_;
    }

    const ctx_type& ctx() const
    {
        return t_;
    }

    T& t_;
};
////////////base/////////////
template <typename T,std::size_t Dec = 10,typename Mode = strick_mode>
struct converter;

/////////////int/////////////
template <std::size_t Dec>
struct converter<int,Dec,strick_mode>:public converter_base<int>
{
    STRICT_MODE_FUNC_IMPL(int,strtol,Dec)
};

template <std::size_t Dec>
struct converter<int,Dec,not_strict_mode>:public converter_base<int>
{
    NOT_STRICT_MODE_FUNC_IMPL(int,strtol,Dec)
};

template <std::size_t Dec>
struct emplace_converter<int,Dec,strick_mode>:public emplace_converter_base<int>
{
    emplace_converter(int& t):emplace_converter_base<int>(t) {};
    STRICT_MODE_FUNC_IMPL(int,strtol,Dec)
};

template <std::size_t Dec>
struct emplace_converter<int,Dec,not_strict_mode>:public emplace_converter_base<int>
{
    emplace_converter(int& t):emplace_converter_base<int>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(int,strtol,Dec)
};
/////////////////////unsigned int/////////////
template <std::size_t Dec>
struct converter<unsigned int,Dec,strick_mode>:public converter_base<unsigned int>
{
    STRICT_MODE_FUNC_IMPL(unsigned int,strtoul,Dec)
};

template <std::size_t Dec>
struct converter<unsigned int,Dec,not_strict_mode>:public converter_base<unsigned int>
{
    NOT_STRICT_MODE_FUNC_IMPL(unsigned int,strtoul,Dec)
};

template <std::size_t Dec>
struct emplace_converter<unsigned int,Dec,strick_mode>:public emplace_converter_base<unsigned int>
{
    emplace_converter(unsigned int& t):emplace_converter_base<unsigned int>(t) {};
    STRICT_MODE_FUNC_IMPL(unsigned int,strtoul,Dec)
};

template <std::size_t Dec>
struct emplace_converter<unsigned int,Dec,not_strict_mode>:public emplace_converter_base<unsigned int>
{
    emplace_converter(unsigned int& t):emplace_converter_base<unsigned int>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(unsigned int,strtoul,Dec)
};
///////////////long/////////////////////////
template <std::size_t Dec>
struct converter<long,Dec,strick_mode>:public converter_base<long>
{
    STRICT_MODE_FUNC_IMPL(long,strtol,Dec)
};

template <std::size_t Dec>
struct converter<long,Dec,not_strict_mode>:public converter_base<long>
{
    NOT_STRICT_MODE_FUNC_IMPL(long,strtol,Dec)
};

template <std::size_t Dec>
struct emplace_converter<long,Dec,strick_mode>:public emplace_converter_base<long>
{
    emplace_converter(long& t):emplace_converter_base<long>(t) {};
    STRICT_MODE_FUNC_IMPL(long,strtol,Dec)
};

template <std::size_t Dec>
struct emplace_converter<long,Dec,not_strict_mode>:public emplace_converter_base<long>
{
    emplace_converter(long& t):emplace_converter_base<long>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(long,strtol,Dec)
};
///////////////////unsigned long/////////////////////
template <std::size_t Dec>
struct converter<unsigned long,Dec,strick_mode>:public converter_base<unsigned long>
{
    STRICT_MODE_FUNC_IMPL(unsigned long,strtoul,Dec)
};

template <std::size_t Dec>
struct converter<unsigned long,Dec,not_strict_mode>:public converter_base<unsigned long>
{
    NOT_STRICT_MODE_FUNC_IMPL(unsigned long,strtoul,Dec)
};

template <std::size_t Dec>
struct emplace_converter<unsigned long,Dec,strick_mode>:public emplace_converter_base<unsigned long>
{
    emplace_converter(unsigned long& t):emplace_converter_base<unsigned long>(t) {};
    STRICT_MODE_FUNC_IMPL(unsigned long,strtoul,Dec)
};

template <std::size_t Dec>
struct emplace_converter<unsigned long,Dec,not_strict_mode>:public emplace_converter_base<unsigned long>
{
    emplace_converter(unsigned long& t):emplace_converter_base<unsigned long>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(unsigned long,strtoul,Dec)
};
//////////////////////long long///////////////////////////////////
template <std::size_t Dec>
struct converter<long long,Dec,strick_mode>:public converter_base<long long>
{
    STRICT_MODE_FUNC_IMPL(long long,strtoll,Dec)
};

template <std::size_t Dec>
struct converter<long long,Dec,not_strict_mode>:public converter_base<long long>
{
    NOT_STRICT_MODE_FUNC_IMPL(long long,strtoll,Dec)
};

template <std::size_t Dec>
struct emplace_converter<long long,Dec,strick_mode>:public emplace_converter_base<long long>
{
    emplace_converter(long long& t):emplace_converter_base<long long>(t) {};
    STRICT_MODE_FUNC_IMPL(long long,strtoll,Dec)
};

template <std::size_t Dec>
struct emplace_converter<long long,Dec,not_strict_mode>:public emplace_converter_base<long long>
{
    emplace_converter(long long& t):emplace_converter_base<long long>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(long long ,strtoll,Dec)
};
///////////////////////////unsigned long long //////////////////////
template <std::size_t Dec>
struct converter<unsigned long long,Dec,strick_mode>:public converter_base<unsigned long long>
{
    STRICT_MODE_FUNC_IMPL(unsigned long long,strtoull,Dec)
};

template <std::size_t Dec>
struct converter<unsigned long long,Dec,not_strict_mode>:public converter_base<unsigned long long>
{
    NOT_STRICT_MODE_FUNC_IMPL(unsigned long long,strtoull,Dec)
};

template <std::size_t Dec>
struct emplace_converter<unsigned long long,Dec,strick_mode>:public emplace_converter_base<unsigned long long>
{
    emplace_converter(unsigned long long& t):emplace_converter_base<unsigned long long>(t) {};
    STRICT_MODE_FUNC_IMPL(unsigned long long,strtoull,Dec)
};

template <std::size_t Dec>
struct emplace_converter<unsigned long long,Dec,not_strict_mode>:public empalce_converter_base<unsigned long long>
{
    emplace_converter(unsigned long long& t):emplace_converter_base<unsigned long long>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(unsigned long long,strtoull,Dec)
};
///////////////////////////double //////////////////////
template <>
struct converter<double,Dec,strick_mode>:public converter_base<double>
{
    STRICT_MODE_FUNC_IMPL2(unsigned long long,strtod)
};

template <>
struct converter<double,Dec,not_strict_mode>:public converter_base<double>
{
    NOT_STRICT_MODE_FUNC_IMPL2(double,strtod)
};

template <std::size_t Dec>
struct emplace_converter<double,Dec,strick_mode>:public emplace_converter_base<double>
{
    emplace_converter(double& t):emplace_converter_base<double>(t) {};
    STRICT_MODE_FUNC_IMPL(double,strtol)
};

template <std::size_t Dec>
struct emplace_converter<double,Dec,not_strict_mode>:public emplace_converter_base<double>
{
    emplace_converter(double& t):emplace_converter_base<double>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(double,strtod)
};
///////////////////////////float //////////////////////
template <>
struct converter<float,Dec,strick_mode>:public converter_base<float>
{
    STRICT_MODE_FUNC_IMPL2(float,strtof)
};

template <>
struct converter<float,Dec,not_strict_mode>:public converter_base<float>
{
    NOT_STRICT_MODE_FUNC_IMPL2(float,strtof)
};
template <std::size_t Dec>
struct emplace_converter<float,Dec,strick_mode>:public emplace_converter_base<float>
{
    emplace_converter(float& t):emplace_converter_base<float>(t) {};
    STRICT_MODE_FUNC_IMPL(float,strtof)
};

template <std::size_t Dec>
struct emplace_converter<float,Dec,not_strict_mode>:public emplace_converter_base<float>
{
    emplace_converter(float& t):emplace_converter_base<float>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(float,strtof)
};
///////////////////////////long double //////////////////////
template <>
struct converter<long double,Dec,strick_mode>:public converter_base<long double>
{
    STRICT_MODE_FUNC_IMPL2(long double,strtold)
};

template <>
struct converter<long double,Dec,not_strict_mode>:public converter_base<long double>
{
    NOT_STRICT_MODE_FUNC_IMPL2(long double,strtold)
};
template <std::size_t Dec>
struct emplace_converter<long double,Dec,strick_mode>:public emplace_converter_base<long double>
{
    emplace_converter(long double& t):emplace_converter_base<long double>(t) {};
    STRICT_MODE_FUNC_IMPL(long double,strtold)
};

template <std::size_t Dec>
struct emplace_converter<long double,Dec,not_strict_mode>:public emplace_converter_base<long double>
{
    emplace_converter(long double& t):emplace_converter_base<long double>(t) {}
    NOT_STRICT_MODE_FUNC_IMPL(long double,strtold)
};


#define converter _converter

} //end namespace



#endif


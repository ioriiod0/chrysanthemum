// ======================================================================================
// File         : action.h
// Author       : Lei Gao , Qianhong Wang
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
    inline static long _strtol(const char* str,char** str_end,int base)
    {
        return std::strtol(str,str_end,base);
    }
    inline static long _strtoul(const char* str,char** str_end,int base)
    {
        return std::strtoul(str,str_end,base);
    }        
    inline static long _strtoll(const char* str,char** str_end,int base)
    {
        return std::strtoll(str,str_end,base);
    }
    inline static long _strtoull(const char* str,char** str_end,int base)
    {
        return std::strtoull(str,str_end,base);
    }
    inline static long _strtod(const char* str,char** str_end)
    {
        return std::strtod(str,str_end);
    }
    inline static long _strtold(const char* str,char** str_end)
    {
        return std::strtold(str,str_end);
    }
    inline static long _strtof(const char* str,char** str_end)
    {
        return std::strtof(str,str_end);
    }

};

template <>
struct converter_character_type_traits<wchar_t>
{
    inline static long _strtol(const wchar_t* str,wchar_t** str_end,int base)
    {
        return std::wcstol(str,str_end,base);
    }
    inline static long _strtoul(const wchar_t* str,wchar_t** str_end,int base)
    {
        return std::wcstoul(str,str_end,base);
    }        
    inline static long _strtoll(const wchar_t* str,wchar_t** str_end,int base)
    {
        return std::wcstoll(str,str_end,base);
    }
    inline static long _strtoull(const wchar_t* str,wchar_t** str_end,int base)
    {
        return std::wcstoull(str,str_end,base);
    }
    inline static long _strtod(const wchar_t* str,wchar_t** str_end)
    {
        return std::wcstod(str,str_end);
    }
    inline static long _strtold(const wchar_t* str,wchar_t** str_end)
    {
        return std::wcstold(str,str_end);
    }
    inline static long _strtof(const wchar_t* str,wchar_t** str_end)
    {
        return std::wcstof(str,str_end);
    }


};


#define STRICT_MODE_FUNC_IMPL(TYPE,FUNC,DEC) \
    template <typename Iterator> \
    bool operator()(Iterator first,Iterator last) \
    { \
        typedef typename std::iterator_traits<Iterator>::pointer pointer; \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        pointer p; \
        std::string str(first,last); \
        ctx() = converter_character_type_traits<value_type>::FUNC(&(*str.begin()),&p,DEC); \
        return p == &(*str.end()); \
    } \
    template <typename Iterator> \
    inline static bool do_convert(Iterator first,Iterator last, TYPE& t) \
    { \
        typedef typename std::iterator_traits<Iterator>::pointer pointer; \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        pointer p; \
        std::string str(first,last); \
        ctx() = converter_character_type_traits<value_type>::FUNC(&(*str.begin()),&p,DEC); \
        return p == &(*str.end()); \
    } 

 // #define NOT_STRICT_MODE_FUNC_IMPL(TYPE,FUNC,DEC) \
 //    template <typename Iterator> \
 //    bool operator()(Iterator first,Iterator last) \
 //    { \
 //        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
 //        ctx() = converter_character_type_traits<value_type>::FUNC(&*first,NULL,DEC); \
 //        return true; \
 //    } \
 //    template <typename Iterator> \
 //    inline static bool do_convert(Iterator first,Iterator last, TYPE& t) \
 //    { \
 //        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
 //        t = converter_character_type_traits<value_type>::FUNC(&*first,NULL,DEC); \
 //        return true; \
 //    } 

#define STRICT_MODE_FUNC_IMPL2(TYPE,FUNC) \
    template <typename Iterator> \
    bool operator()(Iterator first,Iterator last) \
    { \
        typedef typename std::iterator_traits<Iterator>::pointer pointer; \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        pointer p; \
        std::string str(first,last); \
        ctx() = converter_character_type_traits<value_type>::FUNC(&(*str.begin()),&p); \
        return p == &(*str.end()); \
    } \
    template <typename Iterator> \
    inline static bool do_convert(Iterator first,Iterator last, TYPE& t) \
    { \
        typedef typename std::iterator_traits<Iterator>::pointer pointer; \
        typedef typename std::iterator_traits<Iterator>::value_type value_type; \
        pointer p; \
        std::string str(first,last); \
        ctx() = converter_character_type_traits<value_type>::FUNC(&(*str.begin()),&p); \
        return p == &(*str.end()); \
    } 

// #define NOT_STRICT_MODE_FUNC_IMPL2(TYPE,FUNC) \
//     template <typename Iterator> \
//     bool operator()(Iterator first,Iterator last) \
//     { \
//         typedef typename std::iterator_traits<Iterator>::value_type value_type; \
//         ctx() = converter_character_type_traits<value_type>::FUNC(&*first,NULL); \
//         return true; \
//     } \
//     template <typename Iterator> \
//     inline static bool do_convert(Iterator first,Iterator last, TYPE& t) \
//     { \
//         typedef typename std::iterator_traits<Iterator>::value_type value_type; \
//         t = converter_character_type_traits<value_type>::FUNC(&*first,NULL); \
//         return true; \
//     } 

// struct strict_mode;
// struct not_strict_mode;

template <typename T>
struct converter_base
{
    typedef T ctx_type;

    T& ctx()
    {
        return t_;
    }

    const T& ctx() const
    {
        return t_;
    }

    T t_;
};

template <typename T>
struct emplace_converter_base
{
    typedef T ctx_type;

    emplace_converter_base(T& t):t_(t) {}

    T& ctx()
    {
        return t_;
    }

    const T& ctx() const
    {
        return t_;
    }

    T& t_;
};
////////////base/////////////
template <typename T,std::size_t Dec = 10> //,typename Mode = strict_mode>
struct converter;
template <typename T,std::size_t Dec = 10> //,typename Mode = strict_mode>
struct emplace_converter;
/////////////int/////////////
template <std::size_t Dec>
struct converter<int,Dec>:public converter_base<int>
{
    STRICT_MODE_FUNC_IMPL(int,_strtol,Dec)
};

// template <std::size_t Dec>
// struct converter<int,Dec,not_strict_mode>:public converter_base<int>
// {
//     NOT_STRICT_MODE_FUNC_IMPL(int,_strtol,Dec)
// };

template <std::size_t Dec>
struct emplace_converter<int,Dec>:public emplace_converter_base<int>
{
    emplace_converter(int& t):emplace_converter_base<int>(t) {};
    STRICT_MODE_FUNC_IMPL(int,_strtol,Dec)
};

// template <std::size_t Dec>
// struct emplace_converter<int,Dec,not_strict_mode>:public emplace_converter_base<int>
// {
//     emplace_converter(int& t):emplace_converter_base<int>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL(int,_strtol,Dec)
// };
/////////////////////unsigned int/////////////
template <std::size_t Dec>
struct converter<unsigned int,Dec>:public converter_base<unsigned int>
{
    STRICT_MODE_FUNC_IMPL(unsigned int,_strtoul,Dec)
};

// template <std::size_t Dec>
// struct converter<unsigned int,Dec,not_strict_mode>:public converter_base<unsigned int>
// {
//     NOT_STRICT_MODE_FUNC_IMPL(unsigned int,_strtoul,Dec)
// };

template <std::size_t Dec>
struct emplace_converter<unsigned int,Dec>:public emplace_converter_base<unsigned int>
{
    emplace_converter(unsigned int& t):emplace_converter_base<unsigned int>(t) {};
    STRICT_MODE_FUNC_IMPL(unsigned int,_strtoul,Dec)
};

// template <std::size_t Dec>
// struct emplace_converter<unsigned int,Dec,not_strict_mode>:public emplace_converter_base<unsigned int>
// {
//     emplace_converter(unsigned int& t):emplace_converter_base<unsigned int>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL(unsigned int,_strtoul,Dec)
// };
///////////////long/////////////////////////
template <std::size_t Dec>
struct converter<long,Dec>:public converter_base<long>
{
    STRICT_MODE_FUNC_IMPL(long,_strtol,Dec)
};

// template <std::size_t Dec>
// struct converter<long,Dec,not_strict_mode>:public converter_base<long>
// {
//     NOT_STRICT_MODE_FUNC_IMPL(long,_strtol,Dec)
// };

template <std::size_t Dec>
struct emplace_converter<long,Dec>:public emplace_converter_base<long>
{
    emplace_converter(long& t):emplace_converter_base<long>(t) {};
    STRICT_MODE_FUNC_IMPL(long,_strtol,Dec)
};

// template <std::size_t Dec>
// struct emplace_converter<long,Dec,not_strict_mode>:public emplace_converter_base<long>
// {
//     emplace_converter(long& t):emplace_converter_base<long>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL(long,_strtol,Dec)
// };
///////////////////unsigned long/////////////////////
template <std::size_t Dec>
struct converter<unsigned long,Dec>:public converter_base<unsigned long>
{
    STRICT_MODE_FUNC_IMPL(unsigned long,_strtoul,Dec)
};

// template <std::size_t Dec>
// struct converter<unsigned long,Dec,not_strict_mode>:public converter_base<unsigned long>
// {
//     NOT_STRICT_MODE_FUNC_IMPL(unsigned long,_strtoul,Dec)
// };

template <std::size_t Dec>
struct emplace_converter<unsigned long,Dec>:public emplace_converter_base<unsigned long>
{
    emplace_converter(unsigned long& t):emplace_converter_base<unsigned long>(t) {};
    STRICT_MODE_FUNC_IMPL(unsigned long,_strtoul,Dec)
};

// template <std::size_t Dec>
// struct emplace_converter<unsigned long,Dec,not_strict_mode>:public emplace_converter_base<unsigned long>
// {
//     emplace_converter(unsigned long& t):emplace_converter_base<unsigned long>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL(unsigned long,_strtoul,Dec)
// };
//////////////////////long long///////////////////////////////////
template <std::size_t Dec>
struct converter<long long,Dec>:public converter_base<long long>
{
    STRICT_MODE_FUNC_IMPL(long long,_strtoll,Dec)
};

// template <std::size_t Dec>
// struct converter<long long,Dec,not_strict_mode>:public converter_base<long long>
// {
//     NOT_STRICT_MODE_FUNC_IMPL(long long,_strtoll,Dec)
// };

template <std::size_t Dec>
struct emplace_converter<long long,Dec>:public emplace_converter_base<long long>
{
    emplace_converter(long long& t):emplace_converter_base<long long>(t) {};
    STRICT_MODE_FUNC_IMPL(long long,_strtoll,Dec)
};

// template <std::size_t Dec>
// struct emplace_converter<long long,Dec,not_strict_mode>:public emplace_converter_base<long long>
// {
//     emplace_converter(long long& t):emplace_converter_base<long long>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL(long long ,_strtoll,Dec)
// };
///////////////////////////unsigned long long //////////////////////
template <std::size_t Dec>
struct converter<unsigned long long,Dec>:public converter_base<unsigned long long>
{
    STRICT_MODE_FUNC_IMPL(unsigned long long,_strtoull,Dec)
};

// template <std::size_t Dec>
// struct converter<unsigned long long,Dec,not_strict_mode>:public converter_base<unsigned long long>
// {
//     NOT_STRICT_MODE_FUNC_IMPL(unsigned long long,_strtoull,Dec)
// };

template <std::size_t Dec>
struct emplace_converter<unsigned long long,Dec>:public emplace_converter_base<unsigned long long>
{
    emplace_converter(unsigned long long& t):emplace_converter_base<unsigned long long>(t) {}
    STRICT_MODE_FUNC_IMPL(unsigned long long,_strtoull,Dec)
};

// template <std::size_t Dec>
// struct emplace_converter<unsigned long long,Dec,not_strict_mode>:public emplace_converter_base<unsigned long long>
// {
//     emplace_converter(unsigned long long& t):emplace_converter_base<unsigned long long>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL(unsigned long long,_strtoull,Dec)
// };
///////////////////////////double //////////////////////
template <std::size_t Dec>
struct converter<double,Dec>:public converter_base<double>
{
    STRICT_MODE_FUNC_IMPL2(unsigned long long,_strtod)
};

// template <std::size_t Dec>
// struct converter<double,Dec,not_strict_mode>:public converter_base<double>
// {
//     NOT_STRICT_MODE_FUNC_IMPL2(double,_strtod)
// };

template <std::size_t Dec>
struct emplace_converter<double,Dec>:public emplace_converter_base<double>
{
    emplace_converter(double& t):emplace_converter_base<double>(t) {};
    STRICT_MODE_FUNC_IMPL2(double,_strtod)
};

// template <std::size_t Dec>
// struct emplace_converter<double,Dec,not_strict_mode>:public emplace_converter_base<double>
// {
//     emplace_converter(double& t):emplace_converter_base<double>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL2(double,_strtod)
// };
///////////////////////////float //////////////////////
template <std::size_t Dec>
struct converter<float,Dec>:public converter_base<float>
{
    STRICT_MODE_FUNC_IMPL2(float,_strtof)
};

// template <std::size_t Dec>
// struct converter<float,Dec,not_strict_mode>:public converter_base<float>
// {
//     NOT_STRICT_MODE_FUNC_IMPL2(float,_strtof)
// };
template <std::size_t Dec>
struct emplace_converter<float,Dec>:public emplace_converter_base<float>
{
    emplace_converter(float& t):emplace_converter_base<float>(t) {};
    STRICT_MODE_FUNC_IMPL2(float,_strtof)
};

// template <std::size_t Dec>
// struct emplace_converter<float,Dec,not_strict_mode>:public emplace_converter_base<float>
// {
//     emplace_converter(float& t):emplace_converter_base<float>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL2(float,_strtof)
// };
///////////////////////////long double //////////////////////
template <std::size_t Dec>
struct converter<long double,Dec>:public converter_base<long double>
{
    STRICT_MODE_FUNC_IMPL2(long double,_strtold)
};

// template <std::size_t Dec>
// struct converter<long double,Dec,not_strict_mode>:public converter_base<long double>
// {
//     NOT_STRICT_MODE_FUNC_IMPL2(long double,_strtold)
// };
template <std::size_t Dec>
struct emplace_converter<long double,Dec>:public emplace_converter_base<long double>
{
    emplace_converter(long double& t):emplace_converter_base<long double>(t) {};
    STRICT_MODE_FUNC_IMPL2(long double,_strtold)
};

// template <std::size_t Dec>
// struct emplace_converter<long double,Dec,not_strict_mode>:public emplace_converter_base<long double>
// {
//     emplace_converter(long double& t):emplace_converter_base<long double>(t) {}
//     NOT_STRICT_MODE_FUNC_IMPL2(long double,_strtold)
// };

struct to_string:public converter_base<std::string>
{
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        ctx().assign(first,last);
        return true;
    }
};

struct emplace_to_string:public emplace_converter_base<std::string>
{
    emplace_to_string(std::string& str):emplace_converter_base<std::string>(str) {}
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        ctx().assign(first,last);
        return true;
    }
};

#define _converter converter
#define _emplace_converter emplace_converter
#define _to_string to_string
#define _emplace_to_string emplace_to_string

} //end namespace



#endif


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
#include "basic_action.h"


#define DECLARE_CONVERT_FUNCTION_1_1(FUNC) \
    template <typename Iterator,typename T1> \
    inline static void do_convert(Iterator first,Iterator last,std::tuple<T1>& t) \
    { \
        std::string str(first,last); \
        std::get<0>(t) = FUNC(str.c_str()); \
    }
////////////////////////////////////////////////////////////
#define DECLARE_CONVERT_FUNCTION_1_2(FUNC,DEFAUT_VAL) \
    template <typename Iterator,typename T1> \
    inline static void do_convert(Iterator first,Iterator last,std::tuple<T1>& t) \
    { \
        std::string str(first,last); \
        std::get<0>(t) = FUNC(str.c_str(),DEFAUT_VAL); \
    }

#define DECLARE_CONVERT_FUNCTION_2_2(FUNC) \
    template <typename Iterator,typename T1,typename T2> \
    inline static void do_convert(Iterator first,Iterator last,std::tuple<T1,T2>& t) \
    { \
        std::string str(first,last); \
        std::get<0>(t) = FUNC(str.c_str(),std::get<1>(t)); \
    }
//////////////////////////////////////////////////////////////////
#define DECLARE_CONVERT_FUNCTION_2_3(FUNC,DEFAUT_VAL) \
    template <typename Iterator,typename T1,typename T2> \
    inline static void do_convert(Iterator first,Iterator last,std::tuple<T1,T2>& t) \
    { \
        std::string str(first,last); \
        std::get<0>(t) = FUNC(str.c_str(),DEFAUT_VAL,std::get<1>(t)); \
    }

#define DECLARE_CONVERT_FUNCTION_1_3(FUNC,DEFAUT_VAL1,DEFAUT_VAL2) \
    template <typename Iterator,typename T1> \
    inline static void do_convert(Iterator first,Iterator last,std::tuple<T1>& t) \
    { \
        std::string str(first,last); \
        std::get<0>(t) = FUNC(str.c_str(),DEFAUT_VAL1,DEFAUT_VAL2); \
    } 
#define DECLARE_CONVERT_FUNCTION_3_3(FUNC) \
    template <typename Iterator,typename T1,typename T2,typename T3> \
    inline static void do_convert(Iterator first,Iterator last,std::tuple<T1,T2,T3>& t) \
    { \
        std::string str(first,last); \
        std::get<0>(t) = FUNC(str.c_str(),std::get<2>(t),std::get<1>(t)); \
    }

template <typename T>
struct converter_traits;

template <>
struct converter_traits<int>
{
    /////////////////////////////////////
    DECLARE_CONVERT_FUNCTION_1_3(strtol,NULL,10)
    DECLARE_CONVERT_FUNCTION_2_3(strtol,NULL)
    DECLARE_CONVERT_FUNCTION_3_3(strtol)
};

template <>
struct converter_traits<long>
{     
    DECLARE_CONVERT_FUNCTION_1_3(strtol,NULL,10)
    DECLARE_CONVERT_FUNCTION_2_3(strtol,NULL)
    DECLARE_CONVERT_FUNCTION_3_3(strtol)
};

template <>
struct converter_traits<unsigned int>
{   
    DECLARE_CONVERT_FUNCTION_1_3(strtoul,NULL,10)
    DECLARE_CONVERT_FUNCTION_2_3(strtoul,NULL)
    DECLARE_CONVERT_FUNCTION_3_3(strtoul)
};

template <>
struct converter_traits<unsigned long>
{    
    DECLARE_CONVERT_FUNCTION_1_3(strtoul,NULL,10)
    DECLARE_CONVERT_FUNCTION_2_3(strtoul,NULL)
    DECLARE_CONVERT_FUNCTION_3_3(strtoul)
};

template <>
struct converter_traits<long long>
{    
    DECLARE_CONVERT_FUNCTION_1_3(strtoll,NULL,10)
    DECLARE_CONVERT_FUNCTION_2_3(strtoll,NULL)
    DECLARE_CONVERT_FUNCTION_3_3(strtoll)

};

template <>
struct converter_traits<unsigned long long>
{   
    DECLARE_CONVERT_FUNCTION_1_3(strtoull,NULL,10)
    DECLARE_CONVERT_FUNCTION_2_3(strtoull,NULL)
    DECLARE_CONVERT_FUNCTION_3_3(strtoull)
};

template <>
struct converter_traits<double>
{    
    DECLARE_CONVERT_FUNCTION_1_2(strtod,NULL)
    DECLARE_CONVERT_FUNCTION_2_2(strtod)
};

template <>
struct converter_traits<float>
{   
    DECLARE_CONVERT_FUNCTION_1_2(strtof,NULL)
    DECLARE_CONVERT_FUNCTION_2_2(strtof)
};

template <>
struct converter_traits<long double>
{    
    DECLARE_CONVERT_FUNCTION_1_2(strtold,NULL)
    DECLARE_CONVERT_FUNCTION_2_2(strtold)

};

template <>
struct converter_traits<std::string>
{    
    template <typename Iterator,typename T>
    inline static void do_convert(Iterator first,Iterator last,std::tuple<T>& t)
    {
        std::get<0>(t).assign(first,last);
    }
};

template <>
struct converter_traits<char>
{    
    template <typename Iterator,typename T>
    inline static void do_convert(Iterator first,Iterator last,std::tuple<T>& t)
    {
        std::get<0>(t) = *first;
    }
};



template <template <class> class Traits,typename... Args>
struct converter
{
    ////////////////////////
    typedef typename std::remove_reference<typename at<0,Args...>::type>::type data_type;
    ////////////////////////
    converter(Args&&... args):tuple_(std::forward<Args>(args)...) {}
    /////////////////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        Traits<data_type>::do_convert(first,last,tuple_);
        return true;
    }

    ///////////////////////
    data_type& data()
    {
        return std::get<0>(tuple_);
    }
    const data_type& data() const
    {
        return std::get<0>(tuple_);
    }
    std::tuple<Args...> tuple_;
};


template <typename... Args>
auto _converter(Args&&... args)
    -> converter<converter_traits,Args...>
{
    return converter<converter_traits,Args...>(std::forward<Args>(args)...);
}



// template <template <class> class Traits>
// struct converter<std::string,Traits>
// {
//     to_string(std::string& s):str_(s) {}
//     ////////////////////////
//     template <typename Iterator>
//     bool operator()(Iterator first,Iterator last)
//     {
//         str_.assign(first,last);
//         return true;
//     }
//     ///////////////////////
//     std::string& str_;
// };

// template <template <class> class Traits>
// struct converter<float,Traits>
// {
//     converter(float& i):data_(i) {}
//     /////////////////////////////////////
//     template <typename Iterator>
//     bool operator()(Iterator first,Iterator last)
//     {
//         data_ = Traits<float>::do_convert(first,last);
//         return true;
//     }
//     ////////////////////////
//     float& data_;
// };

// template <template <class> class Traits>
// struct converter<double,Traits>
// {
//     converter(double& i):data_(i) {}
//     /////////////////////////////////////
//     template <typename Iterator>
//     bool operator()(Iterator first,Iterator last)
//     {
//         data_ = Traits<float>::do_convert(first,last);
//         return true;
//     }
//     ////////////////////////
//     double& data_;
// };

// template <template <class> class Traits>
// struct converter<long double,Traits>
// {
//     converter(long double& i):data_(i) {}
//     /////////////////////////////////////
//     template <typename Iterator>
//     bool operator()(Iterator first,Iterator last)
//     {
//         data_ = Traits<long double>::do_convert(first,last);
//         return true;
//     }
//     ////////////////////////
//     long double& data_;
// };






#endif


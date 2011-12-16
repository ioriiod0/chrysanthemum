// ======================================================================================
// File         : action.h
// Author       : Lei Gao 
// Last Change  : 12/13/2011 | 13:32:14 PM | Tuesday,December
// Description  : 
// ======================================================================================
#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <string>
#include <tuple>

template <typename T>
struct converter_traits;

template <>
struct converter_traits<int>
{
    template <typename Iterator,typename Tuple>
    inline static int do_convert(Iterator first,Iterator last,const Tuple& t)
    {
        std::string str(first,last);
        return stoi(str,std::get<0>(t),std::get<1>(t));
    }
};

template <>
struct converter_traits<long>
{     
    template <typename Iterator,typename Tuple>
    inline static long do_convert(Iterator first,Iterator last,const Tuple& t)   
    {
        std::string str(first,last);
        return stol(str,std::get<0>(t),std::get<1>(t));
    }

};

template <>
struct converter_traits<unsigned int>
{   
    template <typename Iterator,typename Tuple>
    inline static unsigned int do_convert(Iterator first,Iterator last,const Tuple& t)    
    {
        std::string str(first,last);
        return stoul(str,std::get<0>(t),std::get<1>(t));
    }

};

template <>
struct converter_traits<unsigned long>
{    
    template <typename Iterator,typename Tuple>
    inline static unsigned long do_convert(Iterator first,Iterator last,const Tuple& t)    
    {
        std::string str(first,last);
        return stoul(str,std::get<0>(t),std::get<1>(t));
    }

};

template <>
struct converter_traits<long long>
{    
    template <typename Iterator,typename Tuple>
    inline static long long do_convert(Iterator first,Iterator last,const Tuple& t)    
    {
        std::string str(first,last);
        return stoll(str,std::get<0>(t),std::get<1>(t));
    }

};

template <>
struct converter_traits<unsigned long long>
{   
    template <typename Iterator,typename Tuple>
    inline static unsigned long long do_convert(Iterator first,Iterator last,const Tuple& t)    
    {
        std::string str(first,last);
        return stoull(str,std::get<0>(t),std::get<1>(t));
    }

};

template <>
struct converter_traits<double>
{    
    template <typename Iterator,typename Tuple>
    inline static double do_convert(Iterator first,Iterator last,const Tuple& t)    
    {
        std::string str(first,last);
        return stod(str);
    }

};

template <>
struct converter_traits<float>
{   
    template <typename Iterator,typename Tuple>
    inline static float do_convert(Iterator first,Iterator last,const Tuple& t)    
    {
        std::string str(first,last);
        return stof(str);
    }

};

template <>
struct converter_traits<long double>
{    
    template <typename Iterator,typename Tuple>
    inline static long double do_convert(Iterator first,Iterator last,const Tuple& t)
    {
        std::string str(first,last);
        return stold(str);
    }

};

template <>
struct converter_traits<std::string>
{    
    template <typename Iterator,typename Tuple>
    inline static std::string do_convert(Iterator first,Iterator last,const Tuple& t)
    {
        return std::string(first,last);
    }
};



template <typename Numeric,typename... Args,template <class> class Traits = converter_traits>
struct converter
{
    converter(Numeric& i,Args... args):data_(i),tuple_(args) {}
    /////////////////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        Traits<Numeric>::do_convert(first,last,NULL,base_);
        return true;
    }
    ////////////////////////
    
    std::tuple<Args...> tuple_;
};


template <template <class> class Traits>
struct converter<std::string,Traits>
{
    to_string(std::string& s):str_(s) {}
    ////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        str_.assign(first,last);
        return true;
    }
    ///////////////////////
    std::string& str_;
};

template <template <class> class Traits>
struct converter<float,Traits>
{
    converter(float& i):data_(i) {}
    /////////////////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        data_ = Traits<float>::do_convert(first,last);
        return true;
    }
    ////////////////////////
    float& data_;
};

template <template <class> class Traits>
struct converter<double,Traits>
{
    converter(double& i):data_(i) {}
    /////////////////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        data_ = Traits<float>::do_convert(first,last);
        return true;
    }
    ////////////////////////
    double& data_;
};

template <template <class> class Traits>
struct converter<long double,Traits>
{
    converter(long double& i):data_(i) {}
    /////////////////////////////////////
    template <typename Iterator>
    bool operator()(Iterator first,Iterator last)
    {
        data_ = Traits<long double>::do_convert(first,last);
        return true;
    }
    ////////////////////////
    long double& data_;
};






#endif


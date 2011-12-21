// ======================================================================================
// File         : ps.h
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 01:43:39 AM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __pS_H__
#define __pS_H__

#include <cctype>


struct alpha_p
{

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last || !std::isalpha(*first++))
            return false;
        return true;
    }  
};



struct digit_p 
{

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last || !std::isdigit(*first++))
            return false;
        return true;
    }
 

};

struct cntrl_p
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last || !std::iscntrl(*first++))
            return false;
        return true;
    }
    
};


struct space_p
{

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last || !std::isspace(*first++))
            return false;
        return true;
    }
 };


struct oct_p
{
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last)
            return false;
        ++first;
        return true;
    }
 };


struct char_p
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



struct upalpha_p
{

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {

        if(first == last || !std::isupper(*first++))
            return false;
        return true;
    }
};


struct loalpha_p
{

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {

        if(first == last || !std::islower(*first++))
            return false;
        return true; 
    }
};


struct hex_p
{

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last)
            return false;
        char ch = *first;
        if(std::isdigit(ch) || ( ch>='A' && ch<='F') || (ch >='a' && ch<='f') )
        {
            ++first;
            return true;
        }
        return false;
    }
};


template <typename CharT,CharT Start,CharT End>
struct range_p
{
public:
    static_assert(Start<End,"Start must less than End");

public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first==last)
            return false;
        if(*first<Start || *first>End)
            return false;
        ++first;
        return true;
    }

};
#define _alpha alpha_p
#define _digit digit_p
#define _space space_p
#define _cntrl cntrl_p
#define _oct oct_p
#define _char char_p
#define _loalpha loalpha_p
#define _upalpha upalpha_p
#define _range range_p

#endif


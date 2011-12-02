// ======================================================================================
// File         : parsers.h
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 01:43:39 AM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __PARSERS_H__
#define __PARSERS_H__

#include <cctype>
#include "data_holder.h"

class alpha_parser:public data_holder<char>
{
public:
    alpha_parser() {}
    ~alpha_parser() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first==last)
            return false;
        if(!std::isalpha(*first))
            return false;
        set_data_and_call_back(*first++);
        return true;
    }  
    // /////////////////////////////////////////
    // template <typename CallBack>
    // alpha_parser& operator<= (const CallBack& cb)
    // {
    //     call_back_function() = cb; 
    //     return *this;
    // }
    // template <typename CallBack>
    // alpha_parser& operator<= (CallBack&& cb)
    // {
    //     call_back_function() = std::move(cb);
    //     return *this;
    // }
    // ////////////////////////////////////////////

};

#define CHAR_TO_NUM(X) ((X)-'0')
class digit_parser:public data_holder<std::size_t>
{
public:
    digit_parser() {}
    ~digit_parser() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last)
            return false;
        if(!std::isdigit(*first))
            return false;
        set_data_and_call_back(CHAR_TO_NUM(*first++));
        return true;
    }
    // /////////////////////////////////////////
    // template <typename CallBack>
    // digit_parser& operator<= (const CallBack& cb)
    // {
    //     call_back_function() = cb; 
    //     return *this;
    // }
    // template <typename CallBack>
    // digit_parser& operator<= (CallBack&& cb)
    // {
    //     call_back_function() = std::move(cb);
    //     return *this;
    // }
    // ////////////////////////////////////////////

};


class cntrl_parser:public data_holder<char>
{
public:
    cntrl_parser() {}
    ~cntrl_parser() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last)
            return false;
        if(!std::iscntrl(*first))
            return false;
        set_data_and_call_back(*first++);
        return true;
    }
    // /////////////////////////////////////////
    // template <typename CallBack>
    // cntrl_parser& operator<= (const CallBack& cb)
    // {
    //     call_back_function() = cb; 
    //     return *this;
    // }
    // template <typename CallBack>
    // cntrl_parser& operator<= (CallBack&& cb)
    // {
    //     call_back_function() = std::move(cb);
    //     return *this;
    // }
    // ////////////////////////////////////////////

};

class space_parser:public data_holder<char>
{
public:
    space_parser() {}
    ~space_parser() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(first == last)
            return false;
        if(!std::isspace(*first))
            return false;
        set_data_and_call_back(*first++);
        return true;
    }
    // /////////////////////////////////////////
    // template <typename CallBack>
    // space_parser& operator<= (const CallBack& cb)
    // {
    //     call_back_function() = cb; 
    //     return *this;
    // }
    // template <typename CallBack>
    // space_parser& operator<= (CallBack&& cb)
    // {
    //     call_back_function() = std::move(cb);
    //     return *this;
    // }
    // ////////////////////////////////////////////

};

typedef alpha_parser _alpha;
typedef digit_parser _digit;
typedef space_parser _space;
typedef cntrl_parser _cntrl;


#endif


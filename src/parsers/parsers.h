// ======================================================================================
// File         : parsers.h
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 01:43:39 AM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __PARSERS_H__
#define __PARSERS_H__

#include <cctype>
#include "../utility/basic_parser.h"

template <typename Iterator>
class alpha_parser:public basic_parser<Iterator,alpha_parser<Iterator>>
{
public:
    alpha_parser() {}
    ~alpha_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last || !std::isalpha(*first++))
            return false;
        return true;
    }  
};


template <typename Iterator>
class digit_parser:public basic_parser<Iterator,digit_parser<Iterator>> 
{
public:
    digit_parser() {}
    ~digit_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last || !std::isdigit(*first++))
            return false;
        return true;
    }
 

};

template <typename Iterator>
class cntrl_parser:public basic_parser<Iterator,cntrl_parser<Iterator>>
{
public:
    cntrl_parser() {}
    ~cntrl_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last || !std::iscntrl(*first++))
            return false;
        return true;
    }
    
};

template <typename Iterator>
class space_parser:public basic_parser<Iterator,space_parser<Iterator>>
{
public:
    space_parser() {}
    ~space_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last || !std::isspace(*first++))
            return false;
        return true;
    }
 };

template <typename Iterator>
class oct_parser:public basic_parser<Iterator,oct_parser<Iterator>>
{
public:
    oct_parser() {}
    ~oct_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last)
            return false;
        ++first;
        return true;
    }
 };

template <typename Iterator>
class char_parser:public basic_parser<Iterator,char_parser<Iterator>>
{
public:
    char_parser() {}
    ~char_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last)
            return false;
        if((int)*first <0 || (int)*first > 127)
            return false;
        ++first;
        return true;
    }
};


template <typename Iterator>
class upalpha_parser:public basic_parser<Iterator,upalpha_parser<Iterator>>
{
public:
    upalpha_parser() {}
    ~upalpha_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {

        if(first == last || !std::isupper(*first++))
            return false;
        return true;
    }
};

template <typename Iterator>
class loalpha_parser:public basic_parser<Iterator,loalpha_parser<Iterator>>
{
public:
    loalpha_parser() {}
    ~loalpha_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
    {

        if(first == last || !std::islower(*first++))
            return false;
        return true; 
    }
};

template <typename Iterator>
class hex_parser:public basic_parser<Iterator,hex_parser<Iterator>>
{
public:
    hex_parser() {}
    ~hex_parser() {}
public:
    bool do_parse(Iterator& first,Iterator last)
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

#define _alpha alpha_parser
#define _digit digit_parser
#define _space space_parser
#define _cntrl cntrl_parser
#define _oct oct_parser
#define _char char_parser
#define _loalpha loalpha_parser
#define _upalpha upalpha_parser

#endif


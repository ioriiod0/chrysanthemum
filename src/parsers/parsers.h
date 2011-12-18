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
struct alpha_parser:public basic_parser<Iterator,alpha_parser<Iterator>>
{

public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last || !std::isalpha(*first++))
            return false;
        return true;
    }  
};


template <typename Iterator>
struct digit_parser:public basic_parser<Iterator,digit_parser<Iterator>> 
{

public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last || !std::isdigit(*first++))
            return false;
        return true;
    }
 

};

template <typename Iterator>
struct cntrl_parser:public basic_parser<Iterator,cntrl_parser<Iterator>>
{

public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last || !std::iscntrl(*first++))
            return false;
        return true;
    }
    
};

template <typename Iterator>
struct space_parser:public basic_parser<Iterator,space_parser<Iterator>>
{

public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first == last || !std::isspace(*first++))
            return false;
        return true;
    }
 };

template <typename Iterator>
struct oct_parser:public basic_parser<Iterator,oct_parser<Iterator>>
{
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
struct char_parser:public basic_parser<Iterator,char_parser<Iterator>>
{

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
struct upalpha_parser:public basic_parser<Iterator,upalpha_parser<Iterator>>
{

public:
    bool do_parse(Iterator& first,Iterator last)
    {

        if(first == last || !std::isupper(*first++))
            return false;
        return true;
    }
};

template <typename Iterator>
struct loalpha_parser:public basic_parser<Iterator,loalpha_parser<Iterator>>
{

public:
    bool do_parse(Iterator& first,Iterator last)
    {

        if(first == last || !std::islower(*first++))
            return false;
        return true; 
    }
};

template <typename Iterator>
struct hex_parser:public basic_parser<Iterator,hex_parser<Iterator>>
{

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


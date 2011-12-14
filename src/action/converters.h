// ======================================================================================
// File         : action.h
// Author       : Lei Gao 
// Last Change  : 12/13/2011 | 13:32:14 PM | Tuesday,December
// Description  : 
// ======================================================================================


#include <string>
#include "basic_action.h"




template <typename Iterator>
struct to_string:public basic_action<Iterator>
{
    to_string(std::string& s):str_(s) {}
    ////////////////////////
    bool operator()(Iterator first,Iterator last)
    {
        str.assign(first,last);
        return true;
    }
    ///////////////////////
    std::string& str_;
};


template <typename Iterator,typename Integer>
struct str_to_integer;


template <typename Iterator>
struct str_to_integer<Iterator,int>:public basic_action<Iterator>
{
    str_to_integer(int& _i):i(d) {}
    /////////////////////////////////////
    bool operator()(Iterator first,Iterator last)
    {
        std::string str(first,last);
        i_ = stoi(str);
        return true;
    }
    ////////////////////////
    int& i_;
};

template <typename Iterator>
struct str_to_integer<Iterator,long>:public basic_action<Iterator>
{
    str_to_integer(long& _i):i(d) {}
    /////////////////////////////////////
    bool operator()(Iterator first,Iterator last)
    {
        std::string str(first,last);
        i_ = stoi(str);
        return true;
    }
    ////////////////////////
    long& i_;
};

template <typename Iterator>
struct str_to_integer<Iterator,long>:public basic_action<Iterator>
{
    str_to_integer(long& _i):i(d) {}
    /////////////////////////////////////
    bool operator()(Iterator first,Iterator last)
    {
        std::string str(first,last);
        i_ = stol(str);
        return true;
    }
    ////////////////////////
    long& i_;
};



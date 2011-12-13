// ======================================================================================
// File         : action.h
// Author       : Lei Gao 
// Last Change  : 12/13/2011 | 13:32:14 PM | Tuesday,December
// Description  : 
// ======================================================================================


#include <functional>
#include <string>

/////////////////////////to_string////////////////////////////////

template <typename Iterator>
struct to_string
{
    to_string(std::string& s):str(s) {}
    ////////////////////////
    bool operator()(Iterator first,Iterator last)
    {
        str.assign(first,last);
        return true;
    }
    ///////////////////////
    std::string& str;
};






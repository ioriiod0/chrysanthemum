// ======================================================================================
// File         : range.h
// Author       : Lei Gao 
// Last Change  : 12/10/2011 | 14:35:54 PM | Saturday,December
// Description  : 
// ======================================================================================

#include "../utility/data_holder.h"

template <typename Iterator,typename CharT,CharT Start,CharT End>
struct range:public basic_parser<Iterator,range<Iterator,CharT,Start,End>>
{
public:
    static_assert(Start<End,"Start must less than End");

public:
    bool do_parse(Iterator& first,Iterator last)
    {
        if(first==last)
            return false;
        if(*first<Start || *first>End)
            return false;
        ++first;
        return true;
    }

};


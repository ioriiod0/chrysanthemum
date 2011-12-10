// ======================================================================================
// File         : range.h
// Author       : Lei Gao 
// Last Change  : 12/10/2011 | 14:35:54 PM | Saturday,December
// Description  : 
// ======================================================================================

#include "../utility/data_holder.h"

template <typename CharT,CharT Start,CharT End>
class range:public data_holder<CharT>
{
public:
    static_assert(Start<End,"Start must less than End");
public:
    range() {}
    ~range() {}
public:
    template <typename Iterator>
    bool operator() (Iterator& first,Iterator last)
    {
        if(first==last)
            return false;
        if(*first<Start || *first>End)
            return false;
        set_data_and_call_back(*first++);
    }

};


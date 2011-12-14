// ======================================================================================
// File         : data_holder.h
// Author       : Lei Gao 
// Last Change  : 12/14/2011 | 16:14:16 PM | Wednesday,December
// Description  : 
// ======================================================================================

#ifndef __DATA_HOLDER_H__
#define __DATA_HOLDER_H__

#include "basic_action.h"
#include "converter.h"

template <typename Iterator,typename T,typename Converter>
class data_holder:public basic_action<Iterator>
{
public:
    typedef T data_type;
public:
    data_holder() {}
    ~data_holder() {}
public:
    bool operator() (Iterator first,Iterator last)
    {
        Converter f(data_);
        return f(first,last);
    }
public:  
    ////////////////////////////////////
    data_type& data()
    {
        return data_;
    }
    const data_type& data() const
    {
        return data_;
    }   
protected:
    data_type data_;
};


#endif

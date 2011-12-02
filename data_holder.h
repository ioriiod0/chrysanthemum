// ======================================================================================
// File         : data_holder.h
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 01:36:25 AM | Thursday,December
// Description  : 
// ======================================================================================
#ifndef __DATA_HOLDER_H__
#define __DATA_HOLDER_H__
#include <tuple>
#include <functional>
#include <type_traits>

template <typename T>
class data_holder
{
public:
    typedef T data_type;
    typedef std::function<void(T&)> call_back_type;
public:
    data_holder() {}
    ~data_holder() {}
public:  
    ////////////////////////////////////
    void call_back()
    {
        if(call_back_)
            call_back_(data_);
    }
    /////////////////////////////////////////
    void set_data_and_call_back(const data_type& t)
    {
        data_ = t;
        call_back();
    }
    ////////////////////////////////////
    data_type& data()
    {
        return data_;
    }
    const data_type& data() const
    {
        return data_;
    }
    ///////////////////////////////////////////
    call_back_type& call_back_function()
    {
        return call_back_;
    }
    const call_back_type& call_function() const
    {
        return call_back_;
    }
   
protected:
    data_type data_;
    call_back_type call_back_;

};

 /////////////////////////////////////////
    template <typename Parser,typename CallBack>
    inline typename std::remove_reference<Parser>::type&& 
        operator<= (Parser&& p,CallBack&& cb)
    {
        p.call_back_function() = std::forward<CallBack>(cb); 
        return static_cast<typename std::remove_reference<Parser>::type&&>(p);
    }
   ////////////////////////////////////////////

#endif



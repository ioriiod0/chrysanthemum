// ======================================================================================
// File         : call_back_holder.h
// Author       : Gao Lei 
// Last Change  : 12/08/2011 | 21:11:36 PM | Thursday,December
// Description  : 
// ======================================================================================

#ifndef __CALL_BACK_HOLDER_H__
#define __CALL_BACK_HOLDER_H__
#include <functional>
#include "utility.h"

template <typename T>
class call_back_holder
{
public:
    typedef std::function<bool(T& t)> call_back_type;
public:
    call_back_holder() {}
    ~call_back_holder() {}
public:
    bool call_back(T& t)
    {
        if(cb_)
            return cb_(t);
        return true;
    }
    call_back_type& get_cb()
    {
        return cb_
    }
    const call_back_type& get_cb()
    {
        return cb_;
    }

protected:
    call_back_type cb_;
};

template <>
class call_back_holder<UNUSED>
{
public:
    template <typename T>
    bool do_call_back(const T& t)
    {
        return true;
    }
};




/////////////////////////////////////////
template <typename Parser,typename CallBack>
inline typename std::remove_reference<Parser>::type&& 
    operator<= (Parser&& p,CallBack&& cb)
{
    p.get_cb() = std::forward<CallBack>(cb); 
    return static_cast<typename std::remove_reference<Parser>::type&&>(p);
}
////////////////////////////////////////////


#endif


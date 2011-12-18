// ======================================================================================
// File         : basic_action.h
// Author       : Lei Gao 
// Last Change  : 12/14/2011 | 14:36:05 PM | Wednesday,December
// Description  : 
// ======================================================================================


#ifndef __BASIC_ACTION_H__
#define __BASIC_ACTION_H__


#include <functional>
#include <type_traits>
#include <string>
#include "../compound/literal_p.h" 


/////////////////////////////////////////
template <typename Parser,typename CallBack>
inline typename std::remove_reference<Parser>::type&& 
    operator<= (Parser&& p,CallBack&& cb)
{
    p[std::forward<CallBack>(cb)]; 
    return static_cast<typename std::remove_reference<Parser>::type&&>(p);
}


#endif


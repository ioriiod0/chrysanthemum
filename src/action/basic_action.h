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


template <typename Iterator>
class basic_action
{
public:
    typedef Iterator iterator;
public:
    basic_action() {}
    ~basic_action() {}
};


/////////////////////////////////////////
template <typename Parser,typename CallBack>
inline typename std::remove_reference<Parser>::type&& 
    operator<= (Parser&& p,CallBack&& cb)
{
    p[std::forward<CallBack>(cb)]; 
    return static_cast<typename std::remove_reference<Parser>::type&&>(p);
}
////////////////////////////////////////////
template <typename CallBack>
inline auto operator<= (const char* str,CallBack&& cb)
    ->decltype(_literal<typename std::remove_reference<CallBack>::type::iterator>(str))
{
    auto p = _literal<typename std::remove_reference<CallBack>::type::iterator>(str);
    p[std::forward<CallBack>(cb)]; 
    return p;
}
//////////////////////////////////////////////////////////////
template <typename CallBack>
inline auto operator<= (const std::string& str,CallBack&& cb) 
    -> decltype(_literal<typename std::remove_reference<CallBack>::type::iterator>(str))
{
    auto p = _literal<typename std::remove_reference<CallBack>::type::iterator>(str);
    p[std::forward<CallBack>(cb)]; 
    return p;
}
/////////////////////////to_string////////////////////////////////
template <typename CallBack>
inline auto operator<= (char ch,CallBack&& cb) 
    -> decltype(_literal<typename std::remove_reference<CallBack>::type::iterator>(ch))
{
    auto p = _literal<typename std::remove_reference<CallBack>::type::iterator>(ch);
    p[std::forward<CallBack>(cb)]; 
    return p;
}
#endif


// ======================================================================================
// File         : basic_parser.h
// Author       : Lei Gao 
// Last Change  : 12/12/2011 | 14:38:47 PM | Monday,December
// Description  : 
// ======================================================================================


#ifndef __BASIC_PARSER_H__
#define __BASIC_PARSER_H__


#include <functional>

template <typename Iterator,typename Derived>
class basic_parser
{
public:
    typedef std::function<bool(Iterator,Iterator)> call_back_type;
public:
    basic_parser() {}
    ~basic_parser() {}
    /////////////////////////////
    bool operator() (Iterator& first,Iterator last)
    {
        Iterator it = first;
        if(!static_cast<Derived*>(this)->do_parse(first,last))
            return false;
        if(cb_)
            return cb_(it,first);
        return true;
    }
    ///////////////////////////////////////
    call_back_type& get_cb()
    {
        return cb_;
    }
    const call_back_type& get_cb() const
    {
        return cb_;
    }
protected:
    call_back_type cb_;
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

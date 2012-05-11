// ======================================================================================
// File         : optional_p.h
// Author       : Lei Gao , Qianhong Wang
// Last Change  : 12/07/2011 | 15:44:33 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __OPTIONAL_P_H__
#define __OPTIONAL_P_H__

#include <string>
#include <type_traits>
#include "literal_p.h"


namespace chrysanthemum{


template <typename Parser>
class optional_p:public parser_base<optional_p<Parser>>
{

public:
    optional_p(Parser&& p):parser_(std::forward<Parser>(p)) {}
public:
    template <typename Scanner>
    bool operator()(Scanner& scan)
    {
        //////////////////////////////////////////
        Scanner save = scan;
        if(parser_(scan))
        {
            return true;
        }
        scan = save;
        return true;
    }
    
private:
    Parser parser_;
};



template <typename Arg>
inline auto _optional(Arg&& arg) -> optional_p<Arg> 
{
    return optional_p<Arg>(std::forward<Arg>(arg));
}

namespace ops{

template <typename T1>
inline auto  operator- (parser_base<T1>&& t1)
    -> optional_p<T1> 
{
    return _optional(std::move(t1.derived()));
}

template <typename T1>
inline auto  operator- (parser_base<T1>& t1) 
    -> optional_p<T1&> 
{
    return _optional(t1.derived());
}

}//end namespace ops

} //end namespace

#endif


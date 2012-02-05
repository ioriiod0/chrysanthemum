// ======================================================================================
// File         : optional_p.h
// Author       : Lei Gao 
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
class optional_p
{

public:
    optional_p(Parser&& p):parser_(std::forward<Parser>(p)) {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        //////////////////////////////////////////
        Iterator it = first;
        if(parser_(first,last))
        {
            return true;
        }
        first = it;
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


} //end namespace

#endif


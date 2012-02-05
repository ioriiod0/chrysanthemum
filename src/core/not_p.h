// ======================================================================================
// File         : not_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:44:36 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __NOT_P_H__
#define __NOT_P_H__
#include <type_traits>
#include <tuple>
#include "../utility/meta_fuctions.h"
#include "literal_p.h"
#include "parser_base.h"

namespace chrysanthemum{

template <typename Parser>
class not_p:public parser_base<not_p<Parser>>
{

    public:
        not_p(Parser&& p):parser_(std::forward<Parser>(p)) {}
    public:
        template <typename Iterator>
        bool operator()(Iterator& first,Iterator last)
        {
            if(!parser_(first,last))
                return true;
            return false;
        }
    private:
        Parser parser_;
};


template <typename Arg>
inline auto _not(Arg&& arg) -> not_p<Arg> 
{
    return not_p<Arg>(std::forward<Arg>(arg));
}

namespace ops{

template <typename T1>
inline auto  operator! (parser_base<T1>&& t1)
    -> not_p<T1> 
{
    return _not(std::move(t1.derived()));
}

template <typename T1>
inline auto  operator! (parser_base<T1>& t1) 
    -> not_p<T1&> 
{
    return _not(t1.derived());
}

}//end namespace ops

}//end namespace

#endif

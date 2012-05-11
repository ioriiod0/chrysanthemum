// ======================================================================================
// File         : repeat_p.h
// Author       : Lei Gao , Qianhong Wang
// Last Change  : 12/07/2011 | 15:45:37 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __REPEAT_P_H__
#define __REPEAT_P_H__

#include <type_traits>
#include <tuple>
#include "../utility/meta_fuctions.h"
#include "literal_p.h"
#include "parser_base.h"

namespace chrysanthemum{

const static std::size_t INFINITE = 0;

template <std::size_t N,typename Parser,std::size_t M>
class repeat_p:public parser_base<repeat_p<N,Parser,M> >
{
public:
    repeat_p(Parser&& t):parser_(std::forward<Parser>(t)) {}
public:
    template <typename Scanner>
    bool operator()(Scanner& scan)
    {
        ///////////////////////////////////////
        std::size_t counter=0;
        while(counter++ < N)
        {
            if(!parser_(scan))
                return false;
        }
        //counter == N
        Scanner save;
        while(counter++ <= M)
        {
            save = scan;
            if(!parser_(scan))
            {
                scan = save;
                break;
            }
        }
        return true;
    }

   private:
    Parser parser_;

};


template <std::size_t N,typename Parser>
class repeat_p<N,Parser,INFINITE>:public parser_base<repeat_p<N,Parser,INFINITE>>
{
public:
    repeat_p(Parser&& t):parser_(std::forward<Parser>(t)) {}
    ~repeat_p() {}
public:
    template <typename Scanner>
    bool operator()(Scanner& scan)
    {
        std::size_t counter=0;
        while(counter++ < N)
        {
            if(!parser_(scan))
                return false;
        }
        /////////////////////////////////////////////
        Scanner save;
        for(;;)
        {
            save = scan;
            if(!parser_(scan))
            {
                scan = save;
                break;
            }
        }
        return true; 
    }
private:
    Parser parser_;

};


template <std::size_t N,std::size_t M,typename Arg>
inline auto _repeat(Arg&& arg) -> repeat_p<N,Arg,M>
{
    return repeat_p<N,Arg,M>(std::forward<Arg>(arg));
}


template <std::size_t N,typename Arg>
inline auto _N(Arg&& arg) ->repeat_p<N,Arg,N> 
{
    return repeat_p<N,Arg,N>(std::forward<Arg>(arg));
}

namespace ops{

template <typename T1>
inline auto  operator* (parser_base<T1>&& t1)
    -> repeat_p<0,T1,INFINITE> 
{
    return _repeat<0,INFINITE>(std::move(t1.derived()));
}

template <typename T1>
inline auto  operator* (parser_base<T1>& t1)
    -> repeat_p<0,T1&,INFINITE> 
{
    return _repeat<0,INFINITE>(t1.derived());
}

template <typename T1>
inline auto  operator+ (parser_base<T1>&& t1) 
    -> repeat_p<1,T1,INFINITE> 
{
    return _repeat<1,INFINITE>(std::move(t1.derived()));
}

template <typename T1>
inline auto  operator+ (parser_base<T1>& t1) 
    -> repeat_p<1,T1&,INFINITE> 
{
    return _repeat<1,INFINITE>(t1.derived());
}


} //end namespace ops

}// end namespace

#endif

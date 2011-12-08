// ======================================================================================
// File         : repeat_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:45:37 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __REPEAT_P_H__
#define __REPEAT_P_H__


#include "../utility/data_holder.h"


const static std::size_t INFINITE = 0;

template <std::size_t N,typename Parser,std::size_t M>
class repeat:
    public data_holder< std::vector<typename std::remove_reference<Parser>::type::data_type> >
{
public:
    typedef std::vector<typename std::remove_reference<Parser>::type::data_type> data_type;
    typedef data_holder<data_type> data_holder_type;
public:
    repeat(Parser&& t):parser_(std::forward<Parser>(t)) {}
    ~repeat() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        //////////clear data() first/////////
        data_holder_type::data().clear();
        ///////////////////////////////////////
        std::size_t counter=0;
        while(counter++ < N)
        {
            if(!parser_(first,last))
                return false;
            data_holder_type::data().push_back(parser_.data());
        }
        //counter == N
        Iterator it;
        while(counter++ <= M)
        {
            it = first;
            if(!parser_(first,last))
            {
                first = it;
                break;
            }
            data_holder_type::data().push_back(parser_.data());
        }
        return data_holder_type::call_back();
    }

   private:
    Parser parser_;

};


template <std::size_t N,typename Parser>
class repeat<N,Parser,INFINITE>:
    public data_holder<std::vector<typename std::remove_reference<Parser>::type::data_type>>
{
public:
    typedef std::vector<typename std::remove_reference<Parser>::type::data_type> data_type;
    typedef data_holder<data_type> data_holder_type;
public:
    repeat(Parser&& t):parser_(t) {}
    ~repeat() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        std::size_t counter=0;
        while(counter++ < N)
        {
            if(!parser_(first,last))
                return false;
            data_holder_type::data().push_back(parser_.data());
        }
        /////////////////////////////////////////////
        Iterator it;
        for(;;)
        {
            it = first;
            if(!parser_(first,last))
            {
                first = it;
                break;
            }
            data_holder_type::data().push_back(parser_.data());
        }
        return data_holder_type::call_back();
    }
private:
    Parser parser_;

};


template <std::size_t N,std::size_t M,typename Arg>
auto _repeat(Arg&& arg) -> repeat<N,Arg,M>
{
    return repeat<N,Arg,M>(std::forward<Arg>(arg));
}


template <std::size_t N,typename Arg>
auto _N(Arg&& arg) ->repeat<N,Arg,N> 
{
    return repeat<N,Arg,N>(std::forward<Arg>(arg));
}

#endif

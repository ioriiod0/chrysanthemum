// ======================================================================================
// File         : repeat.h
// Author       : Gao Lei 
// Last Change  : 12/02/2011 | 03:17:55 AM | Friday,December
// Description  : 
// ======================================================================================

#include "data_holder.h"


const static std::size_t INFINITE = 0;

template <std::size_t N,typename Parser,std::size_t M>
class repeat:
    public data_holder< std::vector<typename std::remove_reference<Parser>::type::data_type> >
{
public:
    typedef std::vector<typename std::remove_reference<Parser>::type::data_type> data_type;
    typedef data_holder<data_type> data_holder_type;
public:
    repeat(Parser&& t):parser_(t) {}
    //repeat(const repeat& r):parser_(r.parser_) {}
    //repeat(repeat&& r):parser_(std::move(r.parser_)) {}
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
        data_holder_type::call_back();
        return true;
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
        data_holder_type::call_back();
        return true;
    }
   //  /////////////////////////////////////////
   //  template <typename CallBack>
   //  repeat& operator<= (const CallBack& cb)
   //  {
   //      data_holder_type::call_back_function() = cb; 
   //      return *this;
   //  }
   //  template <typename CallBack>
   //  repeat& operator<= (CallBack&& cb)
   //  {
   //      data_holder_type::call_back_function() = std::move(cb);
   //      return *this;
   //  }
   // ////////////////////////////////////////////
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




// template <typename Parser,std::size_t M>
// class repeat<0,Parser,M>
// {
// public:
//     typedef std::vector<typename Parser::data_type> data_type;
//     typedef data_holder<data_type> data_holder_type;
// public:
//     repeat(Parser&& t):parser_(t) {}
//     ~repeat() {}
// public:
//     template <typename Iterator>
//     bool operator()(Iterator& first,Iterator last)
//     {
//         std::size_t counter=0;
//         /////////////////////////////////////////////
//         Iterator it = first;
//         while(counter++ < M)
//         {
//             if(!parser_(first,last))
//             {
//                 first = it;
//                 break;
//             }
//             data_holder_type::data().push_back(parser_.data());
//         }
//         data_holder_type::call_back();
//         return true;
//     }
//     /////////////////////////////////////////
//     template <typename CallBack>
//     repeat& operator<= (const CallBack& cb)
//     {
//         call_back_function() = cb; 
//         return *this;
//     }
//     template <typename CallBack>
//     repeat& operator<= (CallBack&& cb)
//     {
//         call_back_function() = std::move(cb);
//         return *this;
//     }
//    ////////////////////////////////////////////
// private:
//     Parser parser_;

// };

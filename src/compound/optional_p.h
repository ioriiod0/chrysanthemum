// ======================================================================================
// File         : optional_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:44:33 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __OPTIONAL_P_H__
#define __OPTIONAL_P_H__


#include "../utility/data_holder.h"
#include "../utility/optional.h"


template <typename Parser>
class optional_p:public data_holder< optional<typename Parser::data_type> >
{
public:
    typedef optional<typename Parser::data_type> data_type;
    typedef data_holder<data_type> data_holder_type;
public:
    optional_p(Parser&& p):parser_(std::forward<Parser>(p)) {}
    ~optional_p() {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        ////////////clear data() before parsing//////
        data_holder_type::data().reset();
        //////////////////////////////////////////
        Iterator it = first;
        if(parser_(first,last))
        {
            data_holder_type::data().set(parser_.data());
            return data_holder_type::call_back();
        }
        first = it;
        return data_holder_type::call_back();
    }
    
private:
    Parser parser_;
};



template <typename Arg>
auto _optional(Arg&& arg) -> optional_p<Arg> 
{
    return optional_p<Arg>(std::forward<Arg>(arg));
}


#endif


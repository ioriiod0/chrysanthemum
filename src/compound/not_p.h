// ======================================================================================
// File         : not_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:44:36 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __NOT_P_H__
#define __NOT_P_H__
#include <type_traits>
#include <string>
#include "literal_p.h"
#include "../utility/basic_parser.h"


template <typename Parser>
class not_p:
    public basic_parser<typename std::remove_reference<Parser>::type::iterator,
                        not_p<Parser> >
{
    public:
        typedef typename std::remove_reference<Parser>::type::iterator Iterator;
    public:
        not_p(Parser&& p):parser_(std::forward<Parser>(p)) {}
    public:
        bool do_parse(Iterator& first,Iterator last)
        {
            if(!parser_(first,last))
                return true;
            return false;
        }
    private:
        Parser parser_;
};


template <typename Arg>
auto _not(Arg&& arg) -> not_p<Arg> 
{
    return not_p<Arg>(std::forward<Arg>(arg));
}



#endif

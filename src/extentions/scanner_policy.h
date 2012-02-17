// ======================================================================================
// File         : scanner_policy.h
// Author       : Lei Gao 
// Last Change  : 02/08/2012 | 16:30:34 PM | Wednesday,February
// Description  : 
// ======================================================================================

#ifndef __SCANNER_POLICY_H__
#define __SCANNER_POLICY_H__

#include "character_parsers.h"

namespace chrysanthemum{

    template <typename Iterator>
    struct default_scanner_policy
    {
        /////////////////////////////////////////////
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        //////////////////////////////////////////////
        const value_type& do_get(Iterator it) const
        {
            return *it;
        }
        value_type& do_get(Iterator it)
        {
            return *it;
        }
        void do_increase(Iterator& it)
        {
            ++it;
        }
        bool at_end(Iterator it,Iterator end)
        {
            return it == end;
        }

    };


    
    template <typename Iterator>
    struct line_counter_scanner_policy
    {

        /////////////////////////////////////////////
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        //////////////////////////////////////////////
        line_counter_scanner_policy():consumed(0),line_no(0),col_no(0){}
        //////////////////////////////////////////////
        const value_type& do_get(Iterator it) const
        {
            return *it;
        }
        value_type& do_get(Iterator it)
        {
            return *it;
        }
        void do_increase(Iterator& it)
        {
            ++consumed;
            if(character_type_traits<value_type>::isLF(*it))
            {
                ++line_no;
                col_no = 0;
            }
            else
                ++col_no;
            ++it;
        }
        bool at_end(Iterator it,Iterator end)
        {
            return it == end;
        }

        ///////////////////////
        std::size_t line_no;
        std::size_t col_no;
        std::size_t consumed;

    };



}// end namespace chrysanthemum


#endif


// ======================================================================================
// File         : scanner.h
// Author       : Lei Gao
// Last Change  : 02/08/2012 | 13:56:26 PM | Wednesday,February
// Description  : 
// ======================================================================================

#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <iterator>

namespace chrysanthemum{


    template <typename Iterator,template <class> class Policy>
    struct scanner:public Policy<Iterator>
    {
        ///////////////////////
        typedef Iterator iterator;
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        ///////////////////////
        scanner() {}
        scanner(Iterator first,Iterator last):Policy<Iterator>(),beg(first),cur(first),end(last) {}

        ///////////////////////
        const value_type& get() const
        {
            return Policy<Iterator>::do_get(cur); 
        }
        value_type& get()
        {
            return Policy<Iterator>::do_get(cur);
        } 
        void increase()
        {
            return Policy<Iterator>::do_increase(cur);
        }
        const value_type& get_and_increase() const
        {
            Iterator it = cur;
            Policy<Iterator>::do_increase(cur);
            return Policy<Iterator>::do_get(it);
        }

        value_type& get_and_increase()
        {
            Iterator it = cur;
            Policy<Iterator>::do_increase(cur);
            return Policy<Iterator>::do_get(it);
        }

        bool at_end()
        {
            return Policy<Iterator>::at_end(cur,end);
        }

        ////////////////////
        Iterator beg;
        Iterator end;
        Iterator cur;
        ////////////////////////// 

    };



}


#endif


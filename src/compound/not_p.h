// ======================================================================================
// File         : not_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:44:36 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __NOT_P_H__
#define __NOT_P_H__
#include <type_traits>
#include "../utility/data_holder.h"


template <typename Parser>
class not_p:public data_holder<typename std::remove_reference<Parser>::type::data_type >
{
    public:
        
    public:
    public:
    private:
};


#endif

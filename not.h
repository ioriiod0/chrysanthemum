// ======================================================================================
// File         : not.h
// Author       : Gao Lei 
// Last Change  : 12/03/2011 | 00:12:42 AM | Saturday,December
// Description  : 
// ======================================================================================

#include <type_traits>
#include "data_holder.h"


template <typename Parser>
class not:
    public data_holder<typename std::remove_reference<Parser>::type::data_type >
{
    public:
        
    public:
    public:
    private:
};

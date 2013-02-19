// ======================================================================================
// File         : parser_base.h
// Author       : Gao Lei
// Last Change  : 01/03/2012 | 23:07:35 PM | Tuesday,January
// Description  : 
// ======================================================================================

#ifndef __PARSER_BASE_H__
#define __PARSER_BASE_H__



template <typename Derived>
struct parser_base
{
    typedef Derived derived_type;
    struct basic_parser_tag {};

    derived_type& derived()
    {
        return *(static_cast<derived_type*>(this));
    }

    const derived_type& derived() const
    {
        return *(static_cast<const derived_type*>(this));
    }

};

#endif


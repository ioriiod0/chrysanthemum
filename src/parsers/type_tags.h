// ======================================================================================
// File         : type_tags.h
// Author       : Lei Gao 
// Last Change  : 12/22/2011 | 16:23:04 PM | Thursday,December
// Description  : 
// ======================================================================================

#ifndef __TYPE_TAGS_H__
#define __TYPE_TAGS_H__

struct basic_parser_tag {};
struct context_parser_tag {};



struct basic_parser_base
{
    typedef basic_parser_tag tag_type;
};


struct context_parser_base
{
    typedef context_parser_tag tag_type;
};



#endif

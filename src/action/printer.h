// ======================================================================================
// File         : printer.h
// Author       : Lei Gao 
// Last Change  : 12/20/2011 | 18:39:10 PM | Tuesday,December
// Description  : 
// ======================================================================================
#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <iostream>

namespace chrysanthemum{

template <typename OS>
struct line_printer
{
    line_printer(OS& os):os_(os) {}
    ///////////////////////////
    template <typename T>
    bool operator() (const T& t)
    {
        os_<<t<<"\r\n";
        return true;
    }
    /////////////////////////////
    OS& os_;
};

template <typename OS>
line_printer<OS> _line_printer(OS& os)
{
    return line_printer<OS>(os);
}


} //end namespace




#endif


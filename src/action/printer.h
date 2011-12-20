// ======================================================================================
// File         : printer.h
// Author       : Lei Gao 
// Last Change  : 12/20/2011 | 18:39:10 PM | Tuesday,December
// Description  : 
// ======================================================================================
#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <iostream>


struct line_printer
{
    line_printer(std::ostream& os):os_(os) {}
    ///////////////////////////
    template <typename T>
    bool operator() (const T& t)
    {
        os_<<t<<"\r\n";
        return true;
    }
    /////////////////////////////
    std::ostream& os_;
};


#define _line_printer line_printer


#endif


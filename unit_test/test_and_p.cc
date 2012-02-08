// ======================================================================================
// File         : test2.cc
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 05:17:53 AM | Thursday,December
// Description  : 
// ======================================================================================



#include "../src/core/and_p.h"
#include "../src/core/literal_p.h"
#include "../src/core/scanner.h"
#include "../src/core/compposer.h"
#include "../src/extentions/character_parsers.h"
#include "../src/extentions/scanner_policy.h"

#include <string>
#include <iostream>


using namespace chrysanthemum;
using namespace chrysanthemum::ops;


int main()
{


    _alpha a1; 
    _alpha a2;
    _digit d1;
    _digit d2;
    _space s1;
    _space s2;

    {
        
        //////////////////////////////////////////////////////////////
        typedef std::string::iterator IT;
        auto str_printer = [](IT first,IT last){std::string str(first,last);std::cout<<str<<std::endl;return true;};
        auto ch_printer = [](IT first,IT last){std::cout<<*first<<std::endl;return true;};
        auto p =   ( "你的编号是：" <= str_printer
                    & a1 <= ch_printer
                    & d1 <= ch_printer
                    & ' ' 
                    & a2 
                    & d2 
                    & ' ' 
                    & _alpha() <= ch_printer
                   ) <= str_printer;
        std::string str = "你的编号是：a3 b4 c";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(p(scan))
        {
            std::cout<<"ok"<<std::endl;
        }
        else
        {
            std::cout<<"err"<<std::endl;
        }
        /////////////////////////////////////////////////////////////////
    }
    {
        
        //////////////////////////////////////////////////////////////
        typedef std::string::iterator IT;
        auto str_printer = [](IT first,IT last){std::string str(first,last);std::cout<<str<<std::endl;return true;};
        auto ch_printer = [](IT first,IT last){std::cout<<*first<<std::endl;return true;};
        auto p =   ( "你的编号是：" <= str_printer
                    & a1 <= ch_printer
                    & d1 <= ch_printer
                    & ' ' 
                    & a2 
                    & d2 
                    & ' ' 
                    & _alpha() <= ch_printer
                   ) <= str_printer;
        std::string str = "你的编号是：a3 b4 c";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(p(scan))
        {
            std::cout<<"ok"<<std::endl;
            std::cout<<"line_no:"<<scan.get_line_no()<<std::endl;
            std::cout<<"col_no:"<<scan.get_col_no()<<std::endl;
        }
        else
        {
            std::cout<<"err"<<std::endl;
        }
        /////////////////////////////////////////////////////////////////
    }

    // {
    //     //////////////////////////////////////////////////////////////
    //     typedef std::wstring::iterator IT;
    //     auto str_printer = [](IT first,IT last){std::wstring str(first,last);std::wcout<<str<<std::endl;return true;};
    //     auto ch_printer = [](IT first,IT last){std::wcout<<*first<<std::endl;return true;};
    //     auto p =  (  L"你好啊" <= str_printer
    //                 & a1 <= ch_printer
    //                 & d1 <= ch_printer
    //                 & ' ' 
    //                 & a2 
    //                 & d2 
    //                 & ' ' 
    //                 & _alpha() <= ch_printer
    //               ) <= str_printer;
    //     std::wstring str = L"你好啊a3 b4 c";
    //     IT first = str.begin();
    //     if(p(first,str.end()))
    //     {
    //         std::cout<<"ok"<<std::endl;
    //     }
    //     else
    //     {
    //         std::cout<<"err"<<std::endl;
    //     }
    //     /////////////////////////////////////////////////////////////////
    // }

}


// ====================================================================================
// Copyright (c) 2013, ioriiod0@gmail.com All rights reserved.
// File         : ip_parser.cc
// Author       : ioriiod0@gmail.com
// Last Change  : 02/19/2013 06:33 PM
// Description  : 
// ====================================================================================


#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>


#include "../chrysanthemum/all.h"

using namespace chrysanthemum;
using namespace chrysanthemum::ops;


int main()
{

    
    typedef std::string::iterator IT; //定义迭代器
    typedef scanner<IT,line_counter_scanner_policy> scanner_t; //定义扫描器
    rule<scanner_t,std::vector<std::size_t>,no_skip> ip_parser; //声明规则
    //定义规则
    ip_parser %= (_repeat<1,3>(_digit()) 
                    <= [&ip_parser](IT first,IT last){
                        std::size_t num = converter<std::size_t>::do_convert(first,last); //转换
                        if(num < 0 || num > 255) return false; //判断正确性
                        ip_parser.cur_ctx().push_back(num); //填充context
                        return true;
                    }) % '.';

    std::string str;
    std::cout<<"please input ip address"<<std::endl;
    std::cin>>str;
    scanner_t scan(str.begin(),str.end());
    if(ip_parser(scan) && scan.at_end()) {
        std::for_each(ip_parser.cur_ctx().begin(),ip_parser.cur_ctx().end(),[](std::size_t i){
                      std::cout<<i<<" ";
        });
        std::cout<<"OK"<<std::endl;
    } else {

        std::cout<<"ERROR at:"<<scan.line_no<<" "<<scan.col_no<<std::endl;
    }

    

}



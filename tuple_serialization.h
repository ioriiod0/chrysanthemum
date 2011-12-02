// ======================================================================================
// File         : tuple_serialization.h
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 05:51:09 AM | Thursday,December
// Description  : 
// ======================================================================================


#include <iostream>
#include <ostream>
#include <tuple>

const static char SEP = ',';
const static char BEG = '(';
const static char END = ')';

                       
template <typename CharT,typename Traits,typename Tuple,std::size_t N>                                 
struct tuple_outputer                                                    
{                                                                       
    static void output(std::basic_ostream<CharT,Traits>& os,const Tuple& t)
    {                                                                   
        os<<std::get<std::tuple_size<Tuple>::value - N>(t)<<SEP;       
        tuple_outputer<CharT,Traits,Tuple,N-1>::output(os,t);                   
    }                                                                   
};                                                                      
                                                                        
template <typename CharT,typename Traits,typename Tuple>                                
struct tuple_outputer<CharT,Traits,Tuple,1>                                     
{                                                                       
    static void output(std::basic_ostream<CharT,Traits>& os,const Tuple& t)     
    {                                                                   
        os<<std::get<std::tuple_size<Tuple>::value-1>(t);               
    }                                                                   
};                                                                      

template <typename CharT,typename Traits,typename Tuple>                               
std::basic_ostream<CharT,Traits>& operator<<(std::basic_ostream<CharT,Traits>& os,const Tuple& t)           
{                                                                                               
    os<<BEG;                                                                                     
    tuple_outputer<CharT,Traits,Tuple,std::tuple_size<Tuple>::value>::output(os,t);  
    os<<END;                                                                                                   
    return os;                                                                                                  
}



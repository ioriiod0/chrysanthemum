// ======================================================================================
// File         : composer_p.h
// Author       : Lei Gao 
// Last Change  : 12/20/2011 | 14:29:15 PM | Tuesday,December
// Description  : 
// ======================================================================================


#include <type_traits>
#include <string>
#include "literal_p.h" 



template <typename Parser,typename Converter>
class composer_p_c
{
public:
    typedef typename Converter::ctx_type ctx_type;

    composer_p_c(Parser&& p,Converter&& c):
                    p_(std::forward<Parser>(p)),
                    c_(std::forward<Converter>(c)) {}
public:
    template <typename Iterator>
    bool operator() (Iterator& first,Iterator last)
    {
        Iterator it = first;
        if(p_(first,last))
            return c_(it,first);
        return false;
    }
    
    ctx_type& ctx()
    {
        return c_.ctx();
    }

    const ctx_type& ctx() const
    {
        return c_.ctx();
    }
private:
    Parser p_;
    Converter c_;
};



template <typename Parser,typename Converter>
inline auto _composer_p_c (Parser&& p,Converter&& c)
    -> composer_p_c<Parser,Converter>
{
    return composer_p_c<Parser,Converter>(std::forward<Parser>(p),std::forward<Converter>(c));
}

template <typename Parser,typename Converter>
inline auto operator<< (Parser&& p,Converter&& c)
    -> composer_p_c<Parser,Converter>
{
    return composer_p_c<Parser,Converter>(std::forward<Parser>(p),std::forward<Converter>(c));
}

template <typename Converter>
inline auto operator<< (const char* str,Converter&& c)
    //-> decltype(_composer_p_c(_literal(str),std::forward<Converter>(c)))
    -> composer_p_c<literal_str_p,Converter>
{
    return _composer_p_c(_literal(str),std::forward<Converter>(c));
}

template <typename Converter>
inline auto operator<< (const std::string& str,Converter&& c)
    -> decltype(_composer_p_c(_literal(str),std::forward<Converter>(c)))
{
    return _composer_p_c(_literal(str),std::forward<Converter>(c));
}

template <typename Converter>
inline auto operator<< (std::string&& str,Converter&& c)
    -> decltype(_composer_p_c(_literal(std::move(str)),std::forward<Converter>(c)))
{
    return _composer_p_c(_literal(std::move(str)),std::forward<Converter>(c));
}

template <typename Converter>
inline auto operator<< (char ch,Converter&& c)
    -> decltype(_composer_p_c(_literal(ch),std::forward<Converter>(c)))
{
    return _composer_p_c(_literal(ch),std::forward<Converter>(c));
}



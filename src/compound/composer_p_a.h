// ======================================================================================
// File         : composer_p_a.h
// Author       : Lei Gao 
// Last Change  : 12/20/2011 | 15:07:11 PM | Tuesday,December
// Description  : 
// ======================================================================================



#include <type_traits>
#include <string>
#include "literal_p.h" 



template <typename Parser,typename Action>
class composer_p_a
{
public:
    composer_p_a(Parser&& p,Action&& a):
                    p_(std::forward<Parser>(p)),
                    a_(std::forward<Action>(a)) {}
public:
    template <typename Iterator>
    bool operator() (Iterator& first,Iterator last)
    {
        Iterator it = first;
        if(p_(first,last))
            return a_(p_.ctx());
        return false;
    }
private:
    Parser p_;
    Action a_;
};


template <typename Parser,typename Action>
inline auto _composer_p_a (Parser&& p,Action&& c)
    -> composer_p_a<Parser,Action>
{
    return composer_p_a<Parser,Action>(std::forward<Parser>(p),std::forward<Action>(c));
}

template <typename Parser,typename Action>
inline auto operator<= (Parser&& p,Action&& c)
    -> composer_p_a<Parser,Action>
{
    return composer_p_a<Parser,Action>(std::forward<Parser>(p),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (const char* str,Action&& c)
    -> decltype(_composer_p_a(_literal(str),std::forward<Action>(c)))
{
    return _composer_p_a(_literal(str),std::forward<Action>(c));
}


template <typename Action>
inline auto operator<= (const std::string& str,Action&& c)
    -> decltype(_composer_p_a(_literal(str),std::forward<Action>(c)))
{
    return _composer_p_a(_literal(str),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (char ch,Action&& c)
    -> decltype(_composer_p_a(_literal(ch),std::forward<Action>(c)))
{
    return _composer_p_a(_literal(ch),std::forward<Action>(c));
}


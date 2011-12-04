// ======================================================================================
// File         : variant.h
// Author       : Gao Lei 
// Last Change  : 12/04/2011 | 20:48:39 PM | Sunday,December
// Description  : 
// ======================================================================================


#include <cstring>
#include <type_traits>
#include <stdexcept>

#include "meta_fuctions.h"
struct UNUSED;

template<std::size_t Idx,typename T>
struct choice
{
    const static std::size_t value = Idx;
    typedef T type;
    /////////////////////////
    choice(T&& t):under_lying_(std::forward<T>(t)) {}
    ~choice() {}
    ////////////////////////
    T under_lying_;
};

template <std::size_t Idx,typename T>
choice<Idx,T> _choice(T&& t)
{
    return choice<Idx,T>(std::forward<T>(t));
}

///////////////////////////////////////////////////////////////////////////////////////////////
   
template <typename... Choices>
class mutiple
{
public:
    const static std::size_t buffer_size = max_size_of<Choices...>::value;
    /////////////////////////////helper..////////////////////////////////////////////
    template <std::size_t Idx,typename... Args>
    struct choices_selector;
    template <std::size_t Idx,typename Head,typename... Tails>
    struct choices_selector<Idx,Head,Tails...>
    {
        typedef typename enable_if_else<Idx == Head::value,
                                        typename Head::type,
                                        typename choices_selector<Idx,Tails...>::type >::type type;
    };
    template <std::size_t Idx,typename T>
    struct choices_selector<Idx,T>
    {
        //static_assert(Idx == T::value,"the given Index is invalid!");
        typedef typename enable_if_else<Idx == T::value,
                                        typename T::type,
                                        UNUSED >::type type;
    };

public:
    mutiple():which_(0) {}
    ~mutiple() {}
    //////////////copy-assignment//////
    mutiple& operator=(const mutiple& t)
    {
        if(this!=&t)
        {
            which_ = t.which_;
            memcpy(buffer_,t.buffer_,buffer_size);
        }
        return *this;
    }
    ////////////////copy-constructor//////////////////////
    mutiple(const mutiple& t)
    {
        *this = t; 
    }
    //////////////////////////////////////////////
    
public:
    std::size_t which()
    {
        return which_;
    }
    //////////////////////////////////
    template <std::size_t Idx,typename T>
    void set(T&& t)
    {
        typedef typename choices_selector<Idx,Choices...>::type choice_type;
        which_ = Idx;
        //*static_cast<choice_type*>((void*)buffer_) = std::forward<T>(t);
        new(buffer_) choice_type(std::forward<T>(t));
    }
    ////////////////////////////////////
    template <std::size_t Idx>
    typename choices_selector<Idx,Choices...>::type get()
    {
        typedef typename choices_selector<Idx,Choices...>::type choice_type;
        if(which_!=Idx)
            throw std::invalid_argument("the given idx is different from the value which()!");
        choice_type* p = (choice_type*)buffer_;
        /////////need to call descontructor here!!////
        ///********there may be some bugs!*******///
        choice_type tmp(std::move(*p));
        p->~choice_type();
        return tmp;
    }

    // template <std::size_t Idx>
    // const typename choices_selector<Idx,Choices...>::type& get() const
    // {
    //     typedef typename choices_selector<Idx,Choices...>::type choice_type;
    //     if(which_!=Idx)
    //         throw std::invalid_argument("the given idx is different from the value which()!");
    //     choice_type*p = new(buffer_) choice_type(std::forward<T>(t));
    //     return *p;
    // }
    ///////////////////////////////////

private:
    char buffer_[buffer_size];
    std::size_t which_;
};


// template <std::size_t Idx,typename Mutiple,typename T>
// void set(Mutiple&& m,T&& t)
// {
//     m.set<Idx>(std::forward<T>(t));
// }

// template <std::size_t Idx,typename Mutiple,typename T>
// auto get(Mutiple&& m) -> decltype(m.get<Idx>())
// {
//     return m.get<Idx>();
// }

// template <std::size_t Idx,typename Mutiple,typename T>
// auto get(Mutiple& m) -> decltype(m.get<Idx>())
// {
//     return m.get<Idx>();
// }

// template <std::size_t Idx,typename Mutiple,typename T>
// auto get(Mutiple&& m) -> decltype(m.get<Idx>())&
// {
//     return m.get<Idx>();
// }

// template <std::size_t Idx,typename Mutiple,typename T>
// auto get(Mutiple&& m) -> decltype(m.get<Idx>())&&
// {
//     return m.get<Idx>();
// }
    // ///////////////////
    // template <std::size_t Idx,typename T> 
    // variant& operator=(T&& t)
    // {
    //     which_ = index_of<T,Args...>::value; 
    //     *static_cast<T*>((char*)buffer_) = std::move(t);
    // }
    // template <typename T>
    // variant& operator=(const T& t)
    // {
    //     which_ = index_of<T,Args...>::value; 
    //     *static_cast<T*>((char*)buffer_) = t;
    // }
    // ////////////////////
    // template <typename T>
    // variant(T&& t)
    // {
    //     *this = std::move(t);        
    // }
    // template <typename T>
    // variant(const T& t)
    // {
    //    *this = t;
    // }

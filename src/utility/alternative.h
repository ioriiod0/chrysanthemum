// ======================================================================================
// File         : alternative.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:47:17 PM | Wednesday,December
// Description  : 
// ======================================================================================

#ifndef __ALTERNATIVE_H__
#define __ALTERNATIVE_H__


#include <cstring>
#include <type_traits>
#include <stdexcept>
#include <functional>

#include "meta_fuctions.h"

// struct UNUSED;

// template<std::size_t Idx,typename T>
// struct choice
// {
//     const static std::size_t value = Idx;
//     typedef T type;
//     /////////////////////////
//     choice(T&& t):under_lying_(std::forward<T>(t)) {}
//     ~choice() {}
//     ////////////////////////
//     T under_lying_;
// };

// template <std::size_t Idx,typename T>
// choice<Idx,T> _choice(T&& t)
// {
//     return choice<Idx,T>(std::forward<T>(t));
// }
/////////////////////////////helper..////////////////////////////////////////////
// template <std::size_t Idx,typename... Args>
// struct choices_selector;
// template <std::size_t Idx,typename Head,typename... Tails>
// struct choices_selector<Idx,Head,Tails...>
// {
//     typedef typename enable_if_else<Idx == Head::value,
//                                     typename Head::type,
//                                     typename choices_selector<Idx,Tails...>::type >::type type;
// };
// template <std::size_t Idx,typename T>
// struct choices_selector<Idx,T>
// {
//     //static_assert(Idx == T::value,"the given Index is invalid!");
//     typedef typename enable_if_else<Idx == T::value,
//                                     typename T::type,
//                                     UNUSED >::type type;
// };

///////////////////////////////////////////////////////////////////////////////////////////////



template <typename T>
struct default_deleter
{
    void operator()(void* p)
    {
        static_cast<T*>(p)->~T();
    }
};

template <typename T>
struct deleter_traits
{
    typedef default_deleter<T> type;
};

template <typename... Args>
class alternative
{
public:
    const static std::size_t buffer_size = max_size_of<Args...>::value;
    typedef std::function<void(void*)> delete_functor;


public:
    alternative():is_inited_(false) {}
    ~alternative() 
    {
        if(is_inited_ && deleter_)
            deleter_(buffer_);
    }
    //////////////disable copy-assignment//////
    alternative& operator=(const alternative& t) = delete;
    ////////////////disable copy-constructor/////////////
    alternative(const alternative& t) = delete;
    //////////////////////////////////////////////
    alternative& operator=(alternative&& t)
    {
        if(this!=&t)
        {
            is_inited_ = t.is_inited_;
            which_ = t.which_;
            memcpy(buffer_,t.buffer_,buffer_size);
            t.is_inited_ = false;
        }
        return *this;
    }
    alternative(alternative&& t)
    {
        *this = std::move(t);
    }
public:
    operator bool() const
    {
        return is_inited_;
    }
    bool has_value() const
    {
        return is_inited_;
    }
    std::size_t which()
    {
        return which_;
    }
    //////////////////////////////////
    template <std::size_t Idx,typename T>
    void set(T&& t)
    {        
        typedef typename at<Idx,Args...>::type ith_type;
        typedef typename deleter_traits<ith_type>::type deleter_type;
        if(is_inited_ && deleter_)
            deleter_(buffer_);
        which_ = Idx;
        new(buffer_) ith_type(std::forward<T>(t));
        deleter_ =  deleter_type();
        is_inited_ = true;
    }
    ////////////////////////////////////
    template <std::size_t Idx>
    typename at<Idx,Args...>::type& get()
    {
        typedef typename at<Idx,Args...>::type ith_type;
        if(which_!=Idx || is_inited_ == false)
            throw std::invalid_argument("the given idx is different from the"
                                        "value which() or the value has not been inited");
        return *((ith_type*)buffer_);
    }

    template <std::size_t Idx>
    const typename at<Idx,Args...>::type& get() const
    {
        typedef typename at<Idx,Args...>::type ith_type;
        if(which_!=Idx || is_inited_ = false)
            throw std::invalid_argument("the given idx is different from the"
                                        "value which() or the value has not been inited");
        return *((ith_type*)buffer_);
    }


    ///////////////////////////////////

private:
    char buffer_[buffer_size];
    std::size_t which_;
    bool is_inited_;
    delete_functor deleter_;

};

#endif

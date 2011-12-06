// ======================================================================================
// File         : variant.h
// Author       : Gao Lei 
// Last Change  : 12/04/2011 | 20:48:39 PM | Sunday,December
// Description  : 
// ======================================================================================


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

// template <typename T>
// struct default_cloner
// {
//     void operator()(void* p_dst,void* d_src)
//     {
//         *(static_cast<T*>(p_dst)) = *(static_cast<T*>(p_src));
//     }
// };

template <typename T>
struct deleter_traits
{
    typedef default_deleter<T> type;
};

// template <typename T>
// struct cloner_traits
// {
//     typedef default_cloner<T> type;
// };

template <typename... Args>
class mutiple
{
public:
    const static std::size_t buffer_size = max_size_of<Args...>::value;
    typedef std::function<void(void*)> delete_functor;


public:
    mutiple():is_inited_(false) {}
    ~mutiple() 
    {
        if(is_inited_ && deleter_)
            deleter_(buffer_);
    }
    //////////////copy-assignment//////
    mutiple& operator=(const mutiple& t) = delete;
    ////////////////copy-constructor/////////////
    mutiple(const mutiple& t) = delete;
    //////////////////////////////////////////////
    mutiple& operator=(mutiple&& t)
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
    mutiple(mutiple&& t)
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

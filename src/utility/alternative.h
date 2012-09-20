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
#include <typeinfo>

#include "meta_fuctions.h"

namespace chrysanthemum {

// struct UNUSED;


// template <typename T,typename... Args>
// class assignment;

// template <typename T,typename Head,typename... Tails>
// class assignment<T,Head,Tails...>:public assignment<T,Tails...>
// {
// public:
//     const T& operator=(const Head& t)
//     {
//         T* p = static_cast<T*>(this);
//         p->set(t);
//         return *p;
//     }

//     const T& operator=(Head&& t)
//     {
//         T* p = static_cast<T*>(this);
//         p->set(std::move(t));
//         return *p;
//     }

// };

// template <typename T,typename T1>
// class assignment<T,T1>
// {
// public:
//     const T& operator=(const T1& t)
//     {
//         T* p = static_cast<T*>(this);
//         p->set(t);
//         return *p;
//     }

//     const T& operator=(T1&& t)
//     {
//         T* p = static_cast<T*>(this);
//         p->set(std::move(t));
//         return *p;
//     }

// };


template <typename... Args>
class alternative
{
public:

    template <typename T>
    struct default_deleter
    {
        void operator()(void* p)
        {
            static_cast<T*>(p)->~T();
        }
    };

    template <typename T>
    struct default_copyer
    {
        void operator()(void* dst,const void* src)
        {
            new(dst) T(*static_cast<const T*>(src));
        }
    };

    template <typename T>
    struct default_mover
    {
        void operator()(void* dst,const void* src)
        {
            new(dst) T(std::move(*static_cast<const T*>(src)));
        }
    };

    const static std::size_t buffer_size = max_size_of<Args...>::value;
    typedef std::function<void(void*)> delete_functor;
    typedef std::function<void(void*,const void*)> copy_functor;
    typedef std::function<void(void*,void*)> move_functor;

public:

    alternative():is_inited_(false) {}
    ~alternative() 
    {
        if(is_inited_ && deleter_)
            deleter_(buffer_);
    }
    //////////////copy-assignment//////
    const alternative& operator=(const alternative& t)
    {
        if(this!=&t)
        {
            is_inited_ = t.is_inited_;
            type_id_ = t.type_id_;
            copyer_ = t.copyer_;
            deleter_ = t.deleter_;
            mover_ = t.mover_;
            copyer_(buffer_,t.buffer_);
        }
        return *this;
    }
    ////////////////copy-constructor/////////////
    alternative(const alternative& t)
    {
        *this = t;
    }
    //////////////////////////////////////////////
    const alternative& operator=(alternative&& t)
    {
        if(this!=&t)
        {
            is_inited_ = t.is_inited_;
            type_id_ = t.type_id_;
            deleter_ = t.deleter_;
            copyer_ = t.copyer_;
            mover_ = t.mover_;
            mover_(buffer_,t.buffer_);
        }
        return *this;
    }

    // template <typename T>
    // const alternative& operator=(T&& t)
    // {
    //     static_assert(is_type_in_types<T,Args...>::value,"the given type is not in variant's types!");
    //     set(std::forward<T>(t));
    //     return *this;
    // }

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
    std::size_t type_id() const
    {
        return type_id_;
    }
    //////////////////////////////////
    template <typename T>
    void set(T&& t)
    {        
        static_assert(is_type_in_types<T,Args...>::value,"the given type is not in alternative's types!");
        typedef typename std::remove_reference<T>::type type;
        typedef default_deleter<type> deleter_type;
        typedef default_copyer<type> copyer_type;
        typedef default_mover<type> mover_type; 
        if(is_inited_ && deleter_)
            deleter_(buffer_);
        type_id_ = typeid(type).hash_code();
        new(buffer_) type(std::forward<T>(t));
        deleter_ = deleter_type();
        copyer_ = copyer_type();
        mover_ = mover_type();
        is_inited_ = true;
    }

    ////////////////////////////////////
    template <typename T>
    T& get()
    {
        static_assert(is_type_in_types<T,Args...>::value,"the given type is not in alternative's types!");
        if(type_id_!=typeid(T).hash_code() || is_inited_ == false)
            throw std::runtime_error("wrong type_id!! or the value has not been inited");
        return *((T*)buffer_);
    }

    template <typename T>
    const T& get() const
    {
        static_assert(is_type_in_types<T,Args...>::value,"the given type is not in alternative's types!");
        if(type_id_!=typeid(T).hash_code() || is_inited_ == false)
            throw std::runtime_error("wrong type_id!! or the value has not been inited");
        return *((T*)buffer_);
    }


    ///////////////////////////////////

private:
    char buffer_[buffer_size];
    std::size_t type_id_;
    bool is_inited_;
    delete_functor deleter_;
    copy_functor copyer_;
    move_functor mover_;
    

};


template <typename T>
std::size_t type_id()
{
   return typeid(T).hash_code();
}


} //end namespace



#endif

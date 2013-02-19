// ======================================================================================
// File         : variant.h
// Author       : Lei Gao
// Last Change  : 12/07/2011 | 15:47:17 PM | Wednesday,December
// Description  : 
// ======================================================================================

#ifndef __variant_H__
#define __variant_H__


#include <cstring>
#include <type_traits>
#include <stdexcept>
#include <functional>
#include <typeinfo>

#include "meta_fuctions.h"

namespace chrysanthemum {

template <typename... Args>
class variant
{
public:

    /////////////////////////////////////
    // template <typename T,typename DUMMY = void>
    // struct convert {
    //     typedef T type;
    // };

    // template <typename K,typename DUMMY>
    // struct convert<std::map<K,_self>,DUMMY> {
    //     typedef std::map<K,variant> type;
    // };

    // template <typename DUMMY>
    // struct convert<std::vector<_self>,typename DUMMY> {
    //     typedef std::vector<variant> type;
    // };
    ////////////////////////////////////////

    // template <typename T,typename DUMMY = void>
    // struct reverse_convert {
    //     typedef T type;
    // };

    // template <typename K,typename DUMMY>
    // struct reverse_convert<std::map<K,variant>,DUMMY > {
    //     typedef std::map<K,_self> type;
    // };

    // template <typename DUMMY>
    // struct reverse_convert<std::vector<variant>,DUMMY > {
    //     typedef std::vector<_self> type;
    // };

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
    //typedef variant<Args...> variant;

public:

    variant():is_inited_(false) {}
    ~variant() 
    {
        if(is_inited_)
            deleter_(buffer_);
    }
    //////////////copy-assignment//////
    const variant& operator=(const variant& t)
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
    variant(const variant& t)
    {
        *this = t;
    }
    //////////////////////////////////////////////
    const variant& operator=(variant&& t)
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

    variant(variant&& t)
    {
        *this = std::move(t);
    }

public:
    operator bool() const
    {
        return is_inited_;
    }

    std::size_t which() const
    {
        return type_id_;
    }
    //////////////////////////////////
    template <typename T>
    const variant& operator=(T&& t)
    {
        typedef typename std::remove_reference<T>::type U;
        static_assert(is_type_in_types<U,Args...>::value,"the given type is not in variant's types!");
        typedef default_deleter<U> deleter_type;
        typedef default_copyer<U> copyer_type;
        typedef default_mover<U> mover_type;

        if(is_inited_)
            deleter_(buffer_);
        type_id_ = index_of<U,Args...>::value;
        new(buffer_) U(std::forward<T>(t));
        deleter_ = deleter_type();
        copyer_ = copyer_type();
        mover_ = mover_type();
        is_inited_ = true;
    }

    // const variant& operator=(const std::vector<variant>& t)
    // {        
    //     static_assert(is_type_in_types<std::vector<_self>,Args...>::value,"the given type is not in variant's types!");
    //     typedef std::vector<variant> type;
    //     typedef default_deleter<type> deleter_type;
    //     typedef default_copyer<type> copyer_type;
    //     typedef default_mover<type> mover_type; 
    //     if(is_inited_)
    //         deleter_(buffer_);
    //     type_id_ = index_of<std::vector<_self>,Args...>::value;
    //     new(buffer_) type(t);
    //     deleter_ = deleter_type();
    //     copyer_ = copyer_type();
    //     mover_ = mover_type();
    //     is_inited_ = true;
    // }

    // const variant& operator=(std::vector<variant>&& t)
    // {        
    //     static_assert(is_type_in_types<std::vector<_self>,Args...>::value,"the given type is not in variant's types!");
    //     typedef std::vector<variant> type;
    //     typedef default_deleter<type> deleter_type;
    //     typedef default_copyer<type> copyer_type;
    //     typedef default_mover<type> mover_type; 
    //     if(is_inited_)
    //         deleter_(buffer_);
    //     type_id_ = index_of<std::vector<_self>,Args...>::value;
    //     new(buffer_) type(std::move(t));
    //     deleter_ = deleter_type();
    //     copyer_ = copyer_type();
    //     mover_ = mover_type();
    //     is_inited_ = true;
    // }

    // template <typename T>
    // const variant& operator=(const std::map<T,variant>& t)
    // {        
    //     static_assert(is_type_in_types<std::map<T,_self>,Args...>::value,"the given type is not in variant's types!");
    //     typedef std::map<T,variant> type;
    //     typedef default_deleter<type> deleter_type;
    //     typedef default_copyer<type> copyer_type;
    //     typedef default_mover<type> mover_type; 
    //     if(is_inited_)
    //         deleter_(buffer_);
    //     type_id_ = index_of<std::map<T,_self>,Args...>::value;
    //     new(buffer_) type(t);
    //     deleter_ = deleter_type();
    //     copyer_ = copyer_type();
    //     mover_ = mover_type();
    //     is_inited_ = true;
    // }

    // template <typename T>
    // const variant& operator=(std::map<T,variant>&& t)
    // {        
    //     static_assert(is_type_in_types<std::map<T,_self>,Args...>::value,"the given type is not in variant's types!");
    //     typedef std::map<T,variant> type;
    //     typedef default_deleter<type> deleter_type;
    //     typedef default_copyer<type> copyer_type;
    //     typedef default_mover<type> mover_type; 
    //     if(is_inited_)
    //         deleter_(buffer_);
    //     type_id_ = index_of<std::map<T,_self>,Args...>::value;
    //     new(buffer_) type(std::move(t));
    //     deleter_ = deleter_type();
    //     copyer_ = copyer_type();
    //     mover_ = mover_type();
    //     is_inited_ = true;
    // }


    ////////////////////////////////////
    template <typename T>
    T& get()
    {
        //typedef typename reverse_convert<T>::type V;
        static_assert(is_type_in_types<T,Args...>::value,"the given type is not in variant's types!");
        if(type_id_!=index_of<T,Args...>::value || is_inited_ == false)
            throw std::bad_cast();
        return *((T*)buffer_);
    }

    template <typename T>
    const T& get() const
    {
        //typedef typename reverse_convert<T>::type V;
        static_assert(is_type_in_types<T,Args...>::value,"the given type is not in variant's types!");
        if(type_id_!=index_of<T,Args...>::value || is_inited_ == false)
            throw std::bad_cast();
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



} //end namespace



#endif

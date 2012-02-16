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

namespace chrysanthemum {

// struct UNUSED;

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
    alternative& operator=(const alternative& t)
    {
        if(this!=&t)
        {
            is_inited_ = t.is_inited_;
            which_ = t.which_;
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
    alternative& operator=(alternative&& t)
    {
        if(this!=&t)
        {
            is_inited_ = t.is_inited_;
            which_ = t.which_;
            deleter_ = t.deleter_;
            copyer_ = t.copyer_;
            mover_ = t.mover_;
            mover_(buffer_,t.buffer_);
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
    std::size_t which() const
    {
        return which_;
    }
    //////////////////////////////////
    template <std::size_t Idx,typename T>
    void set(T&& t)
    {        
        typedef typename at<Idx,Args...>::type ith_type;
        typedef default_deleter<ith_type> deleter_type;
        typedef default_copyer<ith_type> copyer_type;
        typedef default_mover<ith_type> mover_type;
        if(is_inited_ && deleter_)
            deleter_(buffer_);
        which_ = Idx;
        new(buffer_) ith_type(std::forward<T>(t));
        deleter_ = deleter_type();
        copyer_ = copyer_type();
        mover_ = mover_type();
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
        if(which_!=Idx || is_inited_ == false)
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
    copy_functor copyer_;
    move_functor mover_;
    

};



} //end namespace

#endif

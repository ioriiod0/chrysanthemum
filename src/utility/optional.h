// ======================================================================================
// File         : optional.h
// Author       : Gao Lei , Qianhong Wang
// Last Change  : 12/03/2011 | 00:14:01 AM | Saturday,December
// Description  : 
// ======================================================================================

#ifndef __OPTIONAL_H__
#define __OPTIONAL_H__

namespace chrysanthemum{



template <typename T>
class optional
{
public:
    // internal typedef
    
public:
    // con/de-structor
    optional():is_inited_(false) {}
    optional(T&& t):is_inited_(true),t_(std::forward<T>(t)) {}
    ~optional() {}
    
    optional(const optional& rhs)
    {
       *this = rhs; 
    }
    optional& operator=(const optional& rhs)
    {
        if(this!=&rhs)
        {
            is_inited_ = rhs.is_inited_;
            t_ = rhs.t_;
        }
        return *this;
    }

    optional(optional&& rhs)
    {
        *this = std::move(rhs);
    }
    optional& operator=(optional&& rhs)
    {
        if(this!=&rhs)
        {
            is_inited_ = rhs.is_inited_;
            t_ = std::move(rhs.t_);
        }
        return *this;
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
    void reset()
    {
        is_inited_ = false;
    }
    template <typename U>
    void set(U&& u)
    {
        t_ = std::forward<U>(u);
        is_inited_ = true;
    }
    T& get()
    {
        return t_;
    }
    const T& get() const
    {
        return t_;
    }
private:
    bool is_inited_;
    T t_;

}; // end class optional

} // end namespace

#endif

// ======================================================================================
// File         : optional.h
// Author       : Gao Lei 
// Last Change  : 12/03/2011 | 00:14:01 AM | Saturday,December
// Description  : 
// ======================================================================================

#include <memory>


template <typename T>
class optional
{
public:
    // internal typedef
    
public:
    // con/de-structor
    optional():is_inited_(false) {}
    optional(T&& t):is_inited_(true),sp_(new T(std::forward<T>(t))) {}
    ~optional() {}
    
    optional(const optional& rhs)=delete;
    optional& operator=(const optional& rhs);

    optional(optional&& rhs)
    {
        *this = std::move(rhs);
    }
    optional& operator=(optional&& rhs)
    {
        if(this!=&rhs)
        {
            is_inited_ = rhs.is_inited_;
            sp_ = std::move(rhs.sp_);
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
        sp_.reset();
    }
    template <typename U>
    void set(U&& t)
    {
        sp_.reset(new T(std::forward<U>(t)));
        is_inited_ = true;
    }
    T& get()
    {
        if(!sp_)
            sp_.reset(new T());
        return *sp_;
    }
    const T& get() const
    {
        if(!sp_)
            sp_.reset(new T());
        return *sp_;
    }
private:
    bool is_inited_;
    std::unique_ptr<T> sp_;

}; // end class optional

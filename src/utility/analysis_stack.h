// ======================================================================================
// File         : analysis_stack.h
// Author       : Lei Gao 
// Last Change  : 12/27/2011 | 16:22:05 PM | Tuesday,December
// Description  : 
// ======================================================================================



#ifndef __ANALYSIS_STACK_H__
#define __ANALYSIS_STACK_H__

#include <stack>
#include <memory>

namespace chrysanthemum {

template <typename Alloc = std::allocator<char> >
class analysis_stack
{
public:
    struct stack_node
    {
        stack_node():buffer_(NULL),size_(0) {}
        ///////////////////////////////////////
        char* buffer_;
        std::size_t size_;
        std::function<void(char*)> deleter_;
    };

    template <typename T>
    struct default_deleter
    {
        void operator() (char* buffer)
        {
            T* p = static_cast<T*>(buffer);
            p->~T();
        }
    };

public:
    analysis_stack() = default;
    ~analysis_stack()
    {
       while(!stack_.empty())
       {
           pop(); 
       }
    }
    analysis_stack(const analysis_stack& t) = delete;
    analysis_stack(analysis_stack&& t) = delete;
    analysis_stack& operator=(const analysis_stack& t) = delete;
    analysis_stack& operator=(analysis_stack&& t) = delete;
    ////////////////disable copy-constructor/////////////

public:
    
public:
    template <typename T,typename Deleter>
    void push(const T& t,const Deleter& del = default_deleter<T>())
    {
        stack_node node;
        node.buffer_ = alloc_.allocate(sizeof(T));
        new(node.buffer_) T(t); 
        node.size_ = sizeof(T);
        node.deleter_ = del;
        stack_.push(node);
    }

    template <typename T>
    T& top()
    {
        T* p = static_cast<T*>(stack_.top().buffer_);
        return *p;
    }

    template <typename T>
    const T& top() const
    {
        T* p = static_cast<T*>(stack_.top().buffer_);
        return *p;
    }

    void pop()
    {
        if(stack_.top().deleter_)
        {
            stack_.top().deleter_(stack_.top().buffer_);
        }
        delete stack_.top().buffer_;
        stack_.pop();
    }

    std::size_t size() const
    {
        return stack_.size();
    }

    bool empty() const
    {
        return stack_.empty();
    }
private:
    std::stack<stack_node> stack_;
    Alloc alloc_;

};


} //end namespace



#endif


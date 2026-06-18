template<typename T>
class vector_iterator{
    T* ptr_;
    vector_iterator(T* ptr) : ptr_(ptr) {}
    T& operator*(){
        return *ptr_;
    }
    vector_iterator& operator++(){
        ++ptr_;
        return *this;
    }
    vector_iterator operator++(int){
        vector_iterator temp = *this;
        ptr_++;
        return temp;
    }
    bool operator==(T& itr){
        return ptr_ == itr.ptr_;
    }
    bool operator!=(T& itr){
        return ptr_ != itr.ptr_;
    }
};
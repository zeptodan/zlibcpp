template<typename T>
class vector_iterator{
    private:
    T* ptr_;
    public:
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
    vector_iterator& operator--(){
        --ptr_;
        return *this;
    }
    vector_iterator operator--(int){
        vector_iterator temp = *this;
        ptr_--;
        return temp;
    }
    int operator-(vector_iterator& itr){
        return itr.ptr_ - ptr_;
    }
    bool operator==(vector_iterator& itr){
        return ptr_ == itr.ptr_;
    }
    bool operator!=(vector_iterator& itr){
        return ptr_ != itr.ptr_;
    }
};
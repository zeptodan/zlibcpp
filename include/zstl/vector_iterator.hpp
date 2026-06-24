template<typename T>
class vector_iterator{
    private:
    T* ptr_;
    public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;

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
    difference_type operator-(vector_iterator& itr){
        return itr.ptr_ - ptr_;
    }
    bool operator==(vector_iterator& itr){
        return ptr_ == itr.ptr_;
    }
    bool operator!=(vector_iterator& itr){
        return ptr_ != itr.ptr_;
    }
    bool operator<(vector_iterator& itr){
        return ptr_ < itr.ptr_;
    }
    bool operator>(vector_iterator& itr){
        return ptr_ > itr.ptr_;
    }
    bool operator<=(vector_iterator& itr){
        return this < itr || this == itr;
    }
    bool operator>=(vector_iterator& itr){
        return this > itr || this == itr;
    }
    vector_iterator& operator+=(difference_type n){
        ptr_+=n;
        return *this;
    }
    vector_iterator operator+(difference_type n){
        return vector_iterator(ptr_ + n);
    }
    vector_iterator& operator-=(difference_type n){
        ptr_ -= n;
        return *this;
    }
    vector_iterator operator-(difference_type n){
        return vector_iterator(ptr_ - n);
    }
    T* operator->(){
        return ptr_;
    }
};
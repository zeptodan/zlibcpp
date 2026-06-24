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

    vector_iterator(T* ptr) noexcept : ptr_(ptr) {}
    T& operator*() const noexcept {
        return *ptr_;
    }
    vector_iterator& operator++() noexcept{
        ++ptr_;
        return *this;
    }
    vector_iterator operator++(int) noexcept{
        vector_iterator temp = *this;
        ptr_++;
        return temp;
    }
    vector_iterator& operator--() noexcept{
        --ptr_;
        return *this;
    }
    vector_iterator operator--(int) noexcept{
        vector_iterator temp = *this;
        ptr_--;
        return temp;
    }
    difference_type operator-(const vector_iterator& itr) const noexcept{
        return itr.ptr_ - ptr_;
    }
    bool operator==(const vector_iterator& itr) const noexcept{
        return ptr_ == itr.ptr_;
    }
    bool operator!=(const vector_iterator& itr) const noexcept{
        return ptr_ != itr.ptr_;
    }
    bool operator<(const vector_iterator& itr) const noexcept{
        return ptr_ < itr.ptr_;
    }
    bool operator>(const vector_iterator& itr) const noexcept{
        return ptr_ > itr.ptr_;
    }
    bool operator<=(const vector_iterator& itr) const noexcept{
        return this < itr || this == itr;
    }
    bool operator>=(const vector_iterator& itr) const noexcept{
        return this > itr || this == itr;
    }
    vector_iterator& operator+=(difference_type n) noexcept{
        ptr_+=n;
        return *this;
    }
    vector_iterator operator+(difference_type n) const noexcept{
        return vector_iterator(ptr_ + n);
    }
    vector_iterator& operator-=(difference_type n) noexcept{
        ptr_ -= n;
        return *this;
    }
    vector_iterator operator-(difference_type n) const noexcept{
        return vector_iterator(ptr_ - n);
    }
    T* operator->() const noexcept{
        return ptr_;
    }
};
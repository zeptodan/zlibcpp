template<typename T>
class unordered_map_iterator{
    private:
    T* ptr_;
    T** buckets;
    std::size_t bucket_index;
    std::size_t bucket_count;
    public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair<const Key, T>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
    unordered_map_iterator(T* ptr,T** buckets, std::size_t bucket_index, std::size_t bucket_count) : 
    ptr_(ptr), buckets(buckets), bucket_index(bucket_index), bucket_count(bucket_count) {}
    unordered_map_iterator& operator++(){
        if(ptr_->next){
            ptr_ = ptr_->next;
            return *this;
        }
        for (std::size_t i = bucket_index + 1; i < bucket_count; i++){
            if(buckets[i]){
                ptr_ = buckets[i];
                bucket_index = i;
                return *this;
            }
        }
        ptr_ = nullptr;
        bucket_index = bucket_count;
        return *this;
    }
    unordered_map_iterator operator++(int){
        unordered_map_iterator temp(ptr_, buckets,bucket_index, bucket_count);
        if(ptr_->next){
            ptr_ = ptr_->next;
            return temp;
        }
        for (std::size_t i = bucket_index + 1; i < bucket_count; i++){
            if(buckets[i]){
                ptr_ = buckets[i];
                bucket_index = i;
                return temp;
            }
        }
        ptr_ = nullptr;
        bucket_index = bucket_count;
        return temp;
    }
    reference operator*() const noexcept{
        return ptr_->pair;
    }
    pointer operator->() const noexcept{
        return &(ptr_->pair);
    }
    bool operator==(unordered_map_iterator& itr) const noexcept{
        return ptr_ == itr.ptr_;
    }
    bool operator!=(unordered_map_iterator& itr) const noexcept{
        return ptr_ != itr.ptr_;
    }
};
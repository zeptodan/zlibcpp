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
    unordered_map_iterator operator++(){

    }
    unordered_map_iterator operator++(int){

    }
    reference operator*(){

    }
    pointer operator->(){

    }
    bool operator==(unordered_map_iterator& itr){

    }
    bool operator!=(unordered_map_iterator& itr){
        
    }
};
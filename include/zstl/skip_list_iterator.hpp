template<typename Node>
class skip_list_iterator{
    private:
    Node* ptr_;
    public:
    using value_type = typename Node::value_type;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
    skip_list_iterator(Node* ptr) : ptr_(ptr) {}
    skip_list_iterator& operator++(){
        ptr_ = ptr_->next[0];
        return *this;
    }
    skip_list_iterator operator++(int){
        skip_list_iterator temp(ptr_);
        ptr_ = ptr_->next[0];
        return temp;
    }
    reference operator*() const noexcept{
        return ptr_->pair.second;
    }
    pointer operator->() const noexcept{
        return &ptr_->pair.second;
    }
    bool operator==(const skip_list_iterator& sl) const noexcept{
        return ptr_ == sl.ptr_;
    }
    bool operator!=(const skip_list_iterator& sl) const noexcept{
        return ptr_ != sl.ptr_;
    }
};
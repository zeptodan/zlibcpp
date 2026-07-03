template<typename Node>
class skip_list_iterator{
    using value_type = typename Node::value_type;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
    Node* ptr_;
    skip_list_iterator(Node* ptr) : ptr_(ptr) {}
    skip_list_iterator& operator++(){

    }
    skip_list_iterator operator++(int){

    }
    reference operator*() const noexcept{

    }
    pointer operator->() const noexcept{

    }
    bool operator==() const noexcept{

    }
    bool operator!=() const noexcept{
        
    }
};
#include<stdexcept>
#include"vector_iterator.hpp"
#define GROWTH_FACTOR 2
template<typename type>
class vector{
    using iterator = vector_iterator<type>;
    using const_iterator = vector_iterator<const type>;
    using size_type = std::size_t;
    private:
    type* array;
    type* size_;
    type* capacity_;
    void swap(vector& vec) noexcept{
        std::swap(array,vec.array);
        std::swap(size_,vec.size_);
        std::swap(capacity_,vec.capacity_);
    }
    public:
    vector(){
        array = static_cast<type*>(::operator new(sizeof(type) * 10));
        size_ = array;
        capacity_ = array + 10;
    }
    vector(std::initializer_list<type> list){
        array = static_cast<type*>(::operator new(sizeof(type) * list.size()));
        size_ = array;
        for(auto& elem : list){
            new (size_) type(elem);
            ++size_;
        }
        capacity_ = array + list.size();
    }
    vector(const vector& vec){
        size_type size = vec.size_ - vec.array;
        array = static_cast<type*>(::operator new(sizeof(type) * (vec.capacity_ - vec.array)));
        size_ = array;
        for(int i = 0;i < size;i++){
            new (size_) type(*(vec.array + i));
            ++size_;
        }
        capacity_ = array + (vec.capacity_ - vec.array);
    }
    vector(vector&& vec) noexcept : array(vec.array), size_(vec.size_), capacity_(vec.capacity_){
        vec.array = nullptr;
        vec.size_ = nullptr;
        vec.capacity_ = nullptr;
    }
    vector& operator=(const vector& vec){
        if(this != &vec){
            vector temp(vec);
            swap(temp);
        }
        return *this;
    }
    vector& operator=(vector&& vec) noexcept {
        if (this != &vec){
            for (type* i = array; i != size_;i++){
                i->~type();
            }
            ::operator delete(array);

            array = vec.array;
            size_ = vec.size_;
            capacity_ = vec.capacity_;
            vec.array = nullptr;
            vec.size_ = nullptr;
            vec.capacity_ = nullptr;
        }
        return *this;
    }
    ~vector(){
        for(type* i = array; i != size_;i++){
            i->~type();
        }
        ::operator delete(array);
    }
    type& operator[](int index) noexcept{
        return *(array + index);
    }
    const type& operator[](int index) const noexcept{
        return *(array + index);
    }
    iterator begin() noexcept{
        return iterator(array);
    }
    iterator end() noexcept{
        return iterator(size_);
    }
    const_iterator cbegin() const noexcept{
        return const_iterator(array);
    }
    const_iterator cend() const noexcept{
        return const_iterator(size_);
    }
    type* data() noexcept{
        return array;
    }
    const type* data() const noexcept{
        return array;
    }
    bool is_full() const noexcept{
         return (size_ == capacity_) ? true : false;
    }
    bool empty() const noexcept{
        return array == size_;
    }
    void erase(size_type index){
        if (array + index >= size_ || index < 0){
            throw std::out_of_range("out of bounds");
        }
        for (type* temp = array + index + 1; temp != size_;++temp){
            *(temp - 1) = *temp;
        }
        size_--;
    }
    void push_back(const type& obj){
        if(is_full()){
            resize((capacity_ - array) * GROWTH_FACTOR);
        }
        new (size_) type(obj);
        ++size_;
    }
    void push_back(type&& obj){
        if(is_full()){
            resize((capacity_ - array) * GROWTH_FACTOR);
        }
        new (size_) type(std::move(obj));
        ++size_;
    }
    type& front() noexcept{
        return *array;
    }
    const type& front() const noexcept{
        return *array;
    }
    type& back() noexcept{
        return *(size_ - 1);
    }
    const type& back() const noexcept{
        return *(size_ - 1);
    }
    void pop_back(){
        size_->~type();
        size_--;
        return;
    }
    void resize(int new_size){
        type* temp = static_cast<type*>(::operator new(sizeof(type) * new_size));
        type* start2 = temp;
        for (type* start = array; start != size_;start++,start2++){
            new (start2) type(std::move(*start));
            start->~type();
        }
        ::operator delete(array);
        array = temp;
        size_ = start2;
        capacity_ = temp + new_size;
    }
    type& get(int index) noexcept{
        if(array + index >= capacity_ || index < 0){
            throw std::out_of_range("index out of bounds");
        }
        return array[index];
    }
    const type& get(int index) const noexcept{
        if(array + index >= capacity_ || index < 0){
            throw std::out_of_range("index out of bounds");
        }
        return array[index];
    }
    int size() const noexcept{
        return size_ - array;
    }
    int capacity() const noexcept{
        return capacity_ - array;
    }
};
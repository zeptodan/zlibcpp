#include<stdexcept>
#include"vector_iterator.hpp"
template<typename type>
class vector{
    using iterator = vector_iterator<type>;
    using const_iterator = vector_iterator<const type>;
    using size_type = std::size_t;
    private:
    type* array;
    type* size_;
    type* capacity_;
    public:
    vector(){
        array = new type[10];
        size_ = array;
        capacity_ = array + 10;
    }
    vector(std::initializer_list<type> list){
        array = new type[list.size()];
        size_ = array + list.size();
        for(auto begin = list.begin(), i = 0; begin != list.end();begin++,i++){
            *(array + i) = *begin;
        }
        capacity_ = array + list.size();
    }
    vector(const vector& vec){
        int size = vec.size_ - vec.array;
        array = new type[vec.capacity_ - vec.array];
        for(int i = 0;i < size;i++){
            *(array + i) = *(vec.array + i);
        }
        size_ = array + size;
        capacity_ = array + (vec.capacity_ - vec.array);
    }
    vector(vector&& vec) noexcept : array(vec.array), size_(vec.size_), capacity_(vec.capacity_){
        vec.array = nullptr;
        vec.size_ = nullptr;
        vec.capacity_ = nullptr;
    }
    vector& operator=(const vector& vec){
        int size = vec.size_ - vec.array;
        if (size > capacity_ - array){
            resize(size);
        }
        for (int i = 0; i < size;i++){
            *(array + i) = *(vec.array + i); 
        }
        size_ = array + size;
        return *this;
    }
    vector& operator=(vector&& vec) noexcept {
        int size = vec.size_ - vec.array;
        if (size > capacity_ - array){
            resize(size);
        }
        for (int i = 0; i < size;i++){
            *(array + i) = std::move(*(vec.array + i));
        }
        size_ = array + size;
        return *this;
    }
    ~vector(){
        delete[] array;
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
        *size_++ = obj;
        if(is_full()){
            resize((capacity_ - array) * 1.5);
        }
    }
    void push_back(type&& obj){
        *size_++ = std::move(obj);
        if(is_full()){
            resize((capacity_ - array) * 1.5);
        }
    }
    type& front() noexcept{
        return *array;
    }
    const type& front() const noexcept{
        return *array;
    }
    type& back() noexcept{
        return *(size - 1);
    }
    const type& back() const noexcept{
        return *(size - 1);
    }
    void pop_back(){
        size--;
        return;
    }
    void resize(int new_size){
        type* temp = new type[new_size];
        size_ = temp;
        for (type* start = array; start != capacity_;start++){
            * size_ ++ = *start;
        }
        array = temp;
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
#include<stdexcept>
#include"vector_iterator.hpp"
template<typename type>
class vector{
    using iterator = vector_iterator<type>;
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
        size_ = array;
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
    vector(vector&& vec) : array(vec.array), size_(vec.size_), capacity_(vec.capacity_){
        vec.array = nullptr;
        vec.size_ = nullptr;
        vec.capacity_ = nullptr;
    }
    vector& operator=(vector& vec){
        int size = vec.size_ - vec.array;
        if (size > capacity_ - array){
            resize(size);
        }
        for (int i = 0; i < size;i++){
            *(array + i) = *(vec.array + i); 
        }
        size_ = array + size;
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
    }
    ~vector(){
        delete[] array;
    }
    type& operator[](int index){
        return *(array + index);
    }
    iterator begin(){
        return iterator(array);
    }
    iterator end(){
        return iterator(size_);
    }
    bool is_full(){
         return (size_ == capacity_) ? true : false;
    }
    bool empty(){
        return array == size_;
    }
    void erase(int index){
        if (array + index >= size_){
            throw std::out_of_range("out of bounds");
        }
        for (type* temp = array + index + 1; temp != size_;++temp){
            *(temp - 1) = *temp;
        }
        size_--;
    }
    void add(type& obj){
        *size_++ = obj;
        if(is_full()){
            resize((capacity_ - array) * 1.5);
        }
    }
    void add(type&& obj){
        *size_++ = obj;
        if(is_full()){
            resize((capacity_ - array) * 1.5);
        }
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
    type& get(int index){
        if(array + index >= capacity_){
            throw std::out_of_range("index out of bounds");
        }
        return array[index];
    }
    int size(){
        return size_ - array;
    }
    int capacity(){
        return capacity_ - array;
    }
};
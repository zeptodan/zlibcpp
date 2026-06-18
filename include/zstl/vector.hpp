#include<stdexcept>
template<typename type>
class vector{
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
    bool is_full(){
         return (size_ == capacity_) ? true : false;
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
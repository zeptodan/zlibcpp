#include<stdexcept>
template<typename type>
class vector{
    private:
    type* array;
    type* size;
    type* capacity;
    public:
    vector(){
        array = new type[10];
        size = array;
        capacity = array + 10;
    }
    bool is_full(){
         return (size == capacity) ? true : false;
    }
    void add(type& obj){
        *size++ = obj;
        if(is_full()){
            resize((capacity - array) * 1.5);
        }
    }
    void add(type&& obj){
        *size++ = obj;
        if(is_full()){
            resize((capacity - array) * 1.5);
        }
    }
    void resize(int new_size){
        type* temp = new type[new_size];
        size = temp;
        for (type* start = array; start != capacity;start++){
            *size++ = *start;
        }
        array = temp;
        capacity = temp + new_size;
    }
    type& get(int index){
        if(array + index >= capacity){
            throw std::out_of_range("index out of bounds");
        }
        return array[index];
    }
};
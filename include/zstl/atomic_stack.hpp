#include<atomic>
template<typename T>
class atomic_stack{
    struct node{
        T data;
        node* next;
        node(T&& val) : data(std::move(val)), next(nullptr) {}
    };
    std::atomic<node*> head;
    public:
    atomic_stack() : head(nullptr) {}
    bool try_pop(T& value){
        node* node_ptr = head;
        bool is_popped = head.compare_exchange_weak(node_ptr, node_ptr->next);
        if(is_popped){
            value = std::move(node_ptr->data);
        }
        return is_popped;
    }
    void push(T value){
        node* new_node = new node(std::move(value));
        new_node->next = head;
        while(!head.compare_exchange_weak(new_node->next, new_node))
    }
};
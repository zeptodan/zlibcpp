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
        node* node_ptr = head.load(std::memory_order_relaxed);
        bool is_popped = node_ptr && head.compare_exchange_weak(node_ptr, node_ptr->next, std::memory_order_release, std::memory_order_relaxed);
        if(is_popped){
            value = std::move(node_ptr->data);
            // delete node_ptr;
        }
        return is_popped;
    }
    void push(T value){
        node* new_node = new node(std::move(value));
        new_node->next = head.load(std::memory_order_acquire);
        while(!head.compare_exchange_weak(new_node->next, new_node, std::memory_order_release, std::memory_order_relaxed));
    }
};
#include<atomic>
template<typename T>
class atomic_stack{
    private:
    struct node{
        T data;
        node* next;
        node(T&& val) : data(std::move(val)), next(nullptr) {}
    };
    std::atomic<node*> head;
    std::atomic<node*> to_be_deleted;
    std::atomic<int> threads_in_pop;
    void delete_nodes(node* to_delete){
        node* tmp;
        while(to_delete){
            tmp = to_delete;
            to_delete = to_delete->next;
            delete tmp;
        }
    }
    void chain_pending_nodes(node* nodes)
    {
        node* last=nodes;
        while(node* const next=last->next)
            {
            last=next;
            }
        chain_pending_nodes(nodes,last);
    }
    void chain_pending_nodes(node* first,node* last)
    {
        last->next=to_be_deleted;
        while(!to_be_deleted.compare_exchange_weak(last->next,first));
    }
    void chain_pending_node(node* n)
    {
        if(n){
            chain_pending_nodes(n,n);
        }
    }
    void reclaim(node* old_head){
        if (threads_in_pop == 1){
            node* to_delete = to_be_deleted.exchange(nullptr);
            if(!--threads_in_pop){
                //delete the nodes
                delete_nodes(to_delete);

            }
            else if(to_delete){
                //add the nodes to the chain
                chain_pending_nodes(to_delete);
            }
            delete old_head;
        }
        else{
            //add node to chain
            chain_pending_node(old_head);
            --threads_in_pop;
            return;
        }
    }
    public:
    atomic_stack() : head(nullptr), to_be_deleted(nullptr), threads_in_pop(0) {}
    bool try_pop(T& value){
        ++threads_in_pop;
        node* node_ptr = head.load(std::memory_order_relaxed);
        node* expected = node_ptr;
        bool is_popped = expected && head.compare_exchange_strong(expected, expected->next, std::memory_order_acquire, std::memory_order_relaxed);
        if(is_popped){
            value = std::move(node_ptr->data);
        }
        reclaim(is_popped ? node_ptr : nullptr);
        return is_popped;
    }
    void push(T value){
        node* new_node = new node(std::move(value));
        new_node->next = head.load(std::memory_order_acquire);
        while(!head.compare_exchange_weak(new_node->next, new_node, std::memory_order_release, std::memory_order_relaxed));
    }
};
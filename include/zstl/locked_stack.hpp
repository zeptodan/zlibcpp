#include<mutex>
#include<condition_variable>
template<typename T>
class locked_stack{
    private:
    struct node{
        T data;
        node* next;
        node(T&& value) : data(std::move(value)), next(nullptr) {}
    };
    node* head;
    mutable std::mutex mut;
    mutable std::condition_variable cond;
    node* top(){
        return head;
    }
    public:
    locked_stack() : head(nullptr) {}
    bool try_pop(T& value) {
        std::lock_guard lk(mut);
        node* tmp = top();
        if (!tmp){
            return false;
        }
        value = std::move(tmp->data);
        head = head->next;
        delete tmp;
        return true;
    }
    std::shared_ptr<T> pop() {
        std::unique_lock lk(mut);
        cond.wait(lk, [this](){return top();});
        std::shared_ptr<T> ptr = std::make_shared<T>(std::move(top()->data));
        node* tmp = head;
        head = head->next;
        delete tmp;
        return ptr;
    }
    void push(T value) {
        std::lock_guard lk(mut);
        node* new_node = new node(std::move(value));
        new_node->next = head;
        head = new_node;
        cond.notify_one();
    }
};
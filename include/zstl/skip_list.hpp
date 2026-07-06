#include<functional>
#include"zstl/skip_list_iterator.hpp"
template<typename Key, typename Value, typename Compare = std::less<Key>>
class skip_list{
    private:
    using size_type = std::size_t;
    struct Node{
        using value_type = std::pair<const Key, Value>;
        value_type pair;
        std::vector<Node*> next;
        Node() = default;
        Node(const Key& key) : pair(key, Value()) {}
        Node(const Key& key, const Value& value): pair(key,value) {}
        Node(const Node& node) = default;
    };
    Node* head;
    int max_level = 64;
    int current_level;
    int prob = 0.5;
    size_type size_;
    Compare compare;
    public:
    using iterator = skip_list_iterator<Node>;
    using const_iterator = skip_list_iterator<const Node>;
    skip_list() : current_level(0), size_(0){
        head = new Node();
        head->next.resize(max_level);
    }
    skip_list(const skip_list& sl) : size_(0), current_level(0) {
        head = new Node();
        head->next.resize(max_level);
        Node* current = sl.head;
        while (current->next[0] != nullptr){
            (*this)[current->next[0]->pair.first] = current->next[0]->pair.second;
            current = current->next[0];
        }
    }
    skip_list(skip_list&& sl) noexcept : size_(sl.size_), current_level(sl.current_level), head(sl.head){
        sl.head = nullptr;
        sl.size_ = 0;
        sl.current_level = 0;
    }
    ~skip_list(){
        if (head){
            Node* current = head->next[0], *next;
            while(current != nullptr){
                next = current->next[0];
                delete current;
                current = next;
            }
            delete head;
        }
    }
    skip_list& operator=(const skip_list& sl){
        skip_list temp(sl);
        swap(temp);
        return *this;
    }
    skip_list& operator=(skip_list&& sl) noexcept{
        if (head){
            Node* current = head->next[0], *next;
            while(current != nullptr){
                next = current->next[0];
                delete current;
                current = next;
            }
            delete head;
        }
        head = sl.head;
        size_ = sl.size_;
        current_level = sl.current_level;
        sl.head = nullptr;
        sl.size_ = 0;
        sl.current_level = 0;
        return *this;
    }
    void swap(skip_list& sl){
        std::swap(head, sl.head);
        std::swap(size_, sl.size_);
        std::swap(current_level, sl.current_level);
    }
    Value& operator[](const Key& key){
        Node* current = head;
        Node* pred[max_level];
        for(int layer = current_level; layer >= 0;layer--){
            while(current->next[layer] != nullptr && compare(current->next[layer]->pair.first, key)){
                current = current->next[layer];
            }
            pred[layer] = current;
        }
        if(pred[0]->next[0] != nullptr && key == pred[0]->next[0]->pair.first){
            return pred[0]->next[0]->pair.second;
        }
        Node* node = new Node(key);
        int level = generate_level();
        node->next.resize(level + 1);
        size_++;
        if (level > current_level){
            for (int i = current_level + 1; i <= level;i++){
                pred[i] = head;
            }
            current_level = level;
        }
        //insert the node
        for (int i = level;i >= 0; i--){
            node->next[i] = pred[i]->next[i];
            pred[i]->next[i] = node;
        }
        return node->pair.second;
    }
    int generate_level(){
        int level = 0;
        while (rand() % 2 == 0 && level != max_level - 1){
            level++;
        }
        return level;
    }
    bool contains(const Key& key){
        Node* current = head;
        for(int layer = current_level; layer >= 0;layer--){
            while(current->next[layer] != nullptr && compare(current->next[layer]->pair.first, key)){
                current = current->next[layer];
            }
        }
        if(current->next[0] != nullptr && key == current->next[0]->pair.first){
            return true;
        }
        return false;
    }
    size_type erase(const Key& key){
        Node* current = head;
        Node* pred[max_level];
        for(int layer = current_level; layer >= 0;layer--){
            while(current->next[layer] != nullptr && compare(current->next[layer]->pair.first, key)){
                current = current->next[layer];
            }
            pred[layer] = current;
        }
        if(pred[0]->next[0] != nullptr && key == pred[0]->next[0]->pair.first){
            Node* target = pred[0]->next[0];
            for (int i = current_level; i >= 0; i--){
                pred[i]->next[i] = target->next[0];
            }
            delete target;
            while(current_level > 0 && head->next[current_level] == nullptr){
                current_level--;
            }
            size_--;
            return 1;
        }
        return 0;
    }
    iterator begin() noexcept {
        return iterator(head->next[0]);
    }
    iterator end() noexcept {
        return iterator(nullptr);
    }
    const_iterator cbegin() const noexcept {
        return const_iterator(head->next[0]);
    }
    const_iterator cend() const noexcept {
        return const_iterator(nullptr);
    }
    size_type size() const noexcept {
        return size_;
    }
};
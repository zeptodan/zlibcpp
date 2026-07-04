#include<functional>
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
    using iterator = unordered_map_iterator<Node>;
    using const_iterator = unordered_map_iterator<const Node>;
    skip_list() : current_level(0), size_(0){
        head = new Node();
    }
    skip_list(const skip_list& sl){

    }
    skip_list(skip_list&& sl) noexcept{

    }
    skip_list& operator=(const skip_list& sl){

    }
    skip_list& operator=(skip_list&& sl) noexcept{

    }
    Value& operator[](const Key& key){
        Node* current = head;
        Node* pred[max_level];
        for(int layer = current_level - 1; layer >= 0;layer--){
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
        if (level > current_level){
            for (int i = current_level; i < level;i++){
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
        for(int layer = current_level - 1; layer >= 0;layer--){
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

    }
    iterator begin() noexcept {
        
    }
    iterator end() noexcept {

    }
    const_iterator cbegin() const noexcept {

    }
    const_iterator cend() const noexcept {

    }
    size_type size() const noexcept {
        return size_;
    }
};
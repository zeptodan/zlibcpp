#include<functional>
template<typename Key, typename Value, typename Compare = std::less<Key>>
class skip_list{
    private:
    using size_type = std::size_t;
    struct Node{
        using value_type = std::pair<const Key, Value>;
        value_type pair;
        std::vector<Node*> next;
        Node(const Key& key) : pair(key, Value()) {}
        Node(const Key& key, const Value& value): pair(key,value) {}
        Node(const Node& node) = default;
    };
    Node* head;
    int max_level = 64;
    int current_level;
    int prob = 0.5;
    size_type size_;
    public:
    using iterator = unordered_map_iterator<Node>;
    using const_iterator = unordered_map_iterator<const Node>;
    skip_list(){

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

    }
    bool contains(const Key& key){

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
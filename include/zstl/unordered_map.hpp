#include<functional>
#include"zstl/unordered_map_iterator.hpp"
template<typename Key, typename Value,typename Hash = std::hash<Key>,typename Equal = std::equal_to<Key>>
class unordered_map{
    private:
    using size_type = std::size_t;
    struct Node{
        std::pair<const Key, Value> pair;
        Node* next;
        Node(const Key& key) : pair(key, Value()), next(nullptr) {}
        Node(const Key& key, const Value& value): pair(key,value), next(nullptr) {}
        Node(const Node& node) = default;
    };
    Node** buckets;
    size_type bucket_count;
    size_type size;
    float max_load_factor = 1.0;
    Hash hash;
    Equal equal;
    void swap(unordered_map& map) noexcept{
        std::swap(buckets,map.buckets);
        std::swap(bucket_count,map.bucket_count);
        std::swap(size,map.size);
        std::swap(max_load_factor,map.max_load_factor);
        std::swap(hash,map.hash);
        std::swap(equal,map.equal);
    }
    using iterator = unordered_map_iterator<Node>;
    using const_iterator = unordered_map_iterator<const Node>;
    public:
    unordered_map() : bucket_count(10), size(0) {
        buckets = new Node*[bucket_count]();
    }
    unordered_map(const unordered_map& map) : bucket_count(map.bucket_count), size(map.size) {
        buckets = new Node*[bucket_count]();
        for (size_type i = 0; i < bucket_count;i++){
            Node* next = map.buckets[i];
            while(next){
                Node* node = new Node(*next);
                buckets[i] = node;
                next = next->next;
            }
        }
    }
    unordered_map(unordered_map&& map) noexcept : buckets(map.buckets), bucket_count(map.bucket_count), size(map.size) {
        map.buckets = nullptr;
        map.bucket_count = 0;
        map.size = 0;
    }
    unordered_map& operator=(const unordered_map& map){
        if (this == &map){
            return *this;
        }
        unordered_map temp(map);
        swap(temp);
        return *this;
    }
    unordered_map& operator=(unordered_map&& map) noexcept{
        if (this == &map){
            return *this;
        }
        clear();
        delete[] buckets;
        buckets = map.buckets;
        bucket_count = map.bucket_count;
        size = map.size;
        map.buckets = nullptr;
        map.bucket_count = 0;
        map.size = 0;
    }
    ~unordered_map(){
        clear();
        delete[] buckets;
    }
    iterator begin(){
        // return iterator(buckets[0],buckets,0,bucket_count);
    }
    iterator end(){
        return iterator(nullptr,buckets,bucket_count,bucket_count);
    }
    const_iterator cbegin() const {
        
    }
    const_iterator cend() const {
        return const_iterator(nullptr,buckets,bucket_count,bucket_count);
    }
    Value& operator[](const Key& key){
        size_type index = hash(key) % bucket_count;
        Node* next = buckets[index];
        while(next){
            if (equal(next->pair.first,key)){
                return next->pair.second;
            }
            next = next->next;
        }
        if (size + 1 > max_load_factor * bucket_count){
            rehash(bucket_count * 2);
            index = hash(key) % bucket_count;
        }
        Node* node = new Node(key);
        node->next = buckets[index];
        buckets[index] = node;
        ++size;
        return node->pair.second;
    }
    void clear(){
        if (!buckets){
            return;
        }
        for(size_type i = 0; i < bucket_count;i++){
            Node* next = buckets[i];
            while(next){
                buckets[i] = next->next;
                delete next;
                next = buckets[i];
            }
        }
    }
    void rehash(size_type new_count){
        Node** temp = new Node*[new_count]();
        for(size_type i = 0; i < bucket_count; i++){
            Node* next = buckets[i];
            while(next){
                buckets[i] = next->next;
                size_type index = hash(next->pair.first) % new_count;
                next->next = temp[index];
                temp[index] = next;
                next = buckets[i];
            }
        }
        delete[] buckets;
        buckets = temp;
        bucket_count = new_count;
    }
    size_type erase(const Key& key){
        size_type index = hash(key) % bucket_count;
        Node* prev = buckets[index];
        if (!prev){
            return 0;
        }
        if (equal(prev->pair.first, key)){
            buckets[index] = prev->next;
            delete prev;
            --size;
            return 1;
        }
        Node* next = prev->next;
        while(next){
            if(equal(next->pair.first,key)){
                prev->next = next->next;
                delete next;
                --size;
                return 1;
            }
            prev = next;
            next = next->next;
        }
        return 0;
    }
};
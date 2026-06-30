#include<functional>
template<typename Key, typename Value,typename Hash = std::hash<Key>,typename Equal = std::equal_to<Key>>
class unordered_map{
    private:
    using size_type = std::size_t;
    struct Node{
        std::pair<const Key, Value> pair;
        Node* next;
        Node(const key& key) : pair(key, Value()), next(nullptr) {}
        Node(const Key& key, const Value& value): pair(key,value), next(nullptr) {}
    };
    Node** buckets;
    size_type bucket_count;
    size_type size;
    float max_load_factor = 1.0;
    Hash hash;
    Equal equal;
    public:
    unordered_map(){
        bucket_count = 10;
        buckets = new Node*[bucket_count]();
        size = 0;
    }
    unordered_map(const unordered_map& map){

    }
    unordered_map(unordered_map&& map){

    }
    unordered_map& operator=(const unordered_map& map){

    }
    unordered_map& operator=(unordered_map&& map){
        
    }
    ~unordered_map(){
        for(size_type i = 0; i < bucket_count;i++){
            Node* next = buckets[i];
            if(next){
                buckets[i] = next->next;
                delete next;
                next = buckets[i];
            }
        }
        delete[] buckets;
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
};
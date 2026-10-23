#include <iostream>
#include <unordered_map>
using namespace std;

class LRU {
private:
    struct Node {
        int key, value;
        Node* prev;
        Node* next;

        Node(int k, int v) {
            key = k;
            value = v;
            prev = next = nullptr;
        }
    };

    int capacity;
    unordered_map<int, Node*> cache;

    Node* head;
    Node* tail;

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addToFront(Node* node) {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void moveToFront(Node* node) {
        removeNode(node);
        addToFront(node);
    }

    Node* removeLRU() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

public:
    LRU(int capacity) {
        this->capacity = max(0, capacity);

        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        auto it = cache.find(key);

        if (it == cache.end()) {
            return -1;
        }

        Node* node = it->second;

        moveToFront(node);

        return node->value;
    }

    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }

        auto it = cache.find(key);

        if (it != cache.end()) {
            Node* node = it->second;
            node->value = value;
            moveToFront(node);
            return;
        }

        Node* node = new Node(key, value);
        cache[key] = node;
        addToFront(node);

        if (cache.size() > capacity) {
            Node* lru = removeLRU();

            cache.erase(lru->key);
            delete lru;
        }
    }
    
    ~LRU() {
        Node* current = head;

        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    LRU cache(2);

    cache.put(1, 25);
    cache.put(2, 50);

    cout << cache.get(1) << endl; 

    cache.put(3, 75);             

    cout << cache.get(2) << endl; 
    cout << cache.get(3) << endl; 

    return 0;
}
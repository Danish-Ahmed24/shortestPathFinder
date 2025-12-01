#ifndef SEPARATION_MINHEAP_H
#define SEPARATION_MINHEAP_H

#include <vector>
#include <unordered_map>
#include <utility>

namespace separation {

// Simple min-heap for {distance, node}
class MinHeap {
private:
    std::vector<std::pair<int,int>> heap;    // {distance,node}
    std::unordered_map<int,int> indexMap;    // node -> index
    int parent(int i) const { return (i-1)/2; }
    int leftChild(int i) const { return 2*i+1; }
    int rightChild(int i) const { return 2*i+2; }
    void heapifyUp(int i);
    void heapifyDown(int i);
    void swapNodes(int i, int j);

public:
    void push(int distance, int node);
    std::pair<int,int> top() const;
    void pop();
    bool empty() const;
    int size() const;
};

} // namespace separation

#endif // SEPARATION_MINHEAP_H

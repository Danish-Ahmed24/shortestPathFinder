#include "MinHeap.h"

namespace separation {

void MinHeap::swapNodes(int i, int j) {
    indexMap[heap[i].second] = j;
    indexMap[heap[j].second] = i;
    std::swap(heap[i], heap[j]);
}

void MinHeap::heapifyUp(int i) {
    while (i > 0 && heap[parent(i)].first > heap[i].first) {
        swapNodes(i, parent(i));
        i = parent(i);
    }
}

void MinHeap::heapifyDown(int i) {
    int minIndex = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < (int)heap.size() && heap[left].first < heap[minIndex].first) minIndex = left;
    if (right < (int)heap.size() && heap[right].first < heap[minIndex].first) minIndex = right;
    if (minIndex != i) {
        swapNodes(i, minIndex);
        heapifyDown(minIndex);
    }
}

void MinHeap::push(int distance, int node) {
    auto it = indexMap.find(node);
    if (it != indexMap.end()) {
        int idx = it->second;
        if (distance < heap[idx].first) {
            heap[idx].first = distance;
            heapifyUp(idx);
        }
        return;
    }

    heap.push_back({distance, node});
    int idx = (int)heap.size() - 1;
    indexMap[node] = idx;
    heapifyUp(idx);
}

std::pair<int,int> MinHeap::top() const {
    if (heap.empty()) return {-1,-1};
    return heap[0];
}

void MinHeap::pop() {
    if (heap.empty()) return;
    indexMap.erase(heap[0].second);
    if (heap.size() == 1) { heap.pop_back(); return; }
    heap[0] = heap.back();
    heap.pop_back();
    indexMap[heap[0].second] = 0;
    heapifyDown(0);
}

bool MinHeap::empty() const { return heap.empty(); }
int MinHeap::size() const { return (int)heap.size(); }

} // namespace separation

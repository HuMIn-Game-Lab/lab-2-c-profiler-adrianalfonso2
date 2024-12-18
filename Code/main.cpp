#include "Profiler.h"
#include <thread>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
Profiler *globalProfiler = new Profiler();

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
int inefficientPartition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];  
    int i = low + 1;
    for (int j = low + 1; j <= high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[low], arr[i - 1]);
    return i - 1;
}
void quickSortEfficient(vector<int>& arr, int low, int high) {
    while (low < high) {
        int pivotIndex = partition(arr, low, high);
        if (pivotIndex - low < high - pivotIndex) {
            quickSortEfficient(arr, low, pivotIndex - 1);
            low = pivotIndex + 1;
        } else {
            quickSortEfficient(arr, pivotIndex + 1, high);
            high = pivotIndex - 1;
        }
    }
}
void quickSortInefficient(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = inefficientPartition(arr, low, high); 
        if (pivotIndex - low > high - pivotIndex) {
            quickSortInefficient(arr, low, pivotIndex - 1);
            quickSortInefficient(arr, pivotIndex + 1, high);
        } else {
            quickSortInefficient(arr, pivotIndex + 1, high);
            quickSortInefficient(arr, low, pivotIndex - 1);
        }
        for (int i = low; i <= high; ++i) {
            arr[i] = arr[i];  
        }
    }
}
void efficientQuickSort() {
    vector<int> randomValues;
    for (int i = 0; i < 500000; i++) {  
        randomValues.push_back(rand() % 1000000);
    }
    startProfileSection("EfficientQuickSort");
    quickSortEfficient(randomValues, 0, randomValues.size() - 1);
    endProfileSection("EfficientQuickSort");
}
void inefficientQuickSort() {
    vector<int> randomValues;
    for (int i = 0; i < 500000; i++) {  
        randomValues.push_back(rand() % 1000000);
    }
    startProfileSection("InefficientQuickSort");
    quickSortInefficient(randomValues, 0, randomValues.size() - 1);
    endProfileSection("InefficientQuickSort");
}

void depthFirstSearchHelper(int vertex,
 std::vector<bool>& visited,
  const std::vector<std::vector<int>>& adjacencyList) {
    visited[vertex] = true;
    for (int adjacentVertex : adjacencyList[vertex]) {
        startProfileSection("DFSHelper");
        if (!visited[adjacentVertex]) {
            for (int i = 0; i < 10000; ++i){
                int dummy = i * i;
            }
            depthFirstSearchHelper(adjacentVertex, visited, adjacencyList);
        }
        endProfileSection("DFSHelper");
    }
}
void depthFirstSearch(int startVertex, 
const std::vector<std::vector<int>>& adjacencyList, 
int vertexCount) {vector<bool> visited(vertexCount, false);
    depthFirstSearchHelper(startVertex, visited, adjacencyList);
}
void dfsTest() {
    int vertices = 100;
    std::vector<std::vector<int>> adjacencyList(vertices);
    adjacencyList[0].push_back(1);
    adjacencyList[0].push_back(4);
    adjacencyList[1].push_back(0);
    adjacencyList[1].push_back(2);
    adjacencyList[1].push_back(4);
    adjacencyList[2].push_back(1);
    adjacencyList[2].push_back(3);
    adjacencyList[3].push_back(1);
    adjacencyList[3].push_back(4);
    adjacencyList[4].push_back(0);
    adjacencyList[4].push_back(3);
    startProfileSection("DFSTest");
    depthFirstSearch(0, adjacencyList, vertices);
    endProfileSection("DFSTest");
}
void sleepTest() {
    for (int i = 0; i < 100; i++) {
        startProfileSection("ShortSleepTest");
        startProfileSection("LongSleepTest");
        this_thread::sleep_for(chrono::milliseconds(100));
        endProfileSection("ShortSleepTest");
        this_thread::sleep_for(chrono::milliseconds(100));
        endProfileSection("LongSleepTest");
    }
}
int main() {
    for (int i = 0; i < 1000; i++) {
        efficientQuickSort();
        inefficientQuickSort();
    }
    dfsTest();
    sleepTest();
    displayProfilerStats();
    exportProfilerStatsCSV("ProfilerStats.csv");
    exportProfilerStatsJSON("ProfilerStats.json");
    return 0;
}

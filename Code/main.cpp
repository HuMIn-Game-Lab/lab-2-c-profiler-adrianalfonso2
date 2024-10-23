#include "Profiler.h"
#include <thread>
#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;
Profiler *globalProfiler = new Profiler();
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;      
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std ::swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void quickSortEfficient(vector<int>& arr, int low, int high) {
    while (low < high) {
        int pivotIndex = partition(arr, low, high);
        // Recur on the smaller partition first to avoid deep recursion stack
        if (pivotIndex - low < high - pivotIndex) {
            quickSortEfficient(arr, low, pivotIndex - 1);
            low = pivotIndex + 1;
        } else {
            quickSortEfficient(arr, pivotIndex + 1, high);
            high = pivotIndex - 1;
        }
    }
}
// First test: Efficient quicksort
void efficientQuickSort() {
    vector<int> randomValues;
    for (int i = 0; i < 1000; i++) {
        randomValues.push_back(rand() % 1000);
    }
    startProfileSection("EfficientQuickSort");
    quickSortEfficient(randomValues, 0, randomValues.size() - 1);
    endProfileSection("EfficientQuickSort");
}
// Inefficient quicksort: Using recursion on both halves of the partitioned array without optimizations
void quickSortInefficient(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSortInefficient(arr, low, pivotIndex - 1);  
        quickSortInefficient(arr, pivotIndex + 1, high);
    }
}
// Second test: Inefficient quicksort
void inefficientQuickSort() {
    vector<int> randomValues;
    // Populate vector with random numbers
    for (int i = 0; i < 1000; i++) {
        randomValues.push_back(rand() % 1000);
    }
    // Perform inefficient quicksort
    startProfileSection("InefficientQuickSort");
    quickSortInefficient(randomValues, 0, randomValues.size() - 1);
    endProfileSection("InefficientQuickSort");
}
// Test for Depth-First Search (DFS)
void depthFirstSearchHelper(int vertex, vector<bool>& visited, const vector<int> adjacencyList[]) {
    visited[vertex] = true;

    for (int adjacentVertex : adjacencyList[vertex]) {
        startProfileSection("DFSHelper");
        if (!visited[adjacentVertex]) {
            depthFirstSearchHelper(adjacentVertex, visited, adjacencyList);
        }
        endProfileSection("DFSHelper");
    }
}
// DFS traversal
void depthFirstSearch(int startVertex, const vector<int> adjacencyList[], int vertexCount) {
    vector<bool> visited(vertexCount, false);
    depthFirstSearchHelper(startVertex, visited, adjacencyList);
}
void dfsTest() {
    int vertices = 5;
 // Create adjacency list for graph representation
    vector<int> adjacencyList[vertices];
    adjacencyList[0].push_back(1);
    adjacencyList[0].push_back(4);
    adjacencyList[1].push_back(0);
    adjacencyList[1].push_back(2);
    adjacencyList[1].push_back(3);
    adjacencyList[1].push_back(4);
    adjacencyList[2].push_back(1);
    adjacencyList[2].push_back(3);
    adjacencyList[3].push_back(1);
    adjacencyList[3].push_back(2);
    adjacencyList[3].push_back(4);
    adjacencyList[4].push_back(0);
    adjacencyList[4].push_back(1);
    adjacencyList[4].push_back(3);
    startProfileSection("DFSTest");
    depthFirstSearch(0, adjacencyList, vertices);  // Start DFS from vertex 0
    endProfileSection("DFSTest");
}
// Test with sleeping to simulate time delay
void sleepTest() {
    for (int i = 0; i < 10; i++) {
        startProfileSection("ShortSleepTest");
        startProfileSection("LongSleepTest");
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate short delay
        endProfileSection("ShortSleepTest");
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate long delay
        endProfileSection("LongSleepTest");
    }
}
int main() {
    for (int i = 0; i < 1000; i++) {
        efficientQuickSort();   // Efficient quicksort
        inefficientQuickSort(); // Inefficient quicksort
    }
    // test3(); // 1 second test
    // test4(); // Interweaving test
    // test5(); // DFS test
    // sleepTest(); // Simulate sleep with profiling
    // Print profiler statistics to the console and to CSV/JSON files
    displayProfilerStats();
    exportProfilerStatsCSV("ProfilerStats.csv");
    exportProfilerStatsJSON("ProfilerStats.json");
    return 0;
}
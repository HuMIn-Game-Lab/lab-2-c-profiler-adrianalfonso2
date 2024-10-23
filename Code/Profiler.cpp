#include "Profiler.h"
#include "program_time.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include "json.h"

// Using standard namespaces and JSON library.
using namespace std;
using namespace nlohmann;

// Global profiler pointer
Profiler* Profiler::globalProfilerInstance = nullptr;

// Define macros for easy entry/exit of profiler sections.
#define endProfileSection(section) globalProfilerInstance->ExitSection(section, __FILE__, __FUNCTION__, __LINE__)
#define startProfileSection(section) globalProfilerInstance->EnterSection(section)
#define displayProfilerStats() globalProfilerInstance->printStats()
#define exportProfilerStatsCSV(fileName) globalProfilerInstance->printStatsToCSV(fileName)
#define exportProfilerStatsJSON(fileName) globalProfilerInstance->printStatsToJSON(fileName)

// Destructor for TimeRecordStart, currently empty.
RecordStart::~RecordStart() {}

// Constructor for TimeRecordStop, records section name and elapsed time.
RecordStop::RecordStop(const char* section, double stopTimeInSeconds) {
    this->section = section;
    this->elapsedTime = stopTimeInSeconds;
}

// Extended constructor with more details: line, file, and function names.
RecordStop::RecordStop(const char* section, double timeElapsed, int line, const char* file, const char* function) {
    this->section = section;
    this->elapsedTime = timeElapsed;
    this->line = line;
    this->file = file;
    this->function = function;
}

// Destructor for TimeRecordStop.
RecordStop::~RecordStop() {}

// Constructor for ProfilerStats that initializes with section name and function details.
ProfilerStats::ProfilerStats(const char* section, const char* fileName, const char* funcName, int lineNum) {
    this->section = section;
    callCount = 1;
    totalTime = 0;
    minDuration = DBL_MAX; 
    maxDuration = 0;
    avgDuration = 0;
    this->fileName = fileName;
    this->functionName = funcName;
    this->lineNumber = lineNum;
}

// Constructor for Profiler.
Profiler::Profiler() {
    globalProfilerInstance = this; // Set global profiler instance to this object.
    startTimes.reserve(100);       // Preallocate vector for start times.
    elapsedTimes.reserve(1000000); // Preallocate vector for elapsed times.
}

// Destructor for Profiler.
Profiler::~Profiler() {}

// Function to print profiler statistics to a CSV file.
void Profiler::printStatsToCSV(const char* fileName) {
    ofstream csvFile("Data/ProfilerStats.csv"); // Create output CSV file.
    
    if (csvFile.is_open()) {
        csvFile << "Section, Count, Total Time, Min Time, Max Time, Avg Time, File Name, Function Name, Line Number\n";
        for (auto& stat : stats) {
            csvFile << stat.first << ", " << stat.second->callCount << ", " 
                    << stat.second->totalTime << ", " << stat.second->minDuration << ", "
                    << stat.second->maxDuration << ", " << stat.second->totalTime / stat.second->callCount << ", "
                    << stat.second->fileName << ", " << stat.second->functionName << ", " 
                    << stat.second->lineNumber << "\n";
        }
        csvFile.close();
    } else {
        cout << "Unable to open the CSV file.";
    }
}

// Function to print profiler statistics to a JSON file.
void Profiler::printStatsToJSON(const char* fileName) {
    ordered_json jsonStats;

    for (auto& stat : stats) {
        ordered_json sectionJson;
        sectionJson["Section"] = stat.first;
        sectionJson["Call Count"] = stat.second->callCount;
        sectionJson["Total Time"] = stat.second->totalTime;
        sectionJson["Min Time"] = stat.second->minDuration;
        sectionJson["Max Time"] = stat.second->maxDuration;
        sectionJson["Avg Time"] = stat.second->totalTime / stat.second->callCount;
        sectionJson["File Name"] = stat.second->fileName;
        sectionJson["Function Name"] = stat.second->functionName;
        sectionJson["Line Number"] = stat.second->lineNumber;

        jsonStats.push_back(sectionJson);
    }

    ofstream jsonFile("Data/ProfilerStats.json"); // Output to JSON file.
    jsonFile << jsonStats.dump(4);                // Pretty print with indent of 4.
    jsonFile.close();
}

// Getter for start times vector.
vector<RecordStart> Profiler::getStartTimes() {
    return startTimes;
}

// Getter for elapsed times vector.
vector<RecordStop> Profiler::getElapsedTimes() {
    return elapsedTimes;
}

// Getter for statistics map.
map<const char*, ProfilerStats*> Profiler::getStats() {
    return stats;
}
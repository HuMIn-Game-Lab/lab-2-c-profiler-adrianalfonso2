#include "Profiler.h"
#include <cfloat>
#include <cstdlib>
#include <vector>
#include <map>
#include "program_time.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "json.h"
using namespace std;
using namespace nlohmann;

Profiler* Profiler::globalProfilerInstance = nullptr;
RecordStart::~RecordStart() {}
RecordStop::RecordStop(const char* 
section, 
double stopTimeInSeconds) 
{
    this->section = section;
    this->elapsedTime = stopTimeInSeconds;
}

RecordStop::RecordStop(const char* section, 
double timeElapsed, 
int line, 
const char* file, 
const char* function) {
    this->section = section;
    this->elapsedTime = timeElapsed;
    this->line = line;
    this->file = file;
    this->function = function;
}
RecordStop::~RecordStop() {}
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
Profiler::Profiler() {
    globalProfilerInstance = this;
    startTimes.reserve(100);
    elapsedTimes.reserve(1000000);
}
void Profiler::EnterSection(const char* section) {
    double startTime = RetireveTimeInSecond();
    startTimes.push_back(RecordStart(section, startTime));
}
void Profiler::ExitSection(const char* section,
 const char* file, 
 const char* function, 
 int line) {
    double stopTime = RetireveTimeInSecond();
    double elapsedTime = stopTime - startTimes.back().startSeconds;
    elapsedTimes.push_back(RecordStop(section, 
    elapsedTime, line,
    file, function));
    startTimes.pop_back();
    if (stats.find(section) == stats.end()) {
        stats[section] = new ProfilerStats(section, 
        file, function, 
        line);
    } else {
        ProfilerStats* stat = stats[section];
        stat->callCount++;
        stat->totalTime += elapsedTime;
        stat->minDuration = min(stat->minDuration, elapsedTime);
        stat->maxDuration = max(stat->maxDuration, elapsedTime);
    }
}
Profiler::~Profiler() {}
void Profiler::printStatsToCSV(const char* fileName) {
    ofstream csvFile(fileName);
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
void Profiler::printStats() {
    for (auto& stat : stats) {
        cout << "Section: " << stat.first << endl;
        cout << "Call Count: " << stat.second->callCount << endl;
        cout << "Total Time: " << stat.second->totalTime << endl;
        cout << "Min Time: " << stat.second->minDuration << endl;
        cout << "Max Time: " << stat.second->maxDuration << endl;
        cout << "Avg Time: " << stat.second->totalTime / stat.second->callCount << endl;
        cout << "File Name: " << stat.second->fileName << endl;
        cout << "Function Name: " << stat.second->functionName << endl;
        cout << "Line Number: " << stat.second->lineNumber << endl;
        cout << endl;
    }
}
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
    ofstream jsonFile(fileName);
    jsonFile << jsonStats.dump(4);
    jsonFile.close();
}
vector<RecordStart> Profiler::getStartTimes() {
    return startTimes;
}
vector<RecordStop> Profiler::getElapsedTimes() {
    return elapsedTimes;
}
map<const char*, ProfilerStats*> Profiler::getStats() {
    return stats;
}

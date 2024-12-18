#include <mutex>
#include <stack>
#include <map>
#include <cfloat>
#pragma once 
#include <vector>
#define endProfileSection(section) Profiler::globalProfilerInstance->ExitSection(section, __FILE__, __FUNCTION__, __LINE__)
#define startProfileSection(section) Profiler::globalProfilerInstance->EnterSection(section)
#define displayProfilerStats() Profiler::globalProfilerInstance->printStats()
#define exportProfilerStatsCSV(fileName) Profiler::globalProfilerInstance->printStatsToCSV(fileName)
#define exportProfilerStatsJSON(fileName) Profiler::globalProfilerInstance->printStatsToJSON(fileName)

using namespace std;
class RecordStart {
public:
    RecordStart(const char* section,
     double startSeconds)
        : section(section),
         startSeconds(startSeconds) {} // Constructor initializes section name and start time.
    ~RecordStart(); // Destructor.
    const char* section;  // Name of the section.
    double startSeconds;  // Time when the section starts.
};
// TimeRecordStop class that records the stop time and elapsed time of a section.
class RecordStop {
public:
    RecordStop(const char* section, 
    double stopSeconds);
    RecordStop(const char* section, 
    double elapsedSeconds, int line, const char* file,
     const char* function);
    ~RecordStop(); 
    const char* section;   // Name of the section.
    double elapsedTime;    // Elapsed time in seconds.
    int line;              // Line number where the section was timed.
    const char* file;      // File name where the section was timed.
    const char* function;  // Function name where the section was timed.
};

class ProfilerStats {
public:
    ProfilerStats(const char* section, 
    const char* fileName, 
    const char* funcName, 
    int lineNumber): 
      section(section), 
      callCount(1), 
      totalTime(0), 
      minDuration(DBL_MAX), 
      maxDuration(0), 
      avgDuration(0), 
      fileName(fileName), 
      functionName(funcName), 
      lineNumber(lineNumber) {}
    ~ProfilerStats(); 
    const char* section;   // Section name.
    int callCount;         // Number of times the section has been called.
    double totalTime;      // Total time accumulated for the section.
    double minDuration;    // Minimum duration of any call to this section.
    double maxDuration;    // Maximum duration of any call to this section.
    double avgDuration;    // Average duration of calls to this section.
    const char* fileName;  // Name of the file where the section is timed.
    const char* functionName;  // Name of the function where the section is timed.
    int lineNumber; 
private:
    std::mutex profilerMutex; // Mutex to protect the statistics.
};
class Profiler {
public:
    Profiler();  
    ~Profiler(); 
    void EnterSection(const char* section);
    void ExitSection(const char* section, const char* file, const char* function, int line);
    void printStats();
    void printStatsToCSV(const char* fileName);
    void printStatsToJSON(const char* fileName);
    vector<RecordStart> getStartTimes();
    vector<RecordStop> getElapsedTimes();
    map<const char*, ProfilerStats*> getStats();
    static Profiler* globalProfilerInstance;

private:
    void ReportSectionTime(const char* section, double elapsedSeconds);
    void ReportSectionTime(const char* section, double elapsedSeconds, int line, const char* file, const char* function);
    vector<RecordStart> startTimes;     
    vector<RecordStop> elapsedTimes;     
    std::map<const char*, ProfilerStats*> stats;
    std::stack<std::string> sectionStack;
    std::mutex profilerMutex;
};
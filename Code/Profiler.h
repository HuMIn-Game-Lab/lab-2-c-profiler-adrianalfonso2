#include <map>
#pragma once 
#include <vector>
using namespace std;
#define endProfileSection(section) Profiler::globalProfilerInstance->ExitSection(section, __FILE__, __FUNCTION__, __LINE__)
#define startProfileSection(section) Profiler::globalProfilerInstance->EnterSection(section)
#define displayProfilerStats() Profiler::globalProfilerInstance->printStats()
#define exportProfilerStatsCSV(fileName) Profiler::globalProfilerInstance->printStatsToCSV(fileName)
#define exportProfilerStatsJSON(fileName) Profiler::globalProfilerInstance->printStatsToJSON(fileName)

class RecordStart {
public:
    RecordStart(const char* section, double startSeconds)
        : section(section), startSeconds(startSeconds) {} // Constructor initializes section name and start time.
    ~RecordStart(); // Destructor.

    const char* section;  // Name of the section.
    double startSeconds;  // Time when the section starts.
};

// TimeRecordStop class that records the stop time and elapsed time of a section.
class RecordStop {
public:
    RecordStop(const char* section, double stopSeconds);
    RecordStop(const char* section, double elapsedSeconds, int line, const char* file, const char* function);
    ~RecordStop(); // Destructor.

    const char* section;   // Section name.
    double elapsedTime;    // Elapsed time in seconds.
    int line;              // Line number where the section was timed.
    const char* file;      // File name where the section was timed.
    const char* function;  // Function name where the section was timed.
};

// ProfilerStats class stores statistics related to a particular section.
class ProfilerStats {
public:
    ProfilerStats(const char* section, const char* fileName, const char* funcName, int lineNumber);
    ~ProfilerStats(); // Destructor.

    const char* section;   // Section name.
    int callCount;         // Number of times the section has been called.
    double totalTime;      // Total time accumulated for the section.
    double minDuration;    // Minimum duration of any call to this section.
    double maxDuration;    // Maximum duration of any call to this section.
    double avgDuration;    // Average duration of calls to this section.
    const char* fileName;  // Name of the file where the section is timed.
    const char* functionName;  // Name of the function where the section is timed.
    int lineNumber;        // Line number where the section was timed.
};

// Profiler class responsible for tracking the performance of different code sections.
class Profiler {
public:
    Profiler();  // Constructor.
    ~Profiler(); // Destructor.

    // Functions to enter and exit sections for profiling.
    void EnterSection(const char* section);
    void ExitSection(const char* section, const char* file, const char* function, int line);

    // Functions to print profiling statistics.
    void printStats();
    void printStatsToCSV(const char* fileName);
    void printStatsToJSON(const char* fileName);

    // Accessors for start and elapsed times.
    vector<RecordStart> getStartTimes();
    vector<RecordStop> getElapsedTimes();
    map<const char*, ProfilerStats*> getStats();

    // Static instance of the global profiler.
    static Profiler* globalProfilerInstance;

private:
    // Functions to report time spent in sections.
    void ReportSectionTime(const char* section, double elapsedSeconds);
    void ReportSectionTime(const char* section, double elapsedSeconds, int line, const char* file, const char* function);

    // Data structures to store timing information and statistics.
    map<const char*, ProfilerStats*> stats;  // Stores the statistics for each section.
    vector<RecordStart> startTimes;      // Records the start times of sections.
    vector<RecordStop> elapsedTimes;     // Records the stop and elapsed times of sections.
};
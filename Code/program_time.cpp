#include "program_time.h"
#include <chrono>
using namespace std;
// Function to retrieve the current time in seconds
double RetireveTimeInSecond()
{
    static auto start = chrono::high_resolution_clock::now();
    auto now = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::duration<double>>(now-start).count();
}
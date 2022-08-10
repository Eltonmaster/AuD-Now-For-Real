#ifndef _TIMER_H
#define _TIMER_H
/**
 * Simple implementation of timers for cpu / wall-clock time in seconds.
 *
 * @file
 */

#include <ostream> // ostream operator<<
#ifdef _WIN32 // Windows
    #include <Windows.h> // GetProcessTime: CPU time
#else // WSL, Linux, macOS
    #include <ctime> // clock: CPU time
#endif
#include <chrono> // system_clock: wall-clock time

/**
 * Stores CPU and wall-clock time.
 */
struct Time {
    double cpu;
    double wallclock;
};
std::ostream& operator<<(std::ostream& out, const Time& t) {
    return out << "cpu:        " << t.cpu << "s" << std::endl
               << "wall-clock: " << t.wallclock << "s" << std::endl;
}

/**
 * Allows to measure CPU time between calling
 * start() and stop() method in seconds.
 * See http://www.cplusplus.com/reference/ctime/clock/ and
 * https://docs.microsoft.com/de-de/windows/win32/api/processthreadsapi/nf-processthreadsapi-getprocesstimes.
 */
class CPUTimer {
private:
    #ifdef _WIN32
        FILETIME userTimeStart;
    #else
        clock_t userTimeStart;
    #endif
    double time;
public:
    void start(void) {
        #ifdef _WIN32
            FILETIME creationTime,exitTime,kernelTime;
            if (GetProcessTimes(GetCurrentProcess(),&creationTime,&exitTime,
                &kernelTime,&userTimeStart) == 0){
                    userTimeStart = {0,0};
            }
        #else
            userTimeStart = clock();
        #endif
    }
    double stop(void) {
        #ifdef _WIN32
            FILETIME creationTime,exitTime,kernelTime,userTime;
            if (GetProcessTimes(GetCurrentProcess(),&creationTime,&exitTime,
                &kernelTime,&userTime) == 0){
                    userTime = {0,0};
            }
            time = (double)(userTime.dwLowDateTime |
                ((unsigned long long)userTime.dwHighDateTime << 32)) * 0.0000001;
            time -= (double)(userTimeStart.dwLowDateTime |
                ((unsigned long long)userTimeStart.dwHighDateTime << 32)) * 0.0000001;
        #else
            time = (double)(clock() - userTimeStart) / CLOCKS_PER_SEC;
        #endif
        return time;
    }
    double getTime(void) {
        return time;
    }
};

/**
 * Allows to measure wall-clock time between calling
 * start() and stop() method in seconds.
 * See http://www.cplusplus.com/reference/chrono/system_clock/.
 */
class WallClockTimer {
private:
    std::chrono::system_clock::time_point s;
    std::chrono::duration<double> time;
public:
    void start(void) {
        s = std::chrono::system_clock::now();
    }
    double stop(void) {
        time = (std::chrono::system_clock::now() - s);
        return getTime();
    }
    double getTime(void) {
        return time.count();
    }
};

/**
 * Allows to measure both cpu and wall-clock time between calling
 * start() and stop() method in seconds.
 */
class Timer {
private:
    CPUTimer cpu;
    WallClockTimer wc;
public:
    void start(void) {
        wc.start();
        cpu.start();
    }
    Time stop(void) {
        cpu.stop();
        wc.stop();
        return getTime();
    }
    Time getTime(void) {
        return { cpu.getTime(), wc.getTime() };
    }
    double getCPUTime(void) {
        return cpu.getTime();
    }
    double getWallClockTime(void) {
        return wc.getTime();
    }
};

#endif // _TIMER_H
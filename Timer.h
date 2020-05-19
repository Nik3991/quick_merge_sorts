#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

class Timer
{
public:
    enum time {ms, micros, nanos};
    Timer(time _time)
    {
        m_Time = _time;
        m_Start = high_resolution_clock::now();
    }

    ~Timer()
    {
        m_End = high_resolution_clock::now();
        switch (m_Time)
        {
            case ms:     cout << "time = " << duration_cast<milliseconds>(m_End - m_Start).count() << " ms"    ; break;
            case micros: cout << "time = " << duration_cast<microseconds>(m_End - m_Start).count() << " micros"; break;
            case nanos:  cout << "time = " << duration_cast<nanoseconds>(m_End - m_Start).count()  << " nanos" ; break;
            default:     cout << " incorrect time resolution !"; break;
        }
        cout << endl;
    }
private:
    time_point<system_clock, nanoseconds> m_Start;
    time_point<system_clock, nanoseconds> m_End;
    time m_Time {ms};
};


#endif // TIMER_H

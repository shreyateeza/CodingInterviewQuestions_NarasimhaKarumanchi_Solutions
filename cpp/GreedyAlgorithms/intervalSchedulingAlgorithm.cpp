#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TimeStamp {
private:
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;
public:
    TimeStamp(int Year,int Month,int Day,int Hour,int Minute,int Second);
    unsigned long ToTimeStamp();
    friend std::ostream& operator<<(std::ostream& os, const TimeStamp& time);
};

TimeStamp::TimeStamp(int Year, int Month, int Day, int Hour, int Minute, int Second)
{
    this->Year = Year;
    this->Month = Month;
    this->Day = Day;
    this->Hour = Hour;
    this->Minute = Minute;
    this->Second = Second;
}

unsigned long TimeStamp::ToTimeStamp()
{
    const int BASE_YEAR = 1900;
    unsigned long  timestamp = ((Year - BASE_YEAR) * 31556926) + (Month * 2629743) + (Day * 86400) + (Hour * 3600) + (Minute * 60) + Second;
    return timestamp;
}

ostream& operator<<(std::ostream& os, const TimeStamp& time)
{
    os<< time.Year << "-" << time.Month << "-" << time.Day << " " << time.Hour << ":" << time.Minute << ":" << time.Second;
    return os;
}

struct JOB
{
    string job;
    TimeStamp start;
    TimeStamp stop;
};

class JOBS
{
private:
    vector<JOB>* jobs;

public:
    JOBS();
    void Insert(JOB job);
    void SortByStop();
    void PrintJob();
    vector<JOB> interval_scheduling();
    ~JOBS();
};

JOBS::JOBS()
{
    jobs = new vector<JOB>();
}

JOBS::~JOBS()
{
    delete jobs;
}

void JOBS::Insert(JOB job)
{
    jobs->push_back(job);
}

void JOBS::SortByStop()
{
    std::sort(jobs->begin(), jobs->end(), [](JOB& j1, JOB& j2) {
        return (j1.stop.ToTimeStamp() < j2.stop.ToTimeStamp());
        });
}

vector<JOB> JOBS::interval_scheduling()
{
    vector<JOB> ans;
    TimeStamp last_stop = jobs->front().start;

    for (vector<JOB>::iterator it = jobs->begin(); it != jobs->end(); it++)
    {
        if ((*it).start.ToTimeStamp() >= last_stop.ToTimeStamp())
        {
            ans.push_back(*it);
            last_stop = (*it).stop;
        }
    }
    return ans;
}

void JOBS::PrintJob()
{
    for (vector<JOB>::iterator it = jobs->begin(); it != jobs->end(); it++)
    {
        cout << (*it).job <<" "  << (*it).start << " " << (*it).stop << endl;
    }
}

int main()
{
    JOBS* jobs = new JOBS();

    jobs->Insert(JOB{ "A",TimeStamp(2022,12,10,9,0,0),TimeStamp(2022,12,10,10,0,0)});
    jobs->Insert(JOB{ "B",TimeStamp(2022,12,10,9,30,0),TimeStamp(2022,12,10,10,30,0) });
    jobs->Insert(JOB{ "C",TimeStamp(2022,12,10,10,0,0),TimeStamp(2022,12,10,11,0,0) });
    jobs->Insert(JOB{ "D",TimeStamp(2022,12,10,11,0,0),TimeStamp(2022,12,10,12,30,0) });
    jobs->Insert(JOB{ "E",TimeStamp(2022,12,10,10,30,0),TimeStamp(2022,12,10,13,0,0) });
    jobs->Insert(JOB{ "F",TimeStamp(2022,12,10,12,30,0),TimeStamp(2022,12,10,14,0,0) });
    jobs->Insert(JOB{ "G",TimeStamp(2022,12,10,13,30,0),TimeStamp(2022,12,10,15,0,0) });
    jobs->Insert(JOB{ "H",TimeStamp(2022,12,10,14,0,0),TimeStamp(2022,12,10,15,30,0) });
    jobs->Insert(JOB{ "I",TimeStamp(2022,12,10,15,30,0),TimeStamp(2022,12,10,17,0,0) });
    jobs->Insert(JOB{ "J",TimeStamp(2022,12,10,15,0,0),TimeStamp(2022,12,10,16,30,0) });
    
    jobs->SortByStop();

    vector<JOB> ans = jobs->interval_scheduling();
    
    cout << "JOB      START                STOP" << endl;
    for (auto j : ans) 
    {
        cout << j.job << "   " << j.start << "   " << j.stop << endl;
    }
}
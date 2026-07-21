#ifndef PROCESS_H
#define PROCESS_H

#include <string>
using namespace std;

// struct to store details of a process
struct Process {
    int pid;
    string name;
    int at;     // arrival time
    int bt;     // burst time
    int rt;     // remaining time (only used in round robin)
    int st;     // start time
    int ct;     // completion time
    int wt;     // waiting time
    int tat;    // turnaround time
    bool done;
    int priority;
};

#endif

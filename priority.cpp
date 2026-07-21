#include <iostream>
#include <vector>
#include "priority.h"
#include "result.h"
using namespace std;

void saveToFile(string algorithmName, vector<Process> p, float avgWT, float avgTAT);

Result priorityScheduling(vector<Process> p) {
    int n = p.size();
    int time = 0;
    int completed = 0;
    int totalBurst = 0;

    vector<bool> done(n, false);

    cout << "\n--- Priority Scheduling (Non-Preemptive) ---" << endl;
    cout << "\nGantt Chart:" << endl;

    while (completed < n) {

        int idx = -1;
        int minPriority = 9999;

        // SJF mein bt compare karte the
        // yahan priority compare kar rahe hain
        for (int i = 0; i < n; i++) {
            if (done[i] == false && p[i].at <= time) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        // koi process available nahi — cpu idle
        if (idx == -1) {
            time = time + 1;
            continue;
        }

        cout << "| " << p[idx].name << " ";

        p[idx].st  = time;
        p[idx].ct  = time + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        totalBurst += p[idx].bt;

        done[idx]  = true;
        completed  = completed + 1;
        time       = p[idx].ct;
    }

    cout << "|" << endl;

    cout << "\nPID\tAT\tBT\tPRI\tCT\tWT\tTAT" << endl;

    int totalWT = 0;
    int totalTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].priority << "\t"
             << p[i].ct << "\t" << p[i].wt << "\t" << p[i].tat << endl;

        totalWT  = totalWT  + p[i].wt;
        totalTAT = totalTAT + p[i].tat;
    }

    float avgWT  = (float)totalWT  / n;
    float avgTAT = (float)totalTAT / n;
    float cpu = (float)totalBurst / time * 100;

    cout << "\nAverage Waiting Time = " << avgWT << endl;
    cout << "Average Turnaround Time = " << avgTAT << endl;
    cout << "CPU Utilization = " << cpu << "%" << endl;
    float throughput = (float)n / time;
    cout << "Throughput = " << throughput << endl;
    saveToFile("Priority Scheduling", p, avgWT, avgTAT);
    Result r4;
    r4.algorithm = "Priority Scheduling";
    r4.avgWT = avgWT;
    r4.avgTAT = avgTAT;
    r4.cpuUtilization = cpu;
    r4.throughput = throughput;
    return r4;
}
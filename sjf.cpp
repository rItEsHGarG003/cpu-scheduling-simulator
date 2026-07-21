#include <iostream>
#include <vector>
#include "sjf.h"
#include "result.h"
using namespace std;

void saveToFile(string algorithmName, vector<Process> p, float avgWT, float avgTAT);

Result sjf(vector<Process> p) {
    int n = p.size();
    int time = 0;
    int completed = 0;
    int totalBurst = 0;

    vector<bool> done(n, false);

    cout << "\n--- SJF Scheduling (Non-Preemptive) ---" << endl;
    cout << "\nGantt Chart:" << endl;

    while (completed < n) {

        int idx = -1;
        int minBurst = 9999;

        // find the process with shortest burst time
        // among the ones that have arrived
        for (int i = 0; i < n; i++) {
            if (done[i] == false && p[i].at <= time) {
                if (p[i].bt < minBurst) {
                    minBurst = p[i].bt;
                    idx = i;
                }
            }
        }

        // no process has arrived yet, so cpu is idle
        if (idx == -1) {
            time = time + 1;
            continue;
        }

        cout << "| " << p[idx].name << " ";

        p[idx].st = time;
        p[idx].ct = time + p[idx].bt;
        time = p[idx].ct;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        totalBurst += p[idx].bt;

        done[idx] = true;
        completed += 1;
    }

    cout << "|" << endl;

    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT" << endl;

    int totalWT = 0;
    int totalTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].wt << "\t" << p[i].tat << endl;

        totalWT = totalWT + p[i].wt;
        totalTAT = totalTAT + p[i].tat;
    }

    float avgWT = (float)totalWT / n;
    float avgTAT = (float)totalTAT / n;
    float cpu = (float)totalBurst / time * 100;

    cout << "\nAverage Waiting Time = " << avgWT << endl;
    cout << "Average Turnaround Time = " << avgTAT << endl;
    cout<<"CPU Utilization = "<<cpu<<"%"<<endl;
    float throughput=(float)n/time;
    cout<<"Throughput = "<<throughput<<endl;
    saveToFile("SJF Scheduling", p, avgWT, avgTAT);
    Result r2;
    r2.algorithm = "SJF Scheduling";
    r2.avgWT = avgWT;
    r2.avgTAT = avgTAT; 
    r2.cpuUtilization = cpu;
    r2.throughput = throughput;
    return r2;
}

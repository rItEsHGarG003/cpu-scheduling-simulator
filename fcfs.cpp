#include <iostream>
#include <vector>
#include "fcfs.h"
#include "result.h"
using namespace std;

void saveToFile(string algorithmName, vector<Process> p, float avgWT, float avgTAT);

Result fcfs(vector<Process> p) {
    int n = p.size();

    // sort processes according to arrival time
    // using simple bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int time = 0;
    int totalBurst = 0;

    cout << "\n--- FCFS Scheduling ---" << endl;
    cout << "\nGantt Chart:" << endl;

    for (int i = 0; i < n; i++) {
        // if cpu is free before this process arrives
        if(time < p[i].at) {
            cout << " | Idle | " << p[i].at;
            time = p[i].at;
        }

        p[i].st = time;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalBurst += p[i].bt;

        time = p[i].ct;

        cout << "| " << p[i].name << " ";
    }
    cout << "|" << endl;

    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT" << endl;

    int totalWT = 0;
    int totalTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].wt << "\t" << p[i].tat << endl;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    float avgWT = (float)totalWT / n;
    float avgTAT = (float)totalTAT / n;
    float cpu = (float)totalBurst / time * 100;

    cout << "\nAverage Waiting Time = " << avgWT << endl;
    cout << "Average Turnaround Time = " << avgTAT << endl;
    cout<<"CPU Utilization = "<<cpu<<"%"<<endl;
    float throughput=(float)n/time;
    cout<<"Throughput = "<<throughput<<endl;

    saveToFile("FCFS Scheduling", p, avgWT, avgTAT);
    Result r1;
    r1.algorithm = "FCFS Scheduling";
    r1.avgWT = avgWT;
    r1.avgTAT = avgTAT;
    r1.cpuUtilization = cpu;
    r1.throughput = throughput;
    return r1;
}

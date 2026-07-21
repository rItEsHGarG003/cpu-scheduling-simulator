#include <iostream>
#include <vector>
#include "result.h"
#include "rr.h"
using namespace std;

void saveToFile(string algorithmName, vector<Process> p, float avgWT, float avgTAT);

Result roundRobin(vector<Process> p, int quantum) {
    int n = p.size();
    int totalBurst = 0;

    // sort by arrival time (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt; // remaining time = burst time at start
    }

    int time = 0;
    int completed = 0;

    vector<int> q;            // this acts like our queue, stores index
    vector<bool> inQueue(n, false);

    cout << "\n--- Round Robin Scheduling (Quantum = " << quantum << ") ---" << endl;
    cout << "\nGantt Chart:" << endl;

    // add processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && inQueue[i] == false) {
            q.push_back(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {

        if (q.size() == 0) {
            // nothing in queue, move time forward
            time = time + 1;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && inQueue[i] == false && p[i].rt > 0) {
                    q.push_back(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = q[0];
        q.erase(q.begin());   // remove the front element

        cout << "| " << p[idx].name << " ";

        int run = quantum;
        if (p[idx].rt < quantum) {
            run = p[idx].rt;
        }

        time = time + run;
        p[idx].rt = p[idx].rt - run;

        // check if any new process arrived during this turn
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && inQueue[i] == false && p[i].rt > 0) {
                q.push_back(i);
                inQueue[i] = true;
            }
        }

        if (p[idx].rt > 0) {
            // still has work left, send it to back of queue
            q.push_back(idx);
        } else {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed = completed + 1;
            totalBurst += p[idx].bt;
        }
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
    saveToFile("Round Robin Scheduling", p, avgWT, avgTAT);
    Result r3;
    r3.algorithm = "Round Robin Scheduling";
    r3.avgWT = avgWT;
    r3.avgTAT = avgTAT;
    r3.cpuUtilization = cpu;
    r3.throughput = throughput;
    return r3;
}

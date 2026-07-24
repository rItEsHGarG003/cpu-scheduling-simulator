#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <climits>
#include "process.h"
#include "fcfs.h"
#include "sjf.h"
#include "rr.h"
#include "priority.h"
#include "result.h"
using namespace std;


void saveToFile(string algorithmName, vector<Process> p, float avgWT, float avgTAT) {
    ofstream file("output.txt", ios::app);

    file << "\n========================" << endl;
    file << algorithmName << endl;
    file << "========================" << endl;

    file << "\nPID\tAT\tBT\tCT\tWT\tTAT" << endl;

    for (int i = 0; i < p.size(); i++) {
        file << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct  << "\t" << p[i].wt << "\t" << p[i].tat << endl;
    }

    file << "\nAverage Waiting Time = " << avgWT << endl;
    file << "Average Turnaround Time = " << avgTAT << endl;

    file.close();
    cout << "\nResult saved to output.txt" << endl;
}

void saveToFile(string algorithmName, vector<Process> p, float avgWT, float avgTAT);

// function to take process details from user
vector<Process> getInput() {
    int n;

    // Validate process count
    do {
        cout << "Enter number of processes (1-10): ";
        cin >> n;
        if (n <= 0 || n > 10) {
            cout << "Invalid! Enter between 1 and 10." << endl;
        }
    } while (n <= 0 || n > 10);

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid  = i + 1;
        p[i].name = "P" + to_string(i + 1);
        p[i].done = false;
        p[i].rt   = 0;

        cout << "\nProcess " << p[i].name << endl;

        // Validate arrival time
        do {
            cout << "Arrival Time (>= 0): ";
            cin >> p[i].at;
            if (p[i].at < 0) {
                cout << "Invalid! Arrival time cannot be negative." << endl;
            }
        } while (p[i].at < 0);

        // Validate burst time
        do {
            cout << "Burst Time (>= 1): ";
            cin >> p[i].bt;
            if (p[i].bt <= 0) {
                cout << "Invalid! Burst time must be at least 1." << endl;
            }
        } while (p[i].bt <= 0);

        // Validate priority
        do {
            cout << "Priority (1 = highest, max 10): ";
            cin >> p[i].priority;
            if (p[i].priority <= 0 || p[i].priority > 10) {
                cout << "Invalid! Priority must be between 1 and 10." << endl;
            }
        } while (p[i].priority <= 0 || p[i].priority > 10);
    }

    return p;
}

int main() {
    int choice;

    while (true) {
        cout << "\n========================" << endl;
        cout << " CPU SCHEDULING SIMULATOR" << endl;
        cout << "========================" << endl;
        cout << "1. FCFS" << endl;
        cout << "2. SJF" << endl;
        cout << "3. Round Robin" << endl;
        cout << "4. Priority Scheduling" << endl;
        cout << "5. Compare All" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 6) {
            cout << "\nThank you!" << endl;
            break;
        }

        if (choice == 1) {
            vector<Process> p = getInput();
            fcfs(p);
        }
        else if (choice == 2) {
            vector<Process> p = getInput();
            sjf(p);
        }
        else if (choice == 3) {
            vector<Process> p = getInput();
            int q;
            cout << "Enter Time Quantum: ";
            cin >> q;
            roundRobin(p, q);
        }
        else if (choice == 4) {
            vector<Process> p = getInput();
            priorityScheduling(p);
        }
        else if (choice == 5) {
            vector<Process> p = getInput();
            int q;
            cout << "Enter Time Quantum (for Round Robin): ";
            cin >> q;

            cout << "\n>>> Running FCFS <<<" << endl;
            Result r1 = fcfs(p);

            cout << "\n>>> Running SJF <<<" << endl;
            Result r2 = sjf(p);

            cout << "\n>>> Running Priority Scheduling <<<" << endl;
            Result r3 = priorityScheduling(p);

            cout << "\n>>> Running Round Robin <<<" << endl;
            Result r4 = roundRobin(p, q);

            cout << "\n==========================================================================\n";
            cout << "                 PERFORMANCE COMPARISON\n";
            cout << "==========================================================================\n";

            cout << left
                 << setw(28) << "Algorithm"
                 << setw(12) << "Avg WT"
                 << setw(12) << "Avg TAT"
                 << setw(12) << "CPU %"
                 << setw(12) << "Throughput"
                 << endl;

            cout << "-------------------------------------------------------------------------\n";

            cout << left
                 << setw(28) << r1.algorithm
                 << setw(12) << r1.avgWT
                 << setw(12) << r1.avgTAT
                 << setw(12) << r1.cpuUtilization
                 << setw(12) << r1.throughput
                 << endl;

            cout << left
                 << setw(28) << r2.algorithm
                 << setw(12) << r2.avgWT
                 << setw(12) << r2.avgTAT
                 << setw(12) << r2.cpuUtilization
                 << setw(12) << r2.throughput
                 << endl;

            cout << left
                 << setw(28) << r3.algorithm
                 << setw(12) << r3.avgWT
                 << setw(12) << r3.avgTAT
                 << setw(12) << r3.cpuUtilization
                 << setw(12) << r3.throughput
                 << endl;

            cout << left
                 << setw(28) << r4.algorithm
                 << setw(12) << r4.avgWT
                 << setw(12) << r4.avgTAT
                 << setw(12) << r4.cpuUtilization
                 << setw(12) << r4.throughput
                 << endl;

            cout << "==========================================================================\n";
        }
        else if (choice == 6) {
            cout << "\nThank you!" << endl;
            break;
        }
        else {
            cout << "Invalid choice, try again." << endl;
        }
    }
    return 0;
}

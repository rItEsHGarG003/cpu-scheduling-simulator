CPU Scheduling Simulator
=========================

This is a C++ CPU Scheduling Simulator that demonstrates four scheduling algorithms:

1. First Come First Serve (FCFS)
2. Shortest Job First (SJF - Non Preemptive)
3. Round Robin (RR)
4. Priority Scheduling (Non-Preemptive)

The simulator calculates Completion Time, Waiting Time, Turnaround Time, displays a Gantt Chart, compares algorithms, and saves the results to a text file.


How to run
----------

Open this folder in VS Code and run this in the terminal:

g++ -std=c++17 -o scheduler main.cpp fcfs.cpp sjf.cpp rr.cpp priority.cpp

Then run:

./scheduler          (Linux/Mac)
.\scheduler            (Windows)


Files
-----

process.h      - Stores process information
main.cpp       - Menu and input handling
fcfs.cpp       - FCFS Scheduling
sjf.cpp        - Non-Preemptive SJF
rr.cpp         - Round Robin Scheduling
priority.cpp   - Non-Preemptive Priority Scheduling
output.txt     - Stores simulation results


Sample Input
------------

Number of processes: 4
P1 - Arrival: 0, Burst: 5
P2 - Arrival: 1, Burst: 3
P3 - Arrival: 2, Burst: 8
P4 - Arrival: 3, Burst: 2

Use the "Compare All" option to execute all scheduling algorithms on the same set of processes and compare their performance.


What I learned
---------------

Features
--------

✔ Menu Driven Interface
✔ FCFS Scheduling
✔ SJF Scheduling
✔ Round Robin Scheduling
✔ Priority Scheduling
✔ Compare All Algorithms
✔ Gantt Chart
✔ Waiting Time Calculation
✔ Turnaround Time Calculation
✔ Input Validation
✔ Save Results to output.txt
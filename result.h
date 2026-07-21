#ifndef RESULT_H
#define RESULT_H

#include <string>
using namespace std;

struct Result
{
    string algorithm;

    float avgWT;
    float avgTAT;

    float cpuUtilization;

    float throughput;
};

#endif
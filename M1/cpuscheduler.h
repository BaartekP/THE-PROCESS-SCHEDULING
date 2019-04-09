#pragma once
#ifndef M1_cpuscheduler_h_
#define M1_cpuscheduler_h_

#include <vector>
#include <queue>
#include "deviceq.h"

using namespace std;

class CPU;
class IO;

class CPUscheduler {
public:

	void add(Process*,int);
	
	queue<Process*>& get_ReadyQueue();
	CPU* get_CPUs(int);
	IO* get_IOs(int);
	Deviceq* get_devices_queue(int);
	int get_cpuNumb();
	int get_ioNumb();
	int get_max_ready_queue();

	CPUscheduler();
	~CPUscheduler();

private:

	queue<Process*> ReadyQueue;
	vector < CPU* > CPUs;
	vector < IO* > IOs;
	vector <Deviceq*> devices_queues;
	
	const int cpuNumb = 4;
	const int ioNumb = 5;
	int max_ready_queue = 0;


};
#endif 
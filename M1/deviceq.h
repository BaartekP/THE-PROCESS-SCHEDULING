#pragma once
#ifndef M1_Deviceq_h_
#define M1_Deviceq_h_

#include <queue>
using namespace std;

class Process;
class UniformGenerator;

class Deviceq {
public:
	void pop();
	int size();
	int get_max_device_queue();
	void push(Process* p, UniformGenerator* _gen_DQ);
	bool is_empty();
	Process* front();
	Deviceq();
	~Deviceq();
	
private:
	vector<Process*> DeviceQueue;
	int max_device_queue = 0;
};


#endif
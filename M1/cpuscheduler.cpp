#include <iostream>
#include "cpuscheduler.h"
#include "cpu.h"
#include "io.h"


using namespace std;


void CPUscheduler::add(Process *p,int sim_time)
{
	get_ReadyQueue().push(p);
	p->set_start_time(sim_time);
	p->set_birth(sim_time);

	if (get_ReadyQueue().size() > max_ready_queue) {
		max_ready_queue = get_ReadyQueue().size();
	}
	
}

queue<Process*>& CPUscheduler::get_ReadyQueue()
{
	return ReadyQueue;
}

CPU * CPUscheduler::get_CPUs(int i)
{
	return CPUs[i];
}

IO * CPUscheduler::get_IOs(int i)
{
	return IOs[i];
}


Deviceq* CPUscheduler::get_devices_queue(int i)
{
	return devices_queues[i];
}

int CPUscheduler::get_cpuNumb()
{
	return cpuNumb;
}

int CPUscheduler::get_ioNumb()
{
	return ioNumb;
}

int CPUscheduler::get_max_ready_queue()
{
	return max_ready_queue;
}

CPUscheduler::CPUscheduler():cpuNumb(4),ioNumb(5)
{
	for (int i = 0; i < cpuNumb; i++) {
		CPU* cpu = new CPU();			
		CPUs.push_back(cpu);
	}

	for (int i = 0; i < ioNumb; i++) {
		IO* cpu = new IO();
		IOs.push_back(cpu);

		devices_queues.push_back(new Deviceq());	// vector piêciu kolejek
	}
	 
}

CPUscheduler::~CPUscheduler()
{
	/*while (ReadyQueue.size() != 0) {
		ReadyQueue.pop();
	}

	for (int i = 0; i < devices_queues.size(); i++) {

		while (devices_queues[i]->size() != 0) {
			devices_queues[i]->pop();
		}
	}
	
	CPUs.erase(CPUs.begin(), CPUs.end());
	CPUs.clear();
	IOs.erase(IOs.begin(), IOs.end());
	IOs.clear();*/
	

}

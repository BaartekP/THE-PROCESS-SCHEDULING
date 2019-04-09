#include <iostream>
#include "cpu.h"
#include "deviceq.h"


using namespace std;



void CPU::assign_process_cpu(Process * p)
{
	process_cpu = p;
}

void CPU::delete_process_cpu()
{
	delete process_cpu;
	process_cpu = nullptr;
}

Process * CPU::get_process_cpu()
{
	return process_cpu;
}

void CPU::clear_process_cpu()
{

	process_cpu = nullptr;
	
}




bool CPU::is_busy()
{
	return busy;
}

void CPU::set_c_busy(int sim_time)
{
	if(c_idle!=0)
	c_busy += sim_time - c_idle;
}

void CPU::set_c_idle(int sim_time)
{
	c_idle = sim_time;
}

int CPU::get_c_busy()
{
	return c_busy;
}

int CPU::get_c_idle()
{
	return c_idle;
}

void CPU::set_busy(bool a) 
{
	busy = a;
}



CPU::CPU() {
	process_cpu = nullptr;
	busy = false;

}

CPU::~CPU()
{
}

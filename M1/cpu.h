#pragma once
#ifndef M1_cpu_h
#define M1_cpu_h_


#include "process.h"


class CPU {
public:
	void assign_process_cpu(Process *p);			
	void delete_process_cpu();
	Process* get_process_cpu();						
	void clear_process_cpu();						
	bool is_busy();									
	void set_busy(bool);						
	void set_c_busy(int);
	void set_c_idle(int);

	int get_c_busy();
	int get_c_idle();

	CPU();
	~CPU();
private:
	Process* process_cpu;
	bool busy;
	int c_busy=0;
	int c_idle=0;

};

#endif
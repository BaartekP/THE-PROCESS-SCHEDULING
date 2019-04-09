#ifndef M1_simulation_h_
#define M1_simulation_h_

#include <fstream>
#include <sstream>
#include <vector>
#include "generator.h"

class Kernels;
class ExpGenerator;
class UniformGenerator;
class CPUscheduler;

class Simulation {
public:
	void execute(Kernels*,int);
	void new_process(CPUscheduler*, ExpGenerator*, UniformGenerator*, UniformGenerator*, UniformGenerator*, UniformGenerator*);
	void start_of_work_cpu(CPUscheduler* ,int);
	void start_of_work_io(CPUscheduler* ,int);
	void end_of_work_cpu(CPUscheduler* ,int, UniformGenerator* _gen_DQ);
	void end_of_work_io(CPUscheduler* ,int, UniformGenerator*, UniformGenerator*);
	void update_sim_time(CPUscheduler* );
	void set_mode(int,int,int,double);
	void queues(CPUscheduler*);


	Simulation();
	~Simulation();

private:
	double next_arrival,lambda;
	int sim_time, initial_phase,time;
	bool event_trig;
	int cpu_sim_ICT[4] = { -1,-1,-1,-1 };
	int io_sim_ICT[5] = { -1,-1,-1,-1,-1 };
	int mode;
	int all_processes = 0;
	int ended_process = 0; 
	int summ_of_queue_times = 0; 
	std::vector<int> CET_vector;
	int turnaround = 0;

};



#endif

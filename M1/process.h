#pragma once
#ifndef M1_Process_h_
#define M1_Process_h_


class UniformGenerator;

class Process {
public:
	void update_CET_ICT();
	void rand_IOT_ICT(UniformGenerator*, UniformGenerator*);
	void update_ICT(int a);
	void clear_CET();
	void set_start_time(int);
	void update_queue_time(int);
	void set_birth(int);
	void set_static_id();

	
	int get_id();
	int get_CET();
	int get_ICT();
	int get_IOT();
	int get_IOD();
	int get_queue_time();
	int get_birth();
	Process(UniformGenerator*, UniformGenerator*, UniformGenerator*, UniformGenerator*);
	~Process();

private:
	int id,CET, ICT, IOT, IOD,start_time,queue_time,birth;
	static int ID;
	
	


};

#endif

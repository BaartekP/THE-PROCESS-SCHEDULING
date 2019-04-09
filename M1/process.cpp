#include <cstdlib>
#include <ctime>
#include "Process.h"
#include "generator.h"

using namespace std;

int Process::ID = 0;

void Process::update_CET_ICT()
{
	CET -= ICT;
	ICT = 0;
	
}


void Process::rand_IOT_ICT(UniformGenerator* _gen_ICT, UniformGenerator* _gen_IOT)
{
	ICT = (int)_gen_ICT->Rand(0, CET);
	if (ICT != 0)
		IOT = (int)_gen_ICT->Rand(1, 10);
	else
		IOT = 0;
	
}

void Process::update_ICT(int a)
{
	ICT = (rand() % a);
}

void Process::clear_CET()
{
	CET = 0;
}

void Process::set_start_time(int sim_time)
{
	start_time = sim_time;
}

void Process::update_queue_time(int sim_time)
{
	queue_time += sim_time - start_time;
}

void Process::set_birth(int sim_time)
{
	birth = sim_time;
}

void Process::set_static_id()
{
	ID = 0;
}



int Process::get_id()
{
	return id;
}

int Process::get_CET()
{
	return CET;
}

int Process::get_ICT()
{
	return ICT;
}

int Process::get_IOT()
{			
	return IOT;
}

int Process::get_IOD()
{
	return IOD;
}

int Process::get_queue_time()
{
	return queue_time;
}

int Process::get_birth()
{
	return birth;
}

Process::Process(UniformGenerator* _gen_CET, UniformGenerator* _gen_ICT, UniformGenerator* _gen_IOT, UniformGenerator* _gen_IOD)
{
	id = ID++;
	CET = (int) _gen_CET->Rand(1, 51);
	ICT = (int)_gen_ICT->Rand(0, CET+1);
	IOT = (int)_gen_IOT->Rand(1, 11);
	IOD = (int)_gen_IOD->Rand(0, 5);	
	start_time = 0;
	queue_time = 0;
	birth = 0;
	

}

Process::~Process()
{
	
}



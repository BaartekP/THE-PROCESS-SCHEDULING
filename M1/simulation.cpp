#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "simulation.h"
#include "cpuscheduler.h"
#include "cpu.h"
#include "io.h"
#include "generator.h"
#include "kernels.h"

void Simulation::execute(Kernels* seed, int i)

{	
	CPUscheduler* model = new CPUscheduler();
	
	//Generators

	UniformGenerator* _gen_PGT = new UniformGenerator(seed->GetKernel(seed->TPG, i));
	ExpGenerator* _exp_gen_PGT = new ExpGenerator(lambda,_gen_PGT); // 0.127 is goood
	UniformGenerator* _gen_CET = new UniformGenerator(seed->GetKernel(seed->TPW, i));
	UniformGenerator* _gen_ICT = new UniformGenerator(seed->GetKernel(seed->TPIO, i));
	UniformGenerator* _gen_IOT = new UniformGenerator(seed->GetKernel(seed->TPO, i));
	UniformGenerator* _gen_IOD = new UniformGenerator(seed->GetKernel(seed->TPD, i));
	UniformGenerator* _gen_DQ = new UniformGenerator(seed->GetKernel(seed->DQ, i));

	

	printf("\n\t---------------------------------------------------------------------------------\n");
	printf("\t------------------------------- SIMULATION NR : %i -------------------------------\n",i+1);
	printf("\t---------------------------------------------------------------------------------\n");

	while (sim_time < time+initial_phase)
	{
		if (mode == 1 && sim_time>=initial_phase) {
			printf("\t---------------------------------------------------------------------------------\n");
			printf("\tSIMULATION TIME : %i [ ms ]\n", sim_time);
			printf("\t---------------------------------------------------------------------------------\n");
		}

		event_trig = false;
		while (!event_trig) {

			event_trig = true;
			//1. Przyjscie nowego procesu
			if (next_arrival == sim_time) {
				new_process(model,_exp_gen_PGT,_gen_CET,_gen_ICT,_gen_IOT,_gen_IOD);
				if (sim_time >= initial_phase) {
					all_processes++;	// dodatkowa zmienna
				}
				event_trig = false;
			}

			//2. Start pracy na CPU
			for (int i = 0; i < model->get_cpuNumb(); i++) {
				if (model->get_CPUs(i)->is_busy() == false && model->get_ReadyQueue().empty() == false)
				{
					start_of_work_cpu(model,i);
					event_trig = false;
				}

			}

			//3. Koniec pracy na CPU
			for (int i = 0; i < model->get_cpuNumb(); i++) {
				if (cpu_sim_ICT[i] == sim_time) {
					if (model->get_CPUs(i)->is_busy() == true) {
						end_of_work_cpu(model,i,_gen_DQ);
						cpu_sim_ICT[i] = -1;
						event_trig = false;
					}
				}
			}

			//4. Start pracy na IO
			for (int i = 0; i < (model->get_ioNumb()); i++) {

				if (model->get_devices_queue(i)->is_empty() == false && model->get_IOs(i)->is_busy() == false)
				{
					start_of_work_io(model,i);
					event_trig = false;
				}
			}

			//5. Koniec pracy na IO
			for (int i = 0; i < model->get_ioNumb(); i++) {
				if (io_sim_ICT[i] == sim_time) {
					end_of_work_io(model,i, _gen_ICT, _gen_IOT);
					io_sim_ICT[i] = -1;
					event_trig = false;
				}
			}
		}
		
		if (mode == 1 && sim_time>=initial_phase) {
			queues(model);		//wyswietlenie kolejek
			printf("");
			cin.ignore();
		}
		update_sim_time(model);
	}

	// wyœwietlanie statystyk
	if (sim_time >= initial_phase) { 

		double d_ended_process = (double)ended_process;
		double d_sim_time = (double)sim_time;
		double d_initial_phase = (double)initial_phase;
		double d_summ_of_queue_times = (double)summ_of_queue_times;
		double all = (double)all_processes;
		char d = '%';
		double d_turnaround = (double)turnaround;

		printf("\n\tSim time : %i [ms]\t Initial phase : %i [ms]\n", sim_time, initial_phase);
		printf("\n\tAll created processes : %i\t| All ended processes : %i\n", all_processes, ended_process); // dodatkowe
		printf("\n\tMax size of ReadyQueue : %i\t\t\n", model->get_max_ready_queue());
		printf("\n\tMax size of DeviceQueues :");

		for (int i = 0; i < model->get_ioNumb(); i++) {
			printf("\t%i : %i |", i+1, model->get_devices_queue(i)->get_max_device_queue());
		}

		printf("\n\n");	

		for (int i = 0; i < model->get_cpuNumb(); i++) {
			double a = (double)model->get_CPUs(i)->get_c_busy();
			double b = (double)model->get_CPUs(i)->get_c_idle();
			double c = (d_sim_time - d_initial_phase);
			printf("\tCPU nr %i has utilization : %f %c \n", i, (a/c)*100, d);
		}		

		printf("\n\tMean Waiting Time : %f [ms]\n",(d_summ_of_queue_times / d_ended_process));
		printf("\n\tThroughput : %f [terminated/time]\n\tTurnaround time: %f [live_time/terminated]\n\n", d_ended_process / (d_sim_time-d_initial_phase),d_turnaround/d_ended_process); //Liczba skonczonych processow przez jednoske czasu
		
		model->get_CPUs(1)->get_process_cpu()->set_static_id();

	}
}

void Simulation::new_process(CPUscheduler* model,ExpGenerator* _exp_gen_PGT, UniformGenerator* _gen_CET, UniformGenerator* _gen_ICT, UniformGenerator* _gen_IOT, UniformGenerator* _gen_IOD)
{
	Process* process = new Process(_gen_CET, _gen_ICT, _gen_IOT, _gen_IOD);
	int a = process->get_CET();
	if (sim_time >= initial_phase) {
		CET_vector[a - 1] += 1;
	}

	model->add(process,sim_time);
	event_trig = false;
	int x = (int) _exp_gen_PGT->Rand();
	next_arrival += x;
	


	
	if (mode == 1 && sim_time>=initial_phase) {
		printf("\tUtworzenie procesu nr %i\n", process->get_id());
	}
}

void Simulation::start_of_work_cpu(CPUscheduler* model, int i)
{
	Process* p = model->get_ReadyQueue().front();

	model->get_ReadyQueue().pop();										
	p->update_queue_time(sim_time); 
	model->get_CPUs(i)->assign_process_cpu(p);
	model->get_CPUs(i)->set_busy(1);
	if(sim_time>= initial_phase)
		model->get_CPUs(i)->set_c_idle(sim_time);						
	int a = p->get_ICT();
	if (a > 0)															
		cpu_sim_ICT[i] = sim_time + a;
	else
		cpu_sim_ICT[i] = sim_time + p->get_CET();
	if (mode == 1 && sim_time >= initial_phase) {
		printf("\tProces nr %i zaczyna prace na CPU nr %i, planowany czas zakonczenia : %i\n", p->get_id(), i, cpu_sim_ICT[i]);
	}
}

void Simulation::start_of_work_io(CPUscheduler* model,int i)
{
	Process *p = model->get_devices_queue(i)->front();
	model->get_devices_queue(i)->pop();									
	model->get_IOs(i)->assign_process_io(p);
	model->get_IOs(i)->set_busy(1);
	int b = p->get_IOT();
	io_sim_ICT[i] = sim_time + b;
	if (mode == 1 && sim_time >= initial_phase) {
	printf("\tProces nr %i zaczyna prace na IO nr %i, planowany czas zakonczenia : %i\n", p->get_id(), i, io_sim_ICT[i]);
	}
}

void Simulation::end_of_work_cpu(CPUscheduler* model,int i, UniformGenerator* _gen_DQ)
{
	Process *p = model->get_CPUs(i)->get_process_cpu();
	if (p->get_ICT() > 0){
		if (mode == 1 && sim_time >= initial_phase) {
			printf("\tProces nr %i konczy prace na CPU nr %i \n", p->get_id(), i);
		}
		
		p->update_CET_ICT();
		int a = p->get_IOD();				
		model->get_devices_queue(a)->push(p,_gen_DQ);
		model->get_CPUs(i)->clear_process_cpu();							
		model->get_CPUs(i)->set_busy(0);
		if (sim_time >= initial_phase)
		model->get_CPUs(i)->set_c_busy(sim_time);
	}
	else if (p->get_ICT() <= 0) {
		if (mode == 1 && sim_time >= initial_phase) {
			printf("\tProces nr %i konczy prace i usuwa sie z CPU nr %i \n", p->get_id(), i);
		}
		
		
		if (sim_time >= initial_phase) {
			summ_of_queue_times += p->get_queue_time();
			turnaround += sim_time - p->get_birth();


		}
		model->get_CPUs(i)->delete_process_cpu();
		model->get_CPUs(i)->set_busy(0);
		model->get_CPUs(i)->set_c_busy(sim_time);
		if (sim_time >= initial_phase) {
			ended_process++;
			
		}
	}
}

void Simulation::end_of_work_io(CPUscheduler* model,int i, UniformGenerator* _gen_ICT, UniformGenerator* _gen_IOT){
	Process* p = model->get_IOs(i)->get_process_io();
	if (mode == 1 && sim_time >= initial_phase) {
		printf("\tProces nr %i konczy prace na IO nr %i \n", p->get_id(), i);
	}
	p->rand_IOT_ICT( _gen_ICT, _gen_IOT);
	model->get_ReadyQueue().push(p);
	p->set_start_time(sim_time);
	model->get_IOs(i)->clear_process_io();								
	model->get_IOs(i)->set_busy(0);
}

void Simulation::update_sim_time(CPUscheduler* model)
{
	int length_cpu = model->get_cpuNumb();
	int min_cpu = cpu_sim_ICT[0];
	for (int i = 0; i < length_cpu; i++) {
		if (cpu_sim_ICT[i] > sim_time) {
			min_cpu = cpu_sim_ICT[i];
			break;
		}
	}

	for (int i = 1; i <= length_cpu; i++) {
		if (cpu_sim_ICT[i] > sim_time) {
			if (cpu_sim_ICT[i] < min_cpu) {
				min_cpu = cpu_sim_ICT[i];
			}

		}

	}

	int length_io = model->get_ioNumb();
	int min_io = io_sim_ICT[0];
	for (int i = 0; i < length_io; i++) {
		if (io_sim_ICT[i] > sim_time) {
			min_io = io_sim_ICT[i];
			break;
		}
	}

	for (int i = 1; i <= length_io; i++) {
		if (io_sim_ICT[i] > sim_time) {
			if (io_sim_ICT[i] < min_io) {
				min_io = io_sim_ICT[i];
			}
		}
	}

	if (min_cpu > sim_time && min_io > sim_time && next_arrival != sim_time) {

		if (min_cpu <= min_io && min_cpu <= next_arrival)
			sim_time = min_cpu;
		else if (min_io <= min_cpu && min_io <= next_arrival)
			sim_time = min_io;
		else if (next_arrival <= min_cpu && next_arrival <= min_io)
			sim_time = next_arrival;
	}
	else if (min_cpu <= sim_time) {
		if (min_io <= next_arrival && min_io > sim_time)
			sim_time = min_io;
		else
			sim_time = next_arrival;
	}
	else if (min_io <= sim_time) {
		if (min_cpu <= next_arrival && min_cpu > sim_time)
			sim_time = min_cpu;
		else
			sim_time = next_arrival;
	}
	else if (min_io < 0) {
		if (min_cpu <= next_arrival && min_cpu > sim_time)
			sim_time = min_cpu;
		else
			sim_time = next_arrival;
	}
}

void Simulation::set_mode(int a,int b,int c,double d)
{
	mode = a;
	initial_phase = b;
	time = c;
	lambda = d;
}

void Simulation::queues(CPUscheduler* model)
{
	if (model->get_ReadyQueue().empty() == false) {
		printf("\tReady Queue size : %i\n", model->get_ReadyQueue().size());
	}
	for (int i = 0; i < model->get_ioNumb(); i++) {
		if (model->get_devices_queue(i)->is_empty() == false)
			printf("\tDevice Queue nr %i has size : %i\n",i,model->get_devices_queue(i)->size());
	}
}

Simulation::Simulation()
{
	
	time = 0;
	next_arrival = 0;
	sim_time = 0;
	event_trig = false;
	CET_vector.resize(50, 0);
	lambda = 0;

}

Simulation::~Simulation()
{
	
}

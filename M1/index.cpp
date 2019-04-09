#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "simulation.h"
#include "kernels.h"

int main()
{

	Kernels* seed = new Kernels();
	seed->GenerateKernels("seeds.txt");
	seed->ReadKernels("seeds.txt");

	int mode;
	int choice_0 = 0;
	int choice_1 = 0;
	int choice_2 = 0;
	double lambda = 0.127;	
	int time = 1000000;
	int initial_phase = 0;

	printf("\nDo you want to set time? ( default value is 1000000 )\nYES = 1\t| NO = 0 \nAnswer: ");
	std::cin >> choice_0;
	if (choice_0 >= 1)
	{
		printf("\nTime : ");
		std::cin >> time;
	}
	
	printf("\nSelect the mode:\nStepByStep = 1 \t| Continuous = 0\nMode = ");
	std::cin >> mode;

	
	printf("\nDo you want to ommit initial phase?\nYES = 1\t| NO = 0 \nAnswer: ");
	std::cin >> choice_1;

	if (choice_1 >= 1) {
		initial_phase = 1600;
	}
	
	printf("\nDo you want to set Lambda? ( default value is 0.127 )\nYES = 1\t| NO = 0 \nAnswer: ");
	std::cin >> choice_2;
	if (choice_2>=1)
	{
		printf("\nLambda : ");
		std::cin >> lambda;
	}

	for (int i = 0; i < 10; i++) {
		Simulation* cpuscheduler = new Simulation();
		cpuscheduler->set_mode(mode,initial_phase,time,lambda);
		cpuscheduler->execute(seed,i);
		delete cpuscheduler;
	}


system("pause");
return 0;
}
	
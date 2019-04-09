#pragma once
#ifndef M1_M1_Readyq_h_
#define M1_M1_Readyq_h_

#include <queue>
using namespace std;


class Process;

class Readyq {
public:
	
	void delete_r(); // usuwa pierwszy process z kolejki ReadyQueue
	queue <Process*> get_ReadyQ();
	Readyq();
	~Readyq();
private:
	queue <Process*> ReadyQ;
};

#endif 


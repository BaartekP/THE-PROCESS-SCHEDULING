#include <queue>
#include "readyq.h"
#include "process.h"


using namespace std;




void Readyq::delete_r()
{
	ReadyQ.pop();
}

queue <Process*> Readyq::get_ReadyQ()
{
	return ReadyQ;
}

Readyq::Readyq()
{
}

Readyq::~Readyq()
{
	delete& ReadyQ;
}



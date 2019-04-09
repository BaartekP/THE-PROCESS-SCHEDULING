#include <queue>
#include <vector>
#include "Deviceq.h"
#include "process.h"
#include "generator.h"

using namespace std;

Deviceq::Deviceq() {}

Deviceq::~Deviceq()
{
	delete& DeviceQueue;
}

void Deviceq::pop()
{
	DeviceQueue.erase(DeviceQueue.begin());
}

int Deviceq::size()
{
	return DeviceQueue.size();
}

int Deviceq::get_max_device_queue()
{
	return max_device_queue;
}

void Deviceq::push(Process* p, UniformGenerator* dq)
{	
	//DeviceQueue.push_back(p);

	//printf("Do kolejki %i dodaje proces nr %i \n", p->get_IOD(), p->get_id());
	int dq_size = DeviceQueue.size();

	if (dq_size > max_device_queue) {
		max_device_queue = dq_size;
	}

	if (DeviceQueue.empty()) {


		DeviceQueue.push_back(p);
	}
	else{
		int i;
		for (i = 0; i < dq_size; i++) {
			if (p->get_IOT() < DeviceQueue.at(i)->get_IOT())
			{
				DeviceQueue.insert(DeviceQueue.begin()+i, p);
				break;
			}
			else if (p->get_IOT() == DeviceQueue.at(i)->get_IOT())
			{
				int x = (int)dq->Rand(0, 2);
				DeviceQueue.insert((DeviceQueue.begin()+i+x), p);
				break;
			}
		}
		if (p->get_IOT() > DeviceQueue.at(dq_size-1)->get_IOT()) {
			DeviceQueue.push_back(p);
		}

	}
	
	
	
}



bool Deviceq::is_empty()
{
	return DeviceQueue.empty();
}

Process * Deviceq::front()
{
	return DeviceQueue.front();
}

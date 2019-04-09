#include <iostream>
#include "io.h"
#include "deviceq.h"


using namespace std;



void IO::assign_process_io(Process * p)
{
	process_io = p;
}

Process * IO::get_process_io()
{
	return process_io;
}

void IO::clear_process_io()
{
	process_io = nullptr;
}


bool IO::is_busy()
{
	return busy;
}

void IO::set_busy(bool a) 
{
	busy = a;

}

IO::IO() {
	process_io = nullptr;
	busy = false;

}

IO::~IO()
{
}



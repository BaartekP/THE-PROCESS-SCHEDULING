#pragma once
#ifndef M1_io_h_
#define M1_io_h_


#include "process.h"

class IO {
public:
	void assign_process_io(Process *p);			
	Process* get_process_io();						
	void clear_process_io();						
	bool is_busy();									
	void set_busy(bool);							
	IO();
	~IO();
private:
	Process* process_io;
	bool busy;

};

#endif 

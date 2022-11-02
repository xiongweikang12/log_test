#include "log.h"
// #include "head_use.h"
#include<iostream>
#include "test1.h"
using namespace yazi::utility;

int main()
{
	Logger::instance()->open("./test.log");
	Logger::instance()->log(Logger::level::DEBUG,
		__FILE__, __LINE__, "hello world");
	// warn("this is warning");
	// debug("hi");
	// info("hi");
	// warn("hi");
	// error("hi");
	// fatal("hi");
	cout << "all rigth" << endl;
	cout << "test1" << endl;
	print_show(false);
	debug( "hello","my name is %s,age is %d", "jack", 20 );
	
	
	return 0;
}
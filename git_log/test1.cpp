#include <iostream>
#include "test1.h"
#include "log.h"
using namespace yazi::utility;

void print_show(bool yes)
{
	if (yes)
	{
		cout << "test yes" << endl;
	}
	else
	{
		error("test no");
	}
}
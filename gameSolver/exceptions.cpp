#include "exceptions.h"

const char* exception::what() const throw()
{
	return "Unknown Game Value exception happened";
}
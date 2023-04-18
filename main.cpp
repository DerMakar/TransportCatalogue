#include "input_reader.h"
#include "geo.h"
#include "stat_reader.h"
#include <string>
#include <iostream>
#include <cassert>
#include "log_duration.h"


using namespace std::literals;

int main() {
	{
		LOG_DURATION("Total"s);
		TransportCatalogue base;
	
		
		{
			LOG_DURATION("creating"s);
			CreateBase(base);
		}
		{
			LOG_DURATION("process asks"s);
			AskBase(base);
		}
	}
	return 0;
}


#include "stat_reader.h"
#include "transport_catalogue.h"
#include <iostream>

using namespace std::literals;

void AskBase(TransportCatalogue& base) {
    int num_of_queries = ReadLineWithNumber();
    for (int i = 0; i != num_of_queries; ++i) {
        std::string query = ReadLine();
        auto pos = query.find(' ');
        auto name = query.substr(pos + 1);
        base.FindBus(name) == nullptr ? std::cout << query << ": not found"s << std::endl :
        std::cout << query << ": "s << base.GetBusInfo(name) << std::endl;
    }
}
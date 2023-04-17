

#include "stat_reader.h"
#include "transport_catalogue.h"
#include <iostream>

using namespace std::literals;

void AskBase(TransportCatalogue& base) {
    int num_of_queries = ReadLineWithNumber();
    for (int64_t i = 0; i != num_of_queries; ++i) {
        std::string query = ReadLine();
        if (query[0] != 'B') {
            throw std::invalid_argument("You can ask just Bus!"s);
        }
        else{
            auto pos = query.find(' ');
            base.FindBus(query.substr(pos + 1, std::string::npos)) == nullptr ? std::cout << query << ": not found"s << std::endl :
            std::cout << query << ": "s << base.GetBusInfo(query.substr(pos + 1, std::string::npos)) << std::endl;
        }
    }
}
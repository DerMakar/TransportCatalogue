#include <iostream>

#include "input_reader.h"



using namespace std::literals;

std::string ReadLine() {
    std::string s;
    getline(std::cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    std::cin >> result;
    ReadLine();
    return result;
}

Query ParseQuery(std::string query) {
    Query result;
    if (query[0] == 'S') {
        result.type = QueryType::Stop;
    }
    else if (query[0] == 'B') {
        result.type = QueryType::Bus;
    }
    else {
        throw std::invalid_argument("Invalid query"s);
    }
    auto start_of_data = query.find_first_of(" ", 1);
    result.data = query.substr(start_of_data + 1);
    return result;
}

std::vector<std::string_view> SplitIntoWords(std::string_view str) {
    std::vector<std::string_view> result;
    char type;
    auto check = std::count(str.begin(), str.end(), '>');
    check != 0 ? type = '>' : type = '-';
    //Удалите начало из str до первого непробельного символа
     while (!str.empty()) {
        str.remove_prefix(std::min(str.size(), str.find_first_not_of(" ")));
        int64_t stop = str.find(type);
        result.push_back(str.substr(0, stop - 1));
        str.remove_prefix(std::min(str.size(), str.find_first_not_of(type, stop)));


    }
    return result;
}


void CreateBase(TransportCatalogue& base) { //чтение запроса O(N), где N — количество символов в нём
     // укажем число запросов
    std::vector<Query> data; // инициализируем вектор, который соберет все запросы по типам Bus и Stop
    int num_of_queries = ReadLineWithNumber();
    for (int64_t i = 0; i != num_of_queries; ++i) {
        data.push_back(ParseQuery(ReadLine()));
    }
    for (const Query& query_ : data) {
        if (query_.type == QueryType::Stop) {
            base.AddStop(query_.data);
        }
    }
    for (Query query_ : data) {
        if (query_.type == QueryType::Bus) {
            base.AddBus(query_.data);
        }
    }
    
}


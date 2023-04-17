// напишите решение с нуля
/* обработка запросов на создание базы данных
Запросы двух типов:
Stop X: latitude, longitude
- добавляет инфо об остановке
(имя, широта (юг -90, сев +90), долгота(-180,180 относ Гринвича)
Останкино - 55.8199081, 37.6116028
разделение запятой и пробелом после
---
Bus X: описание маршрута
- Запрос на добавление автобусного маршрута X
Название маршрута может состоять из нескольких слов и отделяется от описания двоеточием
форматы:
через тире - от stop1 до stopN и обратно
через > - кольцевой маршрут с конечной stop1 (с чего начал, тем закончил)
гарантируется что остановка на маршруте есть в коллекции остановок
гарантируется, что маршрут Х определен не более чем у одного автобуса
*/

/* ОГРАНИЧЕНИЯ:
- остановка Х передана только в одном запросе
- чтение запроса O(N), где N — количество символов в нём*/

// Читайте cin построчно методом std::getline

/* сохранить запросы, и вначале обработать все запросы остановок, а затем, все запросы маршрутов*/


// Парсинг запроса
// после парсинга складываем в контейнер запросов
// проходим по контейнеру и вызываем методы добавления Stop/Bus
// проверять корректность букв, цифр, двойных пробелов

/* struct Query
category Stop / Bus
data - содержание запроса
*/


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
        // В цикле используйте метод find с одним параметром, чтобы найти номер позиции первого пробела.
        str.remove_prefix(std::min(str.size(), str.find_first_not_of(" ")));
        int64_t stop = str.find(type);
        //Добавьте в результирующий вектор элемент string_view, полученный вызовом метода substr, где начальная позиция будет 0, а конечная — найденная позиция пробела или npos.
        result.push_back(str.substr(0, stop - 1));
        //Сдвиньте начало str так, чтобы оно указывало на позицию за пробелом. Это можно сделать методом remove_prefix, передвигая начало str на указанное в аргументе количество позиций
        //Чтобы не удалить в методе remove_prefix больше символов, чем есть в строке, используйте алгоритм min: str.remove_prefix(min(str.size(), ...))
        str.remove_prefix(std::min(str.size(), str.find_first_not_of(type, stop)));


    }
    return result;
}


void CreateBase(TransportCatalogue& base) {
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


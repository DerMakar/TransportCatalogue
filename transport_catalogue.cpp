// напишите решение с нуля
// код сохраните в свой git-репозиторий
// класс транспортного справочника
/* класс называем TransportCatalogue
методы в нем
- добавление остановки амортизированная O(K) в среднем, К-длина названия

- добавление маршрута
- поиск маршрута по имени - О(К-длина названия)
- поиск остановки по имени - О(К-длина названия)
- получение информации о маршруте - амортизированная O(1) в среднем
методы ничего не вводят-выводят
*/

/* Допустимые символы в названиях маршрутов и остановок — латинские буквы, цифры и пробелы
Все названия непусты, не могут начинаться на пробелы или заканчиваться ими
*/

/* 

Stop AddStop (string)
не может быть пустой

Bus AddBus (string)
не может быть из одной остановки
может быть - (вторую половину докручиваем) или > (замыкаем маршрут) / смеси не должно быть
одна ошибка в маршруте может быть несколько раз
и даже подряд

Stop FindStop

Bus FindBus

??? GetBusInfo
---

*/
#include "transport_catalogue.h"
#include "stat_reader.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip>
#include "input_reader.h"
#include "geo.h"



using namespace std::literals;

// но добавляем только в конец или начало дека, чтобы не инвалидировать
void TransportCatalogue::AddStop(std::string data) {
    Stop result; // " Marushkino: 58.611, 37.20   "s
    auto start_of_stopname = data.find_first_not_of(" ");
    auto end_of_stopname = data.find(':');
    result.name = data.substr(start_of_stopname, end_of_stopname);
    auto start_of_latitude = data.find_first_of("123456789");
    auto end_of_latitude = data.find(",");
    std::string latitude =data.substr(start_of_latitude, end_of_latitude);
    result.lat_ = std::stod(latitude);
    std::string longitude = data.substr(end_of_latitude + 2, std::string::npos);
    result.long_ = std::stod(longitude);
    stops.push_back(result);
    stopname_to_stop[std::string_view(stops.back().name)] = &stops.back();
    CountDistances(result.name);
    
}

void TransportCatalogue::AddBus(std::string_view data) {
    Bus result; // "Bus 758: Marushkino - Stanica"
    auto start_of_busname = data.find_first_not_of(" ");
    auto end_of_busname = data.find(':');
    result.name = data.substr(start_of_busname, end_of_busname);
    auto stops_ = SplitIntoWords(data.substr(end_of_busname + 1));
    for (auto& stop_ : stops_) {
        if (stopname_to_stop.count(stop_) != 0) {
            result.route.push_back(stopname_to_stop.at(stop_));
        }
        else {
                throw std::invalid_argument("You're trying add unvalid Stop to route"s);
        }
    }
    if (std::count(data.begin(), data.end(), '-') != 0) {
        std::vector<Stop*> tmp = result.route;
        result.route.resize(result.route.size() * 2);
        std::copy_backward(tmp.rbegin(), tmp.rend(), result.route.end());
    }
    buses.push_back(result);
    busname_to_bus[std::string_view(buses.back().name)] = &buses.back();
}

Stop* TransportCatalogue::FindStop(std::string_view stop) const {
    return stopname_to_stop.at(stop);
}

Bus* TransportCatalogue::FindBus(std::string_view bus) const {
    if (busname_to_bus.count(bus) == 0) {
        return nullptr;
    }
    return busname_to_bus.at(bus);
}

std::deque<Bus> TransportCatalogue::GetBuses() const {
    return buses;
}

std::deque<Stop> TransportCatalogue::GetStops() const {
    return stops;
}

TransportCatalogue::DistanceInfo TransportCatalogue::GetDistanceCollection() const {
    return stops_to_distance;
}

void TransportCatalogue::CountDistances(std::string_view stop) {
    Coordinates from_;
    Coordinates to_;
    Stop* start_of_dist = stopname_to_stop.at(stop);
    for (const auto& stop_in_coll : stopname_to_stop) {
        Stop* end_of_dist = stop_in_coll.second;
        
    std::pair<Stop*, Stop*> dist = { start_of_dist, end_of_dist };
    if (stops_to_distance.count(dist) != 0) {
        continue;
    }
    from_.lat = start_of_dist->lat_;
    from_.lng = start_of_dist->long_;
    to_.lat = end_of_dist->lat_;
    to_.lng = end_of_dist->long_;
    double dist_ = ComputeDistance(from_, to_);
    stops_to_distance[dist] = dist_;
    CountDistances(stop_in_coll.first);
    }
    
}

std::tuple<int, int, double> TransportCatalogue::GetBusInfo(std::string_view bus) const {
    int num_of_stops_total = busname_to_bus.at(bus)->route.size();
    int num_of_stops_uniq = 1;
    double distance = 0.0;
    std::vector<Stop*> tmp(busname_to_bus.at(bus)->route.size());
    Stop* left = busname_to_bus.at(bus)->route[0];
    tmp.push_back(left);
    for (int i = 1; i < busname_to_bus.at(bus)->route.size(); ++i) {
        Stop* right = busname_to_bus.at(bus)->route[i];
        std::pair dist_ = { left,right };
        distance += stops_to_distance.at(dist_);
        left = right;
        if (std::count(tmp.begin(), tmp.end(), right) == 0) {
            ++num_of_stops_uniq;
            tmp.push_back(right);
        }
        
    }
    return { num_of_stops_total , num_of_stops_uniq , distance };
}

std::ostream& operator<<(std::ostream& out, const std::tuple<int, int, double>& info_){
    std::setprecision(6);
    out << std::get<0>(info_) << " stops on route, "s;
    out << std::get<1>(info_) << " unique stops, "s;
    out << std::get<2>(info_) << " rout length"s;
    return out;

}








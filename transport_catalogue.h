// напишите решение с нуля
// код сохраните в свой git-репозиторий

#pragma once

#include <unordered_map>
#include <deque>
#include <vector>
#include <string>


struct Stop {
	std::string name;
	double lat_ = 0; // широта
	double long_ = 0; // долгота
};

struct Bus {
	std::string name;
	std::vector<Stop*> route;
};

struct StopToDistanceHasher {
	size_t operator()(const std::pair<Stop*, Stop*>& info_) const {
		auto h1 = hasher_(info_.first->name);
		auto h2 = hasher_(info_.second->name);
		return 37 * h1 + h2;
	}

	std::hash<std::string> hasher_;
};

class TransportCatalogue {
	using DistanceInfo = std::unordered_map<std::pair<Stop*, Stop*>, double, StopToDistanceHasher>;
public:
	void AddStop(std::string);
	void AddBus(std::string_view);
	Stop* FindStop(std::string_view) const;
	Bus* FindBus(std::string_view) const;
	std::tuple<int, int, double> GetBusInfo(std::string_view) const;
	std::deque<Bus> GetBuses () const;
	std::deque<Stop> GetStops() const;
	DistanceInfo GetDistanceCollection() const;
	
	
private:
	std::deque<Stop> stops;
	std::deque<Bus> buses;
	std::unordered_map<std::string_view, Stop*> stopname_to_stop; //  - ключ - стринг_вью стопа, значение - ссылка (Stop*) на стоп в деке
	std::unordered_map<std::string_view, Bus*> busname_to_bus;	// -ключ - стринг - вью автобуса, значение - ссылка(Bus*) на маршрут в деке
	DistanceInfo stops_to_distance;
	void CountDistances(std::string_view);
	
	
	
};

std::ostream& operator<<(std::ostream& out, const std::tuple<int, int, double>&);



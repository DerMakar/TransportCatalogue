// напишите решение с нуля
// код сохраните в свой git-репозиторий
// запуск a.exe < in.txt > out.txt и проверка онлайн

/* План разработки и тестов
- Парсинг запроса
- проверить, что куда надо сложил
- проверить, что правильно парсит
- проверка добавления стопов
- проверка добавления маршрутов
- проверка вывода
*/

#include "input_reader.h"
#include "geo.h"
#include "stat_reader.h"
#include <string>
#include <iostream>
#include <cassert>


using namespace std::literals;

void TestParseQuery() {
	Query query;
	query = ParseQuery("Stop Marushkino"s);
	assert(query.type == QueryType::Stop);
	assert(query.data == "Marushkino");
	query = ParseQuery("Stop     Marushkino: 58.611, 37.20   "s);
	assert(query.data == "    Marushkino: 58.611, 37.20   "s);
	query = ParseQuery("Bus 758: Marushkino - Stanica"s);
	assert(query.type == QueryType::Bus);
	assert(query.data == "758: Marushkino - Stanica");
	std::cout << "ParseQuery done!"s << std::endl;
}

void AllTest() {
	TestParseQuery();
	//TestAddStop();
	std::cout << "all tests are ok"s << std::endl;
}

int main() {
	TransportCatalogue base;
	CreateBase(base);
	AskBase(base);
	return 0;
}
// напишите решение с нуля
// код сохраните в свой git-репозиторий

#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include "transport_catalogue.h"

enum class QueryType {
	Stop,
	Bus,
};

struct Query {
	QueryType type;
	std::string data;
};


std::string ReadLine();
int ReadLineWithNumber();
Query ParseQuery(std::string);
std::vector<std::string_view> SplitIntoWords(std::string_view);
void CreateBase(TransportCatalogue&);


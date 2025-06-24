#pragma once
#include <map>
#include <string>
#include "cart.h"

std::map<std::string, double> readMenuFile(const std::string& filename);
void writeOrderToCSV(const std::string& filename, const Cart& cart, double total,
    const std::string& name, const std::string& address, const std::string& phone);
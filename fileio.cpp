#include "fileio.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

std::map<std::string, double> readMenuFile(const std::string& filename) {
    std::map<std::string, double> menu;
    std::ifstream file(filename);
    std::string line;

    if (!file) {
        std::cerr << "Error opening menu file!\n";
        return menu;
    }

    while (std::getline(file, line)) {
        size_t sep = line.find('$');
        if (sep != std::string::npos) {
            std::string item = line.substr(0, sep);
            double price = std::stod(line.substr(sep + 1));
            menu[item] = price;
        }
    }
    return menu;
}

int getNextOrderID(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int maxID = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr;
        if (std::getline(ss, idStr, ',')) {
            int id = std::stoi(idStr);
            if (id > maxID) maxID = id;
        }
    }
    return maxID + 1;
}

void writeOrderToCSV(const std::string& filename, const Cart& cart, double total,
                     const std::string& name, const std::string& address, const std::string& phone) {
    std::ofstream out(filename, std::ios::app);
    if (!out) {
        std::cerr << "[ERROR] Could not write to " << filename << "\n";
        return;
    }

    // Get correct order ID
    int orderId = getNextOrderID(filename);

    // Get current date and time
    auto t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    // Write order entry
    out << orderId << ",\"" << name << "\",\"" << address << "\",\"" << phone << "\","
        << std::put_time(now, "%d/%m/%Y") << " " << std::put_time(now, "%H:%M") << ","
        << std::fixed << std::setprecision(2) << total << ",\"";

    for (const auto& item : cart.getItems()) {
        out << item.itemName << " x" << item.quantity;
        if (!item.customizations.empty())
            out << " (" << item.customizations << ")";
        out << "; ";
    }

    out << "\"\n";
    out.close();
}

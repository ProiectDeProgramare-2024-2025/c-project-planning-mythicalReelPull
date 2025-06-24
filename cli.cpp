#include "cli.h"

#include <fstream>

#include "cart.h"
#include "fileio.h"
#include <iostream>
#include <string>
#include <limits>

#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define RED "\033[31m"

void runInteractiveMode() {
    std::string restaurant = "DaMario";  // or prompt user for it
    std::string menuFile = "menus/" + restaurant + ".txt";
    auto menu = readMenuFile(menuFile);

    Cart cart;
    std::string command;
    std::cout << CYAN << "Welcome to FoodApp CLI. Type 'menu', 'add', 'order', or 'exit'.\n" << RESET;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;

        } else if (command == "menu") {
            std::cout << CYAN << "\n--- MENU ---\n" << RESET;
            for (const auto& pair : menu) {
                std::cout << pair.first << " - $" << pair.second << "\n";
            }

        } else if (command == "add") {
            std::string item;
            int qty;
            std::string custom;

            std::cout << "Item: ";
            std::getline(std::cin, item);
            if (!menu.count(item)) {
                std::cerr << RED << "[ERROR] Not found.\n" << RESET;
                continue;
            }

            std::cout << "Qty: ";
            std::cin >> qty;
            std::cin.ignore();  // consume newline
            std::cout << "Custom: ";
            std::getline(std::cin, custom);

            cart.addItem({item, menu[item], qty, custom});
            std::cout << GREEN << "[OK] Added to cart.\n" << RESET;

        } else if (command == "order") {
            if (cart.getItems().empty()) {
                std::cerr << RED << "[ERROR] Cart is empty. Add items first.\n" << RESET;
                continue;
            }

            std::string name, address, phone;
            std::cout << "Name: ";
            std::getline(std::cin, name);
            std::cout << "Address: ";
            std::getline(std::cin, address);
            std::cout << "Phone: ";
            std::getline(std::cin, phone);

            double total = cart.getTotal();
            std::string csvFile = "histories/" + restaurant + "_orders.csv";
            writeOrderToCSV(csvFile, cart, total, name, address, phone);

            std::cout << GREEN << "[OK] Order placed!\n" << RESET;
            std::cout << YELLOW << "Total: $" << total << "\n" << RESET;

            cart = Cart();  // clear cart
        } else {
            std::cerr << RED << "[ERROR] Unknown command.\n" << RESET;
        }
    }
}

void showOrderHistory(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open order history file.\n";
        return;
    }

    std::string line;
    std::cout << CYAN << "\n--- Order History ---\n" << RESET;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
    std::cout << CYAN << "----------------------\n" << RESET;
}

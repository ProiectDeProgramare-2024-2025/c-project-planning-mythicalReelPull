#include <iostream>
#include <string>
#include "cli.h"
#include "cart.h"
#include "fileio.h"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define RESET "[0m"
#define RED "[31m"

void showHelp() {
    std::cout << "\nAvailable commands:\n"
              "  foodapp.exe                                - Interactive mode\n"
              "  \nfoodapp.exe --history --restaurant <name>  - Show past orders for a restaurant\n"
              "  \nfoodapp.exe --list <restaurant>            - Show menu items from a restaurant\n"
              "  \nfoodapp.exe --order --item \"<Item Name>\" --qty 2 \n"
              "              --custom \"Size: <small, medium, large> Toppings: <comma separated>, Sauces: <comma separated>\" Note: \"None\" \n"
              "              --item \"Water\" --qty 1 \n"
              "              --item \"Cola\" --qty 1 --custom \"Cold\" \n"
              "              --name \"YourName\" --address \"Timisoara\" --phone \"0712345678\" --restaurant DaMario\n"
              "  \nfoodapp.exe --help                         - Show this help menu\n";
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        runInteractiveMode();
    } else {
        std::string arg = argv[1];
        if (arg == "--history") {
            std::string restaurant = "DaMario";
            for (int i = 2; i < argc; ++i) {
                if (std::string(argv[i]) == "--restaurant" && i + 1 < argc) {
                    restaurant = argv[++i];
                }
            }
            std::string historyFile = "histories/" + restaurant + "_orders.csv";
            showOrderHistory(historyFile);

        } else if (arg == "--order") {
            std::vector<std::string> items;
            std::vector<int> quantities;
            std::vector<std::string> customs;
            std::string name, address, phone, restaurant = "DaMario";

            for (int i = 2; i < argc; ++i) {
                std::string key = argv[i];
                if (key == "--item" && i + 1 < argc) items.push_back(argv[++i]);
                else if (key == "--qty" && i + 1 < argc) quantities.push_back(std::stoi(argv[++i]));
                else if (key == "--custom" && i + 1 < argc) customs.push_back(argv[++i]);
                else if (key == "--name" && i + 1 < argc) name = argv[++i];
                else if (key == "--address" && i + 1 < argc) address = argv[++i];
                else if (key == "--phone" && i + 1 < argc) phone = argv[++i];
                else if (key == "--restaurant" && i + 1 < argc) restaurant = argv[++i];
            }

            std::string menuFile = "menus/" + restaurant + ".txt";
            auto menu = readMenuFile(menuFile);

            if (items.empty() || quantities.size() != items.size() || name.empty() || address.empty() || phone.empty()) {
                std::cerr << RED << "\n[ERROR] Missing required fields or mismatched item/qty count.\n" << RESET;
                showHelp();
                return 1;
            }

            Cart cart;
            for (size_t i = 0; i < items.size(); ++i) {
                const std::string& item = items[i];
                int qty = quantities[i];
                std::string custom = (i < customs.size()) ? customs[i] : "";
                if (!menu.count(item)) {
                    std::cerr << RED << "\n[ERROR] Item not found in menu: " << item << "\n" << RESET;
                    return 1;
                }
                cart.addItem({item, menu[item], qty, custom});
            }

            double total = cart.getTotal();
            std::string csvFile = "histories/" + restaurant + "_orders.csv";
            writeOrderToCSV(csvFile, cart, total, name, address, phone);
            std::cout << GREEN << "\n[OK] Order saved from command line! Total: $" << total << "\n" << RESET;

        } else if (arg == "--help") {
            showHelp();

        } else if (arg == "--list") {
            if (argc < 3) {
                std::cerr << RED << "\n[ERROR] Please provide a restaurant name.\n" << RESET;
                return 1;
            }
            std::string restaurant = argv[2];
            std::string menuFile = "menus/" + restaurant + ".txt";
            auto menu = readMenuFile(menuFile);
            std::cout << CYAN << "\n--- MENU ---\n" << RESET;
            for (const auto& pair : menu) {
                std::cout << pair.first << " - $" << pair.second << "\n";
            }

        } else {
            std::cerr << RED << "\n[ERROR] Unknown command.\n" << RESET;
            showHelp();
        }
    }
    return 0;
}



#pragma once
#include <vector>
#include <string>

struct CartItem {
    std::string itemName;
    double unitPrice;
    int quantity;
    std::string customizations;
};

class Cart {
public:
    void addItem(const CartItem& item);
    double getTotal() const;
    const std::vector<CartItem>& getItems() const;

private:
    std::vector<CartItem> items;
};

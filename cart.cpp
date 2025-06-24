#include "cart.h"

void Cart::addItem(const CartItem& item) {
    items.push_back(item);
}

double Cart::getTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.unitPrice * item.quantity;
    }
    return total;
}
const std::vector<CartItem>& Cart::getItems() const {
    return items;
}
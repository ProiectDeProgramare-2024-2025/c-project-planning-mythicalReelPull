# 🍕 FoodApp CLI

A lightweight command-line food ordering system where users can view restaurant menus, place customized orders, and check past order histories.

---

## ✅ Features

- View menu from selected restaurant
- Place orders with customizations (e.g., size, toppings, notes)
- Store and view order history in `.csv` files per restaurant
- Interactive or CLI usage

---

## 📦 Project Structure

```
FoodApp/
├── menus/             # Menu files for each restaurant (e.g., DaMario.txt)
├── histories/         # Auto-generated order history CSVs per restaurant
├── main.cpp           # Entry point
├── cli.cpp/.h         # Interactive mode logic
├── cart.cpp/.h        # Cart data structures and operations
├── fileio.cpp/.h      # File handling (menu reading, CSV writing)
├── Makefile           # Easy compilation
```

---

## 🔧 Dependencies

- **C++17 or newer**: Required for modern STL features
- **Make**: For easy compilation on Linux/Mac or via MinGW on Windows
- **g++**: GNU compiler (or compatible, e.g., Clang)

---

## 🛠️ How to Compile

1. **Using `make`:**
   ```bash
   make
   ```

2. **Manual g++ compilation (if `make` is unavailable):**
   ```bash
   g++ -std=c++17 main.cpp cli.cpp cart.cpp fileio.cpp -o foodapp.exe
   ```

---

## ▶️ Usage

### 1. Run interactively:
```bash
./foodapp.exe
```

### 2. List Menu:
```bash
./foodapp.exe --list DaMario
```

### 3. Place an order:
```bash
./foodapp.exe --order \
    --item "Pizza Diavola" --qty 2 --custom "Size: <small, medium, large> Toppings: <comma separated>, Sauces: <comma separated>" \
    --item "Water" --qty 1 \
    --item "Coca-Cola" --qty 2 --custom "Cold" \
    --name "Alfred" --address "Timisoara" --phone "0712345678" \
    --restaurant DaMario
```

### 4. View order history:
```bash
./foodapp.exe --history --restaurant DaMario
```

---

## 📄 Notes

- All menus should be located in the `menus/` folder as `<restaurant>.txt`
- Order histories will be stored in `histories/<restaurant>_orders.csv`
- You can add new restaurants by simply creating a new menu file in the `menus/` folder

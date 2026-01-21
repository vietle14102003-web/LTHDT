#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include "Product.h"
#include "Order.h"

class Manager {
    vector<Product> products;
    vector<Order> orders;
public:
    void load();
    void save();
    void menu();
};

#endif

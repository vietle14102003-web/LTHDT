#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "OrderItem.h"

class Order {
    string id;
    vector<OrderItem> items;
public:
    Order();

    string getId() const;

    void input();
    void setId(const string &id);

    void addProduct(const Product &p);
    void updateQuantity(const string &pid);
    void removeProduct(const string &pid);
    void updateProductInOrder(const Product &p); 

    bool hasProduct(const string &pid) const;
    bool isEmpty() const;

    void output() const;

    void writeToFile(ofstream &out);
    void readFromFile(ifstream &in);
};

#endif

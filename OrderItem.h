#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "Product.h"

class OrderItem {
    Product product;
    int quantity;
public:
    OrderItem();

    string getProductId() const;

    void input(const Product &p);
    void updateProduct(const Product &p);   
    void setQuantity(int q);
    void output() const;

    void writeToFile(ofstream &out);
    void readFromFile(ifstream &in);
};

#endif

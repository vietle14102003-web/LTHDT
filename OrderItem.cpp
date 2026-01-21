#include "OrderItem.h"
#include <iostream>

OrderItem::OrderItem() : quantity(0) {}

string OrderItem::getProductId() const {
    return product.getId();
}

void OrderItem::input(const Product &p) {
    product = p;
    cout << "So luong: ";
    while (!(cin >> quantity)) {
        cout << "Nhap sai kieu du lieu cua so luong! Nhap lai: ";
        cin.clear(); cin.ignore(1000, '\n');
    }
}

void OrderItem::updateProduct(const Product &p) {
    if (product.getId() == p.getId()) {
        product = p;
    }
}


void OrderItem::setQuantity(int q) {
    quantity = q;
}

void OrderItem::output() const {
    product.output();
    cout << "So luong: " << quantity << endl;
}

void OrderItem::writeToFile(ofstream &out) {
    product.writeToFile(out);
    out.write((char*)&quantity, sizeof(quantity));
}

void OrderItem::readFromFile(ifstream &in) {
    product.readFromFile(in);
    in.read((char*)&quantity, sizeof(quantity));
}

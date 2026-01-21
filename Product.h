#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <fstream>
using namespace std;

class Product {
    string id;
    string name;
    double price;
public:
    Product();
    void setId(const string &id);
    void inputName();
    void inputPrice();

    string getId() const;
    string getName() const;
    double getPrice() const;

    void input();
    void edit();              
    void output() const;

    void writeToFile(ofstream &out);
    void readFromFile(ifstream &in);
};

#endif

#include "Product.h"
#include <iostream>

Product::Product() : price(0) {}

string Product::getId() const { return id; }
string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
void Product::setId(const string &id) {
    this->id = id;
}

void Product::inputName() {
    getline(cin, name);
}

void Product::inputPrice() {
    while (!(cin >> price)) {
        cout << "Nhap sai kieu du lieu cua gia! Nhap lai: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

static void inputDouble(double &x, const string &name) {
    while (true) {
        cin >> x;
        if (!cin.fail()) break;
        cout << "Nhap sai kieu du lieu cua " << name << "! Nhap lai: ";
        cin.clear(); cin.ignore(1000, '\n');
    }
}

void Product::input() {
    cin.ignore();
    cout << "Ma SP: ";
    getline(cin, id);
    cout << "Ten SP: ";
    getline(cin, name);
    cout << "Gia: ";
    inputDouble(price, "gia");
}

void Product::edit() {
    int ch;
    do {
        cout << "\n--- SUA SAN PHAM ---\n";
        cout << "1.Sua ten\n2.Sua gia\n3.Sua tat ca\n0.Thoat\nChon: ";
        cin >> ch;

        switch (ch) {
        case 1:
            cin.ignore();
            cout << "Ten moi: ";
            getline(cin, name);
            break;
        case 2:
            cout << "Gia moi: ";
            inputDouble(price, "gia");
            break;
        case 3:
            cin.ignore();
            cout << "Ten moi: ";
            getline(cin, name);
            cout << "Gia moi: ";
            inputDouble(price, "gia");
            break;
        }
    } while (ch != 0);
}


void Product::output() const {
    cout << "Ma: " << id << " | Ten: " << name << " | Gia: " << price << endl;
}

void Product::writeToFile(ofstream &out) {
    int len = id.size();
    out.write((char*)&len, sizeof(len));
    out.write(id.c_str(), len);

    len = name.size();
    out.write((char*)&len, sizeof(len));
    out.write(name.c_str(), len);

    out.write((char*)&price, sizeof(price));
}

void Product::readFromFile(ifstream &in) {
    int len;
    char buf[256];

    in.read((char*)&len, sizeof(len));
    in.read(buf, len);
    id.assign(buf, len);

    in.read((char*)&len, sizeof(len));
    in.read(buf, len);
    name.assign(buf, len);

    in.read((char*)&price, sizeof(price));
}

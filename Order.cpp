#include "Order.h"
#include <iostream>

using namespace std;

/* ===== HÀM NHẬP INT AN TOÀN (TRÁNH LOOP VÔ HẠN) ===== */
static void inputInt(int &x, const string &name) {
    while (true) {
        cin >> x;
        if (!cin.fail()) break;

        cout << "Nhap sai kieu du lieu cua " << name << "! Nhap lai: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

/* ======================= ORDER ======================= */

Order::Order() {}

string Order::getId() const {
    return id;
}
void Order::setId(const string &id) {
    this->id = id;
}
bool Order::isEmpty() const {
    return items.empty();
}

bool Order::hasProduct(const string &pid) const {
    for (auto &it : items)
        if (it.getProductId() == pid)
            return true;
    return false;
}

void Order::input() {
    cout << "Ma don hang: ";
    cin >> id;
}

void Order::addProduct(const Product &p) {
    if (hasProduct(p.getId())) {
        cout << "San pham da ton tai trong don hang!\n";
        return;
    }

    OrderItem item;
    item.input(p);
    items.push_back(item);
}

void Order::updateQuantity(const string &pid) {
    for (auto &it : items) {
        if (it.getProductId() == pid) {
            int q;
            cout << "So luong moi: ";
            inputInt(q, "so luong");
            it.setQuantity(q);
            cout << "Cap nhat thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay san pham trong don!\n";
}

void Order::removeProduct(const string &pid) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getProductId() == pid) {
            items.erase(it);
            cout << "Da xoa san pham khoi don hang!\n";
            return;
        }
    }
    cout << "Khong tim thay san pham trong don!\n";
}

void Order::output() const {
    cout << "\n===== DON HANG: " << id << " =====\n";
    if (items.empty()) {
        cout << "Don hang rong!\n";
        return;
    }

    for (auto &it : items)
        it.output();
}

/* ================== FILE NHỊ PHÂN ================== */

void Order::writeToFile(ofstream &out) {
    int len = id.size();
    out.write((char*)&len, sizeof(len));
    out.write(id.c_str(), len);

    int n = items.size();
    out.write((char*)&n, sizeof(n));
    for (auto &it : items)
        it.writeToFile(out);
}

void Order::readFromFile(ifstream &in) {
    int len, n;
    char buf[256];

    in.read((char*)&len, sizeof(len));
    in.read(buf, len);
    id.assign(buf, len);

    in.read((char*)&n, sizeof(n));
    items.clear();

    for (int i = 0; i < n; i++) {
        OrderItem it;
        it.readFromFile(in);
        items.push_back(it);
    }
}
void Order::updateProductInOrder(const Product &p) {
    for (auto &it : items)
        it.updateProduct(p);
}


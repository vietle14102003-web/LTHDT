#include "Manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

static void pause() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

static void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* ===== LOAD / SAVE ===== */
void Manager::load() {
    ifstream in("data.bin", ios::binary);
    if (!in) return;

    int n;
    in.read((char*)&n, sizeof(n));
    products.resize(n);
    for (int i = 0; i < n; i++)
        products[i].readFromFile(in);

    in.read((char*)&n, sizeof(n));
    orders.resize(n);
    for (int i = 0; i < n; i++)
        orders[i].readFromFile(in);

    in.close();
}

void Manager::save() {
    ofstream out("data.bin", ios::binary);

    int n = products.size();
    out.write((char*)&n, sizeof(n));
    for (auto &p : products)
        p.writeToFile(out);

    n = orders.size();
    out.write((char*)&n, sizeof(n));
    for (auto &o : orders)
        o.writeToFile(out);

    out.close();
}

/* ===== TIỆN ÍCH ===== */
bool productExists(const vector<Product>& products, const string& id) {
    for (auto &p : products)
        if (p.getId() == id) return true;
    return false;
}

bool orderExists(const vector<Order>& orders, const string& id) {
    for (auto &o : orders)
        if (o.getId() == id) return true;
    return false;
}

bool productInOrders(const vector<Order>& orders, const string& pid) {
    for (auto &o : orders)
        if (o.hasProduct(pid)) return true;
    return false;
}

/* ===== MENU CHÍNH ===== */
void Manager::menu() {
    int choice;

    do {
        clear();
        cout << "========= MENU =========\n";
        cout << "1.Them SP\n2.Sua SP\n3.Xoa SP\n";
        cout << "4.Them don\n5.Sua don\n6.Xoa don\n";
        cout << "7.Hien SP\n8.Hien don\n9.Thoat\n";
        cout << "Chon: ";

        while (!(cin >> choice)) {
            cout << "Nhap sai kieu du lieu cua lua chon! Nhap lai: ";
            cin.clear(); cin.ignore(1000, '\n');
        }

        /* ===== XỬ LÝ ===== */
        if (choice == 1) {
            clear();

            Product p;
            string id;
            bool exists;

            do {
                exists = false;
                cout << "Nhap ma san pham: ";
                cin >> id;

                for (auto &x : products) {
                    if (x.getId() == id) {
                        exists = true;
                        cout << "Ma san pham da ton tai! Vui long nhap lai.\n";
                        break;
                    }
                }
            } while (exists);

            cin.ignore();
            p = Product();   

            p.setId(id);

            cout << "Nhap ten san pham: ";
            p.inputName();

            cout << "Nhap gia: ";
            p.inputPrice();

            products.push_back(p);
            save();

            cout << "Them san pham thanh cong!\n";
            pause();
        }


        else if (choice == 2) {
            clear();
            string id;
            cout << "Nhap ma SP can sua: ";
            cin >> id;

            bool found = false;
            for (auto &p : products)
                if (p.getId() == id) {
                    p.edit();   

                    for (auto &o : orders)
                        o.updateProductInOrder(p);

                    save();
                    cout << "Sua SP va cap nhat don hang thanh cong!\n";
                    found = true;
                    break;
                }

            if (!found)
                cout << "Khong tim thay SP!\n";

            pause();
        }

        else if (choice == 3) {
            clear();
            string id;
            cout << "Nhap ma SP can xoa: ";
            cin >> id;

            if (productInOrders(orders, id)) {
                cout << "Khong the xoa! SP dang nam trong don hang!\n";
                pause();
                continue;
            }

            bool found = false;
            for (auto it = products.begin(); it != products.end(); ++it)
                if (it->getId() == id) {
                    products.erase(it);
                    found = true;
                    cout << "Xoa SP thanh cong!\n";
                    break;
                }

            if (!found) cout << "Khong tim thay SP!\n";
            pause();
        }

        else if (choice == 4) {
            clear();

            Order o;
            string oid;
            bool exists;

            do {
                exists = false;
                cout << "Nhap ma don hang: ";
                cin >> oid;

                for (auto &ord : orders) {
                    if (ord.getId() == oid) {
                        exists = true;
                        cout << "Ma don hang da ton tai! Vui long nhap lai.\n";
                        break;
                    }
                }
            } while (exists);

            o.setId(oid);

            char cont;
            do {
                string pid;
                cout << "Nhap ma san pham: ";
                cin >> pid;

                bool found = false;
                for (auto &p : products) {
                    if (p.getId() == pid) {
                        o.addProduct(p);
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "San pham khong ton tai!\n";

                cout << "Them san pham tiep? (y/n): ";
                cin >> cont;

            } while (cont == 'y' || cont == 'Y');

            if (!o.isEmpty()) {
                orders.push_back(o);
                save();
                cout << "Them don hang thanh cong!\n";
            } else {
                cout << "Don hang rong, khong duoc luu!\n";
            }

            pause();
        }



        else if (choice == 5) {
            clear();
            string oid;
            cout << "Nhap ma don can sua: ";
            cin >> oid;

            bool found = false;
            for (auto &o : orders)
                if (o.getId() == oid) {
                    found = true;
                    int c;
                    do {
                        clear();
                        cout << "1.Them SP\n2.Sua so luong\n3.Xoa SP\n0.Thoat\nChon: ";
                        cin >> c;

                        string pid;
                        if (c == 1) {
                            cout << "Ma SP: ";
                            cin >> pid;
                            for (auto &p : products)
                                if (p.getId() == pid)
                                    o.addProduct(p);
                            pause();
                        }
                        else if (c == 2) {
                            cout << "Ma SP: ";
                            cin >> pid;
                            o.updateQuantity(pid);
                            pause();
                        }
                        else if (c == 3) {
                            cout << "Ma SP: ";
                            cin >> pid;
                            o.removeProduct(pid);
                            pause();
                        }
                    } while (c != 0);
                    break;
                }

            if (!found) {
                cout << "Khong tim thay don!\n";
                pause();
            }
        }

        else if (choice == 6) {
            clear();
            string oid;
            cout << "Nhap ma don can xoa: ";
            cin >> oid;

            bool found = false;
            for (auto it = orders.begin(); it != orders.end(); ++it)
                if (it->getId() == oid) {
                    orders.erase(it);
                    found = true;
                    cout << "Xoa don thanh cong!\n";
                    break;
                }

            if (!found) cout << "Khong tim thay don!\n";
            pause();
        }

        else if (choice == 7) {
            clear();

            // Sap xep san pham theo ma
            sort(products.begin(), products.end(),
                [](const Product &a, const Product &b) {
                    return a.getId() < b.getId();
                });

            cout << "\n===== DANH SACH SAN PHAM =====\n";
            for (auto &p : products) {
                p.output();
            }

            pause();
        }


        else if (choice == 8) {
            clear();

            // Sap xep don hang theo ma
            sort(orders.begin(), orders.end(),
                [](const Order &a, const Order &b) {
                    return a.getId() < b.getId();
                });

            cout << "\n===== DANH SACH DON HANG =====\n";
            for (auto &o : orders) {
                o.output();
            }

            pause();
        }


    } while (choice != 9);

    save();
}

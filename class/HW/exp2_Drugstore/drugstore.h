#ifndef __DRUGSTORE_H__
#define __DRUGSTORE_H__

#include <iostream>
using namespace std;

const int MEDICINE_NUM = 50;
const int PRICE_NUM = 7;

class Medicine {

private:
    int id;
    float origin_price;
    float price;
    int warranty;
    int status; // 1: in store, 2: in warehouse, 0: init,  -1: sold, -2: deleted
    int delete_day;
    // int expire_day;
public:
    enum {
        IN_STORE = 1,
        IN_WAREHOUSE = 2,
        INIT = 0,
        SOLD = -1,
        DELETED = -2,
        EXPIRED = -3
    };

    Medicine(int id, float origin_price, int warranty) {
        this->id = id;
        this->origin_price = origin_price;
        this->price = origin_price;
        this->warranty = warranty;
        this->status = IN_WAREHOUSE;
        this->delete_day = -1;
        // this->expire_day = 
    }

    Medicine() {
        this->id = -1;
        this->origin_price = -1;
        this->warranty = -1;
    }

    void print() {
        cout << "id: " << id << ", status: " << status << ", warranty: " << warranty << endl;
        cout << "  origin_price: " << origin_price << ", price: " << price << endl;
    }

    // < operator
    bool operator < (const Medicine& m) const {
        return this->price < m.price;
    }

    int get_id() {
        return this->id;
    }
    int get_warranty() {
        return this->warranty;
    }
    int get_status() {
        return this->status;
    }
    int get_origin_price() {
        return this->origin_price;
    }
    int get_price() {
        return this->price;
    }

    int init(int id, float origin_price, int warranty) {
        this->id = id;
        this->origin_price = origin_price;
        this->price = origin_price;
        this->warranty = warranty;
        this->status = IN_WAREHOUSE;
        this->delete_day = -1;
        return 1;
    }
    int add_delta_price(int delta_price) {
        this->price = this->origin_price + delta_price;
        return 1;
    }
    int set_id(int id) {
        this->id = id;
        return 1;
    }
    int set_status(int status) {
        this->status = status;
        return 1;
    }
    int decrease_warranty() {
        this->warranty--;
        return 1;
    }

}g_medicine[MEDICINE_NUM];

/*
* compare the price of two medicine
* if the price is the same, compare the warranty, 
* the medicine with longer warranty will be in front
*/
bool cmp_price_ptr(Medicine* a, Medicine* b) {
    if (a->get_price() != b->get_price()) {
        return a->get_price() < b->get_price();
    }
    else {
        return a->get_warranty() > b->get_warranty();
    }
}
bool cmp_price_ref(Medicine &a, Medicine& b) {
    if (a.get_price() != b.get_price()) {
        return a.get_price() < b.get_price();
    }
    else {
        return a.get_warranty() > b.get_warranty();
    }
}
/*
* compare the warranty of two medicine
* the medicine with longer warranty will be in front
*/
bool cmp_warranty_ptr(Medicine* a, Medicine* b) {
    return a->get_warranty() < b->get_warranty();
}

bool cmp_warranty_ref(Medicine &a, Medicine& b) {
    return a.get_warranty() < b.get_warranty();
}

struct CmpWarranty {
    bool operator() (Medicine* a, Medicine* b) {
        // return a->get_warranty() < b->get_warranty(); // 大根堆
        if (a->get_warranty() == b->get_warranty()) {
            // if the warranty is the same, compare the price
            // bigger price will be in front
            return a->get_price() < b->get_price();
        }
        else
        return a->get_warranty() > b->get_warranty(); // 小根堆
    }
};
const int STORE_SIZE = 10;
const int DAY_NUM = 10;

class Strategy {
private:
    int day;
    int medicine_id[STORE_SIZE];
    int medicine_delta_price[STORE_SIZE];

public:
    void print() {
        cout << "day: " << day << endl;
        for (int i = 0; i < STORE_SIZE; i++) {
            cout << "medicine_id: " << medicine_id[i] << ", medicine_delta_price: " << medicine_delta_price[i] << endl;
        }
    }

    int get_day() {
        return this->day;
    }
    int get_medicine_id(int i) {
        return this->medicine_id[i];
    }
    int get_medicine_delta_price(int i) {
        return this->medicine_delta_price[i];
    }

    int set_day(int day) {
        this->day = day;
        return 1;
    }

    int set_medicine_id(int i, int medicine_id) {
        this->medicine_id[i] = medicine_id;
        return 1;
    }
    int set_medicine_delta_price(int i, int medicine_delta_price) {
        this->medicine_delta_price[i] = medicine_delta_price;
        return 1;
    }

    int set_id_and_price(int i, int id, int price) {
        this->medicine_id[i] = id;
        this->medicine_delta_price[i] = price;
        return 1;
    }


}g_strategies[DAY_NUM];

const int DELETE_NUM = 3;

class Delete {
public:
    int day;
    int medicine_id;

    void print() {
        cout << "day: " << day << ", medicine_id: " << medicine_id << endl;
    }
}g_deletes[DELETE_NUM];

const int CUSTOMER_NUM = 3;

#endif // !__DRUGSTORE_H__
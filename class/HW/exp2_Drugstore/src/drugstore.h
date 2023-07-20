#ifndef __DRUGSTORE_H__
#define __DRUGSTORE_H__

#include <iostream>
using namespace std;

class Medicine {
private:
    int id;
    int status;
    float origin_price;
    float price;
    int expire_day;
    int delete_day;
public:
    enum {
        IN_STORE = 1,
        IN_WAREHOUSE = 2,
        INIT = 0,
        SOLD = -1,
        DELETED = -2,
        EXPIRED = -3
    };
    Medicine(int id, float origin_price, int expire_day) {
        this->id = id;
        this->origin_price = origin_price;
        this->price = origin_price;
        this->expire_day = expire_day;
        this->status = IN_WAREHOUSE;
        this->delete_day = -1;
    }

    Medicine() {
        this->id = id;
        this->origin_price = -1;
        this->price = -1;
        this->expire_day = -1;
        this->status = INIT;
        this->delete_day = -1;
    }

    int init(int id, float origin_price, int expire_day) {
        this->id = id;
        this->origin_price = origin_price;
        this->price = origin_price;
        this->expire_day = expire_day;
        this->status = IN_WAREHOUSE;
        this->delete_day = -1;
        return 1;
    }

    void print() {
        cout << "    " << "id: " << id << ", status: " << status << ", expire_day: " << expire_day;
        cout << ", origin_price: " << origin_price << ", price: " << price << endl;
    }

    // get private member
    int get_id() {
        return this->id;
    }
    int get_status() {
        return this->status;
    }
    float get_origin_price() {
        return this->origin_price;
    }
    float get_price() {
        return this->price;
    }
    int get_expire_day() {
        return this->expire_day;
    }
    int get_delete_day() {
        return this->delete_day;
    }

    void set_price_delta(float delta_price){
        this->price = this->origin_price + delta_price;
    }

    void set_status(int status){
        this->status = status;
    }

    void set_delete_day(int delete_day){
        this->delete_day = delete_day;
    }
};

/*
    价格高的在前面
    价格相同，过期时间小的在前
*/
bool seller_cmp_oprice_ptr(Medicine* a, Medicine* b) {
    if (a->get_origin_price() == b->get_origin_price()){
        return a->get_expire_day() < b->get_expire_day();
    }
    else{
        return a->get_origin_price() > b->get_origin_price();
    }
}

bool buyer_cmp_price_ptr(Medicine* a, Medicine* b) {
    if (a->get_price() == b->get_price()){
        return a->get_expire_day() > b->get_expire_day();
    }
    else{
        return a->get_price() < b->get_price();
    }
}

/*
sort medicine by expire_day
if expire_day is the same, sort by price
the smaller expire_day, the more front
*/
bool cmp_expire_day_ptr(Medicine* a, Medicine* b) {
    if (a->get_expire_day() == b->get_expire_day()) {
        return a->get_origin_price() < b->get_origin_price();
    }
    return a->get_expire_day() < b->get_expire_day();
}
bool cmp_expire_day_ref(Medicine& a, Medicine& b) {
    if (a.get_expire_day() == b.get_expire_day()) {
        return a.get_origin_price() > b.get_origin_price();
    }
    return a.get_expire_day() < b.get_expire_day();
}

struct Strategy{

    int mid;
    int delta_id;
    float delta_price;

};

struct Delete{
    int day;
    int mid;
};


#endif // !__DRUGSTORE_H__
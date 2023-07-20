#include <bits/stdc++.h>
#include "drugstore.h"

using namespace std;

/*
-- compile:
g++ -g -Wall drugstore.cpp -o drugstore

-- debug compile:
g++ -g -Wall -DDEBUG drugstore.cpp -o drugstore

-- usage:
./drugstore -m ../test/data1/medicine.txt -s ../test/data1/strategy.txt -d ../test/data1/delete.txt
./drugstore -m ../test/data2/medicine.txt -s ../test/data2/strategy.txt -d ../test/data2/delete.txt
./drugstore -m ../test/data4/medicine.txt -s ../test/data4/strategy.txt -d ../test/data4/delete.txt

./drugstore -m ../data/data2/medicine.txt -s ../data/data2/strategy.txt -d delete.txt
./drugstore -m ./medicine.txt -s ./strategy.txt -d delete.txt

./drugstore -m ../test/data4/medicine.txt -s ../test/data4/strategy.txt -d ../test/data4/delete.txt
*/

#define PRICE_NUM 7
#define SIM_DAY_NUM 10
#define STORE_SIZE 10
#define MEDICINE_NUM 50
#define CUSTOMER_NUM 3

float g_delta_price[PRICE_NUM] = { -1.5, -1, -0.5, 0, 2, 4, 6 };

string medicine_path = "";
string in_strategy_path = "";
string in_delete_path = "";

float g_profit = 0;
float g_purchase_price = 0; // purchase price for sold medicine
float g_sale_price = 0;
float g_warehouse_price = 0;
float g_delete_expired_price = 0;

Strategy g_strategy[SIM_DAY_NUM + 1][STORE_SIZE]; /* g_srategy[day][index] */
// vector<Delete> g_delete;
vector<vector<int>> g_delete(SIM_DAY_NUM + 1, vector<int>(0, 0)); /* g_delete[day][index] */
vector<Medicine> g_medicine;

int parse_argv(int argc, char* argv[]);
int read_files(const string& medicine_path, const string& in_strategy_path, const string& in_delete_path);
void print_all();
int sim_day(int day);

int main(int argc, char* argv[]) {
    parse_argv(argc, argv);
    read_files(medicine_path, in_strategy_path, in_delete_path);
#if DEBUG
    print_all();
#endif
    for (int day = 1; day <= SIM_DAY_NUM; day++) {
        int res = sim_day(day);
        if (res == 0) {
            cout << "day " << day << " failed" << endl;
            break;
        }
    }

    g_profit = g_sale_price - g_purchase_price - g_warehouse_price - g_delete_expired_price;
    // set precision
    cout << fixed << setprecision(5);
    cout << "g_sale_price: " << g_sale_price << endl;
    cout << "g_purchase_price: " << g_purchase_price << endl;
    cout << "g_warehouse_price: " << g_warehouse_price << endl;
    cout << "g_delete_expired_price: " << g_delete_expired_price << endl;
    cout << "g_profit: " << g_profit << endl;

}

int parse_argv(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0) {
            medicine_path = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0) {
            in_strategy_path = argv[++i];
        }
        else if (strcmp(argv[i], "-d") == 0) {
            in_delete_path = argv[++i];
        }
    }
    if (medicine_path == "" || in_strategy_path == "" || in_delete_path == "") {
        cout << "parse argv failed" << endl;
        return 0;
    }
    return 1;
}

int read_files(const string& medicine_path, const string& in_strategy_path, const string& in_delete_path) {
    string line;

    ifstream medicine_file(medicine_path);
    if (!medicine_file.is_open()) {
        cout << "open medicine file failed" << endl;
        return 0;
    }

    int mid = 0;
    while (getline(medicine_file, line)) {
        stringstream ss(line);
        float origin_price;
        int expire_day;
        ss >> origin_price;
        ss >> expire_day;
        Medicine medicine(mid, origin_price, expire_day);
        g_medicine.push_back(medicine);
        mid++;
    }
    if (mid != MEDICINE_NUM) {
        cout << "mid and MEDICNIE_NUM doesn't match" << endl;
        cout << "mid: " << mid << ", MEDICINE_NUM: " << MEDICINE_NUM << endl;
    }
#ifdef DEBUG
    cout << "medicine size: " << g_medicine.size() << endl;
#endif
    medicine_file.close();
    ifstream strategy_file(in_strategy_path);
    if (!strategy_file.is_open()) {
        cout << "open strategy file failed" << endl;
        return 0;
    }
    int day = 0;

    for (day = 1; day <= SIM_DAY_NUM; day++) {
        getline(strategy_file, line);
        istringstream iss(line);
        for (int index = 0; index < STORE_SIZE; index++) {
            string subs;
            int mid, delta_index;
            float delta_price;
            iss >> subs;
            stringstream ss(subs);
            ss >> mid;
            ss.ignore();
            ss >> delta_index;
            delta_price = g_delta_price[delta_index];
            g_strategy[day][index] = { mid, delta_index, delta_price };
        }
    }
    strategy_file.close();
#ifdef DEBUG    
    cout << "strategy read over" << endl;
#endif
    ifstream delete_file(in_delete_path);
    if (!delete_file.is_open()) {
        cout << "open delete file failed" << endl;
        return 0;
    }
    while (getline(delete_file, line)) {
        int day, mid;
        stringstream ss(line);
        ss >> day;
        ss >> mid;
#ifdef DEBUG
        cout << "day: " << day << ", mid: " << mid << endl;
#endif
        g_delete[day].push_back(mid);
    }
    delete_file.close();
#ifdef DEBUG
    cout << "delete size: " << sizeof(g_delete) << endl;
#endif

    return 1;
}

void print_all() {
    cout << "------ print all ------" << endl;
    cout << "medicine: " << endl;
    for (auto medicine : g_medicine) {
        medicine.print();
    }
    cout << "strategy: " << endl;
    for (int day = 1; day <= SIM_DAY_NUM; day++) {
        cout << "day: " << day << endl;
        for (int index = 0; index < STORE_SIZE; index++) {
            cout << "index: " << index << ", ";
            cout << " mid: " << g_strategy[day][index].mid << ", delta_price: " << g_strategy[day][index].delta_price << endl;
        }
    }
    cout << "delete: " << endl;
    for (int day = 1; day <= SIM_DAY_NUM; day++) {
        cout << "day: " << day << " -- ";
        for (auto mid : g_delete[day]) {
            cout << "mid: " << mid << ", ";
        }
        cout << endl;
    }
    cout << "------ print all end ------" << endl;
}

void print_g_medicine() {
    cout << "------ print g_medicine ------" << endl;
    for (auto medicine : g_medicine) {
        medicine.print();
    }
    cout << "------ print g_medicine end ------" << endl;
}

int sim_day(int day) {
#ifdef DEBUG
    cout << "------- Sim day: " << day << " ------" << endl;
#endif
    // delete medicine
    for (auto d_mid : g_delete[day]) {
        auto it = g_medicine.begin();
        while (it != g_medicine.end()) {
            if (it->get_id() == d_mid) {
                if (it->get_status() == Medicine::SOLD) {
                    cout << "delete sold medicine" << endl;
                    return 0;
                }
                if (it->get_status() == Medicine::DELETED) {
                    cout << "delete deleted medicine" << endl;
                    return 0;
                }
                if (it->get_status() == Medicine::EXPIRED) {
                    cout << "delete expired medicine" << endl;
                    return 0;
                }
                it->set_status(Medicine::DELETED);
                it->set_delete_day(day);
                g_delete_expired_price += it->get_origin_price();
#ifdef DEBUG
                cout << "- delete medicine:" << endl;
                it->print();
#endif
                it = g_medicine.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    // choose medicine to sell on the store
    vector<Medicine*> medicine_p_in_store;
    for (auto strategy : g_strategy[day]) {
        int mid = strategy.mid;
        float delta_price = strategy.delta_price;
        for (auto& medicine : g_medicine) {
            if (medicine.get_id() == mid) {
                medicine.set_price_delta(delta_price);
                medicine.set_status(Medicine::IN_STORE);
                medicine_p_in_store.push_back(&medicine);
                break;
            }
        }
    }
    // sort medicine_in_store
    sort(medicine_p_in_store.begin(), medicine_p_in_store.end(), buyer_cmp_price_ptr);
#if DEBUG
    cout << "medicine_p_in_store: " << endl;
    cout << "medicine_p_in_store size: " << medicine_p_in_store.size() << endl;
    for (auto medicine : medicine_p_in_store) {
        medicine->print();
    }
#endif
    int medicine_in_store_num = medicine_p_in_store.size();
    // sell medicine
    for (int i = 0; (i < CUSTOMER_NUM) && (i < medicine_in_store_num); i++) {
        medicine_p_in_store[i]->set_status(Medicine::SOLD);
        // medicine_p_in_store[i]->set_sale_day(day);
        g_sale_price += medicine_p_in_store[i]->get_price();
        g_purchase_price += medicine_p_in_store[i]->get_origin_price();
    }

    auto it = g_medicine.begin();
    while (it != g_medicine.end()) {
        if (it->get_status() == Medicine::SOLD) {
            // print_g_medicine();
#ifdef DEBUG
            cout << "- erase sold medicine:" << endl;
            it->print();
#endif
            it = g_medicine.erase(it);
        }
        else {
            if (it->get_status() == Medicine::IN_WAREHOUSE) {
                // update g_warehouse_price
                float warehouse_price = it->get_expire_day() - day < 5 ? 1 : 0.5;
                g_warehouse_price += warehouse_price;
            }
            else if (it->get_status() == Medicine::IN_STORE) {
                it->set_status(Medicine::IN_WAREHOUSE);
            }

            if (it->get_expire_day() == day) {
                it->set_status(Medicine::EXPIRED);
#ifdef DEBUG
                cout << "- erase expired medicine:" << endl;
                it->print();
#endif
                g_delete_expired_price += it->get_origin_price();
                it = g_medicine.erase(it);
            }
            else {
                ++it;
            }
        }
}
#ifdef DEBUG
    cout << "------ end sim day: " << day << " -------" << endl;
#endif
    return 1;
}
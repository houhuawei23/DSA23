#include <bits/stdc++.h>
#include "drugstore.h"
using namespace std;

// #define DEBUG 1
/*
compile:
    g++ -g -Wall drugstore.cpp -o drugstore
debug compile:
    g++ -g -Wall -DDEBUG drugstore.cpp -o drugstore
usage:
    ./drugstore.exe -m ../test/data1/medicine.txt -s ../test/data1/strategy.txt -d ../test/data1/delete.txt
    ./drugstore -m ../data/data2/medicine.txt -s ../data/data2/strategy.txt -d delete.txt
    ./drugstore -m ./medicine.txt -s ./strategy.txt -d delete.txt

delete.txt是输出文件，代表我在什么时候扔掉过期的药品
*/

float g_delta_price[PRICE_NUM] = { -1.5, -1, -0.5, 0, 2, 4, 6 };

int sim_day(int day);
int read_files(string medicine_path, string strategy_path, string delete_path);

float g_profit = 0;
float g_purchase_price = 0; // purchase price for sold medicine
float g_sale_price = 0;
float g_warehouse_price = 0;
float g_delete_expired_price = 0;

int main(int argc, char* argv[]) {
    // parse the input
    string medicine_path = "";
    string strategy_path = "";
    string delete_path = "";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0) {
            medicine_path = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0) {
            strategy_path = argv[++i];
        }
        else if (strcmp(argv[i], "-d") == 0) {
            delete_path = argv[++i];
        }
    }
#if DEBUG
    cout << "medicine_path: " << medicine_path << endl;
    cout << "strategy_path: " << strategy_path << endl;
    cout << "delete_path: " << delete_path << endl;
#endif
    read_files(medicine_path, strategy_path, delete_path);

    int day = 0;
    // main loop for sim 
    for (day = 0; day < DAY_NUM; day++) {
        int res = sim_day(day);
        if (res == 0) {
            cout << "day " << day << " failed" << endl;
            break;
        }
    }

    g_profit = g_sale_price - g_purchase_price - g_warehouse_price - g_delete_expired_price;
    cout << "g_profit: " << g_profit << endl;
    cout << "g_sale_price: " << g_sale_price << endl;
    cout << "g_purchase_price: " << g_purchase_price << endl;
    cout << "g_warehouse_price: " << g_warehouse_price << endl;
    cout << "g_delete_expired_price: " << g_delete_expired_price << endl;
}


/*
read medicine file, strategy file and delete file
return 1 if success, 0 if failed
*/
int read_files(string medicine_path, string strategy_path, string delete_path) {
    // read medicine file
    ifstream medicine_file(medicine_path);
    if (!medicine_file.is_open()) {
        cout << "medicine file open failed" << endl;
        return 0;
    }
    for (int i = 0; i < MEDICINE_NUM; i++) {
        float origin_price;
        int warranty;
        medicine_file >> origin_price >> warranty;
        g_medicine[i].init(i, origin_price, warranty);
        // g_purchase_price += origin_price;
#if DEBUG
        // g_medicine[i].print();
#endif
    }
    medicine_file.close();

    // read strategy file
    ifstream strategy_file(strategy_path);
    string line;
    if (!strategy_file.is_open()) {
        cout << "strategy file open failed" << endl;
        return 0;
    }
    for (int i = 0; i < DAY_NUM; i++) {
        g_strategies[i].set_day(i);
        getline(strategy_file, line);
        istringstream iss(line);
        for (int j = 0; j < STORE_SIZE; j++) {
            string subs;
            int id, delta_index;
            int delta_price;
            iss >> subs;
            stringstream ss(subs);
            ss >> id;
            ss.ignore();
            ss >> delta_index;
            delta_price = g_delta_price[delta_index];
            g_strategies[i].set_id_and_price(j, id, delta_price);
        }

#if DEBUG
        g_strategies[i].print();
#endif
    }
    strategy_file.close();

    // read delete file
    ifstream delete_file(delete_path);
    if (!delete_file.is_open()) {
        cout << "delete file open failed" << endl;
        return 0;
    }
    for (int i = 0; i < DELETE_NUM; i++) {
        delete_file >> g_deletes[i].day >> g_deletes[i].medicine_id;
    

#if DEBUG
        g_deletes[i].print();
#endif
    }
    delete_file.close();
    return 1;
}

/*
simulate a day
*/
int sim_day(int day) {
    cout << "Simulation day: " << day << endl;
    // delete medicine
    for (int i = 0; i < DELETE_NUM; i++) {
        if (g_deletes[i].day == day) {
            g_medicine[g_deletes[i].medicine_id].set_status(Medicine::DELETED);
            g_delete_expired_price += g_medicine[g_deletes[i].medicine_id].get_origin_price();
            cout << "Delete.txt: medicine " << g_deletes[i].medicine_id << " has been deleted" << endl;
        }
    }

    // 从 g_strategies[day]中，选出要购买的3种药品
    Medicine* medicine_in_store[STORE_SIZE];
    int medicine_in_store_num = 0;
    for (int i = 0; i < STORE_SIZE; i++) {
        if (g_strategies[day].get_medicine_id(i) == -1) {
            cout << "not valid medicine id" << endl;
            continue;
        }
        medicine_in_store[medicine_in_store_num] = &(g_medicine[g_strategies[day].get_medicine_id(i)]);

        // check if the medicine is ok
        if (medicine_in_store[medicine_in_store_num]->get_status() < 0) {
            if (medicine_in_store[medicine_in_store_num]->get_status() == -1) {
                cout << "Warning: medicine " << medicine_in_store[medicine_in_store_num]->get_id() << " has been sold" << endl;
            }
            else if (medicine_in_store[medicine_in_store_num]->get_status() == -2) {
                cout << "Warning: medicine " << medicine_in_store[medicine_in_store_num]->get_id() << " has been deleted" << endl;
            }
            else if (medicine_in_store[medicine_in_store_num]->get_status() == -3) {
                cout << "Warning: medicine " << medicine_in_store[medicine_in_store_num]->get_id() << " has been expired" << endl;
            }
            continue;
        }

        // set the price
        medicine_in_store[medicine_in_store_num]->add_delta_price(g_strategies[day].get_medicine_delta_price(i));
        // set the status
        medicine_in_store[medicine_in_store_num]->set_status(Medicine::IN_STORE);

        medicine_in_store_num++;
    }
    // #if DEBUG
    //     // sort the medicine in store by price
    //     cout << "medicine in store: " << endl;
    //     for (int i = 0; i < medicine_in_store_num; i++) {
    //         medicine_in_store[i]->print();
    //     }
    // #endif  
    sort(medicine_in_store, medicine_in_store + medicine_in_store_num, cmp_price_ptr);
#if DEBUG
    // print the medicine in store
    cout << "with " << medicine_in_store_num << " medicine" << endl;
    cout << "after sorted: medicine in store: " << endl;
    for (int i = 0; i < medicine_in_store_num; i++) {
        medicine_in_store[i]->print();
    }
#endif

    // TODO: 从 g_deletes[day]中，选出要删除的药品
    for (int i = 0; i < CUSTOMER_NUM; i++) {
        medicine_in_store[i]->set_status(Medicine::SOLD);
        cout << "medicine " << medicine_in_store[i]->get_id() << " has been sold" << endl;
        // TODO: update the profit?
        g_sale_price += medicine_in_store[i]->get_price();
        g_purchase_price += medicine_in_store[i]->get_origin_price();
    }

    // update g_warehouse_price
    for (int i = 0; i < MEDICINE_NUM; i++) {
        if (g_medicine[i].get_status() == Medicine::IN_WAREHOUSE) {
            float warehouse_price = 1 ? g_medicine[i].get_warranty() < 5 : 0.5;
            g_warehouse_price += warehouse_price;
        }
    }


    // end of day
    // update medicine status
    for (int i = 0; i < medicine_in_store_num; i++) {
        if (medicine_in_store[i]->get_status() == Medicine::IN_STORE) {
            medicine_in_store[i]->set_status(Medicine::IN_WAREHOUSE);
        }
    }
    for (int i = 0; i < MEDICINE_NUM; i++) {
        if (g_medicine[i].get_status() == Medicine::IN_WAREHOUSE) {
            g_medicine[i].decrease_warranty();
            if (g_medicine[i].get_warranty() == 0) {
                g_medicine[i].set_status(Medicine::EXPIRED);
                g_delete_expired_price += g_medicine[i].get_origin_price();
                cout << "medicine " << g_medicine[i].get_id() << " has been expired" << endl;
            }
        }
    }
    cout << "end of day" << endl;
    cout << endl;
    return 1;
}


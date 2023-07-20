#include <bits/stdc++.h>
#include "drugstore.h"
using namespace std;


float g_delta_price[PRICE_NUM] = { -1.5, -1, -0.5, 0, 2, 4, 6 };
string medicine_path = "";
string in_strategy_path = "";
string out_strategy_path = "";
string in_delete_path = "";
string out_delete_path = "";

int parse_argv(int argc, char* argv[]);

typedef priority_queue<Medicine*, vector<Medicine*>, CmpWarranty> PQMedicine;
typedef vector<Medicine*> VMedicine;

float g_profit = 0;
float g_purchase_price = 0; // purchase price for sold medicine
float g_sale_price = 0;
float g_warehouse_price = 0;
float g_delete_expired_price = 0;

int main(int argc, char* argv[]) {
    int parse_res = parse_argv(argc, argv);

    PQMedicine pq_medicine;
    // priority_queue<Medicine*, vector<Medicine*>, CmpWarranty> pq_medicine_in_store;
    vector<Medicine*> v_medicine_deleted;

    // read medicine
    ifstream medicine_file(medicine_path);
    if (!medicine_file.is_open()) {
        cout << "medicine file open failed" << endl;
    }
    for (int i = 0; i < MEDICINE_NUM; i++) {
        float origin_price;
        int warranty;
        medicine_file >> origin_price >> warranty;

        // Medicine* m = new Medicine(i, origin_price, warranty);
        g_medicine[i].init(i, origin_price, warranty);
        pq_medicine.push(&g_medicine[i]);
    }
    medicine_file.close();
    // pop
    while (!pq_medicine.empty()) {
        Medicine* m = pq_medicine.top();
        pq_medicine.pop();
        m->print();
    }

    // int day = 0;
    // for (day = 0; day < DAY_NUM; day++){
    //     int sim_res = sim_day(day, pq_medicine, v_medicine_deleted);
    //     if (sim_res == 0){
    //         cout << "day " << day << " failed" << endl;
    //         break;
    //     }
    // }

    return 0;
}


float get_delta_price(int day, VMedicine& v_medicine_in_store) {
    float delta_price = 0;
    // for (auto medicine : v_medicine_in_store) {
    //     delta_price += medicine->get_delta_price();
    // }
    return delta_price;
}

int sim_day(int day, PQMedicine& pq_medicine, VMedicine& v_medicine_deleted) {
    cout << "Simulating day " << day << endl;
    VMedicine v_medicine_in_store;
    /* choose medicine to delete */
    // TODO



    /* pop medicine from pq_medicine to pq_medicine_in_store */
    int medicine_in_store_num = 0;
    while (!pq_medicine.empty() && medicine_in_store_num < STORE_SIZE) {
        Medicine* m = pq_medicine.top();
        pq_medicine.pop();
        m->set_status(Medicine::IN_STORE);
        v_medicine_in_store.push_back(m);
        medicine_in_store_num++;
    }
    // set price for medicine in store
    for (auto medicine : v_medicine_in_store) {
        float delta_price = get_delta_price(day, v_medicine_in_store);
        medicine->add_delta_price(g_delta_price[day % PRICE_NUM]);
    }
    /* sort medicine in store by price */
    sort(v_medicine_in_store.begin(), v_medicine_in_store.end(), cmp_price_ptr); // use ptr, not ref
    /* sell medicine */
    int medicine_sold_num = 0;
    for (auto medicine : v_medicine_in_store) {
        if (medicine_sold_num >= CUSTOMER_NUM) {
            break;
        }
        medicine->set_status(Medicine::SOLD);
        medicine_sold_num++;
        g_sale_price += medicine->get_price();
        g_purchase_price += medicine->get_origin_price();
    }

    /* g_warehouse_price */
    for (int i = 0; i < MEDICINE_NUM; i++) {
        if (g_medicine[i].get_status() == Medicine::IN_WAREHOUSE) {
            float warehouse_price = 1 ? g_medicine[i].get_warranty() < 5 : 0.5;
            g_warehouse_price += warehouse_price;
        }
    }

    /* end of the day */
    /* update medicine status */
    

}







int parse_argv(int argc, char* argv[]) {
    // parse the input
    bool in_bitmap[2] = { false, false };
    bool out_bitmap[2] = { false, false };
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0) {
            medicine_path = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0) {
            in_strategy_path = argv[++i];
            in_bitmap[0] = true;
        }
        else if (strcmp(argv[i], "-d") == 0) {
            in_delete_path = argv[++i];
            in_bitmap[1] = true;
        }
        else if (strcmp(argv[i], "-ws") == 0) {
            out_strategy_path = argv[++i];
            out_bitmap[0] = true;
        }
        else if (strcmp(argv[i], "-wd") == 0) {
            out_delete_path = argv[++i];
            out_bitmap[1] = true;
        }
    }

    if (in_bitmap[0] && in_bitmap[1]) {
        cout << "in strategy_path and  delete_path are both set" << endl;
        return 1;
    }
    if (out_bitmap[0] && out_bitmap[1]) {
        cout << "out strategy_path and  delete_path are both set" << endl;
        return 2;
    }
    // 0 for error, 1 for in sim, 2 for out sim
    return 0;
}

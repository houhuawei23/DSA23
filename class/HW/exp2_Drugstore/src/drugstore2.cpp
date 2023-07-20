#include <bits/stdc++.h>
#include "drugstore.h"

using namespace std;

/*
-- compile:
g++ -g -Wall drugstore.cpp -o drugstore

-- debug compile:
g++ -g -Wall -DDEBUG drugstore2.cpp -o drugstore2

-- usage:
./drugstore2 -m ../data/data2/medicine.txt -s ../data/data2/strategy.txt -d delete.txt
./drugstore2 -m ../data/data2/medicine.txt -ws .out_strategy.txt -wd out_delete.txt
./drugstore2 -m ../test/data4/medicine.txt ../test/data4/delete.txt -ws out_strategy.txt -wd out_delete.txt
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
string out_strategy_path = "";
string out_delete_path = "";

float g_profit = 0;
float g_purchase_price = 0; // purchase price for sold medicine
float g_sale_price = 0;
float g_warehouse_price = 0;
float g_delete_expired_price = 0;

Strategy g_strategy[SIM_DAY_NUM + 1][STORE_SIZE]; /* g_srategy[day][index] */
vector<vector<int>> g_delete(SIM_DAY_NUM + 1, vector<int>(0, 0)); /* g_delete[day][index] */
vector<Medicine> g_medicine;

int parse_argv(int argc, char* argv[]);
int parse_argv2(int argc, char* argv[]);
int read_medicine(const string& medicine_path);
int write_strategy(const string& out_strategy_path);
int write_delete(const string& out_delete_path);
int read_files(const string& medicine_path, const string& in_strategy_path, const string& in_delete_path);
int greedy();

int main(int argc, char* argv[]) {
    parse_argv2(argc, argv);
    read_medicine(medicine_path);
    greedy();

    // write_strategy(out_strategy_path);
    // write_delete(out_delete_path);
    return 0;
}
/*
对于保质期 <= 10 的药品，将其按保质期从小到大排序
*/
int greedy() {
    // init g_strategy
    for (int day = 1; day <= SIM_DAY_NUM; day++) {
        for (int i = 0; i < STORE_SIZE; i++) {
            g_strategy[day][i].mid = -1;
            g_strategy[day][i].delta_id = INT_MAX;
            g_strategy[day][i].delta_price = INT_MAX;
        }
    }
    /*
    每天选出前3个推荐卖出并放到药店中，从剩余药品中选出价格最高的7个放到药店中（如果还有的话），称为补充药品
    定价规则：
    1. 记补充药品的最低价为min_origin_price
    2. 尝试对每一个推荐卖出药品进行定价：
        2.1 delta_price 为使 推荐药品price < min_origin_price 的最大的delta_price
        2.2 如果不存在这样的delta_price，则 delta_price = MIN delta_price
    3. 所有补充药品定价规则：delta_price = MAX delta_price
    4. 将在商店中的药品按照价格从高到低排序，价格相同，expire_day大的排在前面
    5. 根据题目规则，应卖出前3个药品，计算相应收益损失
    6. 遍历g_medicine，1将卖出的删除，2更新g_warehouse_price，3将过期的删除，4将在商店中的药品放回仓库
    */
    // 仅维护一个全局的g_medicine，其他都用指针引用
    vector<Medicine*> store_medp;
    vector<Medicine*> warehouse_medp;
    vector<Medicine*> expired_medp;
    vector<Medicine*> deleted_medp;
    int near_expire_day = 1;
    // 初始化xxx_medp
    for (int i = 0; i < MEDICINE_NUM; i++) {
        warehouse_medp.push_back(&g_medicine[i]);
    }
    // 1. 每天选出前3个推荐卖出并放到药店中，从剩余药品中选出价格最高的7个放到药店中（如果还有的话），称为补充药品
    for (int day = 1; day <= SIM_DAY_NUM; day++) {

        // cout << "Greedy day: " << day << endl; 
        // 清空store_medp
        store_medp.clear();
        /* 1.1 选出前3个推荐卖出并放到药店中 */
        /* 1.1 选出3个推荐卖出：先在expire_day小于等于10中的选，如果不够，再选*/
        // sort warehouse_medp by expire_day, if expire_day equal, smaller origin_price first
        sort(warehouse_medp.begin(), warehouse_medp.end(), cmp_expire_day_ptr);
#ifdef DEBUG
        cout << "warehouse_medp sorted by expire_day: " << endl;
        for (int i = 0; i < (int)warehouse_medp.size(); i++) {
            warehouse_medp[i]->print();
        }
#endif
        // choose the first 3 med put into store
        for (int i = 0;
            (i < 3) && (i < (int)warehouse_medp.size());
            i++)
        {
            store_medp.push_back(warehouse_medp.front());
            warehouse_medp.erase(warehouse_medp.begin());
        }
        int recommend_num = store_medp.size();
#ifdef DEBUG
        cout << "chooe 3 in store_medp: " << endl;
        for (int i = 0; i < (int)store_medp.size(); i++) {
            store_medp[i]->print();
        }
        cout << "delete first 3 in warehouse_medp: " << endl;
        for (int i = 0; i < (int)warehouse_medp.size(); i++) {
            warehouse_medp[i]->print();
        }
#endif
        /* 1.2 从剩余药品中选出原价格最高的7个放到药店中（如果还有的话），称为补充药品
                同价格选expire_day小的（商家）
        */
       /* new 1.2 选出7个补充药品
       推荐药品最大原价格为max_rec_oprice
       从剩余药品中的，原价格 > max_rec_oprice 的，选择expire_day小的
       如果不够，就不选了
       */


      
        // sort warehouse_medp by origin_price
        sort(warehouse_medp.begin(), warehouse_medp.end(), seller_cmp_oprice_ptr);
#ifdef DEBUG
        cout << "warehouse_medp sorted by origin_price: " << endl;
        for (int i = 0; i < (int)warehouse_medp.size(); i++) {
            warehouse_medp[i]->print();
        }
#endif
        // choose the first 7 med put into store
        // float min_origin_price_in_warehouse = warehouse_medp.back()->get_origin_price();
        for (int i = 0;
            (i < 7) && (i < (int)warehouse_medp.size());
            i++)
        {
            store_medp.push_back(warehouse_medp.front());
            warehouse_medp.erase(warehouse_medp.begin());
        }
        float min_oprice_supplement = store_medp.back()->get_origin_price();
        int store_med_num = store_medp.size();


        // int supplement_num = store_medp.size() - recommend_num;
#ifdef DEBUG
        cout << "chooe 7 in store_medp: " << endl;
        for (int i = 0; i < (int)store_medp.size(); i++) {
            store_medp[i]->print();
        }
        cout << "delete first 7 in warehouse_medp, size: " << warehouse_medp.size() << endl;
        for (int i = 0; i < (int)warehouse_medp.size(); i++) {
            warehouse_medp[i]->print();
        }
#endif


        // 2. 尝试对每一个推荐卖出药品进行定价：
        // 2.1 delta_price 为使 推荐药品price < min_origin_price + MAX delta price 的最大的delta_price
        // 2.2 如果不存在这样的delta_price，则 delta_price = MIN delta_price
        float max_delta_price = g_delta_price[PRICE_NUM - 1];
        for (int i = 0; i < recommend_num; i++) {
            Medicine* rec_medp = store_medp[i];
            for (int delta_id = PRICE_NUM - 1; delta_id >= 0; delta_id--) {
                float delta_price = g_delta_price[delta_id];
                float price = rec_medp->get_origin_price() + delta_price;
                // cout << "price: " << price << ", min_origin_price_in_warehouse: " << min_oprice_supplement << ", max_delta_price: " << max_delta_price << endl;
                if (price < min_oprice_supplement + max_delta_price) {
                    rec_medp->set_price_delta(delta_price);
                    // set g_strategy
                    g_strategy[day][i].mid = rec_medp->get_id();
                    g_strategy[day][i].delta_id = delta_id;
                    g_strategy[day][i].delta_price = delta_price;
                    break;
                }
            }
            if (g_strategy[day][i].delta_id == INT_MAX) {
                printf("Error: cannot find delta_price for medicine %d\n", rec_medp->get_id());
                rec_medp->set_price_delta(max_delta_price);
                // set g_strategy
                g_strategy[day][i].mid = rec_medp->get_id();
                g_strategy[day][i].delta_id = PRICE_NUM - 1;
                g_strategy[day][i].delta_price = max_delta_price;
                // rec_medp->set_price_delta(g_delta_price[0]);
                // // set g_strategy
                // g_strategy[day][i].mid = rec_medp->get_id();
                // g_strategy[day][i].delta_id = 0;
                // g_strategy[day][i].delta_price = g_delta_price[0];
            }

        }
        // 3. 所有补充药品定价规则：delta_price = MAX delta_price
        for (int i = recommend_num; i < store_med_num; i++) {
            Medicine* sup_medp = store_medp[i];
            sup_medp->set_price_delta(max_delta_price);
            // set g_strategy
            g_strategy[day][i].mid = sup_medp->get_id();
            g_strategy[day][i].delta_id = PRICE_NUM - 1;
            g_strategy[day][i].delta_price = max_delta_price;
        }

        // 4. 将在商店中的药品按照价格从高到低排序，价格相同，expire_day大的排在前面
        sort(store_medp.begin(), store_medp.end(), buyer_cmp_price_ptr);
#ifdef DEBUG
        cout << "4. store_medp sorted by price: " << endl;
        for (int i = 0; i < (int)store_medp.size(); i++) {
            store_medp[i]->print();
        }
#endif
        // 5. 根据题目规则，应卖出前3个药品，计算相应收益损失
        for (int i = 0;
            (i < 3) && (i < store_med_num);
            i++)
        {
            Medicine* sold_medp = store_medp[i];
            g_purchase_price += sold_medp->get_origin_price();
            g_sale_price += sold_medp->get_price();
            store_medp.erase(store_medp.begin());
        }
#ifdef DEBUG
        cout << "5. delete first 3 in store_medp: " << endl;
        for (int i = 0; i < (int)store_medp.size(); i++) {
            store_medp[i]->print();
        }
#endif
        /* 一天结束，更新状态*/
        // 遍历在仓库中的
        auto medpp = warehouse_medp.begin();
        while (medpp != warehouse_medp.end()) {
            // 更新仓库管理费
            float warehouse_price = (*medpp)->get_expire_day() - day < 5 ? 1 : 0.5;
            g_warehouse_price += warehouse_price;

            // 更新过期药品
            if ((*medpp)->get_expire_day() == day) {
                expired_medp.push_back(*medpp);
                g_delete_expired_price += (*medpp)->get_origin_price();
                medpp = warehouse_medp.erase(medpp);
            }
            else {
                medpp++;
            }

        }
        // 遍历在药店中的
        medpp = store_medp.begin();
        while (medpp != store_medp.end()) {
            // 更新过期药品
            if ((*medpp)->get_expire_day() == day) {
                expired_medp.push_back(*medpp);
                g_delete_expired_price += (*medpp)->get_origin_price();
                medpp = store_medp.erase(medpp);
            }
            else {
                // 没过期，移动到仓库
                warehouse_medp.push_back(*medpp);
                medpp++;
            }
        }
        /*将药店中剩余药放回仓库 */
        // cout << "Greedy end day: " << day << endl;
    }

    g_profit = g_sale_price - g_purchase_price - g_warehouse_price - g_delete_expired_price;
    // set precision
    cout << fixed << setprecision(5);
    cout << "g_sale_price: " << g_sale_price << endl;
    cout << "g_purchase_price: " << g_purchase_price << endl;
    cout << "g_warehouse_price: " << g_warehouse_price << endl;
    cout << "g_delete_expired_price: " << g_delete_expired_price << endl;
    cout << "g_profit: " << g_profit << endl;

    return 1;
}


int parse_argv2(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0) {
            medicine_path = argv[++i];
        }
        else if (strcmp(argv[i], "-ws") == 0) {
            out_strategy_path = argv[++i];
        }
        else if (strcmp(argv[i], "-wd") == 0) {
            out_delete_path = argv[++i];
        }
    }
#ifdef DEBUG
    cout << "medicine_path: " << medicine_path << endl;
    cout << "out_strategy_path: " << out_strategy_path << endl;
    cout << "out_delete_path: " << out_delete_path << endl;
#endif
    return 1;
}


int read_medicine(const string& medicine_path) {
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
    return 1;
}

int write_strategy(const string& out_strategy_path) {
    ofstream out_strategy(out_strategy_path);
    if (!out_strategy.is_open()) {
        cout << "Error: cannot open file " << out_strategy_path << endl;
        return 0;
    }
    for (int day = 1; day <= SIM_DAY_NUM; day++) {
        for (int i = 0; i < STORE_SIZE; i++) {
            out_strategy << g_strategy[day][i].mid << "," << g_strategy[day][i].delta_id << "    ";
        }
        out_strategy << endl;
    }
    out_strategy.close();
    return 1;
}

int write_delete(const string& out_delete_path) {
    ofstream out_delete(out_delete_path);
    if (!out_delete.is_open()) {
        cout << "Error: cannot open file " << out_delete_path << endl;
        return 0;
    }
    for (int day = 1; day <= SIM_DAY_NUM; day++) {
        int size = g_delete[day].size();
        for (int i = 0; i < size; i++) {
            out_delete << day << "    " << g_delete[day][i] << endl;
        }
    }
    out_delete.close();
    return 1;
}

// 调整退火的新状态
vector<int> change(vector<int> s) {
    vector<int> new_state = s;
    for (int i = 0; i <= rand() % 5; i++) {
        while (1) {
            int op = rand() % 4;
            if (op == 0) { // 与剩余的药品进行交换
                int x = rand() % 10 + 1, y = rand() % 3, z = rand() % s.size();
                if (g_medicine[s[z]].status >= x && g_medicine[s[x * 3 + y]].status > 10) {
                    swap(new_state[z], new_state[x * 3 + y]);
                    break;
                }
            }
            else { // 内部交换顺序
                int x = rand() % 10 + 1, y = rand() % 3, u = rand() % 10 + 1, v = rand() % 3;
                if (g_medicine[s[x * 3 + y]].status >= u && g_medicine[s[u * 3 + v]].status >= x) {
                    swap(new_state[x * 3 + y], new_state[u * 3 + v]);
                    break;
                }
            }
        }
    }
    return new_state;
}

// 模拟退火求解
void simulatedAnnealing() {
    double T = 10000, dT = 0.993, eps = 1e-6;
    vector<int> state; // 初始状态
    // 初始化 state
    // ...
    double ans = calculate(state);
    while (T > eps) {
        vector<int> new_state = change(state);
        double tmp = calculate(new_state);
        double delta = tmp - ans;
        if (delta > 0 || exp(delta / T) * RAND_MAX > rand()) {
            ans = tmp;
            state = new_state;
        }
        T *= dT;
    }
    // 输出结果
    // ...
}


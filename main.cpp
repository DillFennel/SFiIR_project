#include <iostream>
#include <random>
#include <fstream>
#include <list>

using namespace std;


random_device rd;
mt19937 gen(rd());

struct LCG {
    int state;
    LCG(int _seed){
        state = _seed;
        srand(_seed);
    }
    int generate_100(){
        int r = rand();
        if(r < 0){ r *= -1; }
        r = r%101;
        return r;
    }
    int generate_t_p(){
        int r = generate_100();
        if(r < 25){
            return 1;
        }
        if(r < 48){
            return 2;
        }
        if(r < 69){
            return 3;
        }
        if(r < 81){
            return 4;
        }
        if(r < 90){
            return 5;
        }
        return 6;
    }
    int generate_t_obr(){
        int r = generate_100();
        if(r < 6){
            return 1;
        }
        if(r < 21){
            return 2;
        }
        if(r < 48){
            return 3;
        }
        if(r < 77){
            return 4;
        }
        if(r < 83){
            return 5;
        }
        return 6;
    }
};
int check_copy(bool t_func = 0, int seed = 10){
        LCG lcg(seed);
        int check_size = 100;
        string check_100;
        string gen_100 = "";
        int gen_last;
        for(int i=0; i<check_size; i++){
                if(t_func){
                        gen_last = lcg.generate_t_p();
                }
                else{
                        gen_last = lcg.generate_t_obr();
                }
                gen_100 += to_string(gen_last);
        }
        check_100 = gen_100;
        for(int i = 0; ; i++){
                if(t_func){
                        gen_last = lcg.generate_t_p();
                }
                else{
                        gen_last = lcg.generate_t_obr();
                }
                gen_100.erase(0, 1);
                gen_100 += to_string(gen_last);
                if( check_100 == gen_100){
                        return i;
                }
        }
        return -1;
}
void make_data(int seed = 10){ // n - количество колок
    int n = 9000; // Все кол-во запусков
    int k = 3; // Кол-во отрезков для проверки
    LCG lcg(10);
    int t_p, t_obr;
    vector<vector<int>> t_p_count(k, vector<int> (6, 0));
    vector<vector<int>> t_obr_count(k, vector<int> (6, 0));
    for(int k1=1; k1<k+1; k1++){
        for(int i=n/k*(k1-1)+1; i<n/k*k1; i++){
            t_p = lcg.generate_t_p();
            t_obr =lcg.generate_t_obr();
            t_p_count[k1-1][t_p-1]++;
            t_obr_count[k1-1][t_obr-1]++;
        }
    }
    int pre;
    std::ofstream fout;          // поток для записи
    fout.open("data.txt");      // открываем файл для записиout.open("data.txt");
    fout << n << " " << k << endl;
    fout << "t_p" <<endl;
    for(int k1 = 0; k1 < k; k1++){
        fout << "k: " << k1 << endl;
        pre = 0;
        for(int i = 0; i< 6; i++){
                pre += t_p_count[k1][i]*100/n;
                fout << i+1 << ": " << t_p_count[k1][i] << " " << t_p_count[k1][i]*100/n << " " << pre << endl;
        }
    }
    cout << "t_k done" << endl;
    fout << "t_obr" <<endl;
    for(int k1=0; k1<k; k1++){
        fout << "k: " << k1 << endl;
        pre = 0;
        for(int i = 0; i< 6; i++){
            pre += t_obr_count[k1][i]*100/n;
            fout << i+1 << ": " << t_obr_count[k1][i] << " " << t_obr_count[k1][i]*100/n << " " << pre << pre*100/n << endl;        }
    }
    cout << "t_obr done" << endl;
    fout.close();
}
int main(){ // n - количество колок
        cout << "Раз в сколько запусков повторяется последовательность из 100 чисел для:"<<endl;
        cout << "t_k: " << check_copy(0) << endl << "t_obr: " << check_copy(1) <<endl;
}

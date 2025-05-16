#include <iostream>
#include <random>

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
            return 0;
        }
        if(r < 48){
            return 1;
        }
        if(r < 69){
            return 2;
        }
        if(r < 81){
            return 3;
        }
        if(r < 90){
            return 4;
        }
        if(r<100){
            return 5;
        }
        return 6;
    }
    int generate_t_obr(){
        int r = generate_100();
        if(r < 6){
            return 0;
        }
        if(r < 21){
            return 1;
        }
        if(r < 48){
            return 2;
        }
        if(r < 77){
            return 3;
        }
        if(r < 83){
            return 4;
        }
        if(r < 100){
            return 5;
        }
        return 6;
    }
};

int main(){ // n - количество колонок
    int n = 10000;
    LCG lcg(10);
    int t_p, t_obr;
    vector<int> t_p_count(7, 0);
    vector<int> t_obr_count(7, 0);
    for(int i=0; i<n; i++){
        t_p = lcg.generate_t_p();
        t_obr =lcg.generate_t_obr();
        t_p_count[t_p]++;
        t_obr_count[t_obr]++;
    }
    int pre = 0;
    cout << "t_p" <<endl;
    for(int i = 0; i< 7; i++){
        pre += t_p_count[i]*100/n;
        cout << i << ": " << t_p_count[i] << " " << t_p_count[i]*100/n << " " << pre << endl;
    }
    cout << "t_obr" <<endl;
    pre = 0;
    for(int i = 0; i< 7; i++){
        pre += t_obr_count[i]*100/n;
        cout << i << ": " << t_obr_count[i] << " " << t_obr_count[i]*100/n << " " <<pre << endl;
    }
}
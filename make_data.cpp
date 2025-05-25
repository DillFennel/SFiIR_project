#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cassert>
#include "LCG.h"

using namespace std;

LCG lcg;

struct PentrolPump{
        unsigned waiting;
        unsigned process;
        unsigned done;
	int profit;
	unsigned start;
        unsigned finish;
	PentrolPump(){
		waiting = 0;
		process = 0;
		done = 0;
		profit = 0;
		start = 0;
		finish = 0;
	}
	void addWork(unsigned t){
		assert(process == 0);
		process++;
		start = t;
		finish = t+lcg.generate_t_obr();
	}
	void addWait(){
		assert(waiting == 0);
		waiting++;
	}
	void doneWork() {
		process--;
		done++;
		profit++;
		if(waiting > 0){
			waiting--;
			process++;
			start = finish+1;
			finish = lcg.generate_t_obr();
		}
	}
};std::priority_queue<int, std::vector<int>, std::greater<int> > my_min_heap;
struct Fact{
	vector<PentrolPump> pumps;
	int costs;
	unsigned time;
	int total_profit;
	unsigned working_pumps;
	unsigned waiting_pumps;
	Fact(int n){
		pumps.resize(n);
		time = 0;
		costs = 30*n+75;
		total_profit = -costs;
		working_pumps = 0;
		waiting_pumps = 0;
	}
	void carArrive(unsigned t){
		if(waiting_pumps >= pumps.size()){
			return ;
		}
		if(working_pumps < pumps.size()){
			for(auto pp: pumps){
				if(pp.process == 0){
					pp.addWork(t);
					return ;
				}
			}
		}
		for(auto pp: pumps){
			if(pp.waiting == 0){
				pp.addWait();
				return ;
			}
		}
		cerr << "Error in carArrive func" << endl;
		return ;
	}
	void getDoneCars(unsigned t){
		for(auto pp: pumps){
			if (pp.finish = t-1) {
				pp.doneWork();
				total_profit++;
			}
		}
	}
};
void read_input(int *seed, unsigned *n_pentrol_pump, unsigned *n_try){
	cout << "Введите сид для генератора: ";std::priority_queue<int, std::vector<int>, std::greater<int> > my_min_heap;
	cin >> *seed;
	cout << "Введите максимально кол-во колонок: ";
	cin >> *n_pentrol_pump;
	cout << "Введите кол-во генераций для каждого N: ";
	cin >> *n_try;
}
void document(int n, int i_try, const Fact){
	cout << 1 << endl;
}
int main(){
	int seed;
	unsigned n_pentrol_pump, n_try;
	read_input(&seed, &n_pentrol_pump, &n_try);
	lcg.addSeed(seed);
	unsigned work_start = 0, work_end = 432;
	std::ofstream fout;
    	fout.open("data.txt");
	unsigned  arrival = lcg.generate_t_p();
	for(int n = 1; n < n_pentrol_pump; n++) {
		for (int i_try = 1; i_try < n_try; i_try++) {
			Fact fact(n);
			for (int t = 0; t<work_end; t++) {
				Fact.getDoneCars(t);
				if(arrival == 0){
					Fact.carArrive(t);
					arrival = lcg.generate_t_p();
				}
				else{
					arrival--;
				}
				document(n, i_try, Fact);
			}
		}
	}
}

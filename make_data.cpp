#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cassert>
#include "LCG.h"

using namespace std;

LCG lcg;

struct PetrolPump{
        unsigned waiting;
        unsigned process;
        unsigned done;
	int profit;
	unsigned start;
        unsigned finish;
	unsigned wait_since;
	PetrolPump(){
		waiting = 0;
		process = 0;
		done = 0;
		profit = 0;
		start = 0;
		finish = 0;
		wait_since = 0;
	}
	void addWork(unsigned t){
		assert(process == 0);
		process++;
		assert(process == 1);
		start = t;
		finish = t+lcg.generate_t_obr();
	}
	void addWait(unsigned t){
		assert(waiting == 0);
		waiting++;
		wait_since = t;
	}
	void doneWork() {
		assert(process > 0);
		process--;
		done++;
		profit++;
		if(waiting > 0){
			waiting--;
			process++;
			start = finish;
			finish += lcg.generate_t_obr();
		}
	}
};std::priority_queue<int, std::vector<int>, std::greater<int> > my_min_heap;
struct Fact{
	vector<PetrolPump*> pumps;
	int wages;
	int other_costs;
	unsigned time;
	int total_profit;
	unsigned working_pumps;
	unsigned waiting_pumps;
	Fact(int n){
		for(int i=0; i<n; i++){
			auto pp = new PetrolPump();
			pumps.push_back(pp);
		}
		assert(pumps.size() == n);
		time = 0;
		other_costs = 75;
		wages = 30*n;
		total_profit = 0;
		working_pumps = 0;
		waiting_pumps = 0;
	}
	void carArrive(unsigned t){
		if(waiting_pumps >= pumps.size()){
			return ;
		}
		if(working_pumps < pumps.size()){
			working_pumps++;
			for(auto pp: pumps){
				if(pp->process == 0){
					pp->addWork(t);
					return ;
				}
			}
		}
		waiting_pumps++;
		for(auto pp: pumps){
			if(pp->waiting == 0){
				pp->addWait(t);
				return ;
			}
		}
		cerr << "Error in carArrive func" << endl;
		return ;
	}
	void getDoneCars(unsigned t){
		for(auto pp: pumps){
			 if (pp->process > 0 && pp->finish == t) {
				pp->doneWork();
				total_profit++;
				if(pp->process > 0){
					waiting_pumps--;
				}
				else {
					working_pumps--;
				}
			}
		}
	}
	void finishWork(){
		for(auto pp: pumps){
                        if(pp->process > 0){
				pp->done++;
				pp->process--;
				pp->profit++;
				total_profit++;
				working_pumps--;
			}
			if(pp->waiting > 0){
                                pp->done++;
                                pp->waiting--;
                                pp->profit++;
                                total_profit++;
				waiting_pumps--;
                        }
                }
		assert(working_pumps == 0);
		assert(waiting_pumps == 0);
	}
};
void read_input(int *seed, unsigned *n_petrol_pump, unsigned *n_try){
	cout << "Введите сид для генератора: ";std::priority_queue<int, std::vector<int>, std::greater<int> > my_min_heap;
	cin >> *seed;
	cout << "Введите максимально кол-во колонок: ";
	cin >> *n_petrol_pump;
	cout << "Введите кол-во генераций для каждого N: ";
	cin >> *n_try;
}
void view(int i_try, int n,  unsigned t, const Fact& fact){
	cout << "N: " << n << ", Profit: " << fact.total_profit << endl;
	cout << "\tPumps info: " <<endl;
	cout << "\tCurrent waiting: " << fact.waiting_pumps << ", Current working: " << fact.working_pumps << endl;
	for(int i = 0; i<fact.pumps.size(); i++){
		cout << "\t\tWait: " << fact.pumps[i]->waiting << ", Since: " << fact.pumps[i]->wait_since<< ", In Process: " << fact.pumps[i]->process << ", Start: " << fact.pumps[i]->start << ", Finish: " << fact.pumps[i]->finish << ", Done: " << fact.pumps[i]->done << ", Profit: " << fact.pumps[i]->profit << endl;
	}
}
void document(int i_try, int n,  unsigned t, const Fact& fact){
	std::ofstream fout;
    	fout.open("data.txt", std::ios::app);
	//fout << "N: " << n << ", Profit: " << fact.total_profit << endl;
	//cout << "\tPumps info: " <<endl;
	//cout << "\tCurrent waiting: " << fact.waiting_pumps << ", Current working: " << fact.working_pumps << endl;
	for(int i = 0; i<fact.pumps.size(); i++){
		fout << i_try <<","<<n<<","<<t<<","<<fact.total_profit<<",";
		fout << fact.waiting_pumps<<","<<fact.working_pumps<<",";
		fout<<i<<","<<fact.pumps[i]->waiting<<",";
		if(fact.pumps[i]->waiting > 0){
			fout<< fact.pumps[i]->wait_since;
		} else {
			fout<<"-";
		}
		fout<<","<<fact.pumps[i]->process<<",";
		if(fact.pumps[i]->process > 0){
                        fout<<fact.pumps[i]->start << "," <<fact.pumps[i]->finish;
                } else {
                        fout<<"-,-";
                }
		fout<<","<<fact.pumps[i]->done<<endl;
	}
	fout.close();
}
int main(){
	int seed;
	unsigned n_petrol_pump, n_try;
	read_input(&seed, &n_petrol_pump, &n_try);
	lcg.addSeed(seed);
	std::ofstream fout;
    	fout.open("data.txt");
	fout << "iter,N,time,total_profit,waiting_pumps,working_pumps,num_pump,waiting,wait_since,process,start,finish,done"<<endl;
	fout.close();
	unsigned work_start = 0, work_end = 43200;
	for (int i_try = 0; i_try < n_try; i_try++) {
		vector<Fact*> facts;
		for(int n = 0; n < n_petrol_pump+1; n++) {
			auto new_fact = new Fact(n);
			facts.push_back(new_fact);
		}
		unsigned  arrival = lcg.generate_t_p();
		for (int t = 0; t<work_end; t++) {
			for(auto fact: facts){
				fact->getDoneCars(t);
			}
			if(arrival == 0){
				//cout << "Current time: " << t << endl;
				//cout << "Car arrived" <<endl;
				for(auto fact: facts){
                                	fact->carArrive(t);
					document(i_try, fact->pumps.size(), t, *fact);
                        	}
				arrival = lcg.generate_t_p();
			}
			else{
				arrival--;
			}
			for(auto fact: facts){
                               document(i_try, fact->pumps.size(), t, *fact);
                        }
		}
		for(auto fact: facts){
			fact->finishWork();
			document(i_try, fact->pumps.size(), 432, *fact);
			//cout<< "N: " <<fact->pumps.size() << ", Costs: " << fact->other_costs << ", Wages: " << fact->wages <<", Total Profit: " << fact->total_profit<< endl;
		}
	}
	return 0;
}
void print_pumps(const vector<PetrolPump*> pumps){
	for(auto pp: pumps){
                cout <<"wait: " <<  pp->waiting << ", since: " <<pp->wait_since << ", process: " << pp->process << ", done: " << pp->done << ", start: " << pp->start << ", finish: " << pp->finish << ", profit: " << pp->profit << endl;        
	}
}
int test_PetrolPump(){
	vector<PetrolPump*> pumps;
	for(int i=0; i<3; i++){
		auto pp = new PetrolPump();
		pumps.push_back(pp);
	}
	cout << "Начало" << endl;
	print_pumps(pumps);
	pumps[0]->addWork(0);
	pumps[1]->addWork(0);
	pumps[1]->addWait(2);
	pumps[2]->addWork(2);
	cout <<"На 0 приехала 1 машина, на 1 - 2 машины, на 3 - 1 машина" << endl;
	print_pumps(pumps);
	pumps[0]->doneWork();
	pumps[1]->doneWork();
	cout << "0 и 1 завершили обработку машин" << endl;
	print_pumps(pumps);
	pumps[1]->doneWork();
        pumps[2]->doneWork();
        cout << "1 и 2 завершили обработку машин" << endl;
        print_pumps(pumps);
	return 0;
}

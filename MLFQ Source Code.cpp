#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

class Process {
public:
	string name;
	int response_t;
	int wait_t;
	int turnaround_t;
	vector<int> data;
	int priority;

	
	Process(string arg_name, int inputdata[20], int size) {
		name = arg_name;
		priority = 1;
		response_t = 0;
		wait_t = 0;
		turnaround_t = 0;
		for (int i = (size-1); i >= 0; i--) {
			data.push_back(inputdata[i]);
		}
	}
};

int main() {
	int response_total = 0, wait_total = 0, turnaround_total = 0, current_t = 0;
	float cpu_use = 0;;
	int context = 0;
	int tq = 0;
	bool idleflag = 0;

	//raw data as arrays
	int p1data[] = { 7, 22, 6, 19, 12, 44, 8, 21, 10, 37, 5, 24, 6, 44, 7 , 43, 8 };
	int p2data[] = { 14, 48, 15, 44, 17, 42, 22, 37, 19, 76, 14, 41, 16, 31, 17, 43, 18 };
	int p3data[] = { 8, 43, 7, 41, 6, 45, 8, 21, 9, 35, 14, 18, 5, 26, 3, 31, 6 };
	int p4data[] = { 13, 37, 4, 41, 5, 35, 12, 41, 8, 55, 15, 34, 6, 73, 5, 77, 3 };
	int p5data[] = { 6, 34, 7, 21, 5, 44, 6, 32, 7, 28, 3, 48, 11, 44, 6, 33, 3, 28, 4 };
	int p6data[] = { 9, 32, 4, 28, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8 };
	int p7data[] = { 14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10 };
	int p8data[] = { 4, 64, 5, 53, 6, 44, 4, 73, 6, 87, 5 ,66, 8, 25, 6, 33, 9, 41, 7 };
	int p9data[] = { 13, 37, 8, 41, 7, 27, 12, 29, 5, 27, 6, 18, 3, 33, 4, 62, 6 };

	//declare process objects
	Process p1("P1", p1data, 17);
	Process p2("P2", p2data, 17);
	Process p3("P3", p3data, 17);
	Process p4("P4", p4data, 17);
	Process p5("P5", p5data, 19);
	Process p6("P6", p6data, 17);
	Process p7("P7", p7data, 15);
	Process p8("P8", p8data, 19);
	Process p9("P9", p9data, 17);

	vector<Process*> ready1;
	vector<Process*> ready2;
	vector<Process*> ready3;
	vector<Process*> blocking;
	vector<Process*> complete;
	Process* executing = 0;

	ready1.push_back(&p9);
	ready1.push_back(&p8);
	ready1.push_back(&p7);
	ready1.push_back(&p6);
	ready1.push_back(&p5);
	ready1.push_back(&p4);
	ready1.push_back(&p3);
	ready1.push_back(&p2);
	ready1.push_back(&p1);
	
	
	//main scheduler loop
	do {
		if (executing == 0) {
			//context switch
			tq = 0;
			if (ready1.size() != 0) {
				if (ready1.back()->response_t == 0) {
					ready1.back()->response_t = (ready1.back()->wait_t) +1;
				}
				context++;
				executing = ready1.back();
				ready1.pop_back();
			}
			else if (ready2.size() != 0) {
				if (ready2.back()->response_t == 0) {
					ready2.back()->response_t = (ready2.back()->wait_t) + 1;
				}
				context++;
				executing = ready2.back();
				ready2.pop_back();
			}
			else if (ready3.size() != 0) {
				if (ready3.back()->response_t == 0) {
					ready3.back()->response_t = (ready3.back()->wait_t) + 1;
				}
				context++;
				executing = ready3.back();
				ready3.pop_back();
			}
			if (executing != 0) {
				idleflag = false;
			}
			if (!idleflag) {
				cout << "Current Time: " << current_t << "\n\n";
				if (executing == 0) {
					cout << "Now running: [idle]" << '\n';
				}
				else {
					cout << "Now running: " << executing->name << '\n';
				}
				cout << ".................................................. \n\n";
				cout << "Ready Queue:\tProcess \tBurst \tQueue \n";
				if ((ready1.size() + ready2.size() + ready3.size()) == 0) {
					cout << "\t\t" << "[empty]\n";
				}
				else {
					if (ready1.size() != 0) {
						for (int i = (ready1.size() - 1); i >= 0; i--) {
							if (ready1[i]->data.size() != 0) {
								cout << "\t\t " << ready1[i]->name << "\t\t " << ready1[i]->data.back() << "\t " << "Q" << ready1[i]->priority << "\n";
							}
						}
					}
					if (ready2.size() != 0) {
						for (int i = (ready2.size() - 1); i >= 0; i--) {
							if (ready2[i]->data.size() != 0) {
								cout << "\t\t " << ready2[i]->name << "\t\t " << ready2[i]->data.back() << "\t " << "Q" << ready2[i]->priority << "\n";
							}
						}
					}
					if (ready3.size() != 0) {
						for (int i = (ready3.size() - 1); i >= 0; i--) {
							if (ready3[i]->data.size() != 0) {
								cout << "\t\t " << ready3[i]->name << "\t\t " << ready3[i]->data.back() << "\t " << "Q" << ready3[i]->priority << "\n";
							}

						}
					}
				}
				cout << ".................................................. \n\n";
				cout << "Now in I/O: \tProcess \tRemaining I/O time\n";
				if (blocking.size() == 0) {
					cout << "\t\t" << "[empty]\n";
				}
				else {
					for (int i = (blocking.size() - 1); i >= 0; i--) {
						cout << "\t\t " << blocking[i]->name << "\t\t " << blocking[i]->data.back() << "\n";
					}
				}
				if (complete.size() > 0) {
					cout << ".................................................. \n\n";
					cout << "Completed:\t";
					for (int i = (complete.size() - 1); i >= 0; i--) {
						cout << complete[i]->name;
						if (i != 0) {
							cout << ", ";
						}
						else {
							cout << " ";
						}
					}
					cout << "\n";
				}
				cout << "\n::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n";
			}
			
			if (executing == 0) {
				idleflag = true;
			}
		}
		
		if (ready1.size() != 0) {
			for (int i = 0; i < ready1.size(); i++) {
				ready1[i]->turnaround_t++;
				ready1[i]->wait_t++;
			}
			//sort(ready1.begin(), ready1.end(), [](Process* r1, Process* r2) -> bool {return (*r1).data.back() > (*r2).data.back(); });		
		}
		if (ready2.size() != 0) {
			for (int i = 0; i < ready2.size(); i++) {
				ready2[i]->turnaround_t++;
				ready2[i]->wait_t++;
			}
		}
		if (ready3.size() != 0) {
			for (int i = 0; i < ready3.size(); i++) {
				ready3[i]->turnaround_t++;
				ready3[i]->wait_t++;
			}
		}

		if (blocking.size() != 0) {
			for (int i = (blocking.size() - 1); i >= 0; i--) {
				blocking[i]->data.back()--;
				blocking[i]->turnaround_t++;
				if (blocking[i]->data.back() == 0) {
					blocking[i]->data.pop_back();
					if (blocking[i]->priority == 1) {
						ready1.insert(ready1.begin(), blocking[i]);
					}
					if (blocking[i]->priority == 2) {
						ready2.insert(ready2.begin(), blocking[i]);
					}
					if (blocking[i]->priority == 3) {
						ready3.insert(ready3.begin(), blocking[i]);
					}
					
					blocking.pop_back();
				}
			}
		}


		if (executing != 0) {
			executing->data.back()--;
			executing->turnaround_t++;
			cpu_use++;
			if (executing->data.back() == 0
				|| (executing->priority == 1 && tq == 7)
				|| (executing->priority == 2 && tq == 11)
				|| (executing->priority == 2 && ready1.size() > 0)
				|| (executing->priority == 3 && ready1.size() > 0)
				|| (executing->priority == 3 && ready2.size() > 0)) {
				if (executing->data.back() == 0) {
					executing->data.pop_back();
					if (executing->data.size() == 0) {
						complete.push_back(executing);
						sort(complete.begin(), complete.end(), [](Process* r1, Process* r2) -> bool {return (*r1).name > (*r2).name; });
						executing = 0;
					}

					else {
						blocking.push_back(executing);
						sort(blocking.begin(), blocking.end(), [](Process* r1, Process* r2) -> bool {return (*r1).data.back() > (*r2).data.back(); });
						executing = 0;
					}
				}
				else if ((executing->priority == 1 && tq == 7) || (executing->priority == 2 && tq == 11)) {
					executing->priority++;
				}
				if (executing != 0) {
					if (executing->priority == 1) {
						ready1.insert(ready1.begin(), executing);
					}
					else if (executing->priority == 2) {
						ready2.insert(ready2.begin(), executing);
					}
					else if (executing->priority == 3) {
						ready3.insert(ready3.begin(), executing);
					}
					executing = 0;
				}
				
			}

				
			
		}

		current_t++;
		tq++;
	} while (ready1.size() > 0 || ready2.size() > 0 || ready3.size() > 0 || executing != 0 || blocking.size() > 0);
	
	cout << "Current Time: " << current_t << "\n\n";
	cout << "Now running: nothing" << '\n';
	cout << ".................................................. \n\n";
	cout << "Ready Queue: \tProcess \tBurst \n";
	cout << "\t\t" << "[empty]\n";
	cout << ".................................................. \n\n";
	cout << "Now in I/O: \tProcess \tRemaining I/O time\n";
	cout << "\t\t" << "[empty]\n";
	cout << ".................................................. \n\n";
	cout << "Completed:\t";
	sort(complete.begin(), complete.end(), [](Process* r1, Process* r2) -> bool {return (*r1).name > (*r2).name; });
	for (int i = (complete.size() - 1); i >= 0; i--) {
		cout << complete[i]->name;
		if (i != 0) {
			cout << ", ";
		}
		else {
			cout << " ";
		}
	}
	cout << "\n::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n";


	
	for (int i = 0; i < complete.size(); i++) {
		complete[i]->response_t--;
		turnaround_total += complete[i]->turnaround_t;
		wait_total += complete[i]->wait_t;
		response_total += complete[i]->response_t;
	}

	float cpu_ut = (cpu_use/current_t)*100;
	float avg_w = wait_total / 9.0;
	float avg_resp = response_total / 9.0;
	float avg_tt = turnaround_total / 9.0;

	cout << "Finished\n";
	cout << "Total Time:         " << current_t << '\n';
	cout << "CPU Utilization:    " << cpu_ut << "%\n";
	cout << "Waiting Times       " << "P1   P2   P3   P4   P5   P6   P7   P8   P9\n";
	cout << "                    " << p1.wait_t << "  " << p2.wait_t << "  " << p3.wait_t << "  " << p4.wait_t << "  " << p5.wait_t << "  " << p6.wait_t << "  " << p7.wait_t << "  " << p8.wait_t << "  " << p9.wait_t << '\n';
	cout << "Average Wait:       " << avg_w << '\n';
	cout << "Turnaround Times    " << "P1   P2   P3   P4   P5   P6   P7   P8   P9\n";
	cout << "                    " << p1.turnaround_t << "  " << p2.turnaround_t << "  " << p3.turnaround_t << "  " << p4.turnaround_t << "  " << p5.turnaround_t << "  " << p6.turnaround_t << "  " << p7.turnaround_t << "  " << p8.turnaround_t << "  " << p9.turnaround_t << '\n';
	cout << "Average Turnaround: " << avg_tt << '\n';
	cout << "Response Times      P1   P2   P3   P4   P5   P6   P7   P8   P9" << '\n';
	cout << "                     " << p1.response_t << "    " << p2.response_t << "  " << p3.response_t << "   " << p4.response_t << "   " << p5.response_t << "    " << p6.response_t << "   " << p7.response_t << "  " << p8.response_t << "   " << p9.response_t << '\n';
	cout << "Average Response:   " << avg_resp << '\n';

	//cout << "\ncontext " << context;

	return 0;
}
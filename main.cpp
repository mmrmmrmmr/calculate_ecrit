#include "my_sim.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	RK_sol test{};

	ifstream setting_file;
	setting_file.open("./path.txt");
	string path;
	setting_file >> path;
	setting_file.close();
	setting_file.open(path + "./setting_sim.txt");
	int ele_num = 1;
	int equ_num = 1;
	double end_t;
	double step_t;
	double draw_time;
	{
		setting_file >> ele_num;
		setting_file >> equ_num;
		setting_file >> end_t;
		setting_file >> step_t;
		setting_file >> draw_time;
		// cout << ele_num;
	}
	// test.init(8, 10, 8e2, 1e-2, "./1/");
	test.init(ele_num, equ_num, end_t, step_t, path, draw_time);
	//cout << (test.charges_num);
	test.RK_solve();
}
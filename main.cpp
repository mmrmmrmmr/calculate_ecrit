#include "my_sim.h"
#include <iostream>

using namespace std;

int main()
{
	RK_sol test{};
	test.init(8, 10, 8e-3, 1e-7, "C:\\Users\\mmr88\\Desktop\\1\\");
	//cout << (test.charges_num);
	test.RK_solve();
}
#include <iostream>
#include "create_and_calculate.h"

using namespace std;

class RK_sol 
{
public:
	chemical_equation* chemical_eq;
	element_equation* element_eq;
	double* element_density;
	int* symbol_of_charge;

	ofstream pfile;
	
	int element_num;
	int equation_num;
	
	double end_time;
	double step_time;
	double now_time;
	
	void init(int, int, double, double, string);
	double calcuate_charge();
	void calcuate_electron();
	void calcuate_coefficient(double*, double*);
	void RK_solve();
	void print_f(double*);
	double charges_num;
};

void RK_sol::init(int set_element_num, int set_equation_num, double set_end_time, double set_step_time, string path)
{
	element_num = set_element_num;
	equation_num = set_equation_num;
	end_time = set_end_time;
	step_time = set_step_time;
	pfile.open(path + "ans.txt");

	chemical_eq = create_chemical_equation(equation_num);
	element_eq = create_element_equation(element_num);

	element_density = create_vector_double(element_num);
	symbol_of_charge = create_vector_int(element_num);

	init_vector_double(element_density, element_num, path);
	init_vector_int(symbol_of_charge, element_num, path);
	init_chemical_equation(chemical_eq, equation_num, path);
	init_element_equation(element_eq, element_num, path);
	
	charges_num = calcuate_charge();

	return;
}

double RK_sol::calcuate_charge()
{
	double num = 0;
	for (int i = 0; i < element_num; i++)
	{
		num += *(element_density + i) * *(symbol_of_charge + i);
	}
	return num;
}

void RK_sol::calcuate_electron()
{
	*(element_density) = 0;
	double num = calcuate_charge();
	*(element_density) = num - charges_num;
	//cout << "1 " << *(element_density) << endl;
	return;
}

void RK_sol::calcuate_coefficient(double* chemical_equation_ans, double* element_equation_ans)
{
	for (int i = 0; i < equation_num; i++)
	{
		*(chemical_equation_ans + i) = (chemical_eq + i)->k;
		for (int j = 0; j < (chemical_eq + i)->element_num; j++)
		{
			*(chemical_equation_ans + i) *= my_power(*(element_density + *((chemical_eq + i)->element + j)), *((chemical_eq + i)->coefficient + j));	
		}
		//cout << *(chemical_equation_ans+i) << " ";
	}
	for (int i = 1; i < element_num; i++)
	{
		*(element_equation_ans + i) = 0;
		for (int j = 0; j < (element_eq + i)->equation_num; j++)
		{
			*(element_equation_ans + i) += step_time * (double)*((element_eq + i)->symbol + j) * *(chemical_equation_ans + *((element_eq + i)->seial_num + j));
		}
		//cout << *(element_density + i) << " ";
	}
	//cout << endl;
	//dis(element_equation_ans);
	return;
}

void RK_sol::RK_solve()
{
	double* k1 = create_vector_double(element_num);
	double* k2 = create_vector_double(element_num);
	double* k3 = create_vector_double(element_num);
	double* k4 = create_vector_double(element_num);
	double* k = create_vector_double(element_num);
	double* density_before = create_vector_double(element_num);
	double* ans = create_vector_double(element_num);
	double* equ_ans = create_vector_double(equation_num);
	for (now_time = 0; now_time < end_time; now_time += step_time)
	{
		copy_vector(density_before, element_density, element_num);

		calcuate_coefficient(equ_ans, k1);
		
		copy_vector(k, k1, element_num);
		constant_multiply_vector(step_time / 2, k, element_num);
		vector_plus_vector(element_density, k, element_num);
		calcuate_electron();
		calcuate_coefficient(equ_ans, k2);

		copy_vector(k, k2, element_num);
		constant_multiply_vector(step_time / 2, k, element_num);
		vector_plus_vector(element_density, k, element_num);
		calcuate_electron();
		calcuate_coefficient(equ_ans, k3);

		copy_vector(k, k3, element_num);
		constant_multiply_vector(step_time, k, element_num);
		vector_plus_vector(element_density, k, element_num);
		calcuate_electron();
		calcuate_coefficient(equ_ans, k4);

		for (int i = 1; i < element_num; i++)
		{
			*(element_density + i) = *(density_before + i) + step_time / 6 * *(k1 + i) + step_time / 3 * *(k2 + i) + step_time / 3 * *(k3 + i) + step_time / 6 * *(k4 + i);
			//cout << *(element_density + i) << " ";
		}
		//cout << endl;
		calcuate_electron();
		print_f(element_density);
	}
	return;
	free(k);
	free(k1);
	free(k2);
	free(k3);
	free(k4);
	free(density_before);
	free(equ_ans);
	free(ans);
}

void RK_sol::print_f(double* vector)
{
	pfile << now_time << " ";
	for (int i = 0; i < element_num; i++)
	{
		pfile << * (vector + i) << " ";
	}
	pfile << endl;
	//outfile.close();
	return;
}

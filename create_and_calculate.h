#include <iostream>
#include <fstream>
using namespace std;

struct chemical_equation
{
	double k;
	int element_num;
	int* element;
	int* coefficient;
};

struct element_equation
{
	int equation_num;
	int* seial_num;
	int* symbol;
};

double* create_vector_double(int element_num)
{
	double* vector = (double*)malloc(element_num * sizeof(double));
	if (vector == nullptr) {
		cout << "error" << endl;
	}
	else
	{
		for (int i = 0; i < element_num; i++)
		{
			*(vector + i) = 0;
		}
	}
	return vector;
	free(vector);
}

int* create_vector_int(int element_num)
{
	int* vector = (int*)malloc(element_num * sizeof(int));
	// cout << element_num << endl;
	if (vector == nullptr) {
		cout << "error" << endl;
	}
	else
	{
		for (int i = 0; i < element_num; i++)
		{
			*(vector + i) = 0;
		}
	}
	return vector;
	free(vector);
}

chemical_equation* create_chemical_equation(int equation_num)
{
	chemical_equation* struct_vector = (chemical_equation*)malloc(equation_num * sizeof(chemical_equation));
	if (struct_vector == nullptr)
	{
		cout << "error" << endl;
	}
	//else
	//{
	//	for (int i = 0; i < equation_num; i++)
	//	{
	//		(struct_vector + i)->element = create_vector_int(element_num);
	//		(struct_vector + i)->coefficient = create_vector_int(element_num);
	//	}
	//}
	return struct_vector;
	free(struct_vector);
}

element_equation* create_element_equation(int element_num)
{
	element_equation* struct_vector = (element_equation*)malloc(element_num * sizeof(element_equation));
	if (struct_vector == nullptr)
	{
		cout << "error" << endl;
	}
	//else
	//{
	//	for (int i = 0; i < element_num; i++)
	//	{
	//		(struct_vector + i)->seial_num = create_vector_int(max_equation_num);
	//		(struct_vector + i)->symbol = create_vector_int(max_equation_num);
	//	}
	//}
	return struct_vector;
	free(struct_vector);
}

double** create_matrix(int line_num, int colume_num=1)
{
	double** matrix = (double**)malloc(line_num * sizeof(double*));
	if (matrix == nullptr) {
		cout << "error" << endl;
	}
	else
	{
		for (int i = 0; i < line_num; i++)
		{
			*(matrix+i) = (double*)malloc(colume_num * sizeof(double));
			if (*(matrix + i) == nullptr) {
				cout << "error" << endl;
			}
			else
			{
				*(matrix + i) = create_vector_double(colume_num);
			}
		}
	}
	return matrix;
	free(matrix);
}

void init_vector_double(double* vector, int element_num, string path)
{
	ifstream infile;
	double element = 0;
	infile.open(path + "den.txt");
	for (int i = 0; i < element_num; i++)
	{
		infile >> element;
		*(vector + i) = element;
		// cout << *(vector + i);
	}
	return;
}

void init_vector_int(int* vector, int element_num, string path)
{
	ifstream infile;
	int element = 0;
	infile.open(path + "sym.txt");
	for (int i = 0; i < element_num; i++)
	{
		infile >> element;
		*(vector + i) = element;
		//cout << *(vector + i);
	}
	return;
}

void init_chemical_equation(chemical_equation* vector, int equation_num, string path)
{
	ifstream infile;
	double k = 0;
	int x = 0;
	infile.open(path + "chem.txt");
	for (int i = 0; i < equation_num; i++)
	{
		infile >> k;
		(vector + i)->k = k;
		infile >> x;
		(vector + i)->element_num = x;
		// cout << x << endl;
		(vector + i)->element = create_vector_int(x);
		(vector + i)->coefficient = create_vector_int(x);
		for (int j = 0; j < (vector + i)->element_num; j++)
		{
			infile >> x;
			*((vector + i)->element + j) = x;
			infile >> x;
			*((vector + i)->coefficient + j) = x;
		}
	}
	return;
}

void init_element_equation(element_equation* vector, int element_num, string path)
{
	ifstream infile;
	int x = 0;
	infile.open(path + "ele.txt");
	for (int i = 1; i < element_num; i++)
	{
		infile >> x;
		(vector + i)->equation_num = x;
		(vector + i)->seial_num = create_vector_int(x);
		(vector + i)->symbol = create_vector_int(x);
		for (int j = 0; j < (vector + i)->equation_num; j++)
		{
			infile >> x;
			*((vector + i)->seial_num + j) = x;
			infile >> x;
			*((vector + i)->symbol + j) = x;
		}
	}
	return;
}

double my_power(double x, double a)
{
	double ans = 1;
	for (int i = 1; i < a; i++)
	{
		ans *= x;
	}
	return ans;
}

void vector_plus_vector(double* ans, double* add, int length)
{
	for (int i = 0; i < length; i++)
	{
		*(ans + i) += *(add + i);
	}
	return;
}

void constant_multiply_vector(double constent, double* vector, int length)
{
	for (int i = 0; i < length; i++)
	{
		*(vector + i) *= constent;
	}
	return;
}

void copy_vector(double* ans, double* vector, int length)
{
	for (int i = 1; i < length; i++)
	{
		*(ans + i) = *(vector + i);
	}
	return;
}
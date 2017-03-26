#include "Number.h"

int main(){

	std::cout << "Some numbers: 19, 25, 1, 89, 5, 124, 12" << std::endl;

	Number A = 19;
	A.print_Number_info();
	std::cout << std::endl;

	A = 25;
	A.print_Number_info();
	std::cout << std::endl;

	A = 1;
	A.print_Number_info();
	std::cout << std::endl;

	A = 89;
	A.print_Number_info();
	std::cout << std::endl;

	A = 5;
	A.print_Number_info();
	std::cout << std::endl;

	A = 124;
	A.print_Number_info();
	std::cout << std::endl;

	A = 12;
	A.print_Number_info();
	std::cout << std::endl;

	std::cout << "We can also do multiplication:" << std::endl << std::endl;
	
	A = 61;
	Number B(23);
	A *= B;
	std::cout << "61 * 23:" << std::endl;
	A.print_Number_info();
	std::cout << std::endl;

	A = 101;
	B = 1;
	A *= B;
	std::cout << "101 * 1:" << std::endl;
	A.print_Number_info();
	std::cout << std::endl;

	A = 24;
	B = 99;
	A *= B;
	std::cout << "24 * 99:" << std::endl;
	A.print_Number_info();
	std::cout << std::endl;

	int given;
	std::cout << "Please provide a number : ";
	std::cin >> given;
	std::cout << std::endl;

	Number x = given;

	x.print_Number_info();
	std::cout << std::endl;
	std::cout << "What is the smallest number that has this same unique prime factorization?" << std::endl << std::endl;

	A = x.small_common();
	A.print_Number_info();
}
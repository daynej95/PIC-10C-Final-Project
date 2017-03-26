#include <iostream>

class Number {

private:

	//fields
	int val;
	bool prime;

	int* prime_factors; //the unique prime factors of a Number
	int prime_size; //the number of unique prime factors of a number


	//private member functions:

	//returns true if val is divisible by rhs
	bool is_div(const int& rhs){
		return val % rhs == 0;
	}

	//returns true if val is a prime number
	bool is_prime(){
		for (int i = 2; i < val; i++){
			if (this->is_div(i)){
				return false;
			}
			return true;
		}
	}

public:

	//Default constructor
	Number() : val(1), prime(false), prime_factors(new int[0]), prime_size(0) {}

	//Constructor that takes an int to use for the Number's value (must be a positive int)
	Number(const int& num) : val(num) {
		if (num < 1){
			std::cout << "Warning: non-positive number introduced." << std::endl;
			throw;
		}
		prime = this->is_prime();
	}


};
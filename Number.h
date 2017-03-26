#include <iostream>

//returns true if lhs is divisible by rhs
bool is_div(const int& lhs, const int& rhs){
	return lhs % rhs == 0;
}

bool is_prime(const int& num){
	for (int i = 2; i < num; i++){
		if (is_div(num, i)){
			return false;
		}
		return true;
	}
}

class Number {

private:

	//fields
	int val;
	bool prime;
	int* prime_factors; //the unique prime factors of a Number
	int prime_size; //the amount of unique prime factors of a number


	//private member functions:


	//returns true if val is divisible by rhs
	bool is_div(const int& rhs){
		return ::is_div(val, rhs);
	}

	//returns true if val is a prime number
	bool is_prime(){
		return ::is_prime(val);
	}

	template<typename OutputIt>
	//this function takes an iterator to a container and puts the prime factors of the Number in it
	void prime_factorize(OutputIt begin){
		int i = 2;
		while (i <= val){
			if (this->is_div(i) && is_prime(i)){*begin = i}
			++begin;
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
#include <iostream>

class Number {

private:

	int val;
	bool prime;



public:

	//Default constructor
	Number() : val(1), prime(false){}


	//Constructor that takes an int to use for the Number's value (must be a positive int)
	Number(const int& num) : val(num), prime(false){
		if (num < 1){
			std::cout << "Warning: All numbers must be positive." << std::endl;
			throw;
		}
		prime = this->is_prime();
	}

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




};
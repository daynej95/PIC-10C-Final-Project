#include <iostream>
#include <exception>

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
			++i;
		}
	}
	
	//swap function
	void swap(Number& rhs){
		std::swap(val, rhs.val);
		std::swap(prime, rhs.prime);
		std::swap(prime_factors, rhs.prime_factors);
		std::swap(prime_size, rhs.prime_size);
	}

public:

	//Default constructor
	Number() : val(1), prime(false), prime_factors(nullptr), prime_size(0) {
		try{
			prime_factors = new int[0];
		}
		catch (std::exception &e){
			if (prime_factors) { delete[] prime_factors; }
			prime_factors = nullptr;
			throw;
		}
	

	}

	//Constructor that takes an int to use for the Number's value (must be a positive int)
	Number(const int& num) : val(num), prime(false), prime_factors(nullptr), prime_size(0) {
		if (num < 1){
			std::cout << "Warning: non-positive number introduced." << std::endl;
			throw;
		}
		try{
			prime = this->is_prime();

			int array_size = log2(val); //this will always be an upper bound for the number of prime factors a Number has
			prime_factors = new int[array_size]; //space is wasted, because the number of unique prime factors is almost always less than log2(val), but we can't predict the exact amount
			std::fill_n(prime_factors, array_size, 0);
			this->prime_factorize(prime_factors);

			while (prime_factors[prime_size] != 0){
				prime_size++;
			}
		}
		catch (std::exception &e){
			if (prime_factors) { delete[] prime_factors; }
			prime_factors = nullptr;
			throw;
		}		
	}

	//Copy constructor
	Number(const Number& rhs) : val(rhs.val), prime(rhs.prime), prime_factors(nullptr), prime_size(rhs.prime_size) {
		try{
			int array_size = log2(val);
			prime_factors = new int[array_size];
			for (size_t i = 0; i < array_size; i++){
				prime_factors[i] = rhs.prime_factors[i];
			}
		}
		catch (std::exception &e){
			if (prime_factors) { delete[] prime_factors; }
			prime_factors = nullptr;
			throw;
		}
	}

	//Assignment operator
	Number operator=(Number rhs){
		this->swap(rhs);
		return *this;
	}

	//Move constructor
	Number(Number&& rhs){
		this->swap(rhs);
	}

	//Destructor
	virtual ~Number(){
		delete[] prime_factors;
		prime_factors = nullptr;
	}




};

//returns true if lhs is divisible by rhs
bool is_div(const int& lhs, const int& rhs){
	return lhs % rhs == 0;
}


//returns true if num is a prime number
bool is_prime(const int& num){
	if (num == 1) { return false; }
	for (int i = 2; i < num; i++){
		if (is_div(num, i)){
			return false;
		}
		return true;
	}
}
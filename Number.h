#include <iostream>
#include <exception>

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
	}
	return true;
}

template<typename ForwardIt, typename OutputIt>
//need this merge function to define operator*= later on (we merge the prime factorizations)
void unique_merge(ForwardIt vbegin, ForwardIt vend, ForwardIt wbegin, ForwardIt wend, OutputIt out){
	while (vbegin != vend && wbegin != wend){
		if (*vbegin == *wbegin){
			*out = *vbegin;
			++vbegin;
			++wbegin;
		}
		else if (*vbegin < *wbegin){
			*out = *vbegin;
			++vbegin;
		}
		else{
			*out = *wbegin;
			++wbegin;
		}
		++out;
	}
	while (vbegin != vend){
		*out = *vbegin;
		++vbegin;
		++out;
	}
	while (wbegin != wend){
		*out = *wbegin;
		++wbegin;
		++out;
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
		while (i < val){
			if (this->is_div(i) && ::is_prime(i)){
				*begin = i;
				++begin;
			}
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


	//Acessor Functions:

	int get_value(){return val;}
	bool get_prime(){return prime;}
	int get_prime_size(){return prime_size;}
	int get_ith_unique_prime_factor(int i){
		if (i >= prime_size){
			std::cout << "Error" << std::endl;
			throw;
		}
		return prime_factors[i];
	}
	
	//Printing to the console
	void print_prime_factors(){
		std::cout << "{";
		if (prime_size != 0){
			std::cout << prime_factors[0];
			for (size_t i = 1; i < prime_size; i++){
				std::cout << ", " << prime_factors[i];
			}
		}
		std::cout << "}";
	}
	void print_Number_info(){
		std::cout << "Value: " << val << std::endl;
		std::cout << "Is this number prime? : " << (prime ? "Yes" : "No") << std::endl;
		std::cout << "Prime factors: ";
		print_prime_factors();
		std::cout << std::endl;
	}

	//Some arithmetic

	Number& operator*=(Number rhs){
		val *= rhs.val; //from here I could have just done *this = Number(val), but I think it's more interesting to use the prime factorizations I already have to determine the new one
		prime = (this->is_prime() && rhs.val == 1 || rhs.is_prime() && val == 1); //the product is only prime if one of the inputs is 1 and the other is prime, otherwise it is not prime

		int* temp = new int[prime_size + rhs.prime_size]; //at most, the product's prime factorization will be as big as the sum of those of the two inputs
		std::fill_n(temp, prime_size + rhs.prime_size, 0);
		unique_merge(prime_factors, prime_factors + prime_size, rhs.prime_factors, rhs.prime_factors + rhs.prime_size, temp);

		std::swap(prime_factors, temp);
		delete[] temp;
		temp = nullptr;

		while (prime_factors[prime_size] != 0){
			prime_size++;
		}
		return *this;
	}
	

};
class Number {

private:

	int val;



public:

	//returns true if val is divisible by rhs
	bool is_div(int rhs){
		return val % rhs == 0;
	}

};
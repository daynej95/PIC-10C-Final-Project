class Number {

private:

	int val;



public:

	//returns true if val is divisible by rhs
	bool is_div(int rhs){
		if (val % rhs == 0){
			return true;
		}
		return false;
	}

};
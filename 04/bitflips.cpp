#include <iostream>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <map>

#define BASE 1000000000

using namespace std;

class bigint {
public:

	bigint(): digits() {}
	bigint(uint32_t n): digits(1, n) {}

	void operator+=(const bigint& other) {
		uint32_t carry = 0;
		unsigned int i = 0;
		unsigned int size_this = this->digits.size();
		unsigned int size_other = other.digits.size();
		unsigned int size_min = min(size_this, size_other);

		for (; i < size_min; ++i) {
			uint64_t sum = ((uint64_t) this->digits[i])
				+ ((uint64_t) other.digits[i]) + ((uint64_t)carry);
			this->digits[i] = sum % BASE;
			carry = sum / BASE;
		}

		for (; i < size_this; ++i) {
			uint64_t sum = ((uint64_t) this->digits[i]) + ((uint64_t) carry);
			this->digits[i] = sum % BASE;
			carry = sum / BASE;
		}

		for (; i < size_other; ++i) {
			uint64_t sum = ((uint64_t) other.digits[i]) + ((uint64_t) carry);
			this->digits.push_back(sum % BASE);
			carry = sum / BASE;
		}

		if (carry) {
			this->digits.push_back(carry);
		}

	}

	 void square() {
		bigint copy = *this;
		unsigned int size = this->digits.size();
		this->digits = vector<uint32_t>(1, 0);
		
		for (unsigned int i = 0; i < size; ++i) {

			bigint result(copy);
			result *= copy.digits[i];
			result <<= i;

			*this += result;
		}
	}

	void operator<<=(const int& other) {
		if (other == 0) {
			return;
		}
		this->digits.resize(this->digits.size() + other);
		int size = this->digits.size();

		for (int i = size - 1; i >= other; --i) {
			this->digits[i] = this->digits[i - other];
			this->digits[i - other] = 0;
		}
	}

	void operator*=(const uint32_t& other) {
		uint32_t carry = 0;
		unsigned int i = 0;
		unsigned int size = this->digits.size();

		for (; i < size; ++i) {
			uint64_t sum = ((uint64_t) this->digits[i])*((uint64_t) other)
				+ ((uint64_t) carry);
			this->digits[i] = sum % BASE;
			carry = sum / BASE;
		}

		if (carry) {
			this->digits.push_back(carry);
		}
	}

	void print() {
		cout << digits[digits.size() - 1];

		for (int i = digits.size() - 2; i >= 0; --i) {
			cout.width(9);
			cout.fill('0');
			cout << digits[i];
		}
	}

private:
	vector<uint32_t> digits;
};

bigint pow(uint32_t base, uint32_t exp) {

	if (exp == 0) {
		return bigint(1);
	}

	bigint num = pow(base, exp/2);
	num.square();

	if (exp % 2 == 1) {
		num *= base;
	}

	return num;
}

vector<uint32_t> get_compressed(int num) {
	vector<uint32_t> powers(1, 0);
	int i = 5;
	int sum = 3;
	while (sum < num) {
		powers.push_back(sum);
		sum += i;
		i += 2;
	}
	return powers;
}

bigint uncompress(const vector<uint32_t>& powers) {

	if (powers.size() == 0) {
		return bigint(0);
	}

	static map<int, bigint> memonization = map<int, bigint>();

	map<int, bigint>::iterator element = memonization.find(powers.size());

	if (element != memonization.end()) {
		return element->second;
	}

	bigint num = uncompress(vector<uint32_t>(powers.begin(), --(powers.end())));
	num += pow(2, powers.back());

	memonization[powers.size()] = num;

	return num;
}

int main() {

	int N;
	cin >> N;

	for (int i = 0; i < N; ++i) {
		int n;
		cin >> n;
		uncompress(get_compressed(n)).print();
		cout << endl;
	}
}

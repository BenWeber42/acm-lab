#include <iostream>

#define MOD 100000007

using namespace std;

class vec {
public:
	vec(long long v1, long long v2): v1(v1), v2(v2) {}
	long long v1, v2;
};

class mat {
public:
	mat(long long a11, long long a12, long long a21, long long a22):
		a11(a11), a12(a12), a21(a21), a22(a22) {}

	const mat operator*(const mat& other) const {
		return mat(
				this->a11*other.a11%MOD + this->a12*other.a21%MOD,  // a11
				this->a11*other.a12%MOD + this->a12*other.a22%MOD,  // a12
				this->a21*other.a11%MOD + this->a22*other.a21%MOD,  // a21
				this->a21*other.a12%MOD + this->a22*other.a22%MOD); // a22
	}

	const vec operator*(const vec& other) const {
		return vec(
				a11*other.v1%MOD + a12*other.v2%MOD,
				a21*other.v1%MOD + a22*other.v2%MOD
				);
	}

	const mat pow(long long n) const {
		if (n == 0) {
			return mat(
					1, 0,
					0, 1);
		}
		if (n == 1) {
			return *this;
		}

		mat A = pow(n/2);
		A = A*A;

		if (n%2 == 1) {
			A = (*this)*A;
		}

		return A;
	}

	long long a11, a12, a21, a22;
};

int main() {
	const mat A = mat(
			1, 1,
			1, 0);
	const vec fib = vec(1, 0);

	int N;
	cin >> N;

	for (int i = 0; i < N; ++i) {
		long long n;
		cin >> n;
		vec fib_n = (A.pow(n))*fib;
		cout << (fib_n.v1 % MOD)<< endl;
	}

}

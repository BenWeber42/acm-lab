#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

using namespace std;

template <typename Integer, Integer base>
class BigInt {
public:
    BigInt() {}
    BigInt(Integer other) : digits(1, other) {
        assert(other >= 0);
    }

    BigInt(const BigInt<Integer, base>& other) : digits(other.digits) {}
    BigInt(const BigInt<Integer, base>* other) : digits(other->digits) {}

    void operator+=(Integer other) {
        this->operator+=(BigInt(other));
    }

    void operator+=(const BigInt<Integer, base>& other) {
        int carry = 0, i = 0;
        for (; i < (int) digits.size() && i < (int) other.digits.size(); ++i) {
            digits[i] += carry + other.digits[i];
            carry = digits[i] / base;
            digits[i] %= base;
        }

        for (; i < (int) digits.size() && carry; ++i) {
            digits[i] += carry;
            carry = digits[i] / base;
            digits[i] %= base;
        }

        for (; i < (int) other.digits.size(); ++i) {
            digits.push_back(other.digits[i] + carry);
            carry = digits.back() / base;
            digits.back() %= base;
        }

        if (carry)
            digits.push_back(carry);
    }

    BigInt<Integer, base> operator+(const BigInt<Integer, base>& other) const {
        BigInt<Integer, base> result(this);
        result += other;
        return result;
    }

    void operator<<=(int shift) {
        assert(shift >= 0);
        vector<Integer> shifted_digits(shift + digits.size());
        for (int i = 0; i < (int) digits.size(); ++i) {
            shifted_digits[shift + i] = digits[i];
        }
        swap(digits, shifted_digits);
    }

    BigInt<Integer, base> operator<<(int other) const {
        BigInt<Integer, base> result(this);
        result <<= other;
        return result;
    }

    void operator*=(Integer other) {
        assert(other >= 0);
        int carry = 0;
        for (int i = 0; i < (int) digits.size(); ++i) {
            digits[i] = digits[i]*other + carry;
            carry = digits[i] / base;
            digits[i] %= base;
        }

        if (carry)
            digits.push_back(carry);
    }

    void operator*=(const BigInt<Integer, base>& other) {
        BigInt<Integer, base> left(this);
        digits.clear();
        for (int i = 0; i < (int) other.digits.size(); ++i) {
            BigInt temp(left);
            temp <<= i;
            temp *= other.digits[i];
            this->operator+=(temp);
        }
    }

    BigInt<Integer, base> operator*(const BigInt<Integer, base>& other) const {
        BigInt<Integer, base> result(this);
        result *= other;
        return result;
    }

    void exp(int other) {
        BigInt<Integer, base> result = pow(this, other);
        swap(digits, result.digits());
    }

    friend BigInt<Integer, base> operator+(const Integer& a, const BigInt<Integer, base>& b) {
        return b + a;
    }

    friend BigInt<Integer, base> operator*(const Integer& a, const BigInt<Integer, base>& b) {
        return b*a;
    }

    friend BigInt<Integer, base> pow(const BigInt<Integer, base>& a, Integer b) {
        assert(b >= 0);
        if (b == 1)
            return BigInt<Integer, base>(a);
        if (b == 0)
            return BigInt<Integer, base>(1);

        BigInt<Integer, base> tmp = pow(a, b/2);
        tmp = tmp*tmp;

        if (b%2 == 1)
            tmp *= a;

        return tmp;
    }

    friend ostream& operator<<(ostream& stream, const BigInt<Integer, 1000000000>& bigInt) {
        if (bigInt.digits.empty())
            return stream << 0;

        stream << bigInt.digits.back();
        for (int i = bigInt.digits.size() - 2; i >= 0; --i) {
            stream << setfill('0') << setw(9) << bigInt.digits[i];
        }
        return stream;
    }

private:
    vector<Integer> digits;
}; // end class BigInt

typedef BigInt<unsigned long long int, 1000000000> Int;

vector<Int> memo;
vector<int> memo_initialized;

Int binomial(int n, int k) {
    assert(n >= k && n >= 0 && k >= 0);

    if (n == k || k == 0)
        return Int(1);

    if (n - k < k)
        return binomial(n, n - k);

    if (memo_initialized[n*1000 +k])
        return memo[n*1000 + k];

    Int& mem = memo[n*1000 + k];
    memo_initialized[n*1000 + k] = 1;

    mem = binomial(n - 1, k - 1) + binomial(n - 1, k);

    return mem;
}

Int compute(int n, int a, int b) {
    Int score;

    int xb = 0, xa = (n - 1)/2;

    while (xa >= 0) {

        if (1 + 2*xa + 3*xb == n) {
            score += binomial(xa + xb, xa)*pow(Int(a), xa)*pow(Int(b), xb);
        }

        --xa;
        while (1 + 2*xa + 3*xb < n)
            ++xb;
    }

    return score;
}

int main() {
    ios_base::sync_with_stdio(false);

    memo = vector<Int>(1000*1000);
    memo_initialized = vector<int>(1000*1000);

    int tests;
    cin >> tests;
    while (tests--) {
        int n, a, b;
        cin >> n >> a >> b;

        cout << compute(n, a, b) << endl;
    }
}

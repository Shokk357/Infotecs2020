#include "BigNum.h"

const long long numOrder = 10E8;

BigNum::BigNum(const std::string& expression) {
    for (int i = expression.length(); i > 0; i -= 9)
        if (i < 9)
            val.push_back(atoi(expression.substr(0, i).c_str()));
        else
            val.push_back(atoi(expression.substr(i - 9, 9).c_str()));
}

void BigNum::parse(const std::string &expression) {
    std::string substr;
    for (char elem : expression) {
        if (elem == 'K') {
            BigNum arg(substr);
            *this += arg;
            substr = "";
        } else if (elem == 'B') {
            continue;
        } else {
            substr += elem;
        }
    }
    if (!substr.empty()) {
        BigNum arg(substr);
        *this += arg;
    }
    if (val.empty()) {
        val.push_back(0);
    }
}

BigNum &BigNum::operator+=(const BigNum &arg) {
    int carry = 0;
    for (size_t i = 0; i < std::max(val.size(), arg.val.size()) || carry; i++) {
        if (i == val.size())
            val.push_back(0);
        val[i] += carry + (i < arg.val.size() ? arg.val[i] : 0);
        carry = val[i] >= numOrder;
        if (carry) val[i] -= numOrder;
    }
    return *this;
}

std::string BigNum::toString() {
    std::string ans;
    ans = val.empty() ? "0" : std::to_string(val.back());
    for (int i = (int) val.size() - 2; i >= 0; i--)
        ans.append(std::to_string(val[i]));
    return ans;
}

bool BigNum::isDivide() {
    long long carry = 0;
    for (int i = val.size() - 1; i >= 0; i--) {
        long long cur = val[i] + carry * numOrder;
        val[i] = cur / 32;
        carry = cur % 32;
    }
    return !carry;
}

#ifndef INFOTECSFST_LONGMATH_H
#define INFOTECSFST_LONGMATH_H

#include <string>
#include <vector>

class BigNum {
public:
    BigNum() = default;

    BigNum(const std::string& expression);

    BigNum &operator+=(const BigNum &arg);

    void parse(const std::string &expression);

    std::string toString();

    bool isDivide();

private:
    std::vector<int> val;
};

#endif //INFOTECSFST_LONGMATH_H

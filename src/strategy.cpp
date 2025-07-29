#include "../include/strategy.h"

// 无折扣

double NoDiscount::getDiscountedPrice(const double price) const { return price; }

// 学生折扣（假设8折）
double StudentDiscount::getDiscountedPrice(const double price) const {
    return price * 0.8;
}

// 限时折扣
TimeLimitedDiscount::TimeLimitedDiscount(const double rate) : discountRate(rate) {
}

double TimeLimitedDiscount::getDiscountedPrice(const double price) const {
    return price * discountRate;
}

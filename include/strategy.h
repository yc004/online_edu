#ifndef STRATEGY_H
#define STRATEGY_H

// 折扣策略接口
class DiscountStrategy {
public:
  virtual double getDiscountedPrice(double price) const = 0;
  virtual ~DiscountStrategy() {}
};

// 无折扣
class NoDiscount : public DiscountStrategy {
public:
  double getDiscountedPrice(double price) const override;
};

// 学生折扣
class StudentDiscount : public DiscountStrategy {
public:
  double getDiscountedPrice(double price) const override;
};

// 限时折扣
class TimeLimitedDiscount : public DiscountStrategy {
private:
  double discountRate; // 0.8表示8折
public:
  TimeLimitedDiscount(double rate);
  double getDiscountedPrice(double price) const override;
};

#endif // STRATEGY_H

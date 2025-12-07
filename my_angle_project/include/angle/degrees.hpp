#pragma once
#include <ostream>

namespace ang {

class degrees {
    double v_{0.0};
public:
    explicit constexpr degrees(double x = 0.0) noexcept : v_(x) {}
    constexpr double value() const noexcept { return v_; }

    constexpr degrees operator+(degrees o) const noexcept { return degrees(v_ + o.v_); }
    constexpr degrees operator-(degrees o) const noexcept { return degrees(v_ - o.v_); }
    constexpr degrees operator*(double k) const noexcept { return degrees(v_ * k); }
    constexpr degrees operator/(double k) const noexcept { return degrees(v_ / k); }

    constexpr bool operator==(degrees o) const noexcept { return v_ == o.v_; }
    constexpr bool operator!=(degrees o) const noexcept { return !(*this == o); }
    constexpr bool operator<(degrees o)  const noexcept { return v_ < o.v_; }
    constexpr bool operator>(degrees o)  const noexcept { return o < *this; }
    constexpr bool operator<=(degrees o) const noexcept { return !(o < *this); }
    constexpr bool operator>=(degrees o) const noexcept { return !(*this < o); }

    constexpr operator double() const noexcept { return v_; }
};

inline std::ostream& operator<<(std::ostream& os, degrees d) {
    return os << d.value() << " deg";
}

}
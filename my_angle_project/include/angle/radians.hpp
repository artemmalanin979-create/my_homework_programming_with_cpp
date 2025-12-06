#pragma once
#include <ostream>

namespace ang {

class radians {
    double v_{0.0};
public:
    explicit constexpr radians(double x = 0.0) noexcept : v_(x) {}
    constexpr double value() const noexcept { return v_; }

    constexpr radians operator+(radians o) const noexcept { return radians(v_ + o.v_); }
    constexpr radians operator-(radians o) const noexcept { return radians(v_ - o.v_); }
    constexpr radians operator*(double k) const noexcept { return radians(v_ * k); }
    constexpr radians operator/(double k) const noexcept { return radians(v_ / k); }

    constexpr bool operator==(radians o) const noexcept { return v_ == o.v_; }
    constexpr bool operator!=(radians o) const noexcept { return !(*this == o); }
    constexpr bool operator<(radians o)  const noexcept { return v_ < o.v_; }
    constexpr bool operator>(radians o)  const noexcept { return o < *this; }
    constexpr bool operator<=(radians o) const noexcept { return !(o < *this); }
    constexpr bool operator>=(radians o) const noexcept { return !(*this < o); }

    constexpr operator double() const noexcept { return v_; }
};

inline std::ostream& operator<<(std::ostream& os, radians r) {
    return os << r.value() << " rad";
}

} // namespace ang
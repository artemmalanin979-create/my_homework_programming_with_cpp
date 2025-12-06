#pragma once
#include <angle/degrees.hpp>
#include <angle/radians.hpp>
#include <cmath>        // M_PI

namespace ang {

inline constexpr double pi_v = 3.14159265358979323846;

inline constexpr radians to_radians(degrees d) noexcept {
    return radians(d.value() * pi_v / 180.0);
}
inline constexpr degrees to_degrees(radians r) noexcept {
    return degrees(r.value() * 180.0 / pi_v);
}

} // namespace ang

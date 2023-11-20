#include "Vectortype.h"

//==============================================================================================
Double::Double() noexcept : major(0), minor(0) {};
Double::Double(const string& val) noexcept { AddULL(stoull(val)); };
Double::Double(const Double& val) noexcept { *this = val; };

uint Double::GetMajor() const noexcept { return major; }
uint Double::GetMinor() const noexcept { return minor; }
//==============================================================================================
string Double::toString() const noexcept {
    return to_string(static_cast<ull>(major) * maxui + minor);
}
ostream& operator<<(ostream& c, Double& lng) noexcept {
    return (c << lng.toString());
}
istream& operator>>(istream& c, Double& lng) {
    string s; c >> s;
    Double temp(s);
    lng = temp;
    return c;
}
//==============================================================================================
Double& Double::operator=(const double& val) {
    if (val < 0) throw underflow_error(errors[2]);
    major = 0, minor = static_cast<uint>(val);
    return *this;
}
Double& Double::operator+=(const double& val) {
    uint temp = static_cast<uint>(val);
    if (major == 0 && temp > minor && val < 0) throw underflow_error(errors[2]);
    if (val >= 0) {
        if (overflowMinorSum(temp)) {
            if (overflowMajorSum()) throw overflow_error(errors[0]);
            // ������� minor � ������ ������������
            temp -= maxui - minor, minor = temp, ++major;
        }
        else minor += temp;
    }
    else *this -= abs(val);
    return *this;
}
Double& Double::operator-=(const double& val) {
    uint temp = static_cast<uint>(val);
    if (major == 0 && temp > minor && val > 0) throw underflow_error(errors[2]);
    if (val >= 0) {
        if (temp > minor) {
            if (major == 0) throw underflow_error(errors[2]);
            // ������� minor � ������ ������� ������������
            minor = maxui - (temp - minor), --major;
        }
        else minor -= temp;
    }
    else *this += abs(val);
    return *this;
}
Double& Double::operator*=(const double& val) {
    if (val < 0) throw underflow_error(errors[2]);
    uint temp = static_cast<uint>(val);
    major *= temp;
    AddULL(static_cast<ull>(temp) * minor);
    return *this;
}
Double& Double::operator/=(const double& val) {
    if (val == 0) throw underflow_error(errors[1]);
    if (val < 0) throw underflow_error(errors[3]);
    uint temp = static_cast<uint>(val);
    // ������� ������� �� ������� major
    double rest = static_cast<double>(major) / temp - (major / temp);
    double r = fmod(static_cast<double>(minor), temp);
    // ����� ������. If ���������, ����� ��� major � ������� �� ����� �������� ��������
    if (major != 0 && fmod(static_cast<double>(minor), temp) != static_cast<double>(temp) / 2)
        // � minor ���������� ���������� �����, ���������� �� ���������� +-1
        minor = static_cast<uint>(ceil(static_cast<double>(minor) / temp));
    else minor /= temp;
    major /= temp;
    // ���������� ������� � minor
    // ���� rest ����� ������ 0.5, �� � Double ����� ������������
    if (rest > 0.5) rest -= 0.5, * this += static_cast<Double>(rest * maxui);
    // rest <= 0.5
    *this += static_cast<Double>(rest * maxui);
    return *this;
}
Double& Double::operator%=(const Double& val) {
    Double tempDouble = *this;
    // ����� ������, ����� �������� �������
    tempDouble /= val, tempDouble *= val;
    // ������� �������� �������
    *this -= tempDouble;
    return *this;
}
//==============================================================================================
Double& Double::operator++() {
    return *this += 1;
}
Double Double::operator++(int) {
    return *this += 1;
}
Double& Double::operator--() {
    return *this -= 1;
}
Double Double::operator--(int) {
    return *this -= 1;
}
Double& Double::operator+=(const Double& rlng) {
    if (overflowMajorSum(rlng.major)) throw overflow_error(errors[0]);
    major += rlng.major;
    uint temp = static_cast<uint>(rlng.minor);
    if (overflowMinorSum(temp)) {
        if (overflowMajorSum()) throw overflow_error(errors[0]);
        // ������� minor � ������ ������������
        temp -= maxui - minor, minor = temp, ++major;
    }
    else minor += temp;
    return *this;
}
Double& Double::operator-=(const Double& rlng) {
    if (major < rlng.major) throw underflow_error(errors[2]);
    major -= rlng.major;
    uint temp = static_cast<uint>(rlng.minor);
    if (temp > minor) {
        if (major == 0) throw underflow_error(errors[2]);
        // ������� minor � ������ ������� ������������
        minor = maxui - (temp - minor), --major;
    }
    else minor -= temp;
    return *this;
}
Double& Double::operator*=(const Double& rlng) {
    ull mul1 = static_cast<ull>(major) * maxui + minor;
    ull mul2 = static_cast<ull>(rlng.major) * maxui + rlng.minor;
    *this = 0;
    return AddULL(mul1 * mul2);
}
Double& Double::operator/=(const Double& rlng) {
    ull dividend = static_cast<ull>(major) * maxui + minor;
    ull divider = static_cast<ull>(rlng.major) * maxui + rlng.minor;
    *this = 0;
    // �.�. 2^64 / 2^32 = 2^32, �� Double �� �������� ��������� (2^16;2^32]
    // � ������� ������������� ����� AddULL, ������� �� �������� ������ 2^64 / [1;2^32)
    return AddULL(dividend / divider);
}
Double& Double::operator%=(const Double& rlng) {
    ull dividend = static_cast<ull>(major) * maxui + minor;
    ull divider = static_cast<ull>(rlng.major) * maxui + rlng.minor;
    *this = 0;
    return AddULL(dividend % divider);
}
//==============================================================================================
Double operator+(const double& val, const Double& lng) {
    Double temp = lng;
    return (temp += val);
}
Double operator-(const double& val, const Double& lng) {
    Double temp = lng;
    return temp = val - (static_cast<ull>(temp.GetMajor()) * maxui + temp.GetMinor());
}
Double operator*(const double& val, const Double& lng) {
    Double temp = lng;
    return temp *= val;
}
Double operator/(const double& val, const Double& lng) {
    Double temp = lng;
    return temp = val / (static_cast<ull>(temp.GetMajor()) * maxui + temp.GetMinor());
}
Double operator%(const long& val, const Double& lng) {
    Double temp = lng;
    return temp = val % (static_cast<ull>(temp.GetMajor()) * maxui + temp.GetMinor());
}
Double operator+(const Double& lng, const double& val) {
    Double temp = lng;
    return temp += val;
}
Double operator-(const Double& lng, const double& val) {
    Double temp = lng;
    return temp -= val;
}
Double operator*(const Double& lng, const double& val) {
    Double temp = lng;
    return temp *= val;
}
Double operator/(const Double& lng, const double& val) {
    Double temp = lng;
    return temp /= val;
}
Double operator%(const Double& lng, const double& val) {
    Double temp = lng;
    return temp %= val;
}
Double Double::operator+(const Double& rlng) const {
    Double temp = *this;
    return temp += rlng;
}
Double Double::operator-(const Double& rlng) const {
    Double temp = *this;
    return temp -= rlng;
}
Double Double::operator*(const Double& rlng) const {
    Double temp = *this;
    return temp *= rlng;
}
Double Double::operator/(const Double& rlng) const {
    Double temp = *this;
    return temp /= rlng;
}
Double Double::operator%(const Double& rlng) const {
    Double temp = *this;
    return temp %= rlng;
}
//==============================================================================================
bool operator>(const Double& lng, const double& val) noexcept {
    return (static_cast<ull>(lng.GetMajor()) * maxui + lng.GetMinor() > val);
}
bool operator<(const Double& lng, const double& val) noexcept {
    return (static_cast<ull>(lng.GetMajor()) * maxui + lng.GetMinor() < val);
}
bool operator==(const Double& lng, const double& val) noexcept {
    return (static_cast<ull>(lng.GetMajor()) * maxui + lng.GetMinor() == val);
}
bool operator>=(const Double& lng, const double& val) noexcept {
    return (lng > val || lng == val);
}
bool operator<=(const Double& lng, const double& val) noexcept {
    return (lng < val || lng == val);
}
bool operator!=(const Double& lng, const double& val) noexcept {
    return !(lng == val);
}
bool operator>(const double& val, const Double& lng) noexcept {
    return (lng < val);
}
bool operator<(const double& val, const Double& lng) noexcept {
    return (lng > val);
}
bool operator==(const double& val, const Double& lng) noexcept {
    return (lng == val);
}
bool operator>=(const double& val, const Double& lng) noexcept {
    return (lng <= val);
}
bool operator<=(const double& val, const Double& lng) noexcept {
    return (lng >= val);
}
bool operator!=(const double& val, const Double& lng) noexcept {
    return (lng != val);
}
bool Double::operator>(const Double& rlng) const noexcept {
    if (major == rlng.major) return (minor > rlng.minor);
    return (major > rlng.major);
}
bool Double::operator==(const Double& rlng) const noexcept {
    return (major == rlng.major && minor == rlng.minor);
}
bool Double::operator<(const Double& rlng) const noexcept {
    return (rlng > *this);
}
bool Double::operator>=(const Double& rlng) const noexcept {
    return (*this > rlng || *this == rlng);
}
bool Double::operator<=(const Double& rlng) const noexcept {
    return (rlng > *this || *this == rlng);
}
bool Double::operator!=(const Double& rlng) const noexcept {
    return !(*this == rlng);
}
//==============================================================================================
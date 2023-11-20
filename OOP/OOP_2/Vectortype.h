#ifndef HEADER_99F54CF457064E77
#define HEADER_99F54CF457064E77

#pragma once
#include <cstdint>
#include <iostream>
#include <cmath>
#include <string>
#include <climits>
#include <cassert>

using namespace std;
using uint = uint32_t;
using ull = uint64_t;

constexpr uint maxui = UINT32_MAX;

class Double
{
private:
	uint major = 0, minor = 0;

	// Проверка на переполнение младшего разряда
	bool overflowMinorSum(const double& val) const noexcept {
		return (minor > maxui - val);
	}
	bool overflowMinorMul(const double& val) const noexcept {
		return (minor > maxui / val);
	}
	// Проверка на переполнение старшего разряда
	bool overflowMajorSum(const double& val = 1) const noexcept {
		return (major > maxui - val);
	}
	bool overflowMajorMul(const double& val) const noexcept {
		return (major > maxui / val);
	}
	string errors[4]{
		"Ошибка: Вызвано верхнее переполнение!",
		"Ошибка: Деление на ноль!",
		"Ошибка: Вызвано нижнее переполнение!",
		"Ошибка: Деление на отрицательное число!"
	};
	// Добавляет число предположительно больше unsigned int
	Double& AddULL(const ull& val)
	{
		uint temp = static_cast<uint>(val);
		if (val > maxui) {
			// Ищем количество переполнений
			ull count = val / maxui;
			if (major > maxui - val) throw overflow_error(errors[0]);
			// Добавляем количество переполнений в старший разряд
			major += static_cast<uint>(count);
			// Находим остаток от деления
			temp = static_cast<uint>(val % maxui);
		}
		minor = temp;
		return *this;
	}

public:
	Double() noexcept;
	Double(const string& val) noexcept;
	Double(const double& val) noexcept;

	uint GetMajor() const noexcept;
	uint GetMinor() const noexcept;

	string toString() const noexcept;

	friend ostream& operator<<(ostream& c, const double& major) noexcept;
	friend istream& operator>>(istream& c, double& lng);

	Double& operator=(const double& val);
	Double& operator+=(const double& val);
	Double& operator-=(const double& val);
	Double& operator*=(const double& val);
	Double& operator/=(const double& val);
	Double& operator%=(const double& val);

	Double& operator++();
	Double operator++(int);
	Double& operator--();
	Double operator--(int);
	Double& operator+=(const Double& rlng);
	Double& operator-=(const Double& rlng);
	Double& operator*=(const Double& rlng);
	Double& operator/=(const Double& rlng);
	Double& operator%=(const Double& rlng);

	Double operator+(const Double& rlng) const;
	Double operator-(const Double& rlng) const;
	Double operator*(const Double& rlng) const;
	Double operator/(const Double& rlng) const;
	Double operator%(const Double& rlng) const;

	bool operator>(const Double& rlng) const noexcept;
	bool operator<(const Double& rlng) const noexcept;
	bool operator==(const Double& rlng) const noexcept;
	bool operator>=(const Double& rlng) const noexcept;
	bool operator<=(const Double& rlng) const noexcept;
	bool operator!=(const Double& rlng) const noexcept;
};
Double operator+(const double& val, const Double& lng);
Double operator-(const double& val, const Double& lng);
Double operator*(const double& val, const Double& lng);
Double operator/(const double& val, const Double& lng);
Double operator%(const double& val, const Double& lng);
Double operator+(const Double& lng, const double& val);
Double operator-(const Double& lng, const double& val);
Double operator*(const Double& lng, const double& val);
Double operator/(const Double& lng, const double& val);
Double operator%(const Double& lng, const double& val);

bool operator>(const Double& lng, const double& val) noexcept;
bool operator<(const Double& lng, const double& val) noexcept;
bool operator==(const Double& lng, const double& val) noexcept;
bool operator>=(const Double& lng, const double& val) noexcept;
bool operator<=(const Double& lng, const double& val) noexcept;
bool operator!=(const Double& lng, const double& val) noexcept;
bool operator>(const double& val, const Double& lng) noexcept;
bool operator<(const double& val, const Double& lng) noexcept;
bool operator==(const double& val, const Double& lng) noexcept;
bool operator>=(const double& val, const Double& lng) noexcept;
bool operator<=(const double& val, const Double& lng) noexcept;
bool operator!=(const double& val, const Double& lng) noexcept;

#endif // header guard
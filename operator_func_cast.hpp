#pragma once

#include <functional>
#include <any>

template<typename T>
inline bool compare_values(const T& left, const T& right, const std::string& sign) {
    if (sign == "<")  return left < right;
    if (sign == "<=") return left <= right;
    if (sign == ">")  return left > right;
    if (sign == ">=") return left >= right;
    if (sign == "==") return left == right;
    if (sign == "!=") return left != right;
    return false;
}

inline std::function<bool(const std::any& value)> get_operator_func(const std::string& sign, const std::any& operand) {
    return [sign, operand](const std::any& value) {
        if (value.type() == typeid(int)) {
            return compare_values(std::any_cast<int>(value), std::any_cast<int>(operand), sign);
        }
        else if (value.type() == typeid(float)) {
            return compare_values(std::any_cast<float>(value), std::any_cast<float>(operand), sign);
        }
        else if (value.type() == typeid(double)) {
            return compare_values(std::any_cast<double>(value), std::any_cast<double>(operand), sign);
        }
        else if (value.type() == typeid(std::string)) {
            return compare_values(std::any_cast<std::string>(value), std::any_cast<std::string>(operand), sign);
        }
        else if (value.type() == typeid(const char*)) {
            return compare_values(std::any_cast<const char*>(value), std::any_cast<const char*>(operand), sign);
        }
        else if (value.type() == typeid(bool)) {
            return compare_values(std::any_cast<bool>(value), std::any_cast<bool>(operand), sign);
        }
        else {
            return false;
        }
    };
}


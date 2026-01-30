#include "calculator.h"
#include <iostream>
#include <string>
#include <cmath>
#include <limits>

void Calculator::Set(Number n){
    current_number = n;
}

Number Calculator::GetNumber() const{

    return current_number;
}

void Calculator::Add(Number n){
    current_number += n;
}

void Calculator::Sub(Number n){
    current_number -= n;
}
void Calculator::Div(Number n) {
    if (n == 0) {
        // устанавливаем infinity в зависимости от знака делителя.
        if (std::signbit(n)) {
            current_number = -std::numeric_limits<double>::infinity();
        } else {
            current_number = std::numeric_limits<double>::infinity();
        }
    } else {
        current_number /= n;
    }
}

void Calculator::Mul(Number n){
    current_number *= n;
}

void Calculator::Pow(Number n){
    current_number = pow(current_number, n);
}


void Calculator::Save()
{
    memory_number = current_number;
    flag = true;
}


void Calculator::Load()
{
    if (flag) {
        current_number = memory_number;
    }

}

// Проверяем, есть ли значение в памяти
bool Calculator::HasMem() const
{
    return flag;
}


std::string Calculator::GetNumberRepr() {
    return std::to_string(current_number);
}

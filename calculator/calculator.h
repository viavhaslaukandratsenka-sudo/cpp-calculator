#pragma once
#include <string>

using Number = double;

class Calculator {
public:
    Calculator() : current_number(0.0), memory_number(0.0), flag(false) {}

    void Set(Number n);                    // Заменяет текущее число на n
    Number GetNumber() const;              // Возвращает текущее число
    void Add(Number n);                    // current_number += n
    void Sub(Number n);                    // current_number -= n
    void Div(Number n);                    // current_number /= n
    void Mul(Number n);                    // current_number *= n
    void Pow(Number n);                    // current_number = pow(current_number, n)
    void Save();                           // Сохраняет current_number в память
    void Load();                           // Загружает память в current_number
    bool HasMem() const;                   // true, если память заполнена
    std::string GetNumberRepr();           // std::to_string(current_number)


private:

    Number current_number; // текущее число
    Number memory_number; // число в памяти
    bool flag = false;  // флаг заполненности памяти

};

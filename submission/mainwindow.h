#pragma once
#include "calculator.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE
enum class Operation {
    NO_OPERATION,   // ожидание ввода операции
    MULTIPLICATION, // умножение
    DIVISION,       // деление
    SUBTRACTION,    // вычитание
    ADDITION,       // сложение
    POWER,          // степень
};

class MainWindow : public QMainWindow {
    Q_OBJECT


public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void numbers_clicked(); // общий обработ для всех цифр

    void on_btn_point_clicked();

    void on_btn_clear_last_number_clicked();

    void on_btn_plus_minus_clicked();

    void on_btn_clear_clicked();

    void on_btn_pow_clicked();

    void on_btn_divide_clicked();

    void on_btn_multiply_clicked();

    void on_btn_minus_clicked();

    void on_btn_plus_clicked();

    void on_btn_equals_clicked();

    void on_btn_mStore_clicked();

    void on_btn_mRecall_clicked();

    void on_btn_mClear_clicked();

private:
    Ui::MainWindow* ui;

    Calculator calculator_;
    Number active_number_ = 0.0;           // храним текущее активное число в калькуляторе
    Operation current_operation_ = Operation::NO_OPERATION;  // никаких действий не выполняется
    void SetText(const QString& text);   // сохранит результат в input_number_ и поместит его в l_result.
    void AddText(const QString& suffix);// допишет к input_number_ нужный текст и вызовет SetText
    void SetOperation(Operation op);   // метод вызывается при нажатии всех кнопок операций (+, -, /, *, ^)
    void PerformOperation(double second_num);  // метод отвечает за выполнение действий (+, -, /, *, ^)
    QString input_number_;           // храним число как строку, которое вводит пользователь с помощью кнопок
    QString first_number_str_;      // храним строковую копию первого числа для l_formula
    QString second_number_str_;    // храним строковую копию второго числа для l_formula
    QString NormalizeNumber(const QString &text); // метод нармализует числа
    QString RemoveTrailingZeroes(const QString &text);  // метод удаляет все ненужные 0 из строки и делает числа корректными
    double first_number_ = 0.0;// числовое знач. первого числа (расчеты)
    double memory = 0.0;      // храним числа в памяти
    bool del = true;         // флаг блокировки удаления последних цифр после нажатия кнопки (=)
    bool in_memory = false; //  устанавливаем изначально флаг о том, что число не в памяти    !>
    bool new_input = true; // флаг ввода нового числа                                         !>
    bool isTypingNumber_ = false; // флаг который указывает начал ли user ввод чисел          !>
};

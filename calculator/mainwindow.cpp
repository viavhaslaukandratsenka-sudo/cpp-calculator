#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculator.h"
#include <cmath>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);                 // связываем все элементы из ui файла с окном
    ui->l_result->setText("0");       // устанавливаем нач. значение поля 0 в l_result
    ui->l_memory->setText("");       //  очищаем поле памяти, убираем (M)
    ui->l_formula->setText("");     //  очищаем поле в l_formula

    // указ на обьект       сигнал при нажат.  ук.на класс  метод в классе вызывается при нажатии на люб. кнопку
    connect(ui->btn_zero,   &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_one,    &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_two,    &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_three,  &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_four,   &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_five,   &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_six,    &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_seven,  &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_eight,  &QPushButton::clicked, this, &MainWindow::numbers_clicked);
    connect(ui->btn_nine,   &QPushButton::clicked, this, &MainWindow::numbers_clicked);

}

MainWindow::~MainWindow() {    // деструктор
    delete ui;                 // освобождаем память
}

QString OpToString(Operation op) {                      // метод корректно отображает математические операции в интерфейсе калькулятора!

    switch(op) {
    case Operation::NO_OPERATION: return "";          // если нет операции, возврат пустой строки
    case Operation::ADDITION: return "+";            // если операция +, возврат символ "+"
    case Operation::DIVISION: return "÷";           // если операция /, возврат символ "÷"
    case Operation::MULTIPLICATION: return "×";    // если операция *, возврат символ "×"
    case Operation::SUBTRACTION: return "−";      // если операция -, возврат символ "-"
    case Operation::POWER: return "^";           // если операция ^, возврат символ "^"

    }
    return "";                                 // защита от (undefined behavior)
}

void MainWindow::PerformOperation(double second_num) {       // метод отвечает исключительно за выполнение матем. операции!

    if (current_operation_ == Operation::NO_OPERATION) {   // если операция не выбрана, выходим из функции
        return;
    }

    double result = 0.0;                        // храним результ. вычислений

    switch (current_operation_) {
    case Operation::ADDITION:                // если выбрана операция (+)
        calculator_.Set(first_number_);     // устанавливаем первое число в calculator
        calculator_.Add(second_num);       //  добавляем второе слагаемое
        result = calculator_.GetNumber(); // находим сумму двух чисел и сохран. в переменную result
        break;
    case Operation::SUBTRACTION:             // если выбрана операция (-)
        calculator_.Set(first_number_);     // устанавливаем первое число в calculator
        calculator_.Sub(second_num);       //  добавляем вычитаемое
        result = calculator_.GetNumber(); // находим разность двух чисел и сохран. в переменную result
        break;
    case Operation::MULTIPLICATION:           // если выбрана операция (*)
        calculator_.Set(first_number_);      //  устанавливаем первое число в calculator
        calculator_.Mul(second_num);        //  добавляем второй множитель
        result = calculator_.GetNumber();  //   находим произведение чисел и сохран. в переменную result
        break;
    case Operation::DIVISION:                 // если выбрана операция (/)
        if (second_num == 0) {               // если делитель 0
            ui->l_result->setText("Error"); // выводим сообщение об ошибке
            current_operation_ = Operation::NO_OPERATION; // никаких действий не выполняется
            return;
        }                                    // иначе
        calculator_.Set(first_number_);     // устанавливаем первое число
        calculator_.Div(second_num);       // добавляем делитель
        result = calculator_.GetNumber(); // находим частное чисел и сохран. в переменную result
        break;
    case Operation::POWER:                    // если выбрана  операция (^)
        calculator_.Set(first_number_);      // устанавливаем первое число
        calculator_.Pow(second_num);        // возводим в степень
        result = calculator_.GetNumber();  // находим степень числа и сохраняем в переменную result
        break;
    default:
        return;
    }

    QString result_str = QString::number(result);       // преобразуем результат в строку
    QString normalized = NormalizeNumber(result_str);  // нормализуем строку

}

QString MainWindow::RemoveTrailingZeroes(const QString &text) {    // метод удаляет нули в начале строки!

    for (qsizetype i = 0; i < text.size(); ++i) {    // проходим по строке слева направо
        if (text[i] != '0') {                       // ищем первый символ, который не '0'.
            return text.mid(i);                    //возврат. подстроки
        }
    }                                            // иначе
    return "";                                  // возврат. пустой строки
}

QString MainWindow::NormalizeNumber(const QString &text) {     // метод нармализует числа!

    if (text.isEmpty()) {                                    // если строка пуста
        return "0";                                         // возвращаем 0
    }
    if (text.startsWith('.')) {                           // если ввод начинается с точки (.)

        return NormalizeNumber("0" + text);             // добавляем перед точкой "0" в строку l_result
    }
    if (text.startsWith('-')) {                       // если число начинается с (-)

        return "-" + NormalizeNumber(text.mid(1));  // нармализуем число без минуса и возврат. минус
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {    // если число нач с 0 и точки
        return NormalizeNumber(RemoveTrailingZeroes(text)); // убираем все ненужные нули
    }
    return text;                                          // если ни одно из условий не выполяется, возвращаем исходную строку

}

void MainWindow::numbers_clicked() {                    //  метод отвечает за обработку нажатий на цифровые кнопки калькулятора!

    QPushButton *btn = qobject_cast<QPushButton*>(sender()); // возвращаем указатель на объект(кнопку), которая отправила сигнал
    if (!btn) return;                                // если сигнал не от кнопки,ничего не делаем и выходим из метода

    QString digit = btn->text();                   // получаем цифру кноки

    if (new_input) {                             // если выбрано новое число
        input_number_.clear();                  // удаляем предыдущее число
        SetText("");                           // устанавливаем пустую строку
        new_input = false;                    // уставливае на знач. нового числа флаг !> false
    }
      AddText(digit);                       //  добавляем цифру

}

void MainWindow::SetOperation(Operation op) {      // метод обрабатывает выбор операции +, −, ×, ÷, ^ и подготавливает к вводу второе число!

    bool ok;
    double current = input_number_.toDouble(&ok);
    if (!ok) return;                                       // если преобразование числа не удалось, завершаем работу метода

    if (current_operation_ != Operation::NO_OPERATION) { // если уже была операция и пользователь ввел новое число после первого, посчитаем
        if(input_number_ != first_number_str_) {        // если тек. число не равно первому
            PerformOperation(current);                 // выполняем предыдущее вычисление
        }
    } else {

        first_number_ = current;                   // фиксируем первое число при выборе операции
        first_number_str_ = input_number_;        // сохраняем строку представляющую число
    }

    ui->l_formula->setText(first_number_str_ + " " + OpToString(op));   // показываем формулу: первое число + операция
    current_operation_ = op;                                           // сохраняем тек. знак операции
    new_input = true;                                                 // уставливае на знач. нового числа флаг !> true
    calculator_.Set(0.0);                                            // обнуляем колькулятор
    second_number_str_ = input_number_;                             // сохран. строку
    ui->l_result->setText(second_number_str_);                     // обнавляем текст в l_result

}

void MainWindow::AddText(const QString& suffix) {          // метод отвечает за корректный ввод символа и точки в строку input_number!

    if (suffix == "." && input_number_.contains('.')) {  // если user нажал на кнопку (.) и точка уже есть в l_result
        return;                                         // ничего не возврат
    }

    if (input_number_ == "0" && suffix != ".") {    // Если сейчас "0" при этом добавляем не точку
        SetText(suffix);                           // заменяем 0 на новую цифру
    } else {

        SetText(input_number_ + suffix);        // во всех остальных случаях просто дописываем символ
    }

}


void MainWindow::SetText(const QString& text) {    // метод сохраняет и отображает результат в элементе интерфейса l_result

    input_number_ = NormalizeNumber(text);       // применяем нормализацию числа
    ui->l_result->setText(input_number_);       // обновляем текст в l_result
    active_number_ = input_number_.toDouble(); // обновляем active_number_

}


void MainWindow::on_btn_clear_last_number_clicked() {    // удаление последней цифры

    if(!del) {                         // если не true, блокируем удаление последней цифры
        return;
    }
    if(!input_number_.isEmpty()) {  // если строка не пустая
        input_number_.chop(1);     // удаляем последнюю цифру
        SetText(input_number_);   // обновляем l_result
    }


}

void MainWindow::on_btn_point_clicked() {  // метод кнопки точки (.)

    if (input_number_.contains('.')) {   // если уже есть точка в текущем тексте
        return;                         // то ничего не делаем
    }

    if(current_operation_ != Operation::NO_OPERATION && input_number_ == first_number_str_) {  // если user выбрал операцию и не ввел число
        input_number_ = "";          // очищаем строку ввода
        SetText("");                // и начинаем ввод второго нового числа

    }
    AddText(".");                // добавляем точку (.)
}

void MainWindow::on_btn_plus_minus_clicked() {        // метод кнопки плюс-минус (+,-)

    if (!std::isfinite(active_number_)) {           // если nan и inf, кнопка (+ -) ничего не далает
        return;
    }

    if (input_number_.startsWith('-')) {        // если число изначально с минусом
        input_number_ = input_number_.mid(1);  // убираем  минус
    } else {
        input_number_ = "-" + input_number_; // иначе если изначально без минуса, добавляем минус к числу
    }

    SetText(input_number_);               // синхронизируем строку, экран и числовое значение

}

void MainWindow::on_btn_clear_clicked() {           // метод кнопки удаления (С)

    current_operation_ = Operation::NO_OPERATION; // никаких действий не выполняется
    ui->l_formula->setText("");                  // очищаем строку l_formula
    SetText("0");                               // очищаем и устанавливаем начальное значение 0 в l_result
    del = true;  // устанавливаем знач. флага true которое позволит после удаления открыть доступ к кнопке btn_clear_last_number_

}


void MainWindow::on_btn_pow_clicked() {               // (^)

    SetOperation(Operation::POWER);


}


void MainWindow::on_btn_divide_clicked() {            // (/)

    SetOperation(Operation::DIVISION);

}


void MainWindow::on_btn_multiply_clicked() {          // (*)

    SetOperation(Operation::MULTIPLICATION);


}


void MainWindow::on_btn_minus_clicked() {             // (-)

    SetOperation(Operation::SUBTRACTION);


}


void MainWindow::on_btn_plus_clicked() {              // (+)

    SetOperation(Operation::ADDITION);

}


void MainWindow::on_btn_equals_clicked() {                 //  метод кнопки равно (=)

    if (current_operation_ == Operation::NO_OPERATION) { // если нет операции

        SetText(QString::number(active_number_));      // преобразуем число в строку и обнавляем l_result
        del = false;                                  // запрет удаления цифр после нажатия на кнопку
        return;
    }

    double second_number;                          // создаем локал. переменую которая хранит второе число

    if (input_number_.isEmpty()) {                     // если user не ввел второе число
        second_number = active_number_;               // используем текущее отображаемое число
    } else {
        second_number = input_number_.toDouble();   // иначе, преобразуем число в строку и сохран. в переменную
    }

    ui->l_formula->setText(first_number_str_ + " " + OpToString(current_operation_) + " " + input_number_ + " ="); // показываем в l_formula

    PerformOperation(second_number);                                   // выполняем вычисление

    double result = calculator_.GetNumber();                         // получаем результат из calculator

    QString result_str = NormalizeNumber(QString::number(result)); // преобразуем result в строку

    SetText(result_str);                                         // выводим результат

    // Готовим калькулятор к следующей операции
    first_number_ = result;                                   // числовое знач
    first_number_str_ = result_str;                          // строковое представление
    current_operation_ = Operation::NO_OPERATION;           // сбрасываем тек. операцию чтобы следующее нажатие на кнопку = ничего не выполняло

    del = false;                                          // при нажатии на (=) меняем знач. флага и блокируем кнопку удаления послед. цифры
    new_input = true;                                    // указываем, что начался новый ввод

}

void MainWindow::on_btn_mStore_clicked() {       // метод сохраненяет текущее число в память!

    if (!std::isfinite(active_number_))
        return;

    memory = active_number_;                  // помещаем тек. число в память
    in_memory = true;                        // устанавливам знач true, которое указывает, что в памяти есть знач
    ui->l_memory->setText("M");             // выводим букву M и указваем user, что число сохранено
    new_input = true;                      // указываем, что начался новый ввод

}

void MainWindow::on_btn_mRecall_clicked() {    // метод выводит в l_result сохраненное число из памяти MS!

    if (!in_memory)                                                 // если в памяти ничего нет
        return;                                                    // ничего не делаем

    QString mem_str = NormalizeNumber(QString::number(memory));  // преобразуем число из памяти в строку


    if (current_operation_ != Operation::NO_OPERATION) {      // если операция уже выбрана
        input_number_ = mem_str;                             // делаем число из памяти как текущ. вводимое число
        ui->l_result->setText(mem_str);                     // позываем его в строке l_result
        active_number_ = memory;                           //  помещаем сохран значение в active_number
        return;
    }


    SetText(mem_str);                                  // выводим в l_result и обновляем input_number_ + active_number_
    first_number_ = active_number_;                   // обновляем первое число
    first_number_str_ = mem_str;                     // число из памяти делаем  новым первым числом
    new_input = true;                               // указываем, что начался новый ввод
}

void MainWindow::on_btn_mClear_clicked() {      // метод очищает память!

    memory = 0.0;                // очищаем память
    in_memory = false;          // значение флага false
    ui->l_memory->setText(""); // убираем заглавную букву M из l_memory

}


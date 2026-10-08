#include <iostream>
#include <windows.h>

// Глобальные константы ограничений
const double MIN_VAL = -10000.0;
const double MAX_VAL = 10000.0;

bool isValid(double val) {
    bool result = false;
    if (val >= MIN_VAL && val <= MAX_VAL) {
        result = true;
    }
    return result;
}


class RealNumber {
private:
    double value;

public:
    RealNumber(double val = 0.0) {
        if (isValid(val)) {
            value = val;
        }
        else {
            value = 0.0;
            std::cout << "[Ошибка] Значение выходит за пределы [-10000, 10000]! Установлен 0.\n";
        }
    }

    // Оператор ++ как функция-член
    RealNumber& operator++() { // Префиксный ++
        if (isValid(this->value + 1.0)) {
            this->value += 1.0;
        }
        else {
            std::cout << "[Предупреждение] Достигнут верхний предел (10000)!\n";
        }
        return *this;
    }

    RealNumber operator++(int) { // Постфиксный ++
        RealNumber temp = *this;
        if (isValid(this->value + 1.0)) {
            this->value += 1.0;
        }
        else {
            std::cout << "[Предупреждение] Достигнут верхний предел (10000)!\n";
        }
        return temp;
    }

    // Объявление дружественных операторов --
    friend RealNumber& operator--(RealNumber& obj);
    friend RealNumber operator--(RealNumber& obj, int);

    double getValue() const {
        return value;
    }

    void setValue(double val) {
        if (isValid(val)) {
            value = val;
        }
        else {
            std::cout << "[Ошибка] Значение должно быть в диапазоне от -10000 до 10000!\n";
        }
    }

    void print() const {
        std::cout << value;
    }
};

// Оператор -- как дружественная функция
RealNumber& operator--(RealNumber& obj) { // Префиксный --
    if (isValid(obj.value - 1.0)) {
        obj.value -= 1.0;
    }
    else {
        std::cout << "[Предупреждение] Достигнут нижний предел (-10000)!\n";
    }
    return obj;
}

RealNumber operator--(RealNumber& obj, int) { // Постфиксный --
    RealNumber temp = obj;
    if (isValid(obj.value - 1.0)) {
        obj.value -= 1.0;
    }
    else {
        std::cout << "[Предупреждение] Достигнут нижний предел (-10000)!\n";
    }
    return temp;
}


class IntNumber {
private:
    int value;

public:
    IntNumber(int val = 0) {
        if (isValid(val)) {
            value = val;
        }
        else {
            value = 0;
            std::cout << "[Ошибка] Значение выходит за пределы [-10000, 10000]! Установлен 0.\n";
        }
    }

    // Оператор + как функция-член
    IntNumber operator+(const IntNumber& other) const {
        int resVal = this->value + other.value;
        if (!isValid(resVal)) {
            std::cout << "[Предупреждение] Результат сложения вышел за пределы [-10000, 10000]!\n";
        }
        IntNumber result(isValid(resVal) ? resVal : this->value);
        return result;
    }

    IntNumber operator+(int other) const {
        int resVal = this->value + other;
        if (!isValid(resVal)) {
            std::cout << "[Предупреждение] Результат сложения вышел за пределы [-10000, 10000]!\n";
        }
        IntNumber result(isValid(resVal) ? resVal : this->value);
        return result;
    }

    // Объявление дружественных операторов -
    friend IntNumber operator-(const IntNumber& left, const IntNumber& right);
    friend IntNumber operator-(const IntNumber& left, int right);

    int getValue() const {
        return value;
    }

    void setValue(int val) {
        if (isValid(val)) {
            value = val;
        }
        else {
            std::cout << "[Ошибка] Значение должно быть в диапазоне от -10000 до 10000!\n";
        }
    }

    void print() const {
        std::cout << value;
    }
};

// Оператор - как дружественная функция
IntNumber operator-(const IntNumber& left, const IntNumber& right) {
    int resVal = left.value - right.value;
    if (!isValid(resVal)) {
        std::cout << "[Предупреждение] Результат вычитания вышел за пределы [-10000, 10000]!\n";
    }
    IntNumber result(isValid(resVal) ? resVal : left.value);
    return result;
}

IntNumber operator-(const IntNumber& left, int right) {
    int resVal = left.value - right;
    if (!isValid(resVal)) {
        std::cout << "[Предупреждение] Результат вычитания вышел за пределы [-10000, 10000]!\n";
    }
    IntNumber result(isValid(resVal) ? resVal : left.value);
    return result;
}


void printMenu() {
    std::cout << "\n================ MENU ================\n";
    std::cout << "1. [RealNumber] Ввести новое значение double [-10000, 10000]\n";
    std::cout << "2. [RealNumber] Выполнить ++r (префиксный ++, член класса)\n";
    std::cout << "3. [RealNumber] Выполнить r++ (постфиксный ++, член класса)\n";
    std::cout << "4. [RealNumber] Выполнить --r (префиксный --, friend)\n";
    std::cout << "5. [RealNumber] Выполнить r-- (постфиксный r--, friend)\n";
    std::cout << "--------------------------------------\n";
    std::cout << "6. [IntNumber]  Ввести новые значения i1 и i2 [-10000, 10000]\n";
    std::cout << "7. [IntNumber]  Выполнить i1 + i2 (оператор +, член класса)\n";
    std::cout << "8. [IntNumber]  Выполнить i1 - i2 (оператор -, friend)\n";
    std::cout << "--------------------------------------\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите пункт: ";
}


int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int exitCode = 0;
    int choice = -1;

    RealNumber realObj(5.5);
    IntNumber intObj1(10);
    IntNumber intObj2(4);

    while (choice != 0) {
        std::cout << "\n--------------------------------------";
        std::cout << "\nТекущие данные:";
        std::cout << "\nRealNumber r = "; realObj.print();
        std::cout << "\nIntNumber i1 = "; intObj1.print();
        std::cout << ", i2 = "; intObj2.print();
        std::cout << "\n--------------------------------------\n";

        printMenu();
        std::cin >> choice;

        if (choice == 1) {
            double val = 0.0;
            std::cout << "Введите новое вещественное число (-10000..10000): ";
            std::cin >> val;
            realObj.setValue(val);
        }
        else if (choice == 2) {
            RealNumber res = ++realObj;
            std::cout << "Результат ++r: "; realObj.print();
            std::cout << " (возвращенное значение: "; res.print(); std::cout << ")\n";
        }
        else if (choice == 3) {
            RealNumber res = realObj++;
            std::cout << "Результат r++: "; realObj.print();
            std::cout << " (возвращенное значение: "; res.print(); std::cout << ")\n";
        }
        else if (choice == 4) {
            RealNumber res = --realObj;
            std::cout << "Результат --r: "; realObj.print();
            std::cout << " (возвращенное значение: "; res.print(); std::cout << ")\n";
        }
        else if (choice == 5) {
            RealNumber res = realObj--;
            std::cout << "Результат r--: "; realObj.print();
            std::cout << " (возвращенное значение: "; res.print(); std::cout << ")\n";
        }
        else if (choice == 6) {
            int v1 = 0, v2 = 0;
            std::cout << "Введите значение i1 (-10000..10000): ";
            std::cin >> v1;
            std::cout << "Введите значение i2 (-10000..10000): ";
            std::cin >> v2;
            intObj1.setValue(v1);
            intObj2.setValue(v2);
        }
        else if (choice == 7) {
            IntNumber sum = intObj1 + intObj2;
            std::cout << "i1 + i2 = "; sum.print(); std::cout << "\n";
        }
        else if (choice == 8) {
            IntNumber diff = intObj1 - intObj2;
            std::cout << "i1 - i2 = "; diff.print(); std::cout << "\n";
        }
        else if (choice == 0) {
            std::cout << "Завершение работы программы...\n";
        }
        else {
            std::cout << "Некорректный ввод, попробуйте снова.\n";
        }
    }

    return exitCode;
}
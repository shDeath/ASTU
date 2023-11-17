/*
Ахмедов Шамиль ДИНРБ-21/2
Вариант № 2
Реализовать класс Bill, представляющий собой разовый платеж за телефонный разговор.
Класс должен включать поля: фамилия плательщика, номер телефона, тариф за минуту разговора, скидка (в процентах),
время начала разговора, время окончания разговора, сумма к оплате. Время задается в часах и минутах от начала суток.
Реализовать методы, вычисление продолжительности разговора, вычисление суммы скидки, вычисление суммы к оплате с учетом скидки.
Реализовать методы сравнения по тарифу. Время разговора, подлежащее оплате, вычисляется в минутах. 
*/
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip> // Добавляем для setprecision
#include <sstream> // Добавляем для ostringstream
#include <cassert>

#pragma pack(1)

using namespace std;

class Bill {
    string lastName;
    int64_t phoneNumber;
    double tariff;
    double discount;
    int startTime;
    int endTime;

    string errors[4]
    {
        "Некорректные данные!",
        "Тариф не может быть меньше 0",
        "Скидка должна быть в диапазоне от 0 до 100!",
        "Время не может быть меньше 0"
    };
public:
    // Конструктор с параметрами
    Bill(const string& lastName, int64_t phoneNumber, double tariff, double discount, int startTime, int endTime)
        : lastName(lastName), phoneNumber(phoneNumber), tariff(tariff), discount(discount), startTime(startTime), endTime(endTime) {
        if (tariff < 0 || discount < 0 || discount > 100 || startTime < 0) {// проверка на корректность
            throw invalid_argument(errors[0]);
        }
    }
    //Getters
    string GetLastName() const noexcept {
        return lastName;
    }
    int64_t GetPhoneNumber() const noexcept {
        return phoneNumber;
    }
    double GetTariff() const noexcept {
        return tariff;
    }
    double GetDiscount() const noexcept {
        return discount;
    }
    int GetStartTime() const noexcept {
        return startTime;
    }
    int GetEndTime() const noexcept {
        return endTime;
    }

    //Setters
    void SetLastName(const string& newlastName) noexcept {
        lastName = newlastName;
    }
    void SetPhoneNumber( int newphoneNumber) noexcept {
        phoneNumber = newphoneNumber;
    }
    void SetTariff(const double newtariff) {
        tariff = newtariff;
    }
    void SetDiscount(double newDiscount) {
        discount = newDiscount;
    }
    void SetStartTime(int newStartTime) {
        startTime = newStartTime;
    }
    void SetEndTime(int newEndTime) {
        endTime = newEndTime;
    }

    // Вычисление времени
    int getTime() const {
        if ((endTime - startTime) < 0) {
            throw invalid_argument(errors[3]);
        }
        return endTime - startTime;
    }
    //Вычесление суммы скидки
    double CalculateDisc() const {
        double discSum = getTime() * tariff * discount / 100;
        return discSum;
    }
    //Цена без скидки
    double CalculateCost() const {
        double cost = getTime() * tariff;
        return cost;
    }

    //Вычисление общей суммы
    double CalculateTotalAmount() const {
        double totalAmount = getTime() * tariff - CalculateDisc();
        return totalAmount;
    }
    // Метод сравнения товаров по цене
    bool operator<(const Bill& other) const noexcept {
        return tariff < other.tariff;
    }

    bool operator>(const Bill& other) const noexcept {
        return tariff > other.tariff;
    }

    bool operator==(const Bill& other) const noexcept {
        return tariff == other.tariff;
    }
    // Метод преобразования в строку

    string toString() const  {
        ostringstream result;
        result << lastName << "\n";
        result << phoneNumber << "\n";
        // Устанавливаем желаемое количество знаков после запятой (2)
        result << fixed << setprecision(2) << tariff << " р.\n";
        result << fixed << setprecision(2) << discount << " %\n";
        result << getTime() << " мин.\n";
        return result.str();
    }
    void Read() noexcept;
    void DisplayCost() noexcept;
    void Display() noexcept;
};

//Ввод
void Bill::Read() noexcept {
    string lastName;
    int64_t phoneNumber;
    double tariff;
    double discount;
    int startTime;
    int endTime;
    cout << "Введите Фамилию плательщика: ";
    cin >> lastName;
    cout << "Введите Номер телефона: ";
    cin >> phoneNumber;
    cout << "Введите Тариф за минуту разговора: ";
    cin >> tariff;
    cout << "Введите скидку товара: ";
    cin >> discount;
    cout << "Введите Время начала разговора: ";
    cin >> startTime;
    cout << "Введите Время окончания разговора: ";
    cin >> endTime;
}

void Bill::DisplayCost() noexcept {
    cout << toString();
    cout << endl;
    cout << GetLastName() << endl;
    cout << "Стоимость разговора без скидки: " << CalculateCost() << " р." << endl;
    cout << "Скидка составила: " << CalculateDisc() << " р." << endl;
    cout << "Стоимость разговора со скидкой: " << CalculateTotalAmount() << " р." << endl;
}

//Вывод
void Bill::Display()  noexcept {
    cout << endl;
    DisplayCost();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Ахмедов Шамиль ДИНРБ-21/2" << endl;
    cout << "Вариант 2" << endl;
    cout << "____________________________" << endl;
    try {
        // Создаем второй объект с помощью конструктора с параметрами
        Bill person1("Иванов", 89647896541, 1.5, 5, 2, 5);
        person1.Display(); // Используем метод Display

        // Проверка с использованием assert
        assert(person1.GetLastName() == "Иванов");
        assert(person1.GetPhoneNumber() == 89647896541);
        assert(person1.GetTariff() == 1.5);
        assert(person1.GetDiscount() == 5.0);
        assert(person1.GetStartTime() == 2);
        assert(person1.GetEndTime() == 5);

        // Проверка методов вычисления стоимости и скидки:
        // Проверка метода getTime
        assert(person1.getTime() == 3);
        // Проверка метода CalculateDisc
        assert(person1.CalculateDisc() == 0.225);
        // Проверка метода CalculateCost
        assert(person1.CalculateCost() == 4.5);
        // Проверка метода CalculateCostWithDiscount
        assert(person1.CalculateTotalAmount() == 4.275);

        // Создаем второй объект
        Bill person2("Ахмедов", 89667422119, 1.2, 15.73, 0, 5);
        person2.Read();
        person2.Display(); // Используем метод Display
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    return 0;
}

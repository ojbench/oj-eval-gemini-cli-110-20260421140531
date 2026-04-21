#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int get_month_days(int year, int month) {
    if (month == 2 && is_leap(year)) return 29;
    return month_days[month];
}

class Date {
private:
    int _year;
    int _month;
    int _day;

    bool is_valid(int y, int m, int d) {
        if (y < 1) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > get_month_days(y, m)) return false;
        return true;
    }

    void normalize() {
        while (_day > get_month_days(_year, _month)) {
            _day -= get_month_days(_year, _month);
            _month++;
            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
        while (_day <= 0) {
            _month--;
            if (_month <= 0) {
                _month = 12;
                _year--;
            }
            _day += get_month_days(_year, _month);
        }
    }

    long long to_days() const {
        long long days = 0;
        for (int y = 1; y < _year; ++y) {
            days += is_leap(y) ? 366 : 365;
        }
        for (int m = 1; m < _month; ++m) {
            days += get_month_days(_year, m);
        }
        days += _day;
        return days;
    }

public:
    Date() : _year(1900), _month(1), _day(1) {}
    Date(int yy, int mm, int dd) {
        if (is_valid(yy, mm, dd)) {
            _year = yy;
            _month = mm;
            _day = dd;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }

    Date& operator++() {
        _day++;
        normalize();
        return *this;
    }

    Date operator++(int) {
        Date tmp = *this;
        ++(*this);
        return tmp;
    }

    Date& operator--() {
        _day--;
        normalize();
        return *this;
    }

    Date operator--(int) {
        Date tmp = *this;
        --(*this);
        return tmp;
    }

    Date operator+(int days) const {
        Date res = *this;
        res._day += days;
        res.normalize();
        return res;
    }

    Date operator-(int days) const {
        Date res = *this;
        res._day -= days;
        res.normalize();
        return res;
    }

    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }

    long long operator-(const Date& other) const {
        long long d1 = this->to_days();
        long long d2 = other.to_days();
        return d1 > d2 ? d1 - d2 : d2 - d1;
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << "-" << d._month << "-" << d._day;
        return os;
    }

    void out() const {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

void Test() {
    int op;
    if (!(cin >> op)) return;
    int yy, mm, dd;
    if (op == 1 || op == 0) {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
    }
    if (op == 2 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i = 0; i < 5; ++i) cout << ++d0 << endl;
        for (int i = 0; i < 5; ++i) cout << d0++ << endl;
        for (int i = 0; i < 5; ++i) cout << d0-- << endl;
        for (int i = 0; i < 2; ++i) cout << --d0 << endl;
        cout << d0 << endl;
    }
    if (op == 3 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        cout << d0 - 1000 << endl;
    }
    if (op == 4 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main() {
    Test();
    return 0;
}


#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

#define pass (void)0
using namespace std;

// Создать класс, описывающий целое число и определяющий делители этого числа.
// Определить количество нечетных цифр в числе. Создать класснаследник, хранящий количество делителей числа.
// Для данного двумерного массива найти номер того измерения (строки или столбца), в котором больше всего элементов, являющихся простыми числами.
bool proverca(char *mass, int kol) {
    for (int i = 0; i < kol; i++) {
        if (isdigit(mass[i]))
            void(0);
        else
            return false;
    }
    return true;
}

int perevod(char *mass, int kol) {
    long int massiv = 0;
    for (int i = kol; i >0; i--) {
        int perem = mass[kol - i] - 48;
        long int step = pow(10, i-1);
        long int gjdkf = perem * step;
        massiv += gjdkf;
    }
    return (massiv);
}

long int vvod() {
    
    char mass[999];
    int i = 0;
    cout << "начните ввод" << endl;
    while (1) {
        mass[i] = getchar();
        if (mass[i] == '\n') {
            break;
        }
        i++;
    }
    if (proverca(mass, i)) {
        long int zapas = perevod(mass, i);
        return zapas;
    } else {
        cout << "Неверный ввод" << endl;
        int zapas = -1;
        return zapas;
    }
}

class Chislo {
    vector<unsigned> dividers() {
        unsigned n = chisl;
        vector<unsigned> divs(1, n);
        if (n == 1)
            return divs;
        for (unsigned d = n / 2; d >1; --d)
            // обратный порядок и так как минимальное частное - 2 значит можно нет смысла проверять числа большие n/2
            if (n % d == 0)
                divs.push_back(d);
        divs.push_back(1);
        return divs;
    }
    vector<unsigned> divs = dividers();
    long int chisl;
protected:
    int nechet(int chislo) {
        int n = chislo, kolvo = 0, counter = 0;
        cin >> n;
        int number;
        //int *arr = new int[n];
        while (n) {
            number = n % 10;
            n /= 10;
            if (number % 2 == 0)
                kolvo++;
            //counter++;
        }
        //for (int i = counter - 1; i >= 0; i--) {
        //    cout << arr[i] << ' ';
        //}
        //delete[] arr;
        return kolvo;
    }
public:
    Chislo(long int input) {
        chisl = input;
    }

    void print_deliteli() {
        if (divs.empty()) {
            std::cout << "You enter 0" << std::endl;
        } else if (divs.size() == 2) {
            std::cout << "Number is prime" << chisl << std::endl;
        } else {
            cout << "Dividers: ";
            for (unsigned int div: divs)
                cout << div << "; ";
            cout << endl;
        }
    }

    void print_nechet() {
        int print = nechet(chisl);
        cout << "Количество нечётных цифр" << print << endl;
    }
};

//class Chisla : private Chislo { //ихменить чтоб на вход массив был и через него создавать матрицу
//
//public:
//
//};

void printoptions() {
    cout << "Ввести элемент\t1" << endl;
    cout << "Вывести делители числа\t2" << endl;
    cout << "Вывести количество нечётных цифр\t3" << endl;
    cout << "Вывести строку/столбец в котором больше всего элементов, являющихся простыми числами\t4" << endl;
    cout << "Выход и удаление\t5" << endl;
    //cout << "Добавить перезапись последнего введённого элемента\t6" << endl;//пока не реализованно нигде
    //cout << "Показ всех введённых элементов\t6" << endl;//пока не реализованно нигде
    //cout << "Показ выбранного введённого элемента\t6" << endl;//пока не реализованно нигде
    //cout << "Добавить перезапись выбранного введённого элемента\t6" << endl;//пока не реализованно нигде
}

bool options(int input, Chislo *ptr) {

    int flag = input;
    if (flag == 1) {
        long int uk;
        while (true) {
            uk = vvod();
            if (uk != -1) {
                break;
            } else
                cout << "Введите заново" << endl;
        }
        Chislo pr1(uk);
        *ptr = &pr1;//как-то изменить видимо чтоб функц возвращает
        return true;
    } else if (flag == 2) {
        //проверка на существование представителя родителя
        if (ptr){
            ptr->print_deliteli();
        }
        else{
            cout << "Создайте элемент" << endl;
        }
        return true;
    } else if (flag == 3) {
        if (ptr){
            ptr->print_nechet();
        }
        else{
            cout << "Создайте элемент" << endl;
        }
        return true;
    } else if (flag == 4) {
        //Работа с наследником
        pass;
        return true;
    } else if (flag == 5) {
        return false;
    } else {
        cout << "Неверный ввод пункта - Введите номер пункта заново";
        return true;
    }
}

void menu() {
    int input;
    bool flag = true;
    printoptions();
    Chislo *predstav = nullptr;
    while (flag) {
        cout << "Введите номер пункта" << endl;
        cin >> input;
        flag = options(input, predstav);
    }
}

int main() {
    menu();
    cout << "Конец проги" << endl;
    return 0;
}

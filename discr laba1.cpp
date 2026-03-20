#include <iostream>
#include <windows.h>

using namespace std;

int LEFT_BORDER_CHAR = '!';   // 33
int LEFT_BORDER_SET = 'A';    // 65
int RIGHT_BORDER_SET = 'Z';   // 90
int RIGHT_BORDER_CHAR = '~';  // 126

class Elem {
public:
    Elem* pointer = nullptr;
    char value;
};

auto addElementInSet(Elem& _E, const char& _ch) {
    Elem* _tracker = &_E;
    while (_tracker != nullptr) {
        Elem* next = _tracker->pointer;
        // add element if it last or next will be > than it
        if (next == nullptr || next->value > int(_ch)) {
            Elem* EL = new Elem();
            EL->value = _ch;
            EL->pointer = next;
            _tracker->pointer = EL;
            break;
        }
        else {
            _tracker = next;
        }
    }
}

auto removeElementFromSet(Elem& _E, const char& _ch) {
    Elem* _tracker = &_E;
    Elem* next = _tracker->pointer;
    while(next != nullptr) {
        if (next->value > _ch) {
            cout << "Символа \"" << _ch << "\" нет в массиве " << _E.value << endl;
            break;
        }
        if (next->value == _ch) {
            _tracker->pointer = next->pointer;
            delete next;
            break;
        }
        else if (next->pointer == nullptr) {
            cout << "Символа \"" << _ch << "\" нет в массиве " << _E.value << endl;
        }
        _tracker = next;
        next = _tracker->pointer;
    }
}

auto showSet(Elem& _E) {
    Elem* _tracker = &_E;
    while (_tracker != nullptr) {
        cout << _tracker->value << " ";
        _tracker = _tracker->pointer;
    }
    cout << endl;
}

auto cleanMemory(Elem& _E) {
    Elem* cleaner = &_E;
    while (cleaner != nullptr) {
        Elem* next = cleaner->pointer;
        /*cout << "clean " << cleaner->value << endl;*/
        delete cleaner;
        cleaner = next;
    }
}

auto checkEqual(Elem& _A, Elem& _B) {
    Elem* tracker_A = &_A;
    Elem* tracker_B = &_B;
    if (tracker_A->pointer == nullptr && tracker_B->pointer == nullptr) {
        return true;
    }
    if (tracker_A->pointer == nullptr || tracker_B->pointer == nullptr) {
        return false;
    }
    tracker_A = tracker_A->pointer;
    tracker_B = tracker_B->pointer;
    while (tracker_A->value == tracker_B->value) {
        if (tracker_A->pointer == nullptr && tracker_B->pointer == nullptr) {
            return true;
        }
        if (tracker_A->pointer == nullptr || tracker_B->pointer == nullptr) {
            return false;
        }
        tracker_A = tracker_A->pointer;
        tracker_B = tracker_B->pointer;
    }
    return false;
}

auto setSum(Elem& _A, Elem& _B) {
    Elem* tracker_A = (&_A)->pointer;
    Elem* tracker_B = (&_B)->pointer;
    while(tracker_A != nullptr && tracker_B != nullptr) {
        if (tracker_A->value < tracker_B->value) {
            cout << tracker_A->value << " ";
            tracker_A = tracker_A->pointer;
        }
        else if (tracker_A->value > tracker_B->value) {
            cout << tracker_B->value << " ";
            tracker_B = tracker_B->pointer;
        }
        else {
            cout << tracker_A->value << " ";
            tracker_A = tracker_A->pointer;
            tracker_B = tracker_B->pointer;
        }
    }
    while (tracker_A != nullptr) {
        cout << tracker_A->value << " ";
        tracker_A = tracker_A->pointer;
    }
    while (tracker_B != nullptr) {
        cout << tracker_B->value << " ";
        tracker_B = tracker_B->pointer;
    }
    cout << endl;
}

auto setMultiplication(Elem& _A, Elem& _B) {
    Elem* tracker_A = (&_A)->pointer;
    Elem* tracker_B = (&_B)->pointer;
    while(tracker_A != nullptr && tracker_B != nullptr) {
        if (tracker_A->value == tracker_B->value) {
            cout << tracker_A->value << " ";
            tracker_A = tracker_A->pointer;
            tracker_B = tracker_B->pointer;
        }
        else if (tracker_A->value < tracker_B->value) {
            tracker_A = tracker_A->pointer;
        }
        else {
            tracker_B = tracker_B->pointer;
        }
    }
    cout << endl;
}

auto potencial(Elem& _A, Elem& _B) {
    Elem* tracker_A = (&_A)->pointer;
    Elem* tracker_B = (&_B)->pointer;
    while (tracker_A != nullptr) {
        if (tracker_B != nullptr) {
            if (tracker_A->value > tracker_B->value) {
                tracker_B = tracker_B->pointer;
                continue;
            }
            else if (tracker_A->value == tracker_B->value) {
                tracker_A = tracker_A->pointer;
                continue;
            }
            else if (tracker_A->value < tracker_B->value) {
                cout << tracker_A->value << " ";
                tracker_A = tracker_A->pointer;
            }
        }
        else {
            cout << tracker_A->value << " ";
            tracker_A = tracker_A->pointer;
        }
    }
    cout << endl;
}

auto checkSubset(Elem& _A, Elem& _B) {
    Elem* tracker_A = (&_A)->pointer;
    Elem* tracker_B = (&_B)->pointer;
    if (tracker_B == nullptr) {
        if (tracker_A == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }
    while (tracker_A != nullptr) {
        if (tracker_B == nullptr) {
            return false;
        }
        if (tracker_A->value == tracker_B->value) {
            tracker_A = tracker_A->pointer;
            continue;
        }
        if (tracker_A->value > tracker_B->value) {
            tracker_B = tracker_B->pointer;
            continue;
        }
        if (tracker_A->value < tracker_B->value) {
            return false;
        }
    }
    return true;
}

auto calcSetLen(Elem& _EL) {
    Elem* tracker = _EL.pointer;
    size_t setlen = 0;
    while (tracker != nullptr) {
        setlen += 1;
        tracker = tracker->pointer;
    }
    return setlen;
}

auto powww(int _f, int _s) {
    int i = 1;
    int res = _f;
    while (i != _s) {
        res *= _f;
        i++;
    }
    return res;
}

auto toBinary(int _P, size_t setlen) {
    int* arr = new int[setlen]();
    int num = _P;
    int i = 0;
    while(num != 0) {
        arr[i] = num % 2;
        if (arr[i] == 1) {
            num -= 1;
            num /= 2;
        }
        else if (arr[i] == 0) {
            num /= 2;
        }
        i++;
    }
    i = 0;
    while (i < setlen / 2) {
        int swap = arr[i];
        arr[i] = arr[setlen - 1 - i];
        arr[setlen - 1 - i] = swap;
        i++;
    }
    return arr;
}

auto showBoolean(Elem& _EL) {
    Elem* tracker = _EL.pointer;
    size_t setlen = calcSetLen(_EL);
    int currentDuration = 0;
    int maxNum_andOne = powww(2, int(setlen));
    while (currentDuration != maxNum_andOne) {
        int* binaryNum = toBinary(currentDuration, setlen);
        size_t i = 0;
        while (i < setlen) {
            if (binaryNum[i] == 1) {
                cout << tracker->value << " ";
                tracker = tracker->pointer;
            }
            else if (binaryNum[i] == 0) {
                tracker = tracker->pointer;
            }
            i++;
        }
        delete[] binaryNum;
        cout << endl;
        tracker = _EL.pointer;
        currentDuration++;
    }
}

auto takeUserSet() {
    cout << "Введите название множества (A-Z): ";
    char userSet;
    cin >> userSet;
    cin.clear();
    if (int(userSet) < LEFT_BORDER_SET || int(userSet) > RIGHT_BORDER_SET) {
        cout << "Недопустимое имя множества" << endl;
        return char(0);
    }
    return userSet;
}

auto takeUserChar() {
    cout << "Введите значение: ";
    char userChar;
    cin >> userChar;
    cin.clear();
    if (LEFT_BORDER_CHAR <= (int)userChar && (int)userChar <= RIGHT_BORDER_CHAR) {
        if (userChar < LEFT_BORDER_SET || RIGHT_BORDER_SET < userChar) {
            return userChar;
        }
    }
    cout << "Недопустимый символ" << endl;
    return char(' ');
}

auto cleans(char& _1, int& _2) {
    delete &_1;
    delete &_2;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Elem* setList[26] = {nullptr};

    bool session_flag = true;
    while (session_flag) {
        cout << "1. Cоздать множество" << "\n"
             << "2. Удалить множество" << "\n"
             << "3. Добавить элемент в множество" << "\n"
             << "4. Удалить элемент из множества" << "\n"
             << "5. Вывести булеан множества" << "\n"
             << "6. Показать множество" << "\n"
             << "67. Показать все множества" << "\n"
             << "7. Сумма двух множеств" << "\n"
             << "8. Пересечение двух множеств" << "\n"
             << "9. Разность двух множеств" << "\n"
             << "10. Проверить, является ли первое множество подмножеством второго" << "\n"
             << "11. Проверить, равны ли множества" << "\n"
             << "0. Выход" << "\n"
             << "Ваш выбор: " << endl;
        int userCommand;
        cin >> userCommand;
        cin.clear();
        if (userCommand == 0) {
            session_flag = false;
            continue;
        }
        char userSet;
        if (userCommand != 67) {
            userSet = takeUserSet();
            if (userSet == char(0)) {
                    continue;;
            }
        }
        char* userSet2 = new char;
        int* setpos2 = new int;
        if (7 <= userCommand && userCommand <= 11) {
            *userSet2 = takeUserSet();
            *setpos2 = int(*userSet2) - LEFT_BORDER_SET;
        }
        else {
            delete userSet2;
            delete setpos2;
        }
        int setpos = int(userSet) - LEFT_BORDER_SET;
        switch (userCommand) {
            case 1: {
                if (setList[setpos] != nullptr) {
                    cout << "Такое множество уже существует" << endl;
                    break;
                }
                Elem* newSet = new Elem();
                newSet->value = userSet;
                setList[setpos] = newSet;
                break;
            }
            case 2: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    break;
                }
                cleanMemory(*setList[setpos]);
                setList[setpos] = nullptr;
                break;
            }
            case 3: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    break;
                }
                char userElement = takeUserChar();
                if (userElement == ' ') {
                    break;
                }
                addElementInSet(*setList[setpos], userElement);
                break;
            }
            case 4: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    break;
                }
                char userElement = takeUserChar();
                if (userElement == ' ') {
                    break;
                }
                removeElementFromSet(*setList[setpos], userElement);
                break;
            }
            case 5: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    break;
                }
                showBoolean(*setList[setpos]);
                break;
            }
            case 6: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    break;
                }
                showSet(*setList[setpos]);
                break;
            }
            case 67: {
                for (size_t i = 0; i < 26; i++) {
                    if (setList[i] != nullptr) {
                        showSet(*setList[i]);
                    }
                }
                break;
            }
            case 7: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                if (setList[*setpos2] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                cout << userSet << " + " << *userSet2 << " = ";
                setSum(*setList[setpos], *setList[*setpos2]);
                cleans(*userSet2, *setpos2);
                break;
            }
            case 8: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                if (setList[*setpos2] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                cout << userSet << " & " << *userSet2 << " = ";
                setMultiplication(*setList[setpos], *setList[*setpos2]);
                cleans(*userSet2, *setpos2);
                break;
            }
            case 9: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                if (setList[*setpos2] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                cout << userSet << " - " << *userSet2 << " = ";
                potencial(*setList[setpos], *setList[*setpos2]);
                cleans(*userSet2, *setpos2);
                break;
            }
            case 10: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                if (setList[*setpos2] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                if (checkSubset(*setList[setpos], *setList[*setpos2])) {
                    cout << "Множество " << userSet << " является подмножеством " << *userSet2 << endl;
                }
                else {
                    cout << "Множество " << userSet << " НЕ является подмножеством " << *userSet2 << endl;
                }
                cleans(*userSet2, *setpos2);
                break;
            }
            case 11: {
                if (setList[setpos] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                if (setList[*setpos2] == nullptr) {
                    cout << "Такого множества не существует" << endl;
                    cleans(*userSet2, *setpos2);
                    break;
                }
                if (checkEqual(*setList[setpos], *setList[*setpos2])) {
                    cout << "Множества " << userSet << " и " << *userSet2 << " РАВНЫ" << endl;
                }
                else {
                    cout << "Множества " << userSet << " и " << *userSet2 << " НЕ РАВНЫ" << endl;
                }
                cleans(*userSet2, *setpos2);
                break;
            }
            default: {
                break;
            }
        }
    }
    
    for (size_t i = 0; i < 26; i++) {
        if (setList[i] != nullptr) {
            cleanMemory(*setList[i]);
            cout << "Атоматическое освобождение памяти для множества: " << char(LEFT_BORDER_SET + i) << endl;
        }
    }
    return 0;
}
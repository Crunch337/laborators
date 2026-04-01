/********************************************************************
*           КУРС ИНФОРМАЦИОННЫЕ ТЕХНОЛОГИИ ТЕХНОЛОГИИ               *
*-------------------------------------------------------------------*
* Project Type  : Win32 Console Application                         *
* Project Name  : kt laba2                                          *
* File Name     : kt laba2.cpp                                      *
* Programmer(s) : Можаев С.В.,Иванов Н.И., М3О-107Б-25              *
* Modifyed By   :                                                   *
* Created       : 01/04/26                                          *
* Last Revision : 01/04/26                                          *
* Comment(s)    : Двумерные массивы                                 *
********************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

const int NMAX = 10;   // максимальное количество строк
const int MMAX = 15;   // максимальное количество столбцов

int main() 
{
    setlocale(LC_ALL, "Russian");

    // Матрица A (N1=7, M1=10)
    int N1; // число строк 
    int M1; // число столбцов
    int A[NMAX][MMAX]; // матрица 
    int sumstr[NMAX]; // массив сумм строк
    int minstr = 0; // минимальная сумма элементов строки
    int maxstr = 0; // максимальная сумма элементов строки
    int temp; // вспомгательная переменная
    int count=0; // необходим для подсчёта элементов
    int expected; // используется для проверки на правильное количество элементов

    ifstream file("C:\\Users\\user\\Desktop\\ЛАБЫ\\2 семестр\\A.txt");

    // проверка на открытие файла
    if (!file) 
    {
        cout << "Не удалось открыть файл A.txt" << endl;
        return 1;
    }

    // чтение размеров
    file >> N1;
    if (file) 
    {
        count++;
    }
    file >> M1;
    if (file) 
    {
        count++;
    }

    // проверка на то что у нас есть необходимые данные
    if (count != 2)
    {
        cout << "Ошибка чтения размеров матрицы. Файл пуст или содержит недостаточно данных." << endl;
        return 1;
    }

    // Проверка, чтобы размеры не превышали максимальные   
    if (N1 > NMAX || M1 > MMAX || N1 <=0 || M1 <=0)
    {
        cout << "Размеры матрицы A превышают допустимые или не положительны" << endl;
        return 1;
    }

    // Чтение элементов
    for (int i = 0; i < N1; i++)
    {
        for (int j = 0; j < M1; j++)
        {
            if (file)
            {
                file >> A[i][j];
                count+=1;
            }
        }
    }

    // Проверка, что прочитано достаточно чисел
    expected = 2 + N1 * M1;
    if (count != expected)
    {
        cout << "Неверное количество данных для заполнения матрицы. Прочитано " << count - 2 << " элементов, ожидалось " << N1 * M1 << "." << endl;
        return 1;
    }
    file.close();

    // Обработка матрицы A 
    cout << "Исходная матрица A (" << N1 << "x" << M1 << "):" << endl;
    for (int i = 0; i < N1; i++) 
    {
        for (int j = 0; j < M1; j++){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    // Считаем суммы для каждой строки
    for (int i = 0; i < N1; i++)
    {
        sumstr[i] = 0;
        for (int j = 0; j < M1; j++) {
            sumstr[i] += A[i][j];
        }
        if (sumstr[i] < sumstr[minstr])
        {
            minstr = i;
        }  
        if (sumstr[i] > sumstr[maxstr])
        {
            minstr = i;
        }  
    }
    cout << "\nСтрока с минимальной суммой (" << sumstr[minstr] << ") : " << minstr << endl;
    cout << "Строка с максимальной суммой (" << sumstr[maxstr] << ") : " << maxstr << endl;

    // Меняем строки местами (если это разные строки)
    if (minstr != maxstr)
    {
        for (int j = 0; j < M1; j++) 
        {
            temp = A[minstr][j];
            A[minstr][j] = A[maxstr][j];
            A[maxstr][j] = temp;
        }
    }
    cout << "\nПреобразованная матрица A:" << endl;
    
    // печать преобразованной матрицы
    for (int i = 0; i < N1; i++) 
    {
        for (int j = 0; j < M1; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
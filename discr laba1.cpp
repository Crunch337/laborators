#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
class link {
public:
    int val;         // хранит код символа (ASCII)
    link* next;
};

// Глобальный массив указателей на головы множеств (A-Z)
link* sets[26] = {nullptr};

// Найти множество по имени (вернуть указатель на голову или nullptr)
link* findSet(char name) {
    int idx = name - 'A';
    if (idx < 0 || idx >= 26) return nullptr;
    return sets[idx];
}

// Создать новое множество
bool createSet(char name) {
    int idx = name - 'A';
    if (sets[idx] != nullptr) {
        cout << "Множество " << name << " уже существует\n";
        return false;
    }
    link* head = new link;
    head->val = (int)name;
    head->next = nullptr;
    sets[idx] = head;
    return true;
}

// Удалить множество и освободить память
void deleteSet(char name) {
    int idx = name - 'A';
    link* head = sets[idx];
    if (head == nullptr) {
        cout << "Множество " << name << " не существует\n";
        return;
    }
    link* cur = head;
    while (cur) {
        link* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    sets[idx] = nullptr;
}

// Добавить элемент с сохранением порядка
void addElement(char name, char ch) {
    link* head = findSet(name);
    if (!head) {
        cout << "Множество " << name << " не существует\n";
        return;
    }
    // Проверка допустимости символа (печатный и не заглавная буква)
    if (!(ch >= '!' && ch <= '~') || (ch >= 'A' && ch <= 'Z')) {
        cout << "Недопустимый символ\n";
        return;
    }
    int code = (int)ch;
    link* prev = head;
    link* cur = head->next;
    while (cur && cur->val < code) {
        prev = cur;
        cur = cur->next;
    }
    if (cur && cur->val == code) {
        cout << "Элемент '" << ch << "' уже есть в множестве\n";
        return;
    }
    link* newNode = new link;
    newNode->val = code;
    newNode->next = cur;
    prev->next = newNode;
}

// Удалить элемент
void removeElement(char name, char ch) {
    link* head = findSet(name);
    if (!head) {
        cout << "Множество " << name << " не существует\n";
        return;
    }
    int code = (int)ch;
    link* prev = head;
    link* cur = head->next;
    while (cur && cur->val < code) {
        prev = cur;
        cur = cur->next;
    }
    if (cur && cur->val == code) {
        prev->next = cur->next;
        delete cur;
    } else {
        cout << "Элемент '" << ch << "' не найден\n";
    }
}

// Вывести множество
void printSet(char name) {
    link* head = findSet(name);
    if (!head) {
        cout << "Множество " << name << " не существует\n";
        return;
    }
    link* cur = head;
    while (cur) {
        cout << (char)cur->val;
        if (cur->next) cout << ' ';
        cur = cur->next;
    }
    cout << endl;
}

// Вывести все множества
void printAllSets() {
    bool any = false;
    for (int i = 0; i < 26; ++i) {
        if (sets[i]) {
            printSet('A' + i);
            any = true;
        }
    }
    if (!any) cout << "Нет созданных множеств\n";
}

// Булеан 
void printPowerSet(char name) {
    link* head = findSet(name);
    if (!head) {
        cout << "Множество " << name << " не существует\n";
        return;
    }

    int n = 0;
    link* cur = head->next;
    while (cur) {
        ++n;
        cur = cur->next;
    }
    if (n == 0) {
        cout << "∅\n";
        return;
    }
    char* elems = new char[n];
    cur = head->next;
    for (int i = 0; i < n; ++i) {
        elems[i] = (char)cur->val;
        cur = cur->next;
    }

    unsigned long long total = 1ULL << n;
    for (unsigned long long mask = 0; mask < total; ++mask) {
        bool first = true;
        for (int i = 0; i < n; ++i) {
            if (mask & (1ULL << i)) {
                if (!first) cout << ' ';
                cout << elems[i];
                first = false;
            }
        }
        if (first) cout << "∅";
        cout << endl;
    }
    delete[] elems;
}

// Объединение
void unionSets(char a, char b) {
    link* headA = findSet(a);
    link* headB = findSet(b);
    if (!headA || !headB) {
        cout << "Одно из множеств не существует\n";
        return;
    }
    link* p = headA->next;
    link* q = headB->next;
    while (p && q) {
        if (p->val < q->val) {
            cout << (char)p->val << ' ';
            p = p->next;
        } else if (p->val > q->val) {
            cout << (char)q->val << ' ';
            q = q->next;
        } else {
            cout << (char)p->val << ' ';
            p = p->next;
            q = q->next;
        }
    }
    while (p) { cout << (char)p->val << ' '; p = p->next; }
    while (q) { cout << (char)q->val << ' '; q = q->next; }
    cout << endl;
}

// Пересечение
void intersectSets(char a, char b) {
    link* headA = findSet(a);
    link* headB = findSet(b);
    if (!headA || !headB) {
        cout << "Одно из множеств не существует\n";
        return;
    }
    link* p = headA->next;
    link* q = headB->next;
    while (p && q) {
        if (p->val < q->val) p = p->next;
        else if (p->val > q->val) q = q->next;
        else {
            cout << (char)p->val << ' ';
            p = p->next;
            q = q->next;
        }
    }
    cout << endl;
}
// Разность A \ B
void diffSets(char a, char b) {
    link* headA = findSet(a);
    link* headB = findSet(b);
    if (!headA || !headB) {
        cout << "Одно из множеств не существует\n";
        return;
    }
    link* p = headA->next;
    link* q = headB->next;
    while (p) {
        if (!q || p->val < q->val) {
            cout << (char)p->val << ' ';
            p = p->next;
        } else if (p->val > q->val) {
            q = q->next;
        } else {
            p = p->next;
            q = q->next;
        }
    }
    cout << endl;
}

// Проверка подмножества
bool isSubset(char a, char b) {
    link* headA = findSet(a);
    link* headB = findSet(b);
    if (!headA || !headB) {
        cout << "Одно из множеств не существует\n";
        return false;
    }
    link* p = headA->next;
    link* q = headB->next;
    while (p) {
        while (q && q->val < p->val) 
            q = q->next;
        if (!q || q->val != p->val) 
            return false;
        p = p->next;
    }
    return true;
}
// Проверка равенства
bool areEqual(char a, char b) {
    link* headA = findSet(a);
    link* headB = findSet(b);
    if (!headA || !headB) {
        cout << "Одно из множеств не существует\n";
        return false;
    }
    link* p = headA->next;
    link* q = headB->next;
    while (p && q) {
        if (p->val != q->val) return false;
        p = p->next;
        q = q->next;
    }
    return p == nullptr && q == nullptr;
}

void execute(const string& cmdLine) {
    if (cmdLine.empty()) return;

    size_t pos = 0;
    string cmd;
    while (pos < cmdLine.size() && cmdLine[pos] != ' ') {
        cmd += cmdLine[pos];
        ++pos;
    }
    while (pos < cmdLine.size() && cmdLine[pos] == ' ') ++pos;

    if (cmd == "new") {
        if (pos >= cmdLine.size()) {
            cout << "Ошибка: не указано имя множества\n";
            return;
        }
        char name = cmdLine[pos];
        if (name >= 'A' && name <= 'Z')
            createSet(name);
        else
            cout << "Неверное имя (A-Z)\n";
    }
    else if (cmd == "del") {
        if (pos >= cmdLine.size()) {
            cout << "Ошибка: не указано имя множества\n";
            return;
        }
        char name = cmdLine[pos];
        if (name >= 'A' && name <= 'Z')
            deleteSet(name);
        else
            cout << "Неверное имя (A-Z)\n";
    }
    else if (cmd == "add") {
        if (pos + 2 >= cmdLine.size()) {
            cout << "Ошибка: нужно указать имя и элемент\n";
            return;
        }
        char name = cmdLine[pos];
        char elem = cmdLine[pos+2];
        if (!(name >= 'A' && name <= 'Z')) {
            cout << "Неверное имя (A-Z)\n";
            return;
        }
        if (!(elem >= '!' && elem <= '~') || (elem >= 'A' && elem <= 'Z')) {
            cout << "Недопустимый символ\n";
            return;
        }
        addElement(name, elem);
    }
    else if (cmd == "rem") {
        if (pos + 2 >= cmdLine.size()) {
            cout << "Ошибка: нужно указать имя и элемент\n";
            return;
        }
        char name = cmdLine[pos];
        char elem = cmdLine[pos+2];
        if (!(name >= 'A' && name <= 'Z')) {
            cout << "Неверное имя (A-Z)\n";
            return;
        }
        if (!(elem >= '!' && elem <= '~') || (elem >= 'A' && elem <= 'Z')) {
            cout << "Недопустимый символ\n";
            return;
        }
        removeElement(name, elem);
    }
    else if (cmd == "pow") {
        if (pos >= cmdLine.size()) {
            cout << "Ошибка: не указано имя множества\n";
            return;
        }
        char name = cmdLine[pos];
        if (name >= 'A' && name <= 'Z')
            printPowerSet(name);
        else
            cout << "Неверное имя (A-Z)\n";
    }
    else if (cmd == "see") {
        if (pos < cmdLine.size()) {
            char name = cmdLine[pos];
            if (name >= 'A' && name <= 'Z')
                printSet(name);
            else
                cout << "Неверное имя (A-Z)\n";
        } else {
            printAllSets();
        }
    }
    else if (cmd.size() == 1 && (cmd[0] >= 'A' && cmd[0] <= 'Z')) {
        char left = cmd[0];
        if (pos >= cmdLine.size()) {
            cout << "Ошибка: не указана операция\n";
            return;
        }
        string op;
        while (pos < cmdLine.size() && cmdLine[pos] != ' ') {
            op += cmdLine[pos];
            ++pos;
        }
        while (pos < cmdLine.size() && cmdLine[pos] == ' ') ++pos;
        if (pos >= cmdLine.size()) {
            cout << "Ошибка: не указано второе множество\n";
            return;
        }
        char right = cmdLine[pos];
        if (!(right >= 'A' && right <= 'Z')) {
            cout << "Неверное имя второго множества\n";
            return;
        }
        if (op == "+") {
            cout << left << " + " << right << " = ";
            unionSets(left, right);
        } else if (op == "&") {
            cout << left << " & " << right << " = ";
            intersectSets(left, right);
        } else if (op == "-") {
            cout << left << " - " << right << " = ";
            diffSets(left, right);
        } else if (op == "<") {
            if (isSubset(left, right))
                cout << left << " является подмножеством " << right << endl;
            else
                cout << left << " не является подмножеством " << right << endl;
        } else if (op == "=") {
            if (areEqual(left, right))
                cout << left << " и " << right << " равны" << endl;
            else
                cout << left << " и " << right << " не равны" << endl;
        } else {
            cout << "Неизвестная операция: " << op << endl;
        }
    }
    else if (cmd == "help") {
        cout << "Команды:\n"
             << "  new A\n"
             << "  del A\n"
             << "  add A x\n"
             << "  rem A x\n"
             << "  pow A\n"
             << "  see A\n"
             << "  A + B\n"
             << "  A & B\n"
             << "  A - B\n"
             << "  A < B\n"
             << "  A = B\n"
             << "  exit\n";
    }
    else if (cmd == "exit") {
        exit(0);
    }
    else {
        cout << "Неизвестная команда.Введите help для списка.\n";
    }
}
int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    cout << "Введите команду (help для справки):\n";
    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        execute(line);
    }
    return 0;
}
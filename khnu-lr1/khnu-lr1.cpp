#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// ======================================================
// Задача 1 (динамічна структура TOVAR) :contentReference[oaicite:0]{index=0} :contentReference[oaicite:1]{index=1}
// ======================================================
struct TOVAR {
    string name;     // назва товару
    string unit;     // одиниця виміру
    string sort;     // сорт
    int quantity;    // кількість
    double cost;     // ціна за одиницю
};

list<TOVAR> shop;

// Додати елемент у кінець списку
void addTovar() {
    TOVAR t;
    cout << "Введіть назву товару: ";      getline(cin, t.name);
    cout << "Одиниця виміру: ";           getline(cin, t.unit);
    cout << "Сорт товару: ";              getline(cin, t.sort);
    cout << "Кількість одиниць: ";        cin >> t.quantity;
    cout << "Ціна за одиницю: ";          cin >> t.cost;
    cin.ignore();
    shop.push_back(t);
    cout << "Товар додано.\n";
}

// Видалити елемент за номером (1-based)
void removeTovar() {
    if (shop.empty()) {
        cout << "Список пустий.\n";
        return;
    }
    int idx; cout << "Номер елемента для видалення: "; cin >> idx; cin.ignore();
    if (idx <= 0 || idx > (int)shop.size()) {
        cout << "Невірний номер.\n";
        return;
    }
    auto it = shop.begin();
    advance(it, idx - 1);
    shop.erase(it);
    cout << "Елемент видалено.\n";
}

// Вивести інформацію про елемент за номером
void printOneTovar() {
    if (shop.empty()) {
        cout << "Список пустий.\n";
        return;
    }
    int idx; cout << "Номер елемента для перегляду: "; cin >> idx; cin.ignore();
    if (idx <= 0 || idx > (int)shop.size()) {
        cout << "Невірний номер.\n";
        return;
    }
    auto it = shop.begin();
    advance(it, idx - 1);
    cout << "=== TOVAR #" << idx << " ===\n"
        << "Назва: " << it->name << "\n"
        << "Одиниця: " << it->unit << "\n"
        << "Сорт: " << it->sort << "\n"
        << "Кількість: " << it->quantity << "\n"
        << "Ціна: " << it->cost << "\n";
}

// Вивести весь список
void printAllTovar() {
    if (shop.empty()) {
        cout << "Список пустий.\n";
        return;
    }
    int i = 1;
    for (auto& t : shop) {
        cout << i++ << ". " << t.name
            << " | к-ть: " << t.quantity
            << " | цінa: " << t.cost
            << " | всього: " << t.quantity * t.cost
            << "\n";
    }
}

// ======================================================
// Задача 2 (каталог конспектів Аліси) :contentReference[oaicite:2]{index=2}
// ======================================================
struct Note {
    string discipline;   // назва дисципліни
    string direction;    // технічна/математична/гуманітарна
    string lecturer;     // ім’я лектора
    int pages;           // кількість сторінок
};

vector<Note> catalog;

// Додати запис
void addNote() {
    Note n;
    cout << "Дисципліна: ";          getline(cin, n.discipline);
    cout << "Напрям (tech/math/hum): "; getline(cin, n.direction);
    cout << "Лектор: ";              getline(cin, n.lecturer);
    cout << "Сторінок: ";            cin >> n.pages; cin.ignore();
    catalog.push_back(n);
    cout << "Конспект додано.\n";
}

// Підрахувати контрольну суму (побайтово) і вивести разом з датою
void computeAndPrintChecksum() {
    if (catalog.empty()) {
        cout << "Каталог пустий.\n";
        return;
    }
    // Простіше: будемо додавати всі байти рядкових полів та цілі числа
    unsigned long long checksum = 0;
    for (auto& n : catalog) {
        for (char c : n.discipline) checksum += (unsigned char)c;
        for (char c : n.direction)  checksum += (unsigned char)c;
        for (char c : n.lecturer)   checksum += (unsigned char)c;
        checksum += n.pages;
    }
    // Отримуємо поточну дату
    time_t now = time(nullptr);
    tm   ltmStruct;
    localtime_s(&ltmStruct, &now);    // <-- безпечний варіант для MSVC

    cout << "Контрольна сума: " << checksum << "\n";
    cout << "Дата обчислення: "
        << 1900 + ltmStruct.tm_year << "-"
        << setw(2) << setfill('0') << 1 + ltmStruct.tm_mon << "-"
        << setw(2) << setfill('0') << ltmStruct.tm_mday << "\n";
    cout << "Контрольна сума: " << checksum << "\n";
    cout << "Дата обчислення: "
        << 1900 + ltmStruct.tm_year << "-"
        << setw(2) << setfill('0') << 1 + ltmStruct.tm_mon << "-"
        << setw(2) << setfill('0') << ltmStruct.tm_mday << "\n";
}

// Вивести весь каталог
void printAllNotes() {
    if (catalog.empty()) {
        cout << "Каталог пустий.\n";
        return;
    }
    int i = 1;
    for (auto& n : catalog) {
        cout << i++ << ". " << n.discipline
            << " | " << n.direction
            << " | " << n.lecturer
            << " | сторінок: " << n.pages << "\n";
    }
}

// ======================================================
// Задача 3 (структура StudentExam з методами) :contentReference[oaicite:3]{index=3}
// ======================================================
struct StudentExam {
    string surname;
    int math = 0;     // за замовчуванням 0
    int inf = 0;
    int phys = 0;

    // введення одного запису
    void input() {
        cout << "Прізвище: ";
        getline(cin, surname);
        cout << "Оцінка з математики: ";    cin >> math;
        cout << "Оцінка з інформатики: ";   cin >> inf;
        cout << "Оцінка з фізики: ";        cin >> phys;
        cin.ignore();
    }
    // чи лише одна четвірка?
    bool oneFourOnly() const {
        int cnt4 = 0;
        if (math == 4) ++cnt4;
        if (inf == 4) ++cnt4;
        if (phys == 4) ++cnt4;
        // решта – не четвірки
        return cnt4 == 1 &&
            (math != 4 || (inf != 4 && phys != 4)) &&
            (inf != 4 || (math != 4 && phys != 4)) &&
            (phys != 4 || (math != 4 && inf != 4));
    }
    // чи інформатику відмінно?
    bool infoExcellent() const {
        return inf == 5;
    }
};

void task3() {
    int N;
    cout << "Скільки студентів? "; cin >> N; cin.ignore();
    vector<StudentExam> v(N);
    for (int i = 0; i < N; ++i) {
        cout << "--- Студент #" << i + 1 << " ---\n";
        v[i].input();
    }

    // тільки одна четвірка
    vector<string> only4;
    // інформатика відмінно
    vector<string> inf5;

    for (auto& s : v) {
        if (s.oneFourOnly())  only4.push_back(s.surname);
        if (s.infoExcellent()) inf5.push_back(s.surname);
    }

    cout << "Студенти тільки з однією четвіркою (" << only4.size() << "):\n";
    for (auto& n : only4) cout << "  " << n << "\n";

    cout << "Студенти з інформатики відмінно (" << inf5.size() << "):\n";
    for (auto& n : inf5) cout << "  " << n << "\n";
}

// ======================================================
// Головне меню
// ======================================================
int main() {
    setlocale(LC_ALL, "");
    while (true) {
        cout << "\n=== Меню програм варіанта № 15 ===\n"
            << "1) Динамічна структура TOVAR (add/remove/print)\n"
            << "2) Каталог конспектів Аліси (додати/контрольна сума)\n"
            << "3) Exam: одна четвірка + інформатика відмінно\n"
            << "0) Вихід\n"
            << "Ваш вибір: ";
        int choice; cin >> choice; cin.ignore();
        if (choice == 0) break;

        switch (choice) {
        case 1:
        {
            cout << "\n--- Задача 1: TOVAR Linked List ---\n";
            cout << " a) Додати товар\n";
            cout << " b) Видалити товар за номером\n";
            cout << " c) Переглянути один товар\n";
            cout << " d) Переглянути весь список\n";
            cout << " x) Повернутись\n";
            char op; while (cin >> op && op != 'x') {
                cin.ignore();
                if (op == 'a') addTovar();
                else if (op == 'b') removeTovar();
                else if (op == 'c') printOneTovar();
                else if (op == 'd') printAllTovar();
                else cout << "Невірна команда\n";
                cout << "Операція: ";
            }
        }
        break;
        case 2:
        {
            cout << "\n--- Задача 2: Каталог конспектів Аліси ---\n";
            cout << " a) Додати конспект\n";
            cout << " b) Вивести весь каталог\n";
            cout << " c) Обчислити контрольну суму та дату\n";
            cout << " x) Повернутись\n";
            char op;
            while (cin >> op && op != 'x') {
                cin.ignore();
                if (op == 'a') addNote();
                else if (op == 'b') printAllNotes();
                else if (op == 'c') computeAndPrintChecksum();
                else cout << "Невірна команда\n";
                cout << "Операція: ";
            }
        }
        break;
        case 3:
            cout << "\n--- Задача 3: StudentExam Static ---\n";
            task3();
            break;
        default:
            cout << "Невірний вибір\n";
        }
    }
    cout << "Програма завершена.\n";
    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

// ======================================================
// ������ 1 (�������� ��������� TOVAR) :contentReference[oaicite:0]{index=0} :contentReference[oaicite:1]{index=1}
// ======================================================
struct TOVAR {
    string name;     // ����� ������
    string unit;     // ������� �����
    string sort;     // ����
    int quantity;    // �������
    double cost;     // ���� �� �������
};

list<TOVAR> shop;

// ������ ������� � ����� ������
void addTovar() {
    TOVAR t;
    cout << "������ ����� ������: ";      getline(cin, t.name);
    cout << "������� �����: ";           getline(cin, t.unit);
    cout << "���� ������: ";              getline(cin, t.sort);
    cout << "ʳ������ �������: ";        cin >> t.quantity;
    cout << "ֳ�� �� �������: ";          cin >> t.cost;
    cin.ignore();
    shop.push_back(t);
    cout << "����� ������.\n";
}

// �������� ������� �� ������� (1-based)
void removeTovar() {
    if (shop.empty()) {
        cout << "������ ������.\n";
        return;
    }
    int idx; cout << "����� �������� ��� ���������: "; cin >> idx; cin.ignore();
    if (idx <= 0 || idx > (int)shop.size()) {
        cout << "������� �����.\n";
        return;
    }
    auto it = shop.begin();
    advance(it, idx - 1);
    shop.erase(it);
    cout << "������� ��������.\n";
}

// ������� ���������� ��� ������� �� �������
void printOneTovar() {
    if (shop.empty()) {
        cout << "������ ������.\n";
        return;
    }
    int idx; cout << "����� �������� ��� ���������: "; cin >> idx; cin.ignore();
    if (idx <= 0 || idx > (int)shop.size()) {
        cout << "������� �����.\n";
        return;
    }
    auto it = shop.begin();
    advance(it, idx - 1);
    cout << "=== TOVAR #" << idx << " ===\n"
        << "�����: " << it->name << "\n"
        << "�������: " << it->unit << "\n"
        << "����: " << it->sort << "\n"
        << "ʳ������: " << it->quantity << "\n"
        << "ֳ��: " << it->cost << "\n";
}

// ������� ���� ������
void printAllTovar() {
    if (shop.empty()) {
        cout << "������ ������.\n";
        return;
    }
    int i = 1;
    for (auto& t : shop) {
        cout << i++ << ". " << t.name
            << " | �-��: " << t.quantity
            << " | ���a: " << t.cost
            << " | ������: " << t.quantity * t.cost
            << "\n";
    }
}

// ======================================================
// ������ 2 (������� ��������� ����) :contentReference[oaicite:2]{index=2}
// ======================================================
struct Note {
    string discipline;   // ����� ���������
    string direction;    // �������/�����������/����������
    string lecturer;     // ��� �������
    int pages;           // ������� �������
};

vector<Note> catalog;

// ������ �����
void addNote() {
    Note n;
    cout << "���������: ";          getline(cin, n.discipline);
    cout << "������ (tech/math/hum): "; getline(cin, n.direction);
    cout << "������: ";              getline(cin, n.lecturer);
    cout << "�������: ";            cin >> n.pages; cin.ignore();
    catalog.push_back(n);
    cout << "�������� ������.\n";
}

// ϳ��������� ���������� ���� (���������) � ������� ����� � �����
void computeAndPrintChecksum() {
    if (catalog.empty()) {
        cout << "������� ������.\n";
        return;
    }
    // �������: ������ �������� �� ����� �������� ���� �� ��� �����
    unsigned long long checksum = 0;
    for (auto& n : catalog) {
        for (char c : n.discipline) checksum += (unsigned char)c;
        for (char c : n.direction)  checksum += (unsigned char)c;
        for (char c : n.lecturer)   checksum += (unsigned char)c;
        checksum += n.pages;
    }
    // �������� ������� ����
    time_t now = time(nullptr);
    tm   ltmStruct;
    localtime_s(&ltmStruct, &now);    // <-- ��������� ������ ��� MSVC

    cout << "���������� ����: " << checksum << "\n";
    cout << "���� ����������: "
        << 1900 + ltmStruct.tm_year << "-"
        << setw(2) << setfill('0') << 1 + ltmStruct.tm_mon << "-"
        << setw(2) << setfill('0') << ltmStruct.tm_mday << "\n";
    cout << "���������� ����: " << checksum << "\n";
    cout << "���� ����������: "
        << 1900 + ltmStruct.tm_year << "-"
        << setw(2) << setfill('0') << 1 + ltmStruct.tm_mon << "-"
        << setw(2) << setfill('0') << ltmStruct.tm_mday << "\n";
}

// ������� ���� �������
void printAllNotes() {
    if (catalog.empty()) {
        cout << "������� ������.\n";
        return;
    }
    int i = 1;
    for (auto& n : catalog) {
        cout << i++ << ". " << n.discipline
            << " | " << n.direction
            << " | " << n.lecturer
            << " | �������: " << n.pages << "\n";
    }
}

// ======================================================
// ������ 3 (��������� StudentExam � ��������) :contentReference[oaicite:3]{index=3}
// ======================================================
struct StudentExam {
    string surname;
    int math = 0;     // �� ������������� 0
    int inf = 0;
    int phys = 0;

    // �������� ������ ������
    void input() {
        cout << "�������: ";
        getline(cin, surname);
        cout << "������ � ����������: ";    cin >> math;
        cout << "������ � �����������: ";   cin >> inf;
        cout << "������ � ������: ";        cin >> phys;
        cin.ignore();
    }
    // �� ���� ���� �������?
    bool oneFourOnly() const {
        int cnt4 = 0;
        if (math == 4) ++cnt4;
        if (inf == 4) ++cnt4;
        if (phys == 4) ++cnt4;
        // ����� � �� �������
        return cnt4 == 1 &&
            (math != 4 || (inf != 4 && phys != 4)) &&
            (inf != 4 || (math != 4 && phys != 4)) &&
            (phys != 4 || (math != 4 && inf != 4));
    }
    // �� ����������� ������?
    bool infoExcellent() const {
        return inf == 5;
    }
};

void task3() {
    int N;
    cout << "������ ��������? "; cin >> N; cin.ignore();
    vector<StudentExam> v(N);
    for (int i = 0; i < N; ++i) {
        cout << "--- ������� #" << i + 1 << " ---\n";
        v[i].input();
    }

    // ����� ���� �������
    vector<string> only4;
    // ����������� ������
    vector<string> inf5;

    for (auto& s : v) {
        if (s.oneFourOnly())  only4.push_back(s.surname);
        if (s.infoExcellent()) inf5.push_back(s.surname);
    }

    cout << "�������� ����� � ���� �������� (" << only4.size() << "):\n";
    for (auto& n : only4) cout << "  " << n << "\n";

    cout << "�������� � ����������� ������ (" << inf5.size() << "):\n";
    for (auto& n : inf5) cout << "  " << n << "\n";
}

// ======================================================
// ������� ����
// ======================================================
int main() {
    setlocale(LC_ALL, "");
    while (true) {
        cout << "\n=== ���� ������� ������� � 15 ===\n"
            << "1) �������� ��������� TOVAR (add/remove/print)\n"
            << "2) ������� ��������� ���� (������/���������� ����)\n"
            << "3) Exam: ���� ������� + ����������� ������\n"
            << "0) �����\n"
            << "��� ����: ";
        int choice; cin >> choice; cin.ignore();
        if (choice == 0) break;

        switch (choice) {
        case 1:
        {
            cout << "\n--- ������ 1: TOVAR Linked List ---\n";
            cout << " a) ������ �����\n";
            cout << " b) �������� ����� �� �������\n";
            cout << " c) ����������� ���� �����\n";
            cout << " d) ����������� ���� ������\n";
            cout << " x) �����������\n";
            char op; while (cin >> op && op != 'x') {
                cin.ignore();
                if (op == 'a') addTovar();
                else if (op == 'b') removeTovar();
                else if (op == 'c') printOneTovar();
                else if (op == 'd') printAllTovar();
                else cout << "������ �������\n";
                cout << "��������: ";
            }
        }
        break;
        case 2:
        {
            cout << "\n--- ������ 2: ������� ��������� ���� ---\n";
            cout << " a) ������ ��������\n";
            cout << " b) ������� ���� �������\n";
            cout << " c) ��������� ���������� ���� �� ����\n";
            cout << " x) �����������\n";
            char op;
            while (cin >> op && op != 'x') {
                cin.ignore();
                if (op == 'a') addNote();
                else if (op == 'b') printAllNotes();
                else if (op == 'c') computeAndPrintChecksum();
                else cout << "������ �������\n";
                cout << "��������: ";
            }
        }
        break;
        case 3:
            cout << "\n--- ������ 3: StudentExam Static ---\n";
            task3();
            break;
        default:
            cout << "������� ����\n";
        }
    }
    cout << "�������� ���������.\n";
    return 0;
}

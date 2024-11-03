#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <regex>
#include <iomanip>

using namespace std;

struct Book {
    string title;
    string author;
    string id;
};

struct Borrower {
    string name;
    vector<string> borrowed_books;
};

class LibrarySystem {
private:
    list<Book> books;
    forward_list<Borrower> borrowers;

public:
    // 圖書管理功能
    void addBook() {
        string title, author, id;
        cout << "輸入書名: ";
        cin >> ws;  // 忽略前面的空白
        getline(cin, title);
        cout << "輸入作者: ";
        getline(cin, author);
        cout << "輸入圖書編號 (格式: A1234): ";
        cin >> id;

        if (!isValidBookID(id)) {
            cout << "圖書編號不符合規定！" << endl;
            return;
        }
        books.push_back({ title, author, id });
        cout << "圖書已添加！" << endl;
    }

    void deleteBook() {
        string id;
        cout << "輸入要刪除的圖書編號: ";
        cin >> id;
        books.remove_if([&](const Book& book) { return book.id == id; });
        cout << "圖書已刪除（若存在）。" << endl;
    }

    void searchBook() {
        string id;
        cout << "輸入要搜尋的圖書編號: ";
        cin >> id;
        for (const auto& book : books) {
            if (book.id == id) {
                cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
                return;
            }
        }
        cout << "找不到指定圖書編號的圖書！" << endl;
    }

    void listBooks() {
        books.sort([](const Book& a, const Book& b) { return a.id < b.id; });
        cout << "所有圖書（依圖書編號排序）:" << endl;
        for (const auto& book : books) {
            cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
        }
    }

    // 借閱者管理功能
    void addBorrower() {
        string name;
        int n;
        cout << "輸入借閱者姓名: ";
        cin >> ws;  // 忽略前面的空白
        getline(cin, name);

        cout << "輸入借閱的圖書數量: ";
        cin >> n;

        vector<string> book_ids(n);
        for (int i = 0; i < n; ++i) {
            cout << "輸入圖書編號 " << i + 1 << ": ";
            cin >> book_ids[i];
        }

        borrowers.push_front({ name, book_ids });
        cout << "借閱者已添加！" << endl;
    }

    void deleteBorrower() {
        string name;
        cout << "輸入要刪除的借閱者姓名: ";
        cin >> ws;  // 忽略前面的空白
        getline(cin, name);
        borrowers.remove_if([&](const Borrower& borrower) { return borrower.name == name; });
        cout << "借閱者已刪除（若存在）。" << endl;
    }

    void searchBorrower() {
        string name;
        cout << "輸入要搜尋的借閱者姓名: ";
        cin >> ws;  // 忽略前面的空白
        getline(cin, name);
        for (const auto& borrower : borrowers) {
            if (borrower.name == name) {
                cout << "姓名: " << borrower.name << ", 借閱的圖書編號: ";
                for (const auto& id : borrower.borrowed_books) {
                    cout << id << " ";
                }
                cout << endl;
                return;
            }
        }
        cout << "找不到指定姓名的借閱者！" << endl;
    }

    void listBorrowers() {
        cout << "所有借閱者及其借閱的圖書:" << endl;
        for (const auto& borrower : borrowers) {
            cout << "姓名: " << borrower.name << ", 借閱的圖書編號: ";
            for (const auto& id : borrower.borrowed_books) {
                cout << id << " ";
            }
            cout << endl;
        }
    }

private:
    bool isValidBookID(const string& id) {
        regex pattern("^[A-Z]\\d{4}$");
        return regex_match(id, pattern);
    }
};

void showMenu() {
    cout << "\n圖書館管理系統選單：" << endl;
    cout << "1. 添加新圖書" << endl;
    cout << "2. 刪除圖書" << endl;
    cout << "3. 搜尋圖書" << endl;
    cout << "4. 列出所有圖書" << endl;
    cout << "5. 添加新借閱者" << endl;
    cout << "6. 刪除借閱者" << endl;
    cout << "7. 搜尋借閱者" << endl;
    cout << "8. 列出所有借閱者" << endl;
    cout << "9. 退出" << endl;
    cout << "請選擇操作: ";
}

int main() {
    LibrarySystem library;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            library.addBook();
            break;
        case 2:
            library.deleteBook();
            break;
        case 3:
            library.searchBook();
            break;
        case 4:
            library.listBooks();
            break;
        case 5:
            library.addBorrower();
            break;
        case 6:
            library.deleteBorrower();
            break;
        case 7:
            library.searchBorrower();
            break;
        case 8:
            library.listBorrowers();
            break;
        case 9:
            cout << "退出系統。" << endl;
            return 0;
        default:
            cout << "無效的選項，請重新選擇。" << endl;
            break;
        }
    }
}

#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

// 圖書結構體
struct Book {
    string title;  // 書名
    string author; // 作者
    string id;     // 圖書編號
};

// 借閱者結構體
struct Borrower {
    string name;               // 借閱者姓名
    vector<string> borrowedBooks; // 借閱的圖書編號列表
};

list<Book> books; // 使用雙向鏈結串列管理圖書
forward_list<Borrower> borrowers; // 使用單向鏈結串列管理借閱者

// 驗證圖書編號是否符合規範
bool isValidBookId(const string& id) {
    regex pattern("^[A-Z][0-9]{4}$");
    return regex_match(id, pattern);
}

// 添加新圖書
void addBook() {
    Book book;
    cout << "輸入書名: ";
    cin >> book.title;
    cout << "輸入作者: ";
    cin >> book.author;
    do {
        cout << "輸入圖書編號: ";
        cin >> book.id;
        if (!isValidBookId(book.id)) {
            cout << "圖書編號格式錯誤，請重新輸入。" << endl;
        }
    } while (!isValidBookId(book.id));
    books.push_back(book);
}

// 刪除指定圖書編號的圖書
void deleteBook() {
    string id;
    cout << "輸入要刪除的圖書編號: ";
    cin >> id;
    //從 books 雙向鏈結串列中移除所有圖書編號與變數 id 相同的圖書
    books.remove_if([&id](const Book& book) { return book.id == id; });
}

// 搜索指定圖書編號的圖書
void searchBook() {
    string id;
    cout << "輸入要搜索的圖書編號: ";
    cin >> id;
    auto it = find_if(books.begin(), books.end()/*•	這兩個迭代器定義了 books 的範圍。*/
                      , [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        cout << "書名: " << it->title << ", 作者: " << it->author << ", 圖書編號: " << it->id << endl;
    }
    else {
        cout << "找不到該圖書。" << endl;
    }
}

// 依照圖書編號排序列出所有圖書
void listBooks() {
    books.sort([](const Book& a, const Book& b) { return a.id < b.id; });
    for (const auto& book : books) {
        cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
    }
}

// 添加新借閱者
void addBorrower() {
    Borrower borrower;
    cout << "輸入借閱者姓名: ";
    cin >> borrower.name;
    cout << "輸入借閱的圖書編號（輸入 'done' 結束）: ";
    string bookId;
    while (cin >> bookId && bookId != "done") {
        if (isValidBookId(bookId)) {
            borrower.borrowedBooks.push_back(bookId);
        }
        else {
            cout << "圖書編號格式錯誤，請重新輸入。" << endl;
        }
    }
    borrowers.push_front(borrower);
}

// 刪除指定姓名的借閱者
void deleteBorrower() {
    string name;
    cout << "輸入要刪除的借閱者姓名: ";
    cin >> name;
    borrowers.remove_if([&name](const Borrower& borrower) { return borrower.name == name; });
}

// 搜索指定姓名的借閱者
void searchBorrower() {
    string name;
    cout << "輸入要搜索的借閱者姓名: ";
    cin >> name;
    auto it = find_if(borrowers.begin(), borrowers.end(), [&name](const Borrower& borrower) { return borrower.name == name; });
    if (it != borrowers.end()) {
        cout << "姓名: " << it->name << ", 借閱的圖書編號: ";
        for (const auto& bookId : it->borrowedBooks) {
            cout << bookId << " ";
        }
        cout << endl;
    }
    else {
        cout << "找不到該借閱者。" << endl;
    }
}

// 列出所有借閱者及其借閱的圖書
void listBorrowers() {
    for (const auto& borrower : borrowers) {
        cout << "姓名: " << borrower.name << ", 借閱的圖書編號: ";
        for (const auto& bookId : borrower.borrowedBooks) {
            cout << bookId << " ";
        }
        cout << endl;
    }
}

// 主函式
int main() {
    int choice;
    do {
        cout << "1. 添加新圖書\n2. 刪除圖書\n3. 搜索圖書\n4. 列出所有圖書\n";
        cout << "5. 添加新借閱者\n6. 刪除借閱者\n7. 搜索借閱者\n8. 列出所有借閱者\n9. 退出\n";
        cout << "選擇操作: ";
        cin >> choice;

        // 檢查輸入是否有效
        if (cin.fail()) {
            cin.clear(); // 清除錯誤狀態
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略無效輸入
            cout << "無效的選擇，請輸入數字。" << endl;
            continue;
        }

        // 根據選擇執行相應操作
        switch (choice) {
        case 1: addBook(); break;
        case 2: deleteBook(); break;
        case 3: searchBook(); break;
        case 4: listBooks(); break;
        case 5: addBorrower(); break;
        case 6: deleteBorrower(); break;
        case 7: searchBorrower(); break;
        case 8: listBorrowers(); break;
        case 9: break;
        default: cout << "無效的選擇。" << endl; break;
        }
    } while (choice != 9); // 當選擇不為9時重複循環
    return 0;
}

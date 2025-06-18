#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>
using namespace std; // namespace std 사용

class Book {
public:
    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
    string title;
    string author;
    int maxStock;
    int currentStock;

   
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }
    const vector<Book>& getBooks()
    {
        return books;
    }
    Book* getBookTitle(const string& title)
    {
        for (int i = 0; i < books.size(); ++i)
        {
            if (books[i].title == title)
            {
                return &books[i];
            }
        }
        return nullptr;
    }
    Book* getBookAuthor(const string& author)
    {
        for (int i = 0; i < books.size(); ++i)
        {
            if (books[i].author == author)
            {
                return &books[i];
            }
        }
        return nullptr;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
    bool searchByTitle(const string& title)
    {
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return false;
        }
        for (int i = 0; i < books.size(); ++i)
        {
            if (books[i].title == title)
            {
                cout << "책을 찾았습니다. " << "제목: " << books[i].title<< " , 작가: "<< books[i].author << ", 책 번호: " << i << endl;
                return true;
            }
        }
        cout << "책을 찾지 못했습니다." << endl;
        return false;
    }

    bool searchByAuthor(const string& author)
    {
        bool result = false;
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
        }
        for (int i =0; i< books.size() ; ++i)
        {
            
            if (books[i].author == author)
            {
                cout << "책을 찾았습니다. " << "제목: " << books[i].title << " , 작가: " << books[i].author << ", 책 번호: " << i << endl;
                result = true;
            }
        }
        cout << "책을 찾지 못했습니다." << endl;

        return result;
    }
};

class BorrowManager
{
private:
    unordered_map<string, int> stock;
public:
    BorrowManager() : stock(3) {}




    void initializeStock(Book* book,  int quantity)
    {
        stock.insert(pair<string, int>(book->title, 3));
        cout << "책 재고: " << stock[book->title] << endl;
    }



    void borrowBook(const string& title)
    {
        if (stock.find(title) == stock.end())
        {
            cout << "저희 도선관에는 그 책이 없습니다." << endl;
        }
        else if (stock[title] <= 0)
        {
            cout << "책의 재고가 남아있지 않습니다." << endl;
        }
        else 
        {
            stock[title] -= 1;
            cout << title << " 대여. 현재 재고: " << stock[title] << endl;
            return;
        }
    }

    void returnBook(const string& title)
    {
        if (stock.find(title) == stock.end())
        {
            cout << "저희 도서관의 책이 아닙니다." << endl;
        }
        else if(stock[title] >= 3)
        {
            cout << "책을 빌리지 않았습니다." << endl;
        }
        else
        {
            stock[title] += 1;
            cout << title << " 반납. 현재 재고: " << stock[title] << endl;
            return;
        }
    }


    void displayStock()
    {
        for (const auto& book : stock)
        {
            cout << "제목: " << book.first << ", 현재 재고: " << book.second << endl;
        }
    }
};






int main() {
    BookManager manager;
    BorrowManager borrowManger;
    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 제목을 통해 책 검색" << endl;
        cout << "4. 작가의 이름을 통해 책 검색" << endl;
        cout << "5. 책 반납" << endl;
        cout << "6. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            
            string title, author;
            cout << "책 제목: ";
            getline(cin, title); // 제목 입력 (공백 포함)

            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            if (manager.getBookTitle(title))
            {
                cout << "이미 있는 책입니다. " << endl;
                continue;
            }
            manager.addBook(title, author); // 입력받은 책 정보를 추가
            borrowManger.initializeStock(manager.getBookTitle(title), 3);
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
            borrowManger.displayStock();
        }
        else if (choice == 3) {
            string title;
            cout << "책 제목을 입력하세요: " << endl;

            getline(cin, title);
            if (manager.searchByTitle(title))
            {
                int answer;
                cout << "책을 빌리시겠습니까?  예(1 입력) : 아니요(2 입력) " << endl;
                cin >> answer;
                cin.ignore();
                if (answer == 1)
                {
                    borrowManger.borrowBook(title);
                }
                else if (answer == 2)
                {
                    cout << "처음으로 돌아갑니다. " << endl;
                    continue;
                }
                else
                {
                    cout << "잘못된 입력입니다. 처음으로 돌아갑니다. " << endl;
                    continue;
                }
            }
        }
        else if (choice == 4) {
            string author;
            cout << "작가의 이름을 입력하세요: " << endl;
            getline(cin, author);
            manager.searchByAuthor(author);
        }
        else if (choice == 5){
            string title;
            cout << "반납하실 책 이름을 입력하세요: " << endl;
            getline(cin, title);
            borrowManger.returnBook(title);
        }
        else if (choice == 6) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
           
        }
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        
        
    }

    return 0; // 프로그램 정상 종료
}
//TEST 1
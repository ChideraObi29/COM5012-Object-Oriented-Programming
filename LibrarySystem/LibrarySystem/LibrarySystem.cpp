#include <iostream>
using namespace std;
#include <list>
#include <thread>
#include <chrono>
#include <string>

// Books Class
class Books {
public:
    string title;
    string author;
    string status;

    void getBook(string t, string a, string s) {
        title = t;
        author = a;
        status = s;
    }
    virtual void showBook() { // For Polymorphism
        cout << "Book Title: " << title << endl;
        cout << "Book Author: " << author << endl;
        cout << "Book Status: " << status << endl;
        cout << "--------------------" << endl;
    }
    void setStatus(string newStatus) {
        status = newStatus;
    }

    list<string> reserveList;
};

Books books[10];
int bookCount = 0;

// Other types of books
class AudioBooks : public Books {
public:
    void showBook() override {
        cout << "AudioBook Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Status: " << status << endl;
        cout << "--------------------" << endl;
    }
};

AudioBooks audiobooks[5];
int audioBookCount = 0;

// User Class 
class Users {
private: // Encapsulation
    string name;
    string password;

public:
    void setLogin(string n, string p) {
        name = n;
        password = p;
    }
    bool Login(string n, string p) {
        return (n == name && p == password);
    }

    string getName() {
        return name;
    }
};

// Inheritance Classes 
class Members : public Users {

public:

    int borrowNumber = 0;
    list<string> borrowedBooks;
    string overdueBooks;
    bool isBookReturned = false;
public:
    void showAudioBooks() {
        AudioBooks audio1, audio2;
        audio1.getBook("AudioBook1", "Audio Author", "Coming Soon");
        audio2.getBook("AudioBook2", "Audio Author", "Coming Soon");

        audio1.showBook();
        audio2.showBook();
    }
    void borrowBook() {

        string bookTitle;
        cout << "Enter book title: ";
        cin >> bookTitle;

        try {
            if (borrowNumber >= 5)
                throw "You have reached the maximum number of books to borrow!";

            bool found = false;

            for (int i = 0; i < bookCount; i++) {
                if (books[i].title == bookTitle) {
                    found = true;

                    if (books[i].status != "Available")
                        throw "Book not available";

                    books[i].setStatus("Borrowed");
                    borrowNumber++;
                    borrowedBooks.push_back(bookTitle);

                    cout << "Borrowed " << bookTitle << endl;
                    break;
                }
            }

            if (!found)
                throw "Book not found";
        }
        catch (const char* msg) {
            cout << "Error: " << msg << endl;
        }
    }
    void returnBook() {
        string returnBookTitle;
        cout << "Enter Book Title: ";
        cin >> returnBookTitle;

        try {
            bool found = false;

            for (int i = 0; i < bookCount; i++) {
                if (books[i].title == returnBookTitle) {
                    found = true;

                    if (books[i].status == "Available")
                        throw "This book has being returned already";

                    books[i].setStatus("Available");
                    borrowNumber--;
                    borrowedBooks.remove(returnBookTitle);

                    cout << "You returned " << returnBookTitle << endl;
                    break;
                }
            }

            if (!found)
                throw "Book not found!";
        }
        catch (const char* msg) {
            cout << "Error: " << msg << endl;
        }
    }
    void reserveBook(Books& book7) {
        string reserveTitle;
        cout << "Enter book title to reserve: ";
        cin >> reserveTitle;

        if (reserveTitle == "Book7" && book7.status == "Borrowed") {
            book7.setStatus("Reserved");
            cout << "Reservation request sent." << endl;
        }
        else
            cout << "You have no messages";
    }

    void viewBorrowBooks() {
        cout << "Borrowed Books:" << endl;
        for (string book : borrowedBooks) {
            cout << book << endl;
        }
    }

    void viewMessage(Books& book7) {
        if (book7.status == "Reserved") {
            cout << "Book7 is now available." << endl;
            cout << "You have 3 days to borrow it" << endl;
            cout << "Borrow now? (yes/no): ";

            string confirmation;
            cin >> confirmation;

            if (confirmation == "yes") {
                book7.setStatus("Borrowed");
                cout << "You have borrowed Book7." << endl;
                cout << "You have 14 days to return it" << endl;
                borrowNumber++;
                borrowedBooks.push_back(book7.title);

            }
        }
    }


    void memberInterface() {
        int optionNumber = 0;
        while (optionNumber != 7) {
            cout << "" << endl; //Space bettween senteces
            cout << "== Member Options ==" << endl;
            cout << "1. View Books" << endl;
            cout << "2. Borrow Book" << endl;
            cout << "3. Return Book" << endl;
            cout << "4. Reserve Book" << endl;
            cout << "5. View Messages" << endl;
            cout << "6. View Borrowed Books" << endl;
            cout << "7. Exit" << endl;
            cout << "" << endl;
            cout << "Select an option: ";
            cin >> optionNumber;

            if (optionNumber == 1) {
                cout << "" << endl;

                for (int i = 0; i < bookCount; i++) {
                    books[i].showBook();
                }
                showAudioBooks();
            }
            else if (optionNumber == 2) {
                borrowBook();
            }
            else if (optionNumber == 6) {
                viewBorrowBooks();
            }
            else if (optionNumber == 3) {
                returnBook();
            }
            else if (optionNumber == 4) {
                for (int i = 0; i < bookCount; i++) {
                    if (books[i].title == "Book7") {
                        reserveBook(books[i]);
                        break;
                    }
                }
            }

            else if (optionNumber == 5) {
                for (int i = 0; i < bookCount; i++) {
                    if (books[i].title == "Book7") {
                        viewMessage(books[i]);
                        break;
                    }
                }
            }
        }
    }
};

    class Librarians : public Users {
    public:
        void showAudioBooks() {
            AudioBooks audio1, audio2;
            audio1.getBook("AudioBook1", "Audio Author", "Coming Soon");
            audio2.getBook("AudioBook2", "Audio Author", "Coming Soon");

            audio1.showBook();
            audio2.showBook();
        };
        void addBook() {
            if (bookCount >= 10) {
                cout << "Library is full" << endl;
                return;
            }

            string title, author, status;
            cout << "Enter book title: ";
            cin >> title;

            cout << "Enter book author: ";
            cin >> author;

            cout << "Enter book status (Available or Borrowed): ";
            cin >> status;

            books[bookCount].getBook(title, author, status);

            bookCount++;
            cout << "The book was added." << endl;


        };
        void removeBook() {
            string title;
            cout << "Enter a book title to remove: ";
            cin >> title;

            for (int i = 0; i < bookCount; i++) {
                if (books[i].title == title) {
                    for (int j = i; j < bookCount - 1; j++) {
                        books[j] = books[j + 1];
                    }
                    bookCount--;
                    cout << "The book has been removed." << endl;
                    return;
                }
            }
            cout << "Book not found." << endl;
        };
        void updateBook() {
            string title;

            cout << "Enter book title to update: ";
            cin >> title;

            for (int i = 0; i < bookCount; i++) {

                if (books[i].title == title) {

                    cout << "Enter new title: ";
                    cin >> books[i].title;

                    cout << "Enter new author: ";
                    cin >> books[i].author;

                    cout << "Enter new status: ";
                    cin >> books[i].status;

                    cout << "Book updated successfully." << endl;
                    return;
                }
            }
        };

        void showAddedBooks() {
            for (int i = 0; i < bookCount; i++) {
                cout << "Book Title: " << books[i].title << endl;
                cout << "Book Author: " << books[i].author << endl;
                cout << "Book Status: " << books[i].status << endl;
                cout << "--------------------" << endl;
            }
        };

        string alreadyReserved = "false";

        void allowReservation(Members& member2, Members& member3) {
            string applyReservation1;

            if (alreadyReserved == "false") {
                cout << "Member2 Requested Book7 for reservation" << endl;
                alreadyReserved = "true";

                for (int i = 0; i < bookCount; i++) {
                    if (books[i].title == "Book7") {

                        cout << "Book7 Status: " << books[i].status << endl;

                        cout << "Allow reservation? (yes or no): ";
                        cin >> applyReservation1;

                        if (applyReservation1 == "yes" && books[i].status == "Borrowed") {
                            books[i].reserveList.push_back("Member2");
                            cout << "Reservation added to list." << endl;
                        }
                        else {
                            cout << "Reservation denied." << endl;
                        }

                        break;
                    }
                }
            }
        };

        void allowBorrow(Members& member2, Members& member3) {
            string approval;
            if (member2.borrowNumber == 3) {
                cout << "Member2 Requested Book1 for borrowing" << endl;
                cout << "Total books borrowed: " << member2.borrowNumber << endl;
                cout << "Approve? (yes or no): ";
                cin >> approval;

                if (member2.borrowNumber != 5 && approval == "yes") {

                    for (int i = 0; i < bookCount; i++) {
                        if (books[i].title == "Book1") {
                            books[i].setStatus("Borrowed");
                            member2.borrowNumber++;
                            member2.borrowedBooks.push_back("Book1");
                            cout << "Book1 is now borrowed.\n";
                            break;
                        }
                    }
                }
                else {
                    cout << "Borrowing denied" << endl;
                }
            }

            if (member3.borrowNumber == 5) {
                cout << "" << endl;
                cout << "Member3 Requested Book2 for borrowing" << endl;
                cout << "Total books borrowed: " << member3.borrowNumber << endl;
                cout << "Approve? (yes or no): ";
                cin >> approval;

                if (member3.borrowNumber != 5 && approval == "yes") {

                    for (int i = 0; i < bookCount; i++) {
                        if (books[i].title == "Book2") {
                            books[i].setStatus("Borrowed");
                            member3.borrowNumber++;
                            member3.borrowedBooks.push_back("Book2");
                            cout << "Book2 is now borrowed.\n";
                            break;
                        }
                    }
                }

                else if (member3.borrowNumber == 5 && approval == "yes") {
                    cout << "Borrowing denied." << endl;
                    cout << "Member3 has reached the maximun borrow limit." << endl;
                }
                else {
                    cout << "Borrowing denied." << endl;
                }
            }

        };
        void addReports(Members& member2) {
            string message;
            int reportOption = 0;
            cout << "Select report type" << endl;
            cout << "1. Overdue Books" << endl;
            cin >> reportOption;

            cin.ignore();

            if (reportOption == 1 && member2.isBookReturned == false) {
                cout << "Username: Member2" << endl;
                cout << "Books borrowed: " << member2.overdueBooks << "(Overdue)" << endl;
                cout << "Enter notification message" << endl;
                getline(cin, message);
                cout << "Message sent: " << message << endl;
            }
        };

        void librarianInterface(Members& member2, Members& member3) {
            int optionNumber = 0;

            while (optionNumber != 9) {
                cout << "" << endl; //Space bettween senteces       
                cout << "== Librarian Options ==" << endl;
                cout << "1. View Books" << endl;
                cout << "2. Add Book" << endl;
                cout << "3. Remove Book" << endl;
                cout << "4. Update Book" << endl;
                cout << "6. View Borrow Requests" << endl;
                cout << "7. View Reservation Requests" << endl;
                cout << "8. Add reports" << endl;
                cout << "9. Exit" << endl;
                cout << "Select an option: ";
                cin >> optionNumber;

                if (optionNumber == 1) {
                    cout << "" << endl;
                    showAddedBooks();
                    showAudioBooks();
                }
                else if (optionNumber == 2) {
                    addBook();
                }
                else if (optionNumber == 3) {
                    removeBook();
                }
                else if (optionNumber == 4) {
                    updateBook();
                }
                else if (optionNumber == 6) {
                    allowBorrow(member2, member3);
                }
                else if (optionNumber == 7) {
                    allowReservation(member2, member3);
                }
                else if (optionNumber == 8) {
                    addReports(member2);
                }
            }
        };

    };

    class Administrators : public Users {
    public:
        void addUser(Users& user) {
            string addUser;
			cout << "Enter username to add: " << endl;
			cin >> addUser;
            cout << "The User was added to the system." << endl;
        }
        void removeUser() {
            cout << "Enter username to remove: ";
            string name;
            cin >> name;
            cout << "User " << name << " removed" << endl;
        }
        void changeBorrowLimit(Members& member2) {
            if (member2.isBookReturned == false) {
                cout << "This Member has overdue books" << endl;

                int changedLimit;
                cout << "Enter new borrow limit: ";
                cin >> changedLimit;

                cout << "Borrow limit changed to " << changedLimit << endl;
            }
            else {
                cout << "This member has no overdue books" << endl;
            }
        };

        void adminInterface(Members& member2) {
            int optionNumber = 0;

            while (optionNumber != 4) {
                cout << "1. == Admin Options ==" << endl;
                cout << "1. Add User" << endl;
                cout << "2. Remove User" << endl;
                cout << "3. Add penalties" << endl;
                cout << "4. Exit" << endl;
                cout << "Select: ";
                cin >> optionNumber;

                if (optionNumber == 1) {
                    Users u;
                    addUser(u);
                }
                else if (optionNumber == 2) {
                    removeUser();
                }
                else if (optionNumber == 3) {
                    changeBorrowLimit(member2);
                }
            }
        }
    };

    int main() {

        // Users Objects 
        Members member1;
        member1.setLogin("member", "pword1");

        Members member2;
        member2.borrowNumber = 3;
        member2.overdueBooks = "Book5";
        member2.isBookReturned = false;

        Members member3;
        member3.borrowNumber = 5;

        Librarians librarian1;
        librarian1.setLogin("librarian", "pword2");

        Administrators admin1;
        admin1.setLogin("admin", "pword3");

        // Books arrays
        books[0].getBook("Book1", "Book Author", "Available");
        books[1].getBook("Book2", "Book Author", "Available");
        books[2].getBook("Book3", "Book Author", "Available");
        books[3].getBook("Book4", "Book Author", "Available");
        books[4].getBook("Book5", "Book Author", "Available");
        books[5].getBook("Book6", "Book Author", "Available");
        books[6].getBook("Book7", "Book Author", "Borrowed");

        // Audio Books
        audiobooks[0].getBook("AudioBook1", "Audio Author", "Coming Soon");
        audiobooks[1].getBook("AudioBook2", "Audio Author", "Coming Soon");
        audiobooks[2].getBook("AudioBook3", "Audio Author", "Coming Soon");
        audiobooks[3].getBook("AudioBook4", "Audio Author", "Coming Soon");

        audioBookCount = 4;
        bookCount = 7;

        // Login Procedure
        string name, pass;
        cout << "== Smart Library System ==" << endl;
        cout << "Enter Your Account Name: ";
        cin >> name;

        cout << "Enter Your Password: ";
        cin >> pass;

        try {

            if (member1.Login(name, pass)) {
                member1.memberInterface();
            }

            else if (librarian1.Login(name, pass)) {
                librarian1.librarianInterface(member2, member3);
            }

            else if (admin1.Login(name, pass)) {
                admin1.adminInterface(member2);
            }

            else {
                throw  "Login Failed";
            }
        }
        catch (const char* msg) {
            cout << "Error: " << msg << endl;
        }
    }
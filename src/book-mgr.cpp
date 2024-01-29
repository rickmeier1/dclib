#include "book-mgr.h"
#include <iostream>

using namespace std;

BookManager::BookManager() {
    books.clear();
    loadBooks();
}

void BookManager::loadBooks() {
    auto book1 = shared_ptr<BookInfo>(BookInfo::create("Harry Potter and the Philosopher's Stone", "J.K. Rowling"));
    addBook(book1);
}

BookManager &BookManager::getInstance() {
    static BookManager instance;
    return instance;
}

vector<shared_ptr<BookInfo>> BookManager::getBooks() {
    vector<shared_ptr<BookInfo>> list;
    for (auto &book : books) {
        list.push_back(book.second);
    }
    return list;
}

shared_ptr<BookInfo> BookManager::getBookByTitle(string title) {
    auto book = books[title];
    return book;
}

bool BookManager::addBook(shared_ptr<BookInfo> book) {
    books[book->getTitle()] = book;
    return true;
};

bool BookManager::removeBook(string title) {
    auto pos = books.find(title);
    if (pos == books.end()) {
        return false;
    }
    books.erase(pos);
    return true;
};

bool BookManager::updateBook(std::string lookupTitle, const std::string *title, const std::string *author, const std::string *summary, const std::string *isbn) {
    auto pos = books.find(lookupTitle);
    if (pos == books.end()) {
        return false;
    }
    auto book = pos->second;
    books.erase(pos);

    std::string oldSummary = book->getSummary();
    std::string oldISBN = book->getISBN();
    auto newBookInfo = shared_ptr<BookInfo>(BookInfo::create(title?*title:book->getTitle(), author?*author:book->getAuthor(), summary?summary:&oldSummary, isbn?isbn:&oldISBN));
    books[newBookInfo->getTitle()] = book;

    return true;
};

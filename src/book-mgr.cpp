#include "book-mgr.h"
#include <iostream>

using namespace std;

BookManager::BookManager() {
    books.clear();
    loadBooks();
}

void BookManager::loadBooks() {
    cerr << "BookManager::loadBooks unimplemented" << endl;
}

BookManager &BookManager::getInstance() {
    static BookManager instance;
    return instance;
}


vector<shared_ptr<BookInfo>> BookManager::getBooks() {
    cerr << "BookManager::getBooks unimplemented" << endl;
    return vector<shared_ptr<BookInfo>>();
}

shared_ptr<BookInfo> BookManager::getBookByTitle(string title) {
    cerr << "BookManager::getBookByTitle unimplemented" << endl;
    return nullptr;
}

bool BookManager::addBook(shared_ptr<BookInfo> book) {
    cerr << "BookManager::addBook unimplemented" << endl;
    return false;
};

bool BookManager::removeBook(string title) {
    cerr << "BookManager::removeBook unimplemented" << endl;
    return false;
};

bool BookManager::updateBook(std::string lookupTitle, const std::string *title, const std::string *author, const std::string *summary, const std::string *isbn) {
    cerr << "BookManager::updateBook unimplemented" << endl;
    return false;
};

#include "book-mgr.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
 
using namespace std;
 
using namespace rapidjson;
using namespace std;

const char *kBookPath = "books.json";

BookManager::BookManager() {
    books.clear();
    loadBooks();
}
BookManager::~BookManager() {
    if (modified) {
        saveBooks();
    }
}

void BookManager::loadBooks() {
    ifstream ifs(kBookPath);
    IStreamWrapper isw(ifs);
    
    Document d;
    d.ParseStream(isw);
    if (d.IsArray()) {
        for (Value::ConstValueIterator itr = d.Begin(); itr != d.End(); ++itr) {
            auto summary = itr->GetObject().HasMember("summary") ? itr->GetObject()["summary"].GetString() : "";
            auto isbn = itr->GetObject().HasMember("isbn") ? itr->GetObject()["isbn"].GetString() : "";
            auto book = shared_ptr<BookInfo>(BookInfo::create(itr->GetObject()["title"].GetString(), itr->GetObject()["author"].GetString(), summary, isbn));
            addBook(book);
        }
    }
}

void BookManager::saveBooks() {
    if (books.empty()) {
        filesystem::remove(kBookPath);
        return;
    }

    // JSON Doc
    Document d;
    d.SetArray();

    // Iterate over books
    for (auto &book : books) {
        Value b(kObjectType);
        Value t(kStringType);
        Value a(kStringType);
        Value s(kStringType);
        Value i(kStringType);
        t.SetString(book.second->getTitle(), d.GetAllocator());
        a.SetString(book.second->getAuthor(), d.GetAllocator());
        s.SetString(book.second->getSummary(), d.GetAllocator());
        i.SetString(book.second->getISBN(), d.GetAllocator());
        b.AddMember("title", t, d.GetAllocator());
        b.AddMember("author", a, d.GetAllocator());
        b.AddMember("summary", s, d.GetAllocator());
        b.AddMember("isbn", i, d.GetAllocator());
        d.PushBack(b, d.GetAllocator());
    }

    ofstream ofs(kBookPath);
    OStreamWrapper osw(ofs);
    
    Writer<OStreamWrapper> writer(osw);
    d.Accept(writer);
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

shared_ptr<BookInfo> BookManager::getBookByTitle(const char *pTitle) {
    string title = pTitle;
    auto book = books[title];
    return book;
}

bool BookManager::addBook(shared_ptr<BookInfo> book) {
    books[book->getTitle()] = book;
    modified = true;
    return true;
};

bool BookManager::removeBook(const char *pTitle) {
    string title = pTitle;
    auto pos = books.find(title);
    if (pos == books.end()) {
        return false;
    }
    books.erase(pos);
    modified = true;
    return true;
};

bool BookManager::updateBook(const char *pTitle, const char *pNewTitle, const char *pNewAuthor, const char *pNewSummary, const char *pNewISBN) {
    string title = pTitle;
    auto pos = books.find(title);
    if (pos == books.end()) {
        return false;
    }
    auto book = pos->second;
    books.erase(pos);

    auto newBookInfo = shared_ptr<BookInfo>(BookInfo::create(pNewTitle?pNewTitle:book->getTitle(), pNewAuthor?pNewAuthor:book->getAuthor(), pNewSummary?pNewSummary:book->getSummary(), pNewISBN?pNewISBN:book->getISBN()));
    books[newBookInfo->getTitle()] = book;

    modified = true;
    return true;
};

#include "book-info.h"
#include <memory>
#include <map>

#pragma once

class BookManager {
private:
    std::map<std::string, std::shared_ptr<BookInfo>> books;

    BookManager();

    void loadBooks();

public:
    static BookManager &getInstance();

    std::vector<std::shared_ptr<BookInfo>> getBooks();
    std::shared_ptr<BookInfo> getBookByTitle(std::string title);

    bool addBook(std::shared_ptr<BookInfo> book);
    bool removeBook(std::string title);
    bool updateBook(std::string lookupTitle, const std::string *title=nullptr, const std::string *author=nullptr, const std::string *summary=nullptr, const std::string *isbn=nullptr);
};
#include "book-info.h"
#include <memory>
#include <map>

#pragma once

class BookManager {
private:
    std::map<std::string, std::shared_ptr<BookInfo>> books;
    bool modified = false;

    BookManager();
    ~BookManager();

    void loadBooks();
    void saveBooks();

public:
    static BookManager &getInstance();

    std::vector<std::shared_ptr<BookInfo>> getBooks();
    std::shared_ptr<BookInfo> getBookByTitle(const char *pTitle);

    bool addBook(std::shared_ptr<BookInfo> book);
    bool removeBook(const char *pTitle);
    bool updateBook(const char *pTitle, const char *pNewTitle=nullptr, const char *pNewAuthor=nullptr, const char *pNewSummary=nullptr, const char *pNewISBN=nullptr);
};
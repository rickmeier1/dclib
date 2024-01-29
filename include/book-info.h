#include <string>
#pragma once
class BookInfo {
    private:
        std::string title;
        std::string summary;
        std::string author;
        std::string isbn;

        BookInfo(std::string title, std::string author, std::string summary, std::string isbn);

    public:
        std::string getTitle();
        std::string getSummary();
        std::string getAuthor();
        std::string getISBN();

        static BookInfo* create(std::string title, std::string author, const std::string *pSummary=nullptr, const std::string *pISBN=nullptr);
};
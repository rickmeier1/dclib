#include <string>
#pragma once
class BookInfo {
    private:
        std::string title;
        std::string summary;
        std::string author;
        std::string isbn;

        BookInfo(const char *pTitle, const char *pAuthor, const char *pSummary, const char *pISBN);

    public:
        const char *getTitle() {
            return title.c_str();
        }
        const char *getSummary() {
            return summary.c_str();
        }
        const char *getAuthor() {
            return author.c_str();
        }
        const char *getISBN() {
            return isbn.c_str();
        }

        static BookInfo* create(const char *pTitle, const char *pAuthor, const char *pSummary=nullptr, const char *pISBN=nullptr);
};
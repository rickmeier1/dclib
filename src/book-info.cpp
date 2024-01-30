#include "book-info.h"
#include <string>

using namespace std;

BookInfo* BookInfo::create(const char *pTitle, const char *pAuthor, const char *pSummary, const char *pISBN) {
    if (pTitle == nullptr || *pTitle == '\0' || pAuthor == nullptr || *pAuthor == '\0') {
        return  nullptr;
    }

    return new BookInfo(pTitle, pAuthor, pSummary, pISBN);
}

BookInfo::BookInfo(const char *pTitle, const char *pAuthor, const char *pSummary, const char *pISBN) {
    this->title = pTitle;
    this->author = pAuthor;
    this->summary = pSummary?pSummary:"";
    this->isbn = pISBN?pISBN:"";
}

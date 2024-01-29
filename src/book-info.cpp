#include "book-info.h"
#include <string>

using namespace std;

BookInfo* BookInfo::create(string title, string author, string summary, string isbn) {
    return new BookInfo(title, author, summary, isbn);
}

BookInfo::BookInfo(string title, string author, string summary, string isbn) {
    this->title = title;
    this->author = author;
    this->summary = summary;
    this->isbn = isbn;
}

string BookInfo::getTitle() {
    return title;
}

string BookInfo::getAuthor() {
    return author;
}
string BookInfo::getSummary() {
    return summary;
}
string BookInfo::getISBN() {
    return isbn;
}
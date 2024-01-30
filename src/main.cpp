#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "book-info.h"
#include "cxxopts.hpp"
#include "book-mgr.h"

using namespace std;

bool handleOptions(cxxopts::ParseResult &result);

struct BookValues {
    string title;
    string author;
    string summary;
    string isbn;

    BookValues(cxxopts::ParseResult &result) {
        title = result.count("title") ? result["title"].as<string>() : "";
        author = result.count("author") ? result["author"].as<string>() : "";
        summary = result.count("summary") ? result["summary"].as<string>() : "";
        isbn = result.count("isbn") ? result["isbn"].as<string>() : "";
    }
};

int main(int argc, char const **argv) {
    cxxopts::Options options("dclib", "Fledgling book inventory tool");
    options.add_options("main")
        ("l,list", "List books in library")
        ("c,create", "Create a new book, see create options [-t,-a required]")
        ("r,retrieve", "Retrieve info on a book", cxxopts::value<string>(), "title")
        ("u,update", "Update a book, use create options -t,-a,-s,-i to indicate update fields",cxxopts::value<string>(), "title")
        ("d,delete", "Delete a book", cxxopts::value<string>(), "title");
    options.add_options("create")
        ("t,title", "Book title", cxxopts::value<string>(), "title")
        ("a,author", "Book author", cxxopts::value<string>(), "author")
        ("s,summary", "Book summary", cxxopts::value<string>(), "summary")
        ("i,isbn", "Book ISBN", cxxopts::value<string>(), "isbn");
    vector<string> allOptions = {"main","create"};

    try {
        auto result = options.parse(argc, argv);
        if (!handleOptions(result)) {
            std::cout << options.help(allOptions) << endl;
        }
    } catch (const cxxopts::exceptions::parsing &e) {
        std::cerr << "Error: " << e.what() << endl << endl;
        std::cout << options.help(allOptions) << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool handleOptions(cxxopts::ParseResult &result) {
    BookManager &bm = BookManager::getInstance();

    if (result.count("list")) {
        auto books = bm.getBooks();
        for (auto &book : books) {
            cout << book->getTitle() << " by " << book->getAuthor() << endl;
        }
        return true;
    }

    if (result.count("create")) {
        if (!result.count("title") && !result.count("author")) {
            cerr << "Error: title and author required" << endl;
            return false;
        }

        BookValues bookValues(result);
        shared_ptr<BookInfo> book(BookInfo::create(bookValues.title.c_str(), bookValues.author.c_str(), bookValues.summary.c_str(), bookValues.isbn.c_str()));

        if (!bm.addBook(book)) {
            cerr << bookValues.title << " not found" << endl;
            return false;
        }

        cerr << bookValues.title << " added" << endl;
        return true;
    }

    if (result.count("retrieve")) {
        auto title = result["retrieve"].as<string>();
        auto book = bm.getBookByTitle(title.c_str());
        if (!book) {
            cerr << title << " not found" << endl;
            return false;
        }
        cout << "Title: " << book->getTitle() << endl;
        cout << "Author: " << book->getAuthor() << endl;
        cout << "Summary: " << book->getSummary() << endl;
        cout << "ISBN: " << book->getISBN() << endl;

        return true;
    }

    if (result.count("update")) {
        if (!result.count("title") || !result.count("author") || !result.count("summary") || !result.count("ISBN")) {
            cerr << "Error: title, author, summary or ISBN required for update" << endl;
            return false;
        }
        auto title = result["update"].as<string>();
        BookValues bookValues(result);

        if (!bm.updateBook(title.c_str(), bookValues.title.c_str(), bookValues.author.c_str(), bookValues.summary.c_str(), bookValues.isbn.c_str())) {
            cerr << title << " not found" << endl;
            return false;
        }

        cout << title << " updated" << endl;
        return true;
    }

    if (result.count("delete")) {
        auto title = result["delete"].as<string>();
        if (!bm.removeBook(title.c_str())) {
            cerr << title << " not found" << endl;
            return false;
        }

        cout << title << " removed" << endl;
        return true;
    }

    return false;
}
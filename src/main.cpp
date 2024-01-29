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
    const string *pTitle;
    const string *pAuthor;
    const string *pSummary;
    const string *pISBN;

    BookValues(cxxopts::ParseResult &result) {
        pTitle = result.count("title") ? &result["title"].as<string>() : nullptr;
        pAuthor = result.count("author") ? &result["author"].as<string>() : nullptr;
        pSummary = result.count("summary") ? &result["summary"].as<string>() : nullptr;
        pISBN = result.count("isbn") ? &result["isbn"].as<string>() : nullptr;
    }
};

int main(int argc, char const **argv) {
    cxxopts::Options options("dclib", "Fledgling book inventory tool");
    options.add_options("main")
        ("l,list", "List books in library")
        ("c,create", "Create a new book, see create options [-t,-a required]")
        ("r,retrieve", "Retrieve info on a book [title]", cxxopts::value<string>())
        ("u,update", "Update a book [title], use -t,-a,-s,-i for updated fields",cxxopts::value<string>())
        ("d,delete", "Delete a book [title]", cxxopts::value<string>());
    options.add_options("create")
        ("t,title", "Book title", cxxopts::value<string>())
        ("a,author", "Book author", cxxopts::value<string>())
        ("s,summary", "Book summary", cxxopts::value<string>())
        ("i,isbn", "Book ISBN", cxxopts::value<string>());
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

    auto book1 = shared_ptr<BookInfo>(BookInfo::create("Harry Potter and the Philosopher's Stone", "J.K. Rowling"));
    bm.addBook(book1);

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
        shared_ptr<BookInfo> book(BookInfo::create(*bookValues.pTitle, *bookValues.pAuthor, bookValues.pSummary, bookValues.pISBN));

        if (!bm.addBook(book)) {
            cerr << *bookValues.pTitle << " not found" << endl;
            return false;
        }

        cerr << *bookValues.pTitle << " added" << endl;
        return true;
    }

    if (result.count("retrieve")) {
        auto title = result["opt"].as<string>();
        auto book = bm.getBookByTitle(title);
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
        auto title = result["opt"].as<string>();
        BookValues bookValues(result);

        if (!bm.updateBook(title, bookValues.pTitle, bookValues.pAuthor, bookValues.pSummary, bookValues.pISBN)) {
            cerr << title << " not found" << endl;
            return false;
        }

        cout << title << " updated" << endl;
        return true;
    }

    if (result.count("delete")) {
        if (!result.count("title") && !result.count("author")) {
            cerr << "Error: title and author required" << endl;
            return false;
        }

        auto title = result["opt"].as<string>();
        if (!bm.removeBook(title)) {
            cerr << title << " not found" << endl;
            return false;
        }

        cout << title << " removed" << endl;
        return true;
    }

    return false;
}
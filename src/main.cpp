#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "book-info.h"

using namespace std;

int main() {
    auto book1 = unique_ptr<BookInfo>(BookInfo::create("Harry Potter and the Philosopher's Stone", "J.K. Rowling"));
    cout << "Book1: " << book1->getTitle() << endl;
}

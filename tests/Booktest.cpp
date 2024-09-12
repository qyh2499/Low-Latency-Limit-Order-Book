#include <iostream>
#include "../order_book/Book.hpp"

int main(int argc, const char * argv[]) {
    Book book;
    book.addLimitOrder(0, 1, 100, 10);
    book.addLimitOrder(0, 1, 100, 5);
    book.addLimitOrder(0, 1, 100, 15);

    book.addLimitOrder(0, 0, 50, 5);
    book.addLimitOrder(0, 0, 150, 10);
    book.addLimitOrder(0, 0, 50, 20);

    book.printOrderBook();
    return 0;
}

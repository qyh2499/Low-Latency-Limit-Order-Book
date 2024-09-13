#include <iostream>
#include "../order_book/Book.hpp"

int main(int argc, const char * argv[]) {
    Book book;
    book.addLimitOrder(0, 1, 100, 10);
    book.printOrderBook();

    book.addLimitOrder(1, 0, 100, 5);
    book.printOrderBook();

    return 0;
}

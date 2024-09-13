#include <iostream>
#include "../order_book/Book.hpp"

int main(int argc, const char * argv[]) {
    Book book;
    book.addLimitOrder(0, 1, 100, 100);
    book.addLimitOrder(1, 1, 50, 100);
    book.addLimitOrder(2, 1, 25, 50);
    book.printOrderBook();

    book.cancelLimitOrder(0);
    book.cancelLimitOrder(1);
    book.printOrderBook();

    book.cancelLimitOrder(2);
    book.printOrderBook();

    book.addLimitOrder(1, 1, 100, 5);
    book.addLimitOrder(2, 1, 100, 15);

    book.addLimitOrder(3, 0, 50, 5);
    book.addLimitOrder(4, 0, 150, 10);
    book.addLimitOrder(5, 0, 50, 20);
    book.addLimitOrder(6, 0, 100, 30);
    book.addLimitOrder(7, 0, 50, 5);
    book.addLimitOrder(8, 0, 150, 10);
    book.addLimitOrder(9, 0, 50, 20);
    book.addLimitOrder(10, 0, 100, 30);
    book.printOrderBook();

    book.addMarketOrder(7, 1, 60);
    book.printOrderBook();

    return 0;
}

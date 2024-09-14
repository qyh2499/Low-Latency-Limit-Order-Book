#ifndef ORDERGENERATOR_HPP
#define ORDERGENERATOR_HPP

#include "../order_book/Book.hpp"
#include "../order_book/Limit.hpp"
#include "../order_book/Order.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <algorithm>
#include <functional>
#include <numeric>

class Book;

class OrderGenerator
{

private:
    Book *book;
    int orderId = 1;
    std::ofstream file;

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen;

    void createMarketOrder();
    void createLimitOrder();
    void cancelLimitOrder();
    void createLimitInMarket();

public:
    OrderGenerator(Book *book);
    void randomInitialOrders(const std::string &filePath, int numberOfOrders, int centreOfBook);
    void randomOrders(const std::string &filePath, int numberOfOrders);
};


#endif
#ifndef ORDERPROCESSTIMER_HPP
#define ORDERPROCESSTIMER_HPP

#include "../order_book/Book.hpp"
#include <string>
#include <unordered_map>
#include <string_view>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

class Book;

class OrderProcessTimer
{
private:
    Book *book;

    using OrderFunction = void (OrderProcessTimer::*)(std::istringstream &);
    std::unordered_map<std::string_view, OrderFunction> orderFunctions;

    void loadMarketOrder(std::istringstream &iss);
    void loadAddLimitOrder(std::istringstream &iss);
    void loadCancelLimitOrder(std::istringstream &iss);

public:
    OrderProcessTimer(Book *book);
    void loadOrdersFromFile(const std::string &inputFile, const std::string &outputFile);
};


#endif
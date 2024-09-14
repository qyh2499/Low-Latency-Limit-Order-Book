#include "./order_generator/orderGenerator.hpp"
#include "./order_generator/orderProcessTimer.hpp"
#include <iostream>
#include <vector>
#include <chrono>

int main()
{
    Book *book = new Book();
    OrderGenerator orderGenerator(book);
    OrderProcessTimer orderProcessTimer(book);

    // Create the initial ones
    // orderGenerator.randomInitialOrders("C:/Users/johnh/PROJECTS/Limit-Order-Book/data/initialRandomOrders.txt", 10000, 500);
    
    // // Measures time
    auto start = std::chrono::high_resolution_clock::now();
    orderProcessTimer.loadOrdersFromFile("C:/Users/johnh/PROJECTS/Limit-Order-Book/data/initialRandomOrders.txt",
                                         "C:/Users/johnh/PROJECTS/Limit-Order-Book/data/initialPerformance.txt");
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cerr << "Total Time for Initial Orders: " << duration.count() << " ms" << std::endl;
    
    // book->printOrderBook();
    // book->cancelLimitOrder(998);

    // Create more orders
    // orderGenerator.randomOrders("C:/Users/johnh/PROJECTS/Limit-Order-Book/data/randomOrders.txt", 10000000);

    // // // Measures time
    start = std::chrono::high_resolution_clock::now();
    orderProcessTimer.loadOrdersFromFile("C:/Users/johnh/PROJECTS/Limit-Order-Book/data/randomOrders.txt",
                                         "C:/Users/johnh/PROJECTS/Limit-Order-Book/data/performance.txt");
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cerr << "Total Time to Process Orders: " << duration.count() << " ms" << std::endl;

    delete book;
    return 0;
}
#ifndef BOOK_HPP
#define BOOK_HPP

#include "../AVL/AVLTree.hpp"
#include "Order.hpp"
#include "Limit.hpp"
#include <random>
#include <unordered_map>

class Limit;
class Order;

class Book
{
private:
    AVLTree<Limit> *buyTree;
    AVLTree<Limit> *sellTree;
    std::unordered_map<int, Order *> orderMap;

    void insertLimit(int limitPrice, bool buyOrSell);
    void deleteLimit(int limitPrice, bool buyOrSell);
    void processMarketOrder(int orderId, bool buyOrSell, int shares);
    int processLimitOrderInMarket(int orderId, bool buyOrSell, int shares, int limitPrice);

public:
    Book();
    ~Book();

    // Counts used in order book perforamce visualisations
    int executedOrdersCount = 0;
    int AVLTreeBalanceCount = 0;

    // Getter and setter functions
    AVLTree<Limit> *getBuyTree() const;
    AVLTree<Limit> *getSellTree() const;
    AVLTreeNode<Limit> *getLowestSell() const;
    AVLTreeNode<Limit> *getHighestBuy() const;

    // Functions for different types of orders
    void addMarketOrder(int orderId, bool buyOrSell, int shares);
    void addLimitOrder(int orderId, bool buyOrSell, int shares, int limitPrice);
    void cancelLimitOrder(int orderId);

    // Functions that needed to be public for testing purposes
    Order *searchOrderMap(int orderId) const;
    AVLTreeNode<Limit> *searchLimitMaps(int limitPrice, bool buyOrSell) const;
    Order *getRandomOrder(std::mt19937 gen) const;

    // Functions for visualising the order book
    void printBookEdges() const;
    void printOrderBook() const;
};

#endif
#include "Book.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>

Book::Book() : buyTree(new AVLTree<Limit>()), sellTree(new AVLTree<Limit>())
{
}

Book::~Book()
{
    for (auto &[id, order] : orderMap)
    {
        delete order;
    }
    orderMap.clear();
}

// PRIVATE FUNCTIONS
void Book::insertLimit(int limitPrice, bool buyOrSell)
{
    auto &tree = buyOrSell ? buyTree : sellTree;
    tree->insert(limitPrice, Limit(limitPrice, buyOrSell));
}

void Book::deleteLimit(int limitPrice, bool buyOrSell)
{
    auto &tree = buyOrSell ? buyTree : sellTree;
    tree->remove(limitPrice);
}

// PUBLIC FUNCTIONS
AVLTree<Limit> *Book::getBuyTree() const
{
    return buyTree;
}

AVLTree<Limit> *Book::getSellTree() const
{
    return sellTree;
}

AVLTreeNode<Limit> *Book::getLowestSell() const
{
    return sellTree->getMinNode();
}

AVLTreeNode<Limit> *Book::getHighestBuy() const
{
    return buyTree->getMaxNode();
}

void Book::addLimitOrder(int orderId, bool buyOrSell, int shares, int limitPrice)
{
    AVLTreeBalanceCount = 0;

    if (shares != 0)
    {
        // Create new order
        Order *newOrder = new Order(orderId, buyOrSell, shares, limitPrice);
        orderMap.emplace(orderId, newOrder);

        // Insert limit (if not exist) and insert order
        insertLimit(limitPrice, buyOrSell);
        auto &tree = buyOrSell ? buyTree : sellTree;
        ((tree->find(limitPrice))->value).append(newOrder);
    }
}

void Book::cancelLimitOrder(int orderId)
{
    executedOrdersCount = 0;
    AVLTreeBalanceCount = 0;
    Order *order = searchOrderMap(orderId);

    if (order != nullptr)
    {
        order->remove();
        if (order->getParentLimit()->getSize() == 0)
        {
            deleteLimit(order->getLimit(), order->getBuyOrSell());
        }
        orderMap.erase(orderId);
        delete order;
    }
}

// Search the order map to find an order
Order *Book::searchOrderMap(int orderId) const
{
    auto it = orderMap.find(orderId);
    if (it != orderMap.end())
    {
        return it->second;
    }
    else
    {
        std::cout << "No order number " << orderId << std::endl;
        return nullptr;
    }
}

// Search the limit maps to find a limit
AVLTreeNode<Limit> *Book::searchLimitMaps(int limitPrice, bool buyOrSell) const
{
    auto &tree = buyOrSell ? buyTree : sellTree;
    auto it = tree->find(limitPrice);
    if (it == nullptr)
    {
        std::cout << "No " << (buyOrSell ? "buy " : "sell ") << "limit at " << limitPrice << std::endl;
    }
    return it;
}

void Book::printBookEdges() const
{
    std::cout << "Buy edge: " << getHighestBuy()->value.getLimitPrice()
              << "Sell edge: " << getLowestSell()->value.getLimitPrice() << std::endl;
}

// Print out all the limit and stop levels and their liquidity
void Book::printOrderBook() const
{
    std::cout << "BUY TREE:" << std::endl;
    buyTree->display();
    std::cout << "SELL TREE:" << std::endl;
    sellTree->display();    
}

#include "Limit.hpp"
#include "Order.hpp"
#include <iostream>

Limit::Limit(int limitPrice, bool buyOrSell, int size, int totalVolume)
    : limitPrice(limitPrice), buyOrSell(buyOrSell), size(size), totalVolume(totalVolume),
      headOrder(nullptr), tailOrder(nullptr) {}

Limit::~Limit(){}

Order *Limit::getHeadOrder() const
{
    return headOrder;
}

int Limit::getLimitPrice() const
{
    return limitPrice;
}

int Limit::getSize() const
{
    return size;
}

int Limit::getTotalVolume() const
{
    return totalVolume;
}

bool Limit::getBuyOrSell() const
{
    return buyOrSell;
}

Limit *Limit::getParent() const
{
    return parent;
}

Limit *Limit::getLeftChild() const
{
    return leftChild;
}

Limit *Limit::getRightChild() const
{
    return rightChild;
}

void Limit::setParent(Limit *newParent)
{
    parent = newParent;
}

void Limit::setLeftChild(Limit *newLeftChild)
{
    leftChild = newLeftChild;
}

void Limit::setRightChild(Limit *newRightChild)
{
    rightChild = newRightChild;
}

void Limit::partiallyFillTotalVolume(int orderedShares)
{
    totalVolume -= orderedShares;
}

// Add an order to the limit
void Limit::append(Order *order)
{
    if (headOrder == nullptr)
    {
        headOrder = tailOrder = order;
    }
    else
    {
        tailOrder->nextOrder = order;
        order->prevOrder = tailOrder;
        order->nextOrder = nullptr;
        tailOrder = order;
    }
    size += 1;
    totalVolume += order->getShares();
    order->parentLimit = this;
}

void Limit::printForward() const
{
    Order *current = headOrder;
    while (current != nullptr)
    {
        std::cout << current->getOrderId() << " ";
        current = current->nextOrder;
    }
    std::cout << std::endl;
}

void Limit::printBackward() const
{
    Order *current = tailOrder;
    while (current != nullptr)
    {
        std::cout << current->getOrderId() << " ";
        current = current->prevOrder;
    }
    std::cout << std::endl;
}

void Limit::print() const
{
    std::cout << "Limit Price: " << limitPrice
              << ", Limit Volume: " << totalVolume
              << ", Limit Size: " << size
              << std::endl;
}
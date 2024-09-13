#include "Limit.hpp"
#include "Order.hpp"
#include <iostream>

Limit::Limit(int limitPrice, bool buyOrSell, int size, int totalVolume)
    : limitPrice(limitPrice), buyOrSell(buyOrSell), size(size), totalVolume(totalVolume), headOrder(nullptr), tailOrder(nullptr) {}

Limit::~Limit() {}

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

void Limit::partiallyFillVolume(int orderShares) {
    totalVolume -= orderShares;
}


void Limit::printOrders() const
{
    Order *current = headOrder;
    while (current != nullptr)
    {
        std::cout << current->getIdNumber() << " ";
        current = current->nextOrder;
    }
    std::cout << std::endl;
}

void Limit::printInfoString() const
{
    std::cout << "Price: " << limitPrice
              << ", Volume: " << totalVolume
              << ", Size: " << size;
}

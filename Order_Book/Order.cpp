#include "Order.hpp"
#include "Limit.hpp"

Order::Order(int idNumber, bool buyOrSell, int shares, int limit, int entryTime, int eventTime)
    : idNumber(idNumber),
      buyOrSell(buyOrSell),
      shares(shares),
      limit(limit),
      entryTime(entryTime),
      eventTime(eventTime),
      nextOrder(nullptr),
      prevOrder(nullptr),
      parentLimit(nullptr)
{
}

int Order::getIdNumber() const
{
    return idNumber;
}

int Order::getShares() const
{
    return shares;
}

int Order::getLimit() const
{
    return limit;
}

bool Order::getBuyOrSell() const
{
    return buyOrSell;
}

Limit *Order::getParentLimit() const
{
    return parentLimit;
}

// Process the order
void Order::process()
{
    // The order must be the head order, ignore if not
    if (!prevOrder)
    {
        if (nextOrder == nullptr)
        {
            parentLimit->headOrder = nullptr;
            parentLimit->tailOrder = nullptr;
        }
        else
        {
            parentLimit->headOrder = nextOrder;
            nextOrder->prevOrder = nullptr;
        }

        // Remove counts in parantLimit
        parentLimit->size -= 1;
        parentLimit->totalVolume -= shares;
    }
}

// Remove the order
void Order::remove()
{
    if (prevOrder == nullptr) // This is the headOrder
    {
        parentLimit->headOrder = nextOrder;
    }
    else
    {
        prevOrder->nextOrder = nextOrder;
    }
    if (nextOrder == nullptr) // This is the tailOrder
    {
        parentLimit->tailOrder = prevOrder;
    }
    else
    {
        nextOrder->prevOrder = prevOrder;
    }

    // Remove counts in parantLimit
    parentLimit->size -= 1;
    parentLimit->totalVolume -= shares;
}


void Order::partiallyFillOrder(int orderShares) {
    shares -= orderShares;
    parentLimit->partiallyFillVolume(orderShares);
}

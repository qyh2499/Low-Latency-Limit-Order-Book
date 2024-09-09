#include "Order.hpp"
#include "Limit.hpp"

Order::Order(int _idNumber, bool _buyOrSell, int _shares, int _limit, int _entryTime, int _eventTime)
    : idNumber(_idNumber),
      buyOrSell(_buyOrSell),
      shares(_shares),
      limit(_limit),
      entryTime(_entryTime),
      eventTime(_eventTime),
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
    if (!prevOrder) // This is the headOrder
    {
        parentLimit->headOrder = nextOrder;
    }
    else
    {
        prevOrder->nextOrder = nextOrder;
    }
    if (!nextOrder) // This is the tailOrder
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

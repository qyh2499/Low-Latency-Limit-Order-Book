#ifndef ORDER_HPP
#define ORDER_HPP

class Limit;

class Order
{

private:
    int idNumber;
    bool buyOrSell;
    int shares;
    int limit;
    int entryTime;
    int eventTime;
    Order *nextOrder;
    Order *prevOrder;
    Limit *parentLimit;

    friend class Limit;

public:
    Order(int _idNumber, bool _buyOrSell, int _shares, int _limit, int _entryTime, int _eventTime);

    int getIdNumber() const;
    int getShares() const;
    int getLimit() const;
    int getEntryTime() const;
    int getEventTime() const;
    bool getBuyOrSell() const;
    Limit *getParentLimit() const;

    void process();
    void remove();
};

#endif
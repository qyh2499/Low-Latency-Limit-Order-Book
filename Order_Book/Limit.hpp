#ifndef LIMIT_HPP
#define LIMIT_HPP

class Order;

class Limit
{

private:
    int limitPrice;
    int size;
    int totalVolume;
    bool buyOrSell;
    Order *headOrder;
    Order *tailOrder;

    friend class Order;

public:
    Limit(int limitPrice, bool buyOrSell, int size = 0, int totalVolume = 0);
    ~Limit();

    Order *getHeadOrder() const;
    int getLimitPrice() const;
    int getSize() const;
    int getTotalVolume() const;
    bool getBuyOrSell() const;

    void append(Order *_order);

    void printOrders() const;
    void printInfoString() const;
};



#endif
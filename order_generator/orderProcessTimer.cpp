#include "orderProcessTimer.hpp"

void OrderProcessTimer::loadMarketOrder(std::istringstream &iss)
{
    int orderId, shares;
    bool buyOrSell;
    iss >> orderId >> buyOrSell >> shares;
    book->addMarketOrder(orderId, buyOrSell, shares);
}

void OrderProcessTimer::loadAddLimitOrder(std::istringstream &iss)
{
    int orderId, shares, limitPrice;
    bool buyOrSell;
    iss >> orderId >> buyOrSell >> shares >> limitPrice;
    book->addLimitOrder(orderId, buyOrSell, shares, limitPrice);
}

void OrderProcessTimer::loadCancelLimitOrder(std::istringstream &iss)
{
    int orderId;
    iss >> orderId;
    book->cancelLimitOrder(orderId);
}

OrderProcessTimer::OrderProcessTimer(Book *book) : book(book)
{
    orderFunctions = {
        {"Market", &OrderProcessTimer::loadMarketOrder},
        {"AddLimit", &OrderProcessTimer::loadAddLimitOrder},
        {"CancelLimit", &OrderProcessTimer::loadCancelLimitOrder},
        {"AddLimitInMarket", &OrderProcessTimer::loadAddLimitOrder}
    };
}

void OrderProcessTimer::loadOrdersFromFile(const std::string &inputFile, const std::string &outputFile)
{
    std::ifstream file(inputFile);

    std::ofstream outFile(outputFile, std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening CSV file for writing." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string directive;
        iss >> directive;

        auto it = orderFunctions.find(directive);
        if (it != orderFunctions.end())
        {
            auto start = std::chrono::steady_clock::now();
            (this->*(it->second))(iss);
            auto end = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            outFile << directive << "," << duration.count() << "," << book->executedOrdersCount << "," << book->AVLTreeBalanceCount << std::endl;
        }
        else
        {
            std::cerr << "Unknown order type: " << directive << std::endl;
        }
    }
    file.close();
    outFile.close();
}

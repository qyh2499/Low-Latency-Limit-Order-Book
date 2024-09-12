# Low Latency Limit Order Book
Low latency limit order book in C++

Architecture:
```
Order
  int idNumber;
  bool buyOrSell;
  int shares;
  int limit;
  int entryTime;
  int eventTime;
  Order *nextOrder;
  Order *prevOrder;
  Limit *parentLimit;

Limit  // representing a single limit price
  int limitPrice;
  int size;
  int totalVolume;
  Limit *parent;
  Limit *leftChild;
  Limit *rightChild;
  Order *headOrder;
  Order *tailOrder;

Book
  Limit *buyTree;
  Limit *sellTree;
  Limit *lowestSell;
  Limit *highestBuy;
```


Primary Sources:
- [WK's High Frequency Trading Blog](https://web.archive.org/web/20110219163448/http://howtohft.wordpress.com/2011/02/15/how-to-build-a-fast-limit-order-book/)
- [Limit Order Book Implementation in Java](https://medium.com/@mhfizt/limit-order-book-implementation-in-java-dd39821e5a4f)
- [Efficient implementation of AVLTree (Modified)](https://github.com/KadirEmreOto/AVL-Tree/tree/master)
- [AVL Trees](https://kukuruku.co/hub/cpp/avl-trees)


# Low Latency Limit Order Book
Low latency limit order book in C++

### Architecture ([reference](https://web.archive.org/web/20110219163448/http://howtohft.wordpress.com/2011/02/15/how-to-build-a-fast-limit-order-book/)):
```
Order // Representing a single order
  int idNumber;
  bool buyOrSell;
  int shares;
  int limit;
  int entryTime;
  int eventTime;
  Order *nextOrder;
  Order *prevOrder;
  Limit *parentLimit;

Limit  // Representing a single limit price
  int limitPrice;
  int size;
  int totalVolume;
  bool buyOrSell;
  Order *headOrder;
  Order *tailOrder;

Book
  Limit *buyTree;
  Limit *sellTree;
```

The idea is to use a AVL tree of Limit objects ordered by limitPrice for each side (buy and sell) of the book. Each Limit object then contains a double-end linked list of Order objects, where the headOrder is the first order to arrive in the book.

**Using this structure, we expect the following performance on average time:**

```
Add Order – O(log M) for the first order to add the corresponding limit to the tree, O(1) otherwise
Cancel Order – O(1)
Execute Order – O(1)
GetVolumeAtLimit – O(1)
GetBestBid/Offer – O(1)
```

### Performance: Test Done with Intel i7-8565U CPU @ 1.80GHz

The timestamps (in nanoseconds) of each directive to the limit order book is recorded and the difference is noted as the latency of an directive.

![Latency Histogram](https://github.com/user-attachments/assets/b35d15dd-f2a2-47c6-928f-b6ae546248e2)\

![Order Type Latency](https://github.com/user-attachments/assets/9e867451-61e8-4c77-925c-d916c6e8e5f9)


### Primary Sources:
- [WK's High Frequency Trading Blog](https://web.archive.org/web/20110219163448/http://howtohft.wordpress.com/2011/02/15/how-to-build-a-fast-limit-order-book/)
- [Limit Order Book Implementation in Java](https://medium.com/@mhfizt/limit-order-book-implementation-in-java-dd39821e5a4f)
- [Efficient implementation of AVLTree (Modified)](https://github.com/KadirEmreOto/AVL-Tree/tree/master)
- [AVL Trees](https://kukuruku.co/hub/cpp/avl-trees)

Order generator and other code reference from: [GitHub](https://github.com/brprojects/Limit-Order-Book)

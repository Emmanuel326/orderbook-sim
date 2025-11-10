#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "order.h"

typedef struct PriceLevel {
    price_t price;
    quantity_t total_quantity;
    Order *head;
    Order *tail;
    struct PriceLevel *next;
    struct PriceLevel *prev;
} PriceLevel;

typedef struct {
    PriceLevel *bids; // descending linked list
    PriceLevel *asks; // ascending linked list
} OrderBook;

OrderBook *create_orderbook();
void destroy_orderbook(OrderBook *ob);
void orderbook_add_order(OrderBook *ob, Order *order);

#endif /* ORDERBOOK_H */

#ifndef ORDER_H
#define ORDER_H

#include "types.h"

typedef enum {
    SIDE_BUY,
    SIDE_SELL
} Side;

typedef struct Order {
    order_id_t id;
    price_t price;
    quantity_t quantity;
    Side side;
    int64_t timestamp;
    struct Order *next;
} Order;

Order *create_order(order_id_t id, price_t price, quantity_t quantity, Side side);
void destroy_order(Order *order);

#endif /* ORDER_H */

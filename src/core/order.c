#include <stdlib.h>

#include "order.h"
#include "utils/time.h"

Order *create_order(order_id_t id, price_t price, quantity_t quantity, Side side) {
    Order *order = (Order *) malloc(sizeof(Order));
    if (!order) {
        return NULL;
    }
    order->id = id;
    order->price = price;
    order->quantity = quantity;
    order->side = side;
    order->timestamp = get_timestamp_ns();
    order->next = NULL;
    return order;
}

void destroy_order(Order *order) {
    if (order) {
        free(order);
    }
}

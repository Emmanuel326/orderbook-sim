#ifndef ORDER_H
#define ORDER_H

#include "types.h" //Depend on the bsic types we defined in types.h

typedef struct {
    OrderID    order_id;
    Side       side;
    Quanitity  initial_quantity;
    Quantity   remaining_quantity;
    Timestamp  entry_time;
    //we will add User/Client ID and Instrument ID later on
} Order;


//create a new order
Order create_new_order(OrderID id, Side market_side, Price limit_price, Quantity size);

//update the remaining quantity after a trade
void update_order_fill(Order *the_order, Quantity filled_amount);

//check if order is fully executed
int is_order_fully_executed(const Order *the_order);

#endif /* ORDER_H */

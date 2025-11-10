#include <stdlib.h>

#include "orderbook.h"

// Static helper functions

static PriceLevel *create_price_level(price_t price) {
    PriceLevel *pl = (PriceLevel *) malloc(sizeof(PriceLevel));
    if (!pl) return NULL;
    pl->price = price;
    pl->total_quantity = 0;
    pl->head = NULL;
    pl->tail = NULL;
    pl->next = NULL;
    pl->prev = NULL;
    return pl;
}

static void price_level_add_order(PriceLevel *pl, Order *order) {
    if (pl->head == NULL) {
        pl->head = order;
        pl->tail = order;
    } else {
        pl->tail->next = order;
        pl->tail = order;
    }
    order->next = NULL;
    pl->total_quantity += order->quantity;
}

static void destroy_price_level(PriceLevel *pl) {
    Order *current_order = pl->head;
    while(current_order) {
        Order *next_order = current_order->next;
        destroy_order(current_order);
        current_order = next_order;
    }
    free(pl);
}

// Public functions

OrderBook *create_orderbook() {
    OrderBook *ob = (OrderBook *) malloc(sizeof(OrderBook));
    if (!ob) {
        return NULL;
    }
    ob->bids = NULL;
    ob->asks = NULL;
    return ob;
}

void destroy_orderbook(OrderBook *ob) {
    if (!ob) return;

    PriceLevel *current_level = ob->bids;
    while(current_level) {
        PriceLevel *next_level = current_level->next;
        destroy_price_level(current_level);
        current_level = next_level;
    }

    current_level = ob->asks;
    while(current_level) {
        PriceLevel *next_level = current_level->next;
        destroy_price_level(current_level);
        current_level = next_level;
    }
    free(ob);
}

void orderbook_add_order(OrderBook *ob, Order *order) {
    PriceLevel **list_head;

    if (order->side == SIDE_BUY) {
        list_head = &ob->bids;
    } else {
        list_head = &ob->asks;
    }

    PriceLevel *current = *list_head;
    PriceLevel *prev = NULL;

    if (order->side == SIDE_BUY) { // Bids descending
        while (current && current->price > order->price) {
            prev = current;
            current = current->next;
        }
    } else { // Asks ascending
        while (current && current->price < order->price) {
            prev = current;
            current = current->next;
        }
    }

    if (current && current->price == order->price) {
        price_level_add_order(current, order);
    } else {
        PriceLevel *new_level = create_price_level(order->price);
        if (!new_level) {
            return;
        }
        price_level_add_order(new_level, order);

        if (!prev) { // insert at head
            new_level->next = *list_head;
            if(*list_head) (*list_head)->prev = new_level;
            *list_head = new_level;
        } else { // insert after prev
            new_level->next = prev->next;
            if (prev->next) prev->next->prev = new_level;
            prev->next = new_level;
            new_level->prev = prev;
        }
    }
}

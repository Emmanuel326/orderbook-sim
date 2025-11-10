#ifndef EVENT_H
#define EVENT_H

#include "order.h"

typedef enum {
    EVENT_NEW_ORDER,
    EVENT_CANCEL_ORDER
} EventType;

typedef struct {
    EventType type;
    void *data;
} Event;

#endif /* EVENT_H */

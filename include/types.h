//we define the types and contract of data structures here 
#ifndef TYPES_H
#define TYPES_H


#include <stdint.h>

//unique identifier for each order received by the system.
typedef uint64_t OrderID;

//it is a good thing to handle price as integer(eg in cents or fixed-point) to void
//floting-point arithmetic issues in finance
typedef int64_t Price;

//Timestamp of when an order/event occured(eg nanosecond since epoch)
typedef uint64_t Timestamp;


//we represent the side of the market for an order.
typedef enum
{
	SIDE_BUY,
	SIDE_SELL
}Side;

//Represent a state of an order
typedef enum
{
	STATUS_NEW,
	STATUS_PARTIALLY_FILLED,
	STATUS_FILLED,
	STATUS_CANCELLED
}OrderStatus;

#endif //TYPES_H



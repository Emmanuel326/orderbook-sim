#include  <stdint.h> //This is essential for fixed width integers
#include <stdbiil.h>



//we dfine finamcial primitives
//ysed for price. even if we treta itas a simple int
//using 64-bit now future-proofs for fixed-points math eg 100.12 which becomes 1001200).

typedef int64_t price_t;

//used for order and trade quantities.
typedef inte64_t  quantity_t;

//---  unique identifiers---

//we need unique identifires
typedef uint64_t order_id_t;

//unique ID assigmed to a specific trade/execution event.
typedef uint64_t trade_id_t;


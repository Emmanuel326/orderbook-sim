# 🧭 Northstar Specification — OrderBookSim v0.1
**Author:** Emmanuel Nyakundi  
**Date:** 2025-10-31  
**Revision:** 0.1  
**Purpose:** Foundational architecture for a deterministic FIFO order book simulation in C.

---

## 🎯 Core Objective
Simulate the **basic mechanics of a limit order book**, processing buy/sell orders in **FIFO** order, maintaining **best bid/ask**, and ensuring **deterministic, replayable behavior**.

No threads, no locks, no atomics, no trees, and no premature optimization — only clean logic and solid architecture.

---

## 🏗️ Layered Architecture Overview

### 1. Core Layer (`src/core/`)
The **heart** of the simulation — handles data structures and pure matching logic.

| Module | Responsibility | Key Types / Functions |
|--------|----------------|-----------------------|
| **order.c / order.h** | Define the base `Order` struct and helper functions. | `Order`, `create_order()`, `free_order()` |
| **orderbook.c / orderbook.h** | Manage the book — lists of bids/asks, price levels, and best prices. | `OrderBook`, `add_order()`, `remove_order()`, `get_best_bid()`, `get_best_ask()` |
| **matcher.c** | Match incoming orders against the opposite side. | `match_order()`, `execute_trade()` |

🧩 **Core Principle:**  
Pure logic only — no I/O, no CLI, no side effects. Fully testable in isolation.

---

### 2. Engine Layer (`src/engine/`)
The **orchestrator** — drives the simulation via deterministic event flow.

| Module | Responsibility | Key Functions |
|--------|----------------|----------------|
| **event_loop.c** | Main deterministic loop processing incoming events. | `event_loop_run()` |
| **dispatcher.c** | Routes parsed events (ADD, CANCEL, PRINT) to core logic. | `dispatch_event()` |

🧩 **Engine Principle:**  
Implements control flow. Owns the simulation timeline and ensures reproducibility.

---

### 3. API Layer (`src/api/`)
The **interface** — defines how the user or external systems interact with the engine.

| Module | Responsibility | Key Functions |
|--------|----------------|----------------|
| **input_parser.c** | Converts user input into structured events. | `parse_input_line()` |
| **order_interface.c** | Provides a clean API for creating/modifying orders. | `api_add_order()`, `api_cancel_order()` |
| **cli.c** | Command-line interface and output display. | `cli_loop()`, `print_book_state()` |

🧩 **API Principle:**  
No business logic. Only translation between human input ↔ system calls.

---

### 4. Utils Layer (`src/utils/`)
The **toolbox** — provides helpers for logging, timing, and error handling.

| Module | Responsibility | Examples |
|--------|----------------|-----------|
| **logger.c** | Console/file logging for simulation events. | `log_info()`, `log_error()` |
| **errors.c** | Centralized error handling and reporting. | `handle_error()`, `error_to_string()` |
| **time.c** | Deterministic timestamp generator for events. | `get_sim_time()`, `advance_sim_time()` |

🧩 **Utils Principle:**  
Reusable across layers; contains *no domain logic*.

---

### 5. Tests Layer (`tests/`)
Focused on **unit and integration testing** of each logical module.

| File | Purpose |
|------|----------|
| `test_order.c` | Validate order creation, copy, and destruction. |
| `test_orderbook.c` | Validate insertion, lookup, best bid/ask logic. |
| `test_matcher.c` | Validate matching and FIFO fairness. |

🧩 **Testing Principle:**


Each test file focuses on one domain area.  
Builds with `make test`.


## 🔄 Event Flow Overview
┌────────────┐
│ CLI Input │
└─────┬──────┘
│
▼
┌────────────┐
│ InputParser│ parse: “BUY 100 10”
└─────┬──────┘
│ event struct
▼
┌────────────┐
│ Dispatcher │ routes event type
└─────┬──────┘
│
▼
┌────────────┐
│ Event Loop │ calls add/match in core
└─────┬──────┘
│
▼
┌────────────┐
│ OrderBook │ updates state, executes match
└─────┬──────┘
│
▼
┌────────────┐
│ Logger │ records deterministic output
└────────────┘


---



---

## 🧩 Data Model Snapshot

### `Order`
```c
struct Order {
    uint64_t id;
    char side;         // 'B' or 'S'
    double price;
    uint32_t quantity;
    uint64_t timestamp;
    struct Order* next; // for FIFO list
};


OrderBook
struct OrderBook {
    struct Order* bids;
    struct Order* asks;
};


Event

enum EventType { ADD, CANCEL, PRINT };
struct Event {
    enum EventType type;
    struct Order* order;
};


⚡️ Design Principles
| Principle                  | Description                                                               |
| -------------------------- | ------------------------------------------------------------------------- |
| **Determinism**            | Same inputs = same outputs — always.                                      |
| **Separation of Concerns** | Core logic ≠ I/O ≠ Control flow. Each file owns one domain.               |
| **Extendibility**          | Every layer can evolve independently (e.g., add Pro-Rata matching later). |
| **Testability**            | Each component testable in isolation.                                     |
| **Simplicity First**       | Start with correctness, clarity, and learning before optimizing.          |



Project Hierarchy (Baseline)

orderbook-sim/
│
├── include/
│   ├── order.h
│   ├── orderbook.h
│   ├── event.h
│   └── types.h
│
├── src/
│   ├── core/
│   ├── engine/
│   ├── api/
│   ├── utils/
│   └── main.c
│
├── tests/
├── build/
└── docs/
    └── northstar.md



🪶 Summary

This document defines the foundational architecture and philosophy of the OrderBookSim project.
Every future commit, experiment, or optimization should trace back to this “Northstar” to maintain clarity, modularity, and deterministic design.


"Make it work → Make it right → Make it fast."







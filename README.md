# Distributed Cache (System Design: Redis-like Architecture) — In Progress

A system design project aimed at building a Redis-like distributed cache from scratch in modern C++, focusing on scalability, modularity, and clean architectural separation.

The goal is to evolve this into a Redis-like cache with support for in-memory storage, eviction policies, and eventually distributed nodes.

---

## 🔹 Design Thinking

- Built around strict separation of **contract vs implementation**
- Core principle: *high-level logic never depends on concrete storage*
- Designed to evolve into Redis / DB-backed / distributed cache without refactoring consumers.
  
ICache (abstraction)
↓
InMemoryCache (implementation)

---

## 🔹 Current Phase (Phase 1)

Phase 1 focuses on building the **core caching foundation**:

- Defined a clean **ICache abstraction layer**
- Implemented a basic **in-memory cache using unordered_map**
- Added support for **basic operations: get / put / remove / clear / size**
- Introduced **capacity-aware design (bounded cache foundation)**
- Designed a **standardized CacheResult response model for safe API behavior**
- Built system with **interface-first design to support future backend swapping**

---

## 🔹 Design Direction

The system is intentionally structured to evolve:


ICache (contract)
↓
InMemoryCache (Phase 1)
↓
Future: LRU Cache / Redis Backend / Distributed Nodes


---

## 🔹 Engineering Focus

- Strong separation between **abstraction and implementation**
- Avoided tight coupling to ensure future extensibility
- Designed with **Redis-like architecture evolution in mind**
- Minimal and predictable API surface for cache operations

---

## 🔹 Current Status

- Core cache engine (Phase 1) completed
- Unit testing setup in progress using GoogleTest
- Preparing for next phase: eviction policies + performance improvements

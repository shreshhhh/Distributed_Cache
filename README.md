# Distributed Cache System (Phase 1)

A lightweight, interface-driven in-memory cache built in modern C++.  
Focus is on clean abstraction, predictable behavior, and extensibility toward distributed systems.

---

## 🔹 Design Thinking

- Built around strict separation of **contract vs implementation**
- Core principle: *high-level logic never depends on concrete storage*
- Designed to evolve into Redis / DB-backed / distributed cache without refactoring consumers.
  
ICache (abstraction)
↓
InMemoryCache (implementation)


---

## 🔹 What exists in Phase 1

- Defined a **pure abstract cache interface (ICache)** enforcing consistent cache behavior
- Implemented **in-memory cache using unordered_map** with O(1) average operations
- Introduced **bounded cache support** (capacity-aware design)
- Designed a **status-based result system (CacheResult)** instead of raw returns
- Ensured safe access patterns using `find()` (no accidental inserts)

---

## 🔹 Engineering decisions

- Interface-first architecture to support future backend swapping
- Explicit virtual destructor for safe polymorphic deletion
- Separation of `.h / .cpp` for compile-time isolation
- Minimal API surface to reduce misuse and hidden coupling

---

## 🔹 Testing

- GoogleTest-based unit test setup
- Each test runs in isolated fixture (no shared state)
- Validates:
  - basic CRUD behavior
  - boundary conditions
  - capacity handling

---

## 🔹 Current state

- Phase 1: Single-node in-memory cache complete
- Phase 2 direction: eviction policy + concurrency + distributed layer

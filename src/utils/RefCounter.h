//
// Created by Nemesis Verstraete on 05/08/2026.
//

#pragma once
#include <atomic>

namespace obsidium {

class RefCounter {
public:
    RefCounter() = default;

    RefCounter(const RefCounter&) : counter(0) {}

    RefCounter& operator=(const RefCounter&) {
        return *this;
    }

    RefCounter(RefCounter&&) noexcept : counter(0) {}
    RefCounter& operator=(RefCounter&&) noexcept {
        return *this;
    }


    void addRef() {
        counter.fetch_add(1, std::memory_order_relaxed);
    }

    void release() {
        if (counter.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            delete this;
        }
    }

    int getRef() const { return counter.load(); }

    virtual ~RefCounter() = 0;
protected:
    std::atomic<uint32_t> counter{0};
};

}

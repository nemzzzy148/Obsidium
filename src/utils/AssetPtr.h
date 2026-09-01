//
// Created by Nemesis Verstraete on 05/08/2026.
//

#pragma once
#include "RefCounter.h"

namespace obsidium {

template<typename T>
class AssetPtr {
public:
    AssetPtr(T* ptr) : ptr(ptr) { ptr->addRef(); }

    AssetPtr(const AssetPtr& other) : ptr(other.ptr) { if (ptr) ptr->addRef(); }
    AssetPtr& operator=(const AssetPtr& other) {
        if (this != &other) {
            if (ptr) ptr->release();
            ptr = other.ptr;
            if (ptr) ptr->addRef();
        }
        return *this;
    }

    AssetPtr(AssetPtr&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
    AssetPtr& operator=(AssetPtr&& other) noexcept {
        if (this != &other) {
            if (ptr) ptr->release();
            ptr = other.ptr;
            other.ptr == nullptr;
        }
        return *this;
    }

    T* operator->() { return ptr; }
    T& operator*() { return *ptr; }

    explicit operator bool() const { return ptr != nullptr; }

    ~AssetPtr() { ptr->release(); }
private:
    T* ptr = nullptr;
};

}

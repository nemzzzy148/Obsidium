//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "UUID.h"

#include <random>

namespace obsidium {

static std::random_device randomDevice;
static std::mt19937_64 generator(randomDevice());
static std::uniform_int_distribution<uint64_t> uniformDistribution;

UUID_t UUID::generateUUID() {
    return uniformDistribution(generator);
}

}

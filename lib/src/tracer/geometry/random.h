//
// Created by iliya on 4/19/26.
//

#include <random>
#include <cmath>
#include <thread>
#include "tracer/core.h"

#ifndef TRACER_GEOMETRY_RANDOM_H
#define TRACER_GEOMETRY_RANDOM_H

// Класс чисто для функции threadRNG, для экспорта не предусматривается
class Xoshiro256ss {
public:
    using result_type = uint64_t;

    inline Xoshiro256ss() noexcept { seed(12345678); }
    inline explicit Xoshiro256ss(uint64_t s) noexcept { seed(s); }

    inline void seed(uint64_t seed) noexcept {
        for (int i = 0; i < 4; ++i) {
            uint64_t z = (seed += 0x9e3779b97f4a7c15);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            s[i] = z ^ (z >> 31);
        }
    }

    inline uint64_t operator()() noexcept {
        const uint64_t result = rotl(s[1] * 5, 7) * 9;
        const uint64_t t = s[1] << 17;
        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];
        s[2] ^= t;
        s[3] = rotl(s[3], 45);
        return result;
    }

    inline static constexpr uint64_t min() noexcept { return 0; }
    inline static constexpr uint64_t max() noexcept { return UINT64_MAX; }
private:
    uint64_t s[4];

    static inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }
};

inline Xoshiro256ss& threadRNG() {
    thread_local Xoshiro256ss rng(
            std::random_device{}() ^ (uint64_t)std::hash<std::thread::id>{}(std::this_thread::get_id())
    );
    return rng;
}

// Случайная точка на сфере радиуса 1
inline Vector3d randomInUnitSphere() noexcept {
    auto& rng = threadRNG();
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    Vector3d p;
    do {
        p = Vector3d(dist(rng), dist(rng), dist(rng));
    } while (p.hypot() > 1.0f);

    return p.normalize();
}

// Случайное число от 0 до 1
inline float random01() noexcept {
    auto& rng = threadRNG();
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rng);
}

#endif // TRACER_GEOMETRY_RANDOM_H

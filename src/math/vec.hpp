#pragma once

#include <iostream>

#include "macro.hpp"

template<typename T> 
union Vec2 {
    #ifdef USE_ANON_STRUCTS
    struct { T x, y; };
    struct { T u, v; };
    struct { T width, height; };
    #else
    T x, y;
    #endif 

    T& operator[](size_t i) 
    {
        ASSERT_RANGE(i, 0, 1); 
        switch (i) {
            default:
            case 0: return x;
            case 1: return y; 
        }
    }

    const T& operator[](size_t i) const 
    {
        ASSERT_RANGE(i, 0, 1); 
        switch (i) {
            default:
            case 0: return x;
            case 1: return y; 
        }
    }

    friend bool operator==(const Vec2& vec1, const Vec2& vec2)
    {
        return vec1.x == vec2.x && vec1.y == vec2.y; 
    }

    friend bool operator!=(const Vec2& vec1, const Vec2& vec2)
    {
        return vec1.x != vec2.x || vec1.y != vec2.y; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v) 
    {
        os << v.x << ", " << v.y;
        return os;
    }
};

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d; 
typedef Vec2<int32_t> Vec2i;  

template<typename T>
union Vec3 {
    #ifdef USE_ANON_STRUCTS
    struct { T x, y, z; };
    struct { T r, g, b; };
    #else
    T x, y, z; 
    #endif

    T& operator[](size_t i) 
    {
        ASSERT_RANGE(i, 0, 2); 
        switch (i) {
            default:
            case 0: return x;
            case 1: return y; 
            case 2: return z;
        }
    }

    const T& operator[](size_t i) const 
    {
        ASSERT_RANGE(i, 0, 2);
        switch (i) {
            default:
            case 0: return x;
            case 1: return y; 
            case 2: return z; 
        }
    }

    friend bool operator==(const Vec3& vec1, const Vec3& vec2)
    {
        return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
    }

    friend bool operator!=(const Vec3& vec1, const Vec3& vec2)
    {
        return vec1.x != vec2.x || vec1.y != vec2.y || vec1.z != vec2.z; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec3& v) 
    {
        os << v.x << ", " << v.y << ", " << v.z;
        return os;
    }
};

typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d; 
typedef Vec3<int32_t> Vec3i; 

template<typename T>
union Vec4 {
    #ifdef USE_ANON_STRUCTS
    struct { T x, y, z, w; };
    struct { T r, g, b, a; };
    struct { T s, t, p, q; };
    #else
    T x, y, z, w;
    #endif

    T& operator[](size_t i) 
    {
        ASSERT_RANGE(i, 0, 3); 
        switch (i) {
            default:
            case 0: return x;
            case 1: return y; 
            case 2: return z;
            case 3: return w; 
        }
    }

    const T& operator[](size_t i) const 
    {
        ASSERT_RANGE(i, 0, 3); 
        switch (i) {
            default:
            case 0: return x;
            case 1: return y; 
            case 2: return z; 
            case 3: return w; 
        }
    }

    friend bool operator==(const Vec4& vec1, const Vec4& vec2)
    {
        return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.y && vec1.w == vec2.w;
    }

    friend bool operator!=(const Vec4& vec1, const Vec4& vec2)
    {
        return vec1.x != vec2.x || vec1.y != vec2.y || vec1.z != vec2.z || vec1.w != vec2.w; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec4& v) 
    {
        os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
        return os;
    }
};

typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d; 
typedef Vec4<int32_t> Vec4i; 
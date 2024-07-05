#pragma once

#include <iostream>

#include "macro.hpp"

template<typename T>
union Mat3 {
    T m[12]; 
    T m3x3[3][3]; 

    #ifdef USE_ANON_STRUCTS
    struct {
        T m11, m12, m13,
          m21, m22, m23,
          m31, m32, m33;
    };
    #endif

    T& operator[](size_t i) {
        ASSERT_RANGE(i, 0, 11); 
        return m[i]; 
    }

    const T& operator[](size_t i) const {
        ASSERT_RANGE(i, 0, 11); 
        return m[i]; 
    }
};

typedef Mat3<float> Mat3f; 
typedef Mat3<double> Mat3d; 
typedef Mat3<int32_t> Mat3i; 

template<typename T>
union Mat4 {
    T m[16]; 
    T m4x4[4][4];

    #ifdef USE_ANON_STRUCTS
    struct {
        T m11, m12, m13, m14,
          m21, m22, m23, m24,
          m31, m32, m33, m34,
          m41, m42, m43, m44;
    };
    #endif

    T& operator[](size_t i) {
        ASSERT_RANGE(i, 0, 15); 
        return m[i]; 
    }

    const T& operator[](size_t i) const {
        ASSERT_RANGE(i, 0, 15); 
        return m[i];
    }

    Mat4<T> operator*(Mat4 const& o) {
        return {
            m[0]  * o.m[0] + m[1]  * o.m[4] + m[2]  * o.m[8]  + m[3]  * o.m[12],
            m[0]  * o.m[1] + m[1]  * o.m[5] + m[2]  * o.m[9]  + m[3]  * o.m[13],
            m[0]  * o.m[2] + m[1]  * o.m[6] + m[2]  * o.m[10] + m[3]  * o.m[14],
            m[0]  * o.m[3] + m[1]  * o.m[7] + m[2]  * o.m[11] + m[3]  * o.m[15],
            m[4]  * o.m[0] + m[5]  * o.m[4] + m[6]  * o.m[8]  + m[7]  * o.m[12],
            m[4]  * o.m[1] + m[5]  * o.m[5] + m[6]  * o.m[9]  + m[7]  * o.m[13],
            m[4]  * o.m[2] + m[5]  * o.m[6] + m[6]  * o.m[10] + m[7]  * o.m[14],
            m[4]  * o.m[3] + m[5]  * o.m[7] + m[6]  * o.m[11] + m[7]  * o.m[15],
            m[8]  * o.m[0] + m[9]  * o.m[4] + m[10] * o.m[8]  + m[11] * o.m[12],
            m[8]  * o.m[1] + m[9]  * o.m[5] + m[10] * o.m[9]  + m[11] * o.m[13],
            m[8]  * o.m[2] + m[9]  * o.m[6] + m[10] * o.m[10] + m[11] * o.m[14],
            m[8]  * o.m[3] + m[9]  * o.m[7] + m[10] * o.m[11] + m[11] * o.m[15],
            m[12] * o.m[0] + m[13] * o.m[4] + m[14] * o.m[8]  + m[15] * o.m[12],
            m[12] * o.m[1] + m[13] * o.m[5] + m[14] * o.m[9]  + m[15] * o.m[13],
            m[12] * o.m[2] + m[13] * o.m[6] + m[14] * o.m[10] + m[15] * o.m[14],
            m[12] * o.m[3] + m[13] * o.m[7] + m[14] * o.m[11] + m[15] * o.m[15],
        };
    }

    void operator*=(Mat4 const& o) {
        m = (this * o).m; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Mat4& m) {
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                os << m.m4x4[r][c];
                if (r != 3 || c != 3) {
                    os << ", ";
                } 
            }
            os << std::endl;
        }
        return os; 
    }
};

typedef Mat4<float> Mat4f; 
typedef Mat4<double> Mat4d; 
typedef Mat4<int32_t> Mat4i; 

static Mat3f IdentityMat3f() {
    return {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
}

static Mat4f IdentityMat4f() {
    return {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

static Mat4f CreateOrthoProjectionf(float left, float right, float bottom, float top, float near, float far) {
    return {
        2.0f / (right - left), 0.0f, 0.0f, -((right + left) / (right - left)),
        0.0f, 2.0f / (top - bottom), 0.0f, -((top + bottom) / (top - bottom)),
        0.0f, 0.0f, 2.0f / (far - near), -((far + near) / (far - near)),
        0.0f, 0.0f, 0.0f, 1.0f
    };
}
#pragma once

#include <iostream>

#include "macro.hpp"
#include "vec.hpp"

template<typename T>
union Mat3 
{
    T m9[9]; 
    T m3x3[3][3]; 

    #ifdef USE_ANON_STRUCTS
    struct {
        T m11, m12, m13,
          m21, m22, m23,
          m31, m32, m33;
    };
    #endif

    T& operator[](size_t i) 
    {
        ASSERT_RANGE(i, 0, 8); 
        return m9[i]; 
    }

    const T& operator[](size_t i) const 
    {
        ASSERT_RANGE(i, 0, 8); 
        return m9[i]; 
    }

    Mat3<T> operator+(const Mat3<T>& mat) 
    {
        return {
            m9[0] + mat.m9[0], m9[1] + mat.m9[1], m9[2] + mat.m9[2],
            m9[3] + mat.m9[3], m9[4] + mat.m9[4], m9[5] + mat.m9[5],
            m9[6] + mat.m9[6], m9[7] + mat.m9[7], m9[8] + mat.m9[8]
        };
    }

    Mat3<T> operator+=(const Mat3<T>& mat) 
    {
        m9 = (this + mat).m9; 
    }

    Mat3<T> operator-(const Mat3<T>& mat) 
    {
        return 
        {
            m9[0] - mat.m9[0], m9[1] - mat.m9[1], m9[2] - mat.m9[2],
            m9[3] - mat.m9[3], m9[4] - mat.m9[4], m9[5] - mat.m9[5],
            m9[6] - mat.m9[6], m9[7] - mat.m9[7], m9[8] - mat.m9[8]
        };
    }

    Mat3<T> operator-=(const Mat3<T>& mat) 
    {
        m9 = (this - mat).m9; 
    }

    Vec3<T> operator*(const Vec3<T>& vec) 
    {
        return 
        {
            m9[0] * vec[0] + m9[1] * vec[1] + m9[2] * vec[2],
            m9[3] * vec[0] + m9[4] * vec[1] + m9[5] * vec[2],
            m9[6] * vec[0] + m9[7] * vec[1] + m9[8] * vec[2]
        };
    }

    Mat3<T> operator*(const Mat3<T>& mat) 
    {
        return 
        {
            m9[0] * mat.m9[0] + m9[1] * mat.m9[3] + m9[2] * mat.m9[6],
            m9[0] * mat.m9[1] + m9[1] * mat.m9[4] + m9[2] * mat.m9[7],
            m9[0] * mat.m9[2] + m9[1] * mat.m9[5] + m9[2] * mat.m9[8],
            m9[3] * mat.m9[0] + m9[4] * mat.m9[3] + m9[5] * mat.m9[6],
            m9[3] * mat.m9[1] + m9[4] * mat.m9[4] + m9[5] * mat.m9[7],
            m9[3] * mat.m9[2] + m9[4] * mat.m9[5] + m9[5] * mat.m9[8],
            m9[6] * mat.m9[0] + m9[7] * mat.m9[3] + m9[8] * mat.m9[6],
            m9[6] * mat.m9[1] + m9[7] * mat.m9[4] + m9[8] * mat.m9[7],
            m9[6] * mat.m9[2] + m9[7] * mat.m9[5] + m9[8] * mat.m9[8]
        };
    }

    void operator*=(Mat3 const& mat) 
    {
        m9 = (this * mat).m9; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Mat3& mat) 
    {
        for (int r = 0; r < 3; r++) 
        {
            for (int c = 0; c < 3; c++) 
            {
                os << mat.m3x3[r][c];
                if (r != 2 || c != 2) os << ", ";
            }
            os << std::endl;
        }
        return os; 
    }
};

typedef Mat3<float> Mat3f; 
typedef Mat3<double> Mat3d; 
typedef Mat3<int32_t> Mat3i; 

template<typename T>
union Mat4 
{
    T m16[16]; 
    T m4x4[4][4];

    #ifdef USE_ANON_STRUCTS
    struct 
    {
        T m11, m12, m13, m14,
          m21, m22, m23, m24,
          m31, m32, m33, m34,
          m41, m42, m43, m44;
    };
    #endif

    T& operator[](size_t i) 
    {
        ASSERT_RANGE(i, 0, 15); 
        return m16[i]; 
    }

    const T& operator[](size_t i) const 
    {
        ASSERT_RANGE(i, 0, 15); 
        return m16[i];
    }

    Mat4<T> operator+(const Mat4<T>& mat) 
    {
        return {
            m16[0]  + mat.m16[0],  m16[1]  + mat.m16[1],  m16[2]  + mat.m16[2],  m16[3]  + mat.m16[3],
            m16[4]  + mat.m16[4],  m16[5]  + mat.m16[5],  m16[6]  + mat.m16[6],  m16[7]  + mat.m16[7],
            m16[8]  + mat.m16[8],  m16[9]  + mat.m16[9],  m16[10] + mat.m16[10], m16[11] + mat.m16[11],
            m16[12] + mat.m16[12], m16[13] + mat.m16[13], m16[14] + mat.m16[14], m16[15] + mat.m16[15],
        };
    }

    Mat4<T> operator+=(const Mat4<T>& mat) 
    {
        m16 = (this + mat).m16; 
    }

    Mat4<T> operator-(const Mat4<T>& mat) 
    {
        return 
        {
            m16[0]  - mat.m16[0],  m16[1]  - mat.m16[1],  m16[2]  - mat.m16[2],  m16[3]  - mat.m16[3],
            m16[4]  - mat.m16[4],  m16[5]  - mat.m16[5],  m16[6]  - mat.m16[6],  m16[7]  - mat.m16[7],
            m16[8]  - mat.m16[8],  m16[9]  - mat.m16[9],  m16[10] - mat.m16[10], m16[11] - mat.m16[11],
            m16[12] - mat.m16[12], m16[13] - mat.m16[13], m16[14] - mat.m16[14], m16[15] - mat.m16[15],
        };
    }

    Mat4<T> operator-=(const Mat4<T>& mat) 
    {
        m16 = (this - mat).m16; 
    }

    Mat4<T> operator*(const Mat4& mat) 
    {
        return 
        {
            m16[0]  * mat.m16[0] + m16[1]  * mat.m16[4] + m16[2]  * mat.m16[8]  + m16[3]  * mat.m16[12],
            m16[0]  * mat.m16[1] + m16[1]  * mat.m16[5] + m16[2]  * mat.m16[9]  + m16[3]  * mat.m16[13],
            m16[0]  * mat.m16[2] + m16[1]  * mat.m16[6] + m16[2]  * mat.m16[10] + m16[3]  * mat.m16[14],
            m16[0]  * mat.m16[3] + m16[1]  * mat.m16[7] + m16[2]  * mat.m16[11] + m16[3]  * mat.m16[15],
            m16[4]  * mat.m16[0] + m16[5]  * mat.m16[4] + m16[6]  * mat.m16[8]  + m16[7]  * mat.m16[12],
            m16[4]  * mat.m16[1] + m16[5]  * mat.m16[5] + m16[6]  * mat.m16[9]  + m16[7]  * mat.m16[13],
            m16[4]  * mat.m16[2] + m16[5]  * mat.m16[6] + m16[6]  * mat.m16[10] + m16[7]  * mat.m16[14],
            m16[4]  * mat.m16[3] + m16[5]  * mat.m16[7] + m16[6]  * mat.m16[11] + m16[7]  * mat.m16[15],
            m16[8]  * mat.m16[0] + m16[9]  * mat.m16[4] + m16[10] * mat.m16[8]  + m16[11] * mat.m16[12],
            m16[8]  * mat.m16[1] + m16[9]  * mat.m16[5] + m16[10] * mat.m16[9]  + m16[11] * mat.m16[13],
            m16[8]  * mat.m16[2] + m16[9]  * mat.m16[6] + m16[10] * mat.m16[10] + m16[11] * mat.m16[14],
            m16[8]  * mat.m16[3] + m16[9]  * mat.m16[7] + m16[10] * mat.m16[11] + m16[11] * mat.m16[15],
            m16[12] * mat.m16[0] + m16[13] * mat.m16[4] + m16[14] * mat.m16[8]  + m16[15] * mat.m16[12],
            m16[12] * mat.m16[1] + m16[13] * mat.m16[5] + m16[14] * mat.m16[9]  + m16[15] * mat.m16[13],
            m16[12] * mat.m16[2] + m16[13] * mat.m16[6] + m16[14] * mat.m16[10] + m16[15] * mat.m16[14],
            m16[12] * mat.m16[3] + m16[13] * mat.m16[7] + m16[14] * mat.m16[11] + m16[15] * mat.m16[15]
        };
    }

    void operator*=(const Mat4& mat) 
    {
        m16 = (this * mat).m16; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Mat4& mat) 
    {
        for (int r = 0; r < 4; r++) 
        {
            for (int c = 0; c < 4; c++) 
            {
                os << mat.m4x4[r][c];
                if (r != 3 || c != 3) os << ", ";
            }
            os << std::endl;
        }
        return os; 
    }
};

typedef Mat4<float> Mat4f; 
typedef Mat4<double> Mat4d; 
typedef Mat4<int32_t> Mat4i; 

// Utility Functions

static Mat3f IdentityMat3f() 
{
    return 
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
}

static Mat4f IdentityMat4f() 
{
    return 
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

static Mat4f CreateOrthoProjectionf(float left, float right, float bottom, float top, float near, float far) 
{
    return 
    {
        2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
        0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
        0.0f, 0.0f, 2.0f / (far - near), -(far + near) / (far - near),
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

// Generic Functions

template<typename T>
static Mat3<T> TransposeMat3(const Mat3<T>& mat) 
{
    return 
    {
        mat.m9[0], mat.m9[3], mat.m9[6],
        mat.m9[1], mat.m9[4], mat.m9[7],
        mat.m9[2], mat.m9[5], mat.m9[8]
    };
}

template<typename T> 
static Mat4<T> TransposeMat4(const Mat4<T> mat) 
{
    return 
    {
        mat.m16[0], mat.m16[4], mat.m16[8],  mat.m16[12],
        mat.m16[1], mat.m16[5], mat.m16[9],  mat.m16[13],
        mat.m16[2], mat.m16[6], mat.m16[10], mat.m16[14],
        mat.m16[3], mat.m16[7], mat.m16[11], mat.m16[15]
    };
}
#pragma once

template<typename T> 
struct Vec2 {
    T x, y; 
};

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d; 
typedef Vec2<int32_t> Vec2i;  

template<typename T>
struct Vec3 {
    T x, y, z; 
};

typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d; 
typedef Vec3<int32_t> Vec3i;  

template<typename T>
struct Vec4 {
    T x, y, z, w;
};

typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d; 
typedef Vec4<int32_t> Vec4i;  

template<typename T>
struct Mat3 {
    T m00, m01, m02;
    T m10, m11, m12;
    T m20, m21, m22;
};

typedef Mat3<float> Mat3f; 
typedef Mat3<double> Mat3d; 
typedef Mat3<int32_t> Mat3i; 

template<typename T>
struct Mat4 {
    T m00, m01, m02, m03;
    T m10, m11, m12, m13;
    T m20, m21, m22, m23;
    T m30, m31, m32, m33; 
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
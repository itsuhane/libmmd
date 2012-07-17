
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

/**
 * Convention:
 *        Vector: X = [ x_0 x_1 x_2 x_3 ]
 *        Matrix: M = [
 *                      m_00 m_01 m_02 m_03
 *                      m_10 m_11 m_12 m_13
 *                      m_20 m_21 m_22 m_23
 *                      m_30 m_31 m_32 m_33
 *                    ]
 *     Transform: Y = X*M
 */
#ifndef __MATH_HXX_96FA1D6C8B55A3C9CFFA645F66F5B21F_INCLUDED__
#define __MATH_HXX_96FA1D6C8B55A3C9CFFA645F66F5B21F_INCLUDED__

#define mmd_math_const_pi 3.141592653589793238462643383279502884
#define mmd_math_const_eps 1e-7
namespace mmd {

    namespace math {
        template <typename T> inline T sqrt(T x) {
            return static_cast<T>(std::sqrt(static_cast<double>(x)));
        }
        template <typename T> inline T sin(T x) {
            return static_cast<T>(std::sin(static_cast<double>(x)));
        }
        template <typename T> inline T cos(T x) {
            return static_cast<T>(std::cos(static_cast<double>(x)));
        }
        template <typename T> inline T asin(T x) {
            return static_cast<T>(std::asin(static_cast<double>(x)));
        }
        template <typename T> inline T acos(T x) {
            return static_cast<T>(std::acos(static_cast<double>(x)));
        }
        template <typename T> inline T atan2(T y, T x) {
            return static_cast<T>(std::atan2(static_cast<double>(y), static_cast<double>(x)));
        }
        template <typename T> inline T clamp(T x, T min, T max) {
            return std::min(std::max(x, min), max);
        }
    } /* End of namespace math */

#include "pack.inc"
    template <typename T> struct PACKED Complex;
    template <typename T> struct PACKED Point2D;
    template <typename T> union PACKED Vector2D;

    template <typename T> struct PACKED Triple;
    template <typename T> struct PACKED Point3D;
    template <typename T> struct PACKED RGBColor;
    template <typename T> union PACKED Vector3D;

    template <typename T> struct PACKED Quaternion;
    template <typename T> struct PACKED Point4D;
    template <typename T> struct PACKED RGBAColor;
    template <typename T> union PACKED Vector4D;

    template <typename T> union PACKED Matrix4x4;

    template <typename T> struct PACKED Complex {
        typedef T elem_type;

        elem_type re;
        elem_type im;

        void MakeZero();
        static Complex Zero();

        elem_type Norm() const;
        Complex Normalize() const;

        Complex Conjugate() const;

        Complex operator-() const;

        Complex operator+(elem_type a) const;
        Complex operator-(elem_type a) const;
        Complex operator*(elem_type a) const;

        Complex operator+(const Complex& x) const;
        Complex operator-(const Complex& x) const;
        Complex operator*(const Complex& x) const;

        bool operator==(const Complex& x) const;
        bool operator!=(const Complex& x) const;
    };
    template <typename T> Complex<T> operator+(typename Complex<T>::elem_type a, const Complex<T>& x);
    template <typename T> Complex<T> operator-(typename Complex<T>::elem_type a, const Complex<T>& x);
    template <typename T> Complex<T> operator*(typename Complex<T>::elem_type a, const Complex<T>& x);

    template <typename T> struct PACKED Point2D {
        typedef T elem_type;

        elem_type x;
        elem_type y;

        void MakeZero();
        static Point2D Zero();

        elem_type Norm() const;
        Point2D Normalize() const;

        Point2D operator-() const;

        Point2D operator*(elem_type a) const;

        Point2D operator+(const Point2D& p) const;
        Point2D operator-(const Point2D& p) const;

        elem_type operator*(const Point2D& p) const;

        bool operator==(const Point2D& p) const;
        bool operator!=(const Point2D& p) const;
    };
    template <typename T> Point2D<T> operator*(typename Point2D<T>::elem_type a, const Point2D<T>& p);

    template <typename T> union PACKED Vector2D {
        typedef T elem_type;

        elem_type v[2];

        Point2D<elem_type> p;
        Complex<elem_type> c;

        void MakeZero();
        static Vector2D Zero();

        elem_type Norm() const;
        Vector2D Normalize() const;

        Vector2D operator-() const;

        Vector2D operator*(elem_type a) const;

        Vector2D operator+(const Vector2D& x) const;
        Vector2D operator-(const Vector2D& x) const;

        elem_type operator*(const Vector2D& x) const;

        bool operator==(const Vector2D& x) const;
        bool operator!=(const Vector2D& x) const;
    };
    template <typename T> Vector2D<T> operator*(typename Vector2D<T>::elem_type a, const Vector2D<T>& x);

    template <typename T> struct PACKED Triple {
        typedef T elem_type;

        elem_type i;
        elem_type j;
        elem_type k;

        void MakeZero();
        static Triple Zero();

        elem_type Norm() const;
        Triple Normalize() const;

        Triple operator-() const;

        Triple operator*(elem_type a) const;

        Triple operator+(const Triple& t) const;
        Triple operator-(const Triple& t) const;
        Triple operator*(const Triple& t) const;

        bool operator==(const Triple& t) const;
        bool operator!=(const Triple& t) const;
    };
    template <typename T> Triple<T> operator*(typename Triple<T>::elem_type a, const Triple<T>& t);

    template <typename T> struct PACKED Point3D {
        typedef T elem_type;

        elem_type x;
        elem_type y;
        elem_type z;

        void MakeZero();
        static Point3D Zero();

        elem_type Norm() const;
        Point3D Normalize() const;

        Point3D operator-() const;

        Point3D operator*(elem_type a) const;

        Point3D operator+(const Point3D& p) const;
        Point3D operator-(const Point3D& p) const;

        elem_type operator*(const Point3D& p) const;

        bool operator==(const Point3D& p) const;
        bool operator!=(const Point3D& p) const;
    };
    template <typename T> Point3D<T> operator*(typename Point3D<T>::elem_type a, const Point3D<T>& p);

    template <typename T> struct PACKED RGBColor {
        typedef T elem_type;

        elem_type r;
        elem_type g;
        elem_type b;

        void MakeBlack();
        void MakeWhite();
        static RGBColor Black();
        static RGBColor White();

        elem_type ColorIntensity() const;

        RGBColor Clamp() const;

        RGBColor ColorInverse() const;

        operator RGBAColor<elem_type>() const;
    };

    template <typename T> union PACKED Vector3D {
        typedef T elem_type;

        elem_type v[3];
        Point3D<elem_type> p;
        Triple<elem_type> t;
        RGBColor<elem_type> c;
        struct PACKED Downgrade {
            Vector2D<elem_type> vector2d;
            elem_type scalar;
        } downgrade;

        void MakeZero();
        static Vector3D Zero();

        elem_type Norm() const;
        Vector3D Normalize() const;

        Vector3D operator-() const;

        Vector3D operator*(elem_type a) const;

        Vector3D operator+(const Vector3D& x) const;
        Vector3D operator-(const Vector3D& x) const;

        elem_type operator*(const Vector3D& x) const;

        bool operator==(const Vector3D& x) const;
        bool operator!=(const Vector3D& x) const;
    };
    template <typename T> Vector3D<T> operator*(typename Vector3D<T>::elem_type a, const Vector3D<T>& x);

    template <typename T> struct PACKED Quaternion {
        typedef T elem_type;

        elem_type i;
        elem_type j;
        elem_type k;
        elem_type e;

        void MakeIdentity();
        static Quaternion Identity();

        elem_type Norm() const;
        Quaternion Normalize() const;

        Quaternion Conjugate() const;
        Quaternion Inverse() const;

        Quaternion operator-() const;

        Quaternion operator*(elem_type a) const;

        Quaternion operator+(const Quaternion& q) const;
        Quaternion operator-(const Quaternion& q) const;
        Quaternion operator*(const Quaternion& q) const;

        bool operator==(const Quaternion& q) const;
        bool operator!=(const Quaternion& q) const;

        Vector3D<elem_type> GetRotateAxis() const;
        elem_type GetRotateAngle() const;

        Matrix4x4<elem_type> ToRotateMatrix() const;
    };
    template <typename T> Quaternion<T> operator*(typename Quaternion<T>::elem_type a, const Quaternion<T>& q);

    template <typename T> struct PACKED Point4D {
        typedef T elem_type;

        elem_type x;
        elem_type y;
        elem_type z;
        elem_type w;

        void MakeZero();
        static Point4D Zero();

        elem_type Norm() const;
        Point4D Normalize() const;

        Point4D operator-() const;

        Point4D operator*(elem_type a) const;

        Point4D operator+(const Point4D& p) const;
        Point4D operator-(const Point4D& p) const;

        elem_type operator*(const Point4D& p) const;

        bool operator==(const Point4D& p) const;
        bool operator!=(const Point4D& p) const;
    };
    template <typename T> Point4D<T> operator*(typename Point4D<T>::elem_type a, const Point4D<T>& p);

    template <typename T> struct PACKED RGBAColor {
        typedef T elem_type;

        elem_type r;
        elem_type g;
        elem_type b;
        elem_type a;

        void MakeBlack();
        void MakeWhite();
        void MakeOpaque();
        void MakeTransparent();
        static RGBAColor Black();
        static RGBAColor White();
        static RGBAColor BlackTransparent();

        elem_type ColorIntensity() const;

        RGBAColor Clamp() const;

        RGBAColor ColorInverse() const;
        RGBAColor AlphaInverse() const;
        RGBAColor Inverse() const;

        operator RGBColor<elem_type>() const;
    };

    template <typename T> union PACKED Vector4D {
        typedef T elem_type;

        elem_type v[4];
        Point4D<elem_type> p;
        Quaternion<elem_type> q;
        RGBAColor<elem_type> c;
        struct PACKED Downgrade {
            Vector3D<elem_type> vector3d;
            elem_type scalar;
        } downgrade;

        void MakeZero();
        static Vector4D Zero();

        elem_type Norm() const;
        Vector4D Normalize() const;

        Vector3D<elem_type> HomoProject() const;

        Vector4D operator-() const;

        Vector4D operator*(elem_type a) const;

        Vector4D operator+(const Vector4D& x) const;
        Vector4D operator-(const Vector4D& x) const;

        elem_type operator*(const Vector4D& x) const;

        bool operator==(const Vector4D& x) const;
        bool operator!=(const Vector4D& x) const;
    };
    template <typename T> Vector4D<T> operator*(typename Vector4D<T>::elem_type a, const Vector4D<T>& x);

    template <typename T> union PACKED Matrix4x4 {
        typedef T elem_type;

        elem_type v[16];
        struct PACKED VectorArray {
            Vector4D<elem_type> v[4];
        } r;
        struct PACKED Element {
            elem_type a11, a12, a13, a14;
            elem_type a21, a22, a23, a24;
            elem_type a31, a32, a33, a34;
            elem_type a41, a42, a43, a44;
        } e;

        void MakeZero();
        void MakeIdentity();

        static Matrix4x4 Zero();
        static Matrix4x4 Identity();

        Matrix4x4 Transpose() const;
        Matrix4x4 Inverse() const;

        Matrix4x4 operator-() const;

        Matrix4x4 operator*(elem_type a) const;

        Matrix4x4 operator+(const Matrix4x4& m) const;
        Matrix4x4 operator-(const Matrix4x4& m) const;
        Matrix4x4 operator*(const Matrix4x4& m) const;
    };
    template <typename T> Matrix4x4<T> operator*(typename Matrix4x4<T>::elem_type a, const Matrix4x4<T>& m);
    template <typename T> Vector4D<T> operator*(const Vector4D<T>& v, const Matrix4x4<T>& m);

#include "unpack.inc"

    template <typename T> Vector3D<T> rotate(const Vector3D<T>& v, const Matrix4x4<T>& m);
    template <typename T> Vector3D<T> transform(const Vector3D<T>& v, const Matrix4x4<T>& m);

    template <typename T> Quaternion<T> AxisToQuaternion(const Vector3D<T>& axis, typename Vector3D<T>::elem_type angle);

    template <typename T> Vector3D<T> QuaternionToXYZ(const Quaternion<T>& quaternion);
    template <typename T> Vector3D<T> QuaternionToXZY(const Quaternion<T>& quaternion);
    template <typename T> Vector3D<T> QuaternionToYXZ(const Quaternion<T>& quaternion);
    template <typename T> Vector3D<T> QuaternionToYZX(const Quaternion<T>& quaternion);
    template <typename T> Vector3D<T> QuaternionToZXY(const Quaternion<T>& quaternion);
    template <typename T> Vector3D<T> QuaternionToZYX(const Quaternion<T>& quaternion);

    template <typename T> Quaternion<T> XYZToQuaternion(const Vector3D<T>& euler);
    template <typename T> Quaternion<T> XZYToQuaternion(const Vector3D<T>& euler);
    template <typename T> Quaternion<T> YXZToQuaternion(const Vector3D<T>& euler);
    template <typename T> Quaternion<T> YZXToQuaternion(const Vector3D<T>& euler);
    template <typename T> Quaternion<T> ZXYToQuaternion(const Vector3D<T>& euler);
    template <typename T> Quaternion<T> ZYXToQuaternion(const Vector3D<T>& euler);

    template <typename T> class LerpProxy;
    template <typename T> class NLerpProxy;
    template <typename T> class SLerpProxy;

    template <typename T> LerpProxy<T> Lerp(const T& a, const T& b);
    template <typename T> NLerpProxy<T> NLerp(const T& a, const T& b);
    template <typename T> SLerpProxy<T> SLerp(const T& a, const T& b);

    template <typename T, size_t presample_resolution = 32> class Bezier {
    public:
        Bezier();
        Bezier(const Vector2D<T>& c_0, const Vector2D<T>& c_1);
        T operator()(T x) const;
        T operator[](T x) const;

        const Vector2D<T>& GetC(size_t i) const;
        void SetC(const Vector2D<T>& c_0, const Vector2D<T>& c_1);
    private:
        void presample();
        T interpolate(T x) const;
        bool is_linear_;
        T presamples_[presample_resolution];
        Vector2D<T> c_0, c_1;
    };

#include "math_impl.inl"
} /* End of namespace mmd */
#endif /* __MATH_HXX_96FA1D6C8B55A3C9CFFA645F66F5B21F_INCLUDED__ */

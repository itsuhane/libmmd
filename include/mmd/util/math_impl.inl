
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

template <typename T> inline void Complex<T>::MakeZero() {
    re = im = elem_type(0);
}
template <typename T> inline Complex<T> Complex<T>::Zero() {
    Complex<T> result;
    result.MakeZero();
    return result;
}
template <typename T> inline typename Complex<T>::elem_type Complex<T>::Norm() const {
    return math::sqrt(re*re+im*im);
}
template <typename T> inline Complex<T> Complex<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Complex<T> result;
    result.re = re*n;
    result.im = im*n;
    return result;
}
template <typename T> inline Complex<T> Complex<T>::Conjugate() const {
    Complex<T> result;
    result.re = re;
    result.im = -im;
    return result;
}
template <typename T> inline Complex<T> Complex<T>::operator-() const {
    Complex<T> result;
    result.re = -re;
    result.im = -im;
    return result;
}
template <typename T> inline Complex<T> Complex<T>::operator+(typename Complex<T>::elem_type a) const {
    Complex<T> result;
    result.re = re+a;
    result.im = im;
    return result;
}
template <typename T> inline Complex<T> Complex<T>::operator-(typename Complex<T>::elem_type a) const {
    Complex<T> result;
    result.re = re-a;
    result.im = im;
    return result;
}
template <typename T> inline Complex<T> Complex<T>::operator*(typename Complex<T>::elem_type a) const {
    Complex<T> result;
    result.re = re*a;
    result.im = im*a;
    return result;
}
template <typename T> inline Complex<T> Complex<T>::operator+(const Complex<T>& x) const {
    Complex<T> result;
    result.re = re+x.re;
    result.im = im+x.im;
    return result;
}
template <typename T> inline Complex<T> Complex<T>::operator-(const Complex<T>& x) const {
    Complex<T> result;
    result.re = re-x.re;
    result.im = im-x.im;
    return result;
}
template <typename T> inline Complex<T> Complex<T>::operator*(const Complex<T>& x) const {
    Complex<T> result;
    result.re = re*x.re-im*x.im;
    result.im = re*x.im+im*x.re;
    return result;
}
template <typename T> inline bool Complex<T>::operator==(const Complex<T>& x) const {
    return (re==x.re)&&(im==x.im);
}
template <typename T> inline bool Complex<T>::operator!=(const Complex<T>& x) const {
    return (re!=x.re)||(im!=x.im);
}
template <typename T> inline Complex<T> operator+(typename Complex<T>::elem_type a, const Complex<T>& x) {
    Complex<T> result;
    result.re = a+x.re;
    result.im = x.im;
    return result;
}
template <typename T> inline Complex<T> operator-(typename Complex<T>::elem_type a, const Complex<T>& x) {
    Complex<T> result;
    result.re = a-x.re;
    result.im = -x.im;
    return result;
}
template <typename T> inline Complex<T> operator*(typename Complex<T>::elem_type a, const Complex<T>& x) {
    Complex<T> result;
    result.re = a*x.re;
    result.im = a*x.im;
    return result;
}
template <typename T> inline void Point2D<T>::MakeZero() {
    x = y = elem_type(0);
}
template <typename T> inline Point2D<T> Point2D<T>::Zero() {
    Point2D<T> result;
    result.MakeZero();
    return result;
}
template <typename T> inline typename Point2D<T>::elem_type Point2D<T>::Norm() const {
    return math::sqrt(x*x+y*y);
}
template <typename T> inline Point2D<T> Point2D<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Point2D<T> result;
    result.x = x*n;
    result.y = y*n;
    return result;
}
template <typename T> inline Point2D<T> Point2D<T>::operator-() const {
    Point2D<T> result;
    result.x = -x;
    result.y = -y;
    return result;
}
template <typename T> inline Point2D<T> Point2D<T>::operator*(typename Point2D<T>::elem_type a) const {
    Point2D<T> result;
    result.x = x*a;
    result.y = y*a;
    return result;
}
template <typename T> inline Point2D<T> Point2D<T>::operator+(const Point2D<T>& p) const {
    Point2D<T> result;
    result.x = x+p.x;
    result.y = y+p.y;
    return result;
}
template <typename T> inline Point2D<T> Point2D<T>::operator-(const Point2D<T>& p) const {
    Point2D<T> result;
    result.x = x-p.x;
    result.y = y-p.y;
    return result;
}
template <typename T> inline typename Point2D<T>::elem_type Point2D<T>::operator*(const Point2D<T>& p) const {
    return x*p.x+y*p.y;
}
template <typename T> inline bool Point2D<T>::operator==(const Point2D<T>& p) const {
    return (x==p.x)&&(y==p.y);
}
template <typename T> inline bool Point2D<T>::operator!=(const Point2D<T>& p) const {
    return (x!=p.x)||(y!=p.y);
}
template <typename T> inline Point2D<T> operator*(typename Point2D<T>::elem_type a, const Point2D<T>& p) {
    Point2D<T> result;
    result.x = a*p.x;
    result.y = a*p.y;
    return result;
}
template <typename T> inline void Vector2D<T>::MakeZero() {
    v[0] = v[1] = elem_type(0);
}
template <typename T> inline Vector2D<T> Vector2D<T>::Zero() {
    Vector2D<T> result;
    result.MakeZero();;
    return result;
}
template <typename T> inline typename Vector2D<T>::elem_type Vector2D<T>::Norm() const {
    return math::sqrt(v[0]*v[0]+v[1]*v[1]);
}
template <typename T> inline Vector2D<T> Vector2D<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Vector2D<T> result;
    result.v[0] = v[0]*n;
    result.v[1] = v[1]*n;
    return result;
}
template <typename T> inline Vector2D<T> Vector2D<T>::operator-() const {
    Vector2D<T> result;
    result.v[0] = -v[0];
    result.v[1] = -v[1];
    return result;
}
template <typename T> inline Vector2D<T> Vector2D<T>::operator*(typename Vector2D<T>::elem_type a) const {
    Vector2D<T> result;
    result.v[0] = v[0]*a;
    result.v[1] = v[1]*a;
    return result;
}
template <typename T> inline Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& x) const {
    Vector2D<T> result;
    result.v[0] = v[0]+x.v[0];
    result.v[1] = v[1]+x.v[1];
    return result;
}
template <typename T> inline Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& x) const {
    Vector2D<T> result;
    result.v[0] = v[0]-x.v[0];
    result.v[1] = v[1]-x.v[1];
    return result;
}
template <typename T> inline typename Vector2D<T>::elem_type Vector2D<T>::operator*(const Vector2D<T>& x) const {
    return v[0]*x.v[0]+v[1]*x.v[1];
}
template <typename T> inline bool Vector2D<T>::operator==(const Vector2D<T>& x) const {
    return (v[0]==x.v[0])&&(v[1]==x.v[1]);
}
template <typename T> inline bool Vector2D<T>::operator!=(const Vector2D<T>& x) const {
    return (v[0]!=x.v[0])||(v[1]!=x.v[1]);
}
template <typename T> inline Vector2D<T> operator*(typename Vector2D<T>::elem_type a, const Vector2D<T>& x) {
    Vector2D<T> result;
    result.v[0] = a*x.v[0];
    result.v[1] = a*x.v[1];
    return result;
}
template <typename T> inline void Triple<T>::MakeZero() {
    i = j = k = elem_type(0);
}
template <typename T> inline Triple<T> Triple<T>::Zero() {
    Triple<T> result;
    result.MakeZero();
    return result;
}
template <typename T> inline typename Triple<T>::elem_type Triple<T>::Norm() const {
    return math::sqrt(i*i+j*j+k*k);
}
template <typename T> inline Triple<T> Triple<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Triple<T> result;
    result.i = i*n;
    result.j = j*n;
    result.k = k*n;
    return result;
}
template <typename T> inline Triple<T> Triple<T>::operator-() const {
    Triple<T> result;
    result.i = -i;
    result.j = -j;
    result.k = -k;
    return result;
}
template <typename T> inline Triple<T> Triple<T>::operator*(typename Triple<T>::elem_type a) const {
    Triple<T> result;
    result.i = i*a;
    result.j = j*a;
    result.k = k*a;
    return result;
}
template <typename T> inline Triple<T> Triple<T>::operator+(const Triple<T>& t) const {
    Triple<T> result;
    result.i = i+t.i;
    result.j = j+t.j;
    result.k = k+t.k;
    return result;
}
template <typename T> inline Triple<T> Triple<T>::operator-(const Triple<T>& t) const {
    Triple<T> result;
    result.i = i-t.i;
    result.j = j-t.j;
    result.k = k-t.k;
    return result;
}
template <typename T> inline Triple<T> Triple<T>::operator*(const Triple<T>& t) const {
    Triple<T> result;
    result.i = j*t.k-k*t.j;
    result.j = k*t.i-i*t.k;
    result.k = i*t.j-j*t.i;
    return result;
}
template <typename T> inline bool Triple<T>::operator==(const Triple<T>& t) const {
    return (i==t.i)&&(j==t.j)&&(k==t.k);
}
template <typename T> inline bool Triple<T>::operator!=(const Triple<T>& t) const {
    return (i!=t.i)||(j!=t.j)||(k!=t.k);
}
template <typename T> inline Triple<T> operator*(typename Triple<T>::elem_type a, const Triple<T>& t) {
    Triple<T> result;
    result.i = a*t.i;
    result.j = a*t.j;
    result.k = a*t.k;
    return result;
}
template <typename T> inline void Point3D<T>::MakeZero() {
    x = y = z = elem_type(0);
}
template <typename T> inline Point3D<T> Point3D<T>::Zero() {
    Point3D<T> result;
    result.MakeZero();
    return result;
}
template <typename T> inline typename Point3D<T>::elem_type Point3D<T>::Norm() const {
    return math::sqrt(x*x+y*y+z*z);
}
template <typename T> inline Point3D<T> Point3D<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Point3D<T> result;
    result.x = x*n;
    result.y = y*n;
    result.z = z*n;
    return result;
}
template <typename T> inline Point3D<T> Point3D<T>::operator-() const {
    Point3D<T> result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    return result;
}
template <typename T> inline Point3D<T> Point3D<T>::operator*(typename Point3D<T>::elem_type a) const {
    Point3D<T> result;
    result.x = x*a;
    result.y = y*a;
    result.z = z*a;
    return result;
}
template <typename T> inline Point3D<T> Point3D<T>::operator+(const Point3D<T>& p) const {
    Point3D<T> result;
    result.x = x+p.x;
    result.y = y+p.y;
    result.z = z+p.z;
    return result;
}
template <typename T> inline Point3D<T> Point3D<T>::operator-(const Point3D<T>& p) const {
    Point3D<T> result;
    result.x = x-p.x;
    result.y = y-p.y;
    result.z = z-p.z;
    return result;
}
template <typename T> inline typename Point3D<T>::elem_type Point3D<T>::operator*(const Point3D<T>& p) const {
    return x*p.x+y*p.y+z*p.z;
}
template <typename T> inline bool Point3D<T>::operator==(const Point3D<T>& p) const {
    return (x==p.x)&&(y==p.y)&&(z==p.z);
}
template <typename T> inline bool Point3D<T>::operator!=(const Point3D<T>& p) const {
    return (x!=p.x)||(y!=p.y)||(z!=p.z);
}
template <typename T> inline Point3D<T> operator*(typename Point3D<T>::elem_type a, const Point3D<T>& p) {
    Point3D<T> result;
    result.x = a*p.x;
    result.y = a*p.y;
    result.z = a*p.z;
    return result;
}
template <typename T> inline void RGBColor<T>::MakeBlack() {
    r = g = b = elem_type(0);
}
template <typename T> inline void RGBColor<T>::MakeWhite() {
    r = g = b = elem_type(1);
}
template <typename T> inline RGBColor<T> RGBColor<T>::Black() {
    RGBColor<T> result;
    result.MakeBlack();
    return result;
}
template <typename T> inline RGBColor<T> RGBColor<T>::White() {
    RGBColor<T> result;
    result.MakeWhite();
    return result;
}
template <typename T> inline typename RGBColor<T>::elem_type RGBColor<T>::ColorIntensity() const {
    return r+g+b;
}
template <typename T> inline RGBColor<T> RGBColor<T>::Clamp() const {
    RGBColor<T> result;
    result.r = math::clamp(r, elem_type(0), elem_type(1));
    result.g = math::clamp(g, elem_type(0), elem_type(1));
    result.b = math::clamp(b, elem_type(0), elem_type(1));
    return result;
}
template <typename T> inline RGBColor<T> RGBColor<T>::ColorInverse() const {
    RGBColor<T> result;
    result.r = elem_type(1)-r;
    result.g = elem_type(1)-g;
    result.b = elem_type(1)-b;
    return result;
}
template <typename T> inline RGBColor<T>::operator RGBAColor<typename RGBColor<T>::elem_type>() const {
    Vector4D<elem_type> tmp_result;
    tmp_result.downgrade.vector3d.c = *this;
    tmp_result.c.a = elem_type(1);
    return tmp_result.c;
}
template <typename T> inline void Vector3D<T>::MakeZero() {
    v[0] = v[1] = v[2] = elem_type(0);
}
template <typename T> inline Vector3D<T> Vector3D<T>::Zero() {
    Vector3D<T> result;
    result.MakeZero();
    return result;
}
template <typename T> inline typename Vector3D<T>::elem_type Vector3D<T>::Norm() const {
    return math::sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}
template <typename T> inline Vector3D<T> Vector3D<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Vector3D<T> result;
    result.v[0] = v[0]*n;
    result.v[1] = v[1]*n;
    result.v[2] = v[2]*n;
    return result;
}
template <typename T> inline Vector3D<T> Vector3D<T>::operator-() const {
    Vector3D<T> result;
    result.v[0] = -v[0];
    result.v[1] = -v[1];
    result.v[2] = -v[2];
    return result;
}
template <typename T> inline Vector3D<T> Vector3D<T>::operator*(typename Vector3D<T>::elem_type a) const {
    Vector3D<T> result;
    result.v[0] = v[0]*a;
    result.v[1] = v[1]*a;
    result.v[2] = v[2]*a;
    return result;
}
template <typename T> inline Vector3D<T> Vector3D<T>::operator+(const Vector3D<T>& x) const {
    Vector3D<T> result;
    result.v[0] = v[0]+x.v[0];
    result.v[1] = v[1]+x.v[1];
    result.v[2] = v[2]+x.v[2];
    return result;
}
template <typename T> inline Vector3D<T> Vector3D<T>::operator-(const Vector3D<T>& x) const {
    Vector3D<T> result;
    result.v[0] = v[0]-x.v[0];
    result.v[1] = v[1]-x.v[1];
    result.v[2] = v[2]-x.v[2];
    return result;
}
template <typename T> inline typename Vector3D<T>::elem_type Vector3D<T>::operator*(const Vector3D<T>& x) const {
    return v[0]*x.v[0]+v[1]*x.v[1]+v[2]*x.v[2];
}
template <typename T> inline bool Vector3D<T>::operator==(const Vector3D<T>& x) const {
    return (v[0]==x.v[0])&&(v[1]==x.v[1])&&(v[2]==x.v[2]);
}
template <typename T> inline bool Vector3D<T>::operator!=(const Vector3D<T>& x) const {
    return (v[0]!=x.v[0])||(v[1]!=x.v[1])||(v[2]!=x.v[2]);
}
template <typename T> inline Vector3D<T> operator*(typename Vector3D<T>::elem_type a, const Vector3D<T>& x) {
    Vector3D<T> result;
    result.v[0] = a*x.v[0];
    result.v[1] = a*x.v[1];
    result.v[2] = a*x.v[2];
    return result;
}
template <typename T> inline void Quaternion<T>::MakeIdentity() {
    i = j = k = elem_type(0);
    e = elem_type(1);
}
template <typename T> inline Quaternion<T> Quaternion<T>::Identity() {
    Quaternion<T> result;
    result.MakeIdentity();
    return result;
}
template <typename T> inline typename Quaternion<T>::elem_type Quaternion<T>::Norm() const {
    return math::sqrt(i*i+j*j+k*k+e*e);
}
template <typename T> inline Quaternion<T> Quaternion<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Quaternion<T> result;
    result.i = i*n;
    result.j = j*n;
    result.k = k*n;
    result.e = e*n;
    return result;
}
template <typename T> inline Quaternion<T> Quaternion<T>::Conjugate() const {
    Quaternion<T> result;
    result.i = -i;
    result.j = -j;
    result.k = -k;
    result.e = e;
    return result;
}
template <typename T> inline Quaternion<T> Quaternion<T>::Inverse() const {
    elem_type n = elem_type(1)/(i*i+j*j+k*k+e*e);
    return Conjugate()*n;
}
template <typename T> inline Quaternion<T> Quaternion<T>::operator-() const {
    Quaternion<T> result;
    result.i = -i;
    result.j = -j;
    result.k = -k;
    result.e = -e;
    return result;
}
template <typename T> inline Quaternion<T> Quaternion<T>::operator*(typename Quaternion<T>::elem_type a) const {
    Quaternion<T> result;
    result.i = i*a;
    result.j = j*a;
    result.k = k*a;
    result.e = e*a;
    return result;
}
template <typename T> inline Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& q) const {
    Quaternion<T> result;
    result.i = i+q.i;
    result.j = j+q.j;
    result.k = k+q.k;
    result.e = e+q.e;
    return result;
}
template <typename T> inline Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& q) const {
    Quaternion<T> result;
    result.i = i-q.i;
    result.j = j-q.j;
    result.k = k-q.k;
    result.e = e-q.e;
    return result;
}
template <typename T> inline Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& q) const {
    Quaternion<T> result;
    result.i = (e*q.i+i*q.e+j*q.k)-k*q.j;
    result.j = (e*q.j+j*q.e+k*q.i)-i*q.k;
    result.k = (e*q.k+i*q.j+k*q.e)-j*q.i;
    result.e = e*q.e-(i*q.i+j*q.j+k*q.k);
    return result;
}
template <typename T> inline bool Quaternion<T>::operator==(const Quaternion<T>& q) const {
    return (e==q.e)&&(i==q.i)&&(j==q.j)&&(k==q.k);
}
template <typename T> inline bool Quaternion<T>::operator!=(const Quaternion<T>& q) const {
    return (e!=q.e)||(i!=q.i)||(j!=q.j)||(k!=q.k);
}
template <typename T> inline Vector3D<typename Quaternion<T>::elem_type> Quaternion<T>::GetRotateAxis() const {
    Vector3D<T> result;
    result.t.i = i;
    result.t.j = j;
    result.t.k = k;
    elem_type n = result.Norm();
    if(n>elem_type(mmd_math_const_eps)) {
        n = elem_type(1)/n;
        return result*n;
    } else {
        return result;
    }
}
template <typename T> inline typename Quaternion<T>::elem_type Quaternion<T>::GetRotateAngle() const {
    return math::acos(e)*elem_type(2);
}
template <typename T> inline Matrix4x4<typename Quaternion<T>::elem_type> mmd::Quaternion<T>::ToRotateMatrix() const {
    Matrix4x4<elem_type> result;
    elem_type ii = i*i;
    elem_type jj = j*j;
    elem_type kk = k*k;
    elem_type ij = i*j;
    elem_type jk = j*k;
    elem_type ki = i*k;
    elem_type ie = i*e;
    elem_type je = j*e;
    elem_type ke = k*e;
    result.r.v[0].v[0] = elem_type(1)-elem_type(2)*(jj+kk);
    result.r.v[0].v[1] = elem_type(2)*(ij+ke);
    result.r.v[0].v[2] = elem_type(2)*(ki-je);
    result.r.v[1].v[0] = elem_type(2)*(ij-ke);
    result.r.v[1].v[1] = elem_type(1)-elem_type(2)*(kk+ii);
    result.r.v[1].v[2] = elem_type(2)*(jk+ie);
    result.r.v[2].v[0] = elem_type(2)*(ki+je);
    result.r.v[2].v[1] = elem_type(2)*(jk-ie);
    result.r.v[2].v[2] = elem_type(1)-elem_type(2)*(ii+jj);
    result.r.v[0].v[3] = result.r.v[1].v[3] = result.r.v[2].v[3] = result.r.v[3].v[0] = result.r.v[3].v[1] = result.r.v[3].v[2] = elem_type(0);
    result.r.v[3].v[3] = elem_type(1);
    return result;
}
template <typename T> inline Quaternion<T> operator*(typename Quaternion<T>::elem_type a, const Quaternion<T>& q) {
    Quaternion<T> result;
    result.i = a*q.i;
    result.j = a*q.j;
    result.k = a*q.k;
    result.e = a*q.e;
    return result;
}
template <typename T> inline void Point4D<T>::MakeZero() {
    x = y = z = w = elem_type(0);
}
template <typename T> inline Point4D<T> Point4D<T>::Zero() {
    Point4D<T> result;
    result.MakeZero();
    return result;
}
template <typename T> inline typename Point4D<T>::elem_type Point4D<T>::Norm() const {
    return math::sqrt(x*x+y*y+z*z+w*w);
}
template <typename T> inline Point4D<T> Point4D<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Point4D<T> result;
    result.x = x*n;
    result.y = y*n;
    result.z = z*n;
    result.w = w*n;
    return result;
}
template <typename T> inline Point4D<T> Point4D<T>::operator-() const {
    Point4D<T> result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;
    return result;
}
template <typename T> inline Point4D<T> Point4D<T>::operator*(typename Point4D<T>::elem_type a) const {
    Point4D<T> result;
    result.x = x*a;
    result.y = y*a;
    result.z = z*a;
    result.w = w*a;
    return result;
}
template <typename T> inline Point4D<T> Point4D<T>::operator+(const Point4D<T>& p) const {
    Point4D<T> result;
    result.x = x+p.x;
    result.y = y+p.y;
    result.z = z+p.z;
    result.w = w+p.w;
    return result;
}
template <typename T> inline Point4D<T> Point4D<T>::operator-(const Point4D<T>& p) const {
    Point4D<T> result;
    result.x = x-p.x;
    result.y = y-p.y;
    result.z = z-p.z;
    result.w = w-p.w;
    return result;
}
template <typename T> inline typename Point4D<T>::elem_type Point4D<T>::operator*(const Point4D<T>& p) const {
    return x*p.x+y*p.y+z*p.z+w*p.w;
}
template <typename T> inline bool Point4D<T>::operator==(const Point4D<T>& p) const {
    return (x==p.x)&&(y==p.y)&&(z==p.z)&&(w==p.w);
}
template <typename T> inline bool Point4D<T>::operator!=(const Point4D<T>& p) const {
    return (x!=p.x)||(y!=p.y)||(z!=p.z)||(w!=p.w);
}
template <typename T> inline Point4D<T> operator*(typename Point4D<T>::elem_type a, const Point4D<T>& p) {
    Point4D<T> result;
    result.x = a*p.x;
    result.y = a*p.y;
    result.z = a*p.z;
    result.w = a*p.w;
    return result;
}
template <typename T> inline void RGBAColor<T>::MakeBlack() {
    r = g = b = elem_type(0);
}
template <typename T> inline void RGBAColor<T>::MakeWhite() {
    r = g = b = elem_type(1);
}
template <typename T> inline void RGBAColor<T>::MakeOpaque() {
    a = elem_type(1);
}
template <typename T> inline void RGBAColor<T>::MakeTransparent() {
    a = elem_type(1);
}
template <typename T> inline RGBAColor<T> RGBAColor<T>::Black() {
    RGBAColor<T> result;
    result.MakeBlack();
    result.MakeOpaque();
    return result;
}
template <typename T> inline RGBAColor<T> RGBAColor<T>::White() {
    RGBAColor<T> result;
    result.MakeWhite();
    result.MakeOpaque();
    return result;
}
template <typename T> inline RGBAColor<T> RGBAColor<T>::BlackTransparent() {
    RGBAColor<T> result;
    result.MakeBlack();
    result.MakeTransparent();
    return result;
}
template <typename T> inline typename RGBAColor<T>::elem_type RGBAColor<T>::ColorIntensity() const {
    return r+g+b;
}
template <typename T> inline RGBAColor<T> RGBAColor<T>::Clamp() const {
    RGBAColor<T> result;
    result.r = math::clamp(r, elem_type(0), elem_type(1));
    result.g = math::clamp(g, elem_type(0), elem_type(1));
    result.b = math::clamp(b, elem_type(0), elem_type(1));
    result.a = math::clamp(a, elem_type(0), elem_type(1));
    return result;
}
template <typename T> inline RGBAColor<T> RGBAColor<T>::ColorInverse() const {
    RGBAColor<T> result;
    result.r = elem_type(1)-r;
    result.g = elem_type(1)-g;
    result.b = elem_type(1)-b;
    result.a = a;
    return result;
}
template <typename T> inline RGBAColor<T> RGBAColor<T>::AlphaInverse() const {
    RGBAColor<T> result;
    result.r = r;
    result.g = g;
    result.b = b;
    result.a = elem_type(1)-a;
    return result;
}
template <typename T> inline RGBAColor<T> RGBAColor<T>::Inverse() const {
    RGBAColor<T> result;
    result.r = elem_type(1)-r;
    result.g = elem_type(1)-g;
    result.b = elem_type(1)-b;
    result.a = elem_type(1)-a;
    return result;
}
template <typename T> inline RGBAColor<T>::operator RGBColor<typename RGBAColor<T>::elem_type>() const {
    return reinterpret_cast<const Vector4D<elem_type>*>(this)->downgrade.vector3d.c;
}
template <typename T> inline void Vector4D<T>::MakeZero() {
    v[0] = v[1] = v[2] = v[3] = elem_type(0);
}
template <typename T> inline Vector4D<T> Vector4D<T>::Zero() {
    Vector4D<T> result;
    result.MakeZero();
    return result;
}
template <typename T> inline typename Vector4D<T>::elem_type Vector4D<T>::Norm() const {
    return math::sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
}
template <typename T> inline Vector4D<T> Vector4D<T>::Normalize() const {
    elem_type n = elem_type(1)/Norm();
    Vector4D<T> result;
    result.v[0] = v[0]*n;
    result.v[1] = v[1]*n;
    result.v[2] = v[2]*n;
    result.v[3] = v[3]*n;
    return result;
}
template <typename T> inline Vector3D<T> Vector4D<T>::HomoProject() const {
    Vector3D<elem_type> result;
    result.v[0] = v[0]/v[3];
    result.v[1] = v[1]/v[3];
    result.v[2] = v[2]/v[3];
    return result;
}
template <typename T> inline Vector4D<T> Vector4D<T>::operator-() const {
    Vector4D<T> result;
    result.v[0] = -v[0];
    result.v[1] = -v[1];
    result.v[2] = -v[2];
    result.v[3] = -v[3];
    return result;
}
template <typename T> inline Vector4D<T> Vector4D<T>::operator*(typename Vector4D<T>::elem_type a) const {
    Vector4D<T> result;
    result.v[0] = v[0]*a;
    result.v[1] = v[1]*a;
    result.v[2] = v[2]*a;
    result.v[3] = v[3]*a;
    return result;
}
template <typename T> inline Vector4D<T> Vector4D<T>::operator+(const Vector4D<T>& x) const {
    Vector4D<T> result;
    result.v[0] = v[0]+x.v[0];
    result.v[1] = v[1]+x.v[1];
    result.v[2] = v[2]+x.v[2];
    result.v[3] = v[3]+x.v[3];
    return result;
}
template <typename T> inline Vector4D<T> Vector4D<T>::operator-(const Vector4D<T>& x) const {
    Vector4D<T> result;
    result.v[0] = v[0]-x.v[0];
    result.v[1] = v[1]-x.v[1];
    result.v[2] = v[2]-x.v[2];
    result.v[3] = v[3]-x.v[3];
    return result;
}
template <typename T> inline typename Vector4D<T>::elem_type Vector4D<T>::operator*(const Vector4D<T>& x) const {
    return v[0]*x.v[0]+v[1]*x.v[1]+v[2]*x.v[2]+v[3]*x.v[3];
}
template <typename T> inline bool Vector4D<T>::operator==(const Vector4D<T>& x) const {
    return (v[0]==x.v[0])&&(v[1]==x.v[1])&&(v[2]==x.v[2])&&(v[3]==x.v[3]);
}
template <typename T> inline bool Vector4D<T>::operator!=(const Vector4D<T>& x) const {
    return (v[0]!=x.v[0])||(v[1]!=x.v[1])||(v[2]!=x.v[2])||(v[3]!=x.v[3]);
}
template <typename T> inline Vector4D<T> operator*(typename Vector4D<T>::elem_type a, const Vector4D<T>& x) {
    Vector4D<T> result;
    result.v[0] = a*x.v[0];
    result.v[1] = a*x.v[1];
    result.v[2] = a*x.v[2];
    result.v[3] = a*x.v[3];
    return result;
}
template <typename T> inline void Matrix4x4<T>::MakeZero() {
    v[0] = v[1] = v[2] = v[3] = v[4] = v[5] = v[6] = v[7] = v[8] = v[9] = v[10] = v[11] = v[12] = v[13] = v[14] = v[15] = elem_type(0);
}
template <typename T> inline void Matrix4x4<T>::MakeIdentity() {
    v[1] = v[2] = v[3] = v[4] = v[6] = v[7] = v[8] = v[9] = v[11] = v[12] = v[13] = v[14] = elem_type(0);
    v[0] = v[5] = v[10] = v[15] = elem_type(1);
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::Zero() {
    Matrix4x4<T> result;
    result.MakeZero();
    return result;
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::Identity() {
    Matrix4x4<T> result;
    result.MakeIdentity();
    return result;
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::Transpose() const {
    Matrix4x4<T> result;
    result.e.a11 = e.a11;
    result.e.a12 = e.a21;
    result.e.a13 = e.a31;
    result.e.a14 = e.a41;
    result.e.a21 = e.a12;
    result.e.a22 = e.a22;
    result.e.a23 = e.a32;
    result.e.a24 = e.a42;
    result.e.a31 = e.a13;
    result.e.a32 = e.a23;
    result.e.a33 = e.a33;
    result.e.a34 = e.a43;
    result.e.a41 = e.a14;
    result.e.a42 = e.a24;
    result.e.a43 = e.a34;
    result.e.a44 = e.a44;
    return result;
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::Inverse() const {
    Matrix4x4<T> result;
    elem_type r0[8], r1[8], r2[8], r3[8];
    elem_type *s[4];
    s[0] = r0;
    s[1] = r1;
    s[2] = r2;
    s[3] = r3;
    register int i, j, p, jj;
    for(i = 0;i<4;++i) {
        for(j = 0;j<4;++j) {
            s[i][j] = r.v[i].v[j];
            if(i==j) {
                s[i][j+4] = elem_type(1);
            } else {
                s[i][j+4] = elem_type(0);
            }
        }
    }
    elem_type scp[4];
    for(i = 0;i<4;++i) {
        scp[i] = abs(s[i][0]);
        for(j = 1;j<4;++j) {
            elem_type x = abs(s[i][j]);
            if(x>scp[i]) {
                scp[i] = x;
            }
        }
        if(scp[i]==0) {
            return Matrix4x4<T>::Zero();
        }
    }
    int pivot_to;
    elem_type scp_max;
    for(i = 0;i<4;++i) {
        pivot_to = i;
        scp_max = abs(s[i][i]/scp[i]);
        for(p = i+1;p<4;++p) {
            elem_type x = abs(s[p][i]/scp[p]);
            if(x>scp_max) {
                scp_max = x;
                pivot_to = p;
            }
        }
        if(pivot_to!=i) {
            elem_type *ps, pscp;
            ps = s[i];
            s[i] = s[pivot_to];
            s[pivot_to] = ps;
            pscp = scp[i];
            scp[i] = scp[pivot_to];
            scp[pivot_to] = pscp;
        }
        elem_type m;
        for(j = i+1;j<4;++j) {
            m = s[j][i]/s[i][i];
            s[j][i] = elem_type(0);
            for(jj = i+1;jj<8;++jj) {
                s[j][jj] -= m*s[i][jj];
            }
        }
    }
    if(s[3][3]==0) {
        return Matrix4x4<T>::Zero();
    }
    elem_type m;
    for(i = 1;i<4;++i) {
        for(j = 0;j<i;++j) {
            m = s[j][i]/s[i][i];
            for(jj = j+1;jj<8;++jj) {
                s[j][jj] -= m*s[i][jj];
            }
        }
    }
    for(i = 0;i<4;++i) {
        for(j = 0;j<4;++j) {
            result.r.v[i].v[j] = s[i][j+4]/s[i][i];
        }
    }
    return result;
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::operator-() const {
    Matrix4x4<T> result;
    result.v[0] = -v[0];
    result.v[1] = -v[1];
    result.v[2] = -v[2];
    result.v[3] = -v[3];
    result.v[4] = -v[4];
    result.v[5] = -v[5];
    result.v[6] = -v[6];
    result.v[7] = -v[7];
    result.v[8] = -v[8];
    result.v[9] = -v[9];
    result.v[10] = -v[10];
    result.v[11] = -v[11];
    result.v[12] = -v[12];
    result.v[13] = -v[13];
    result.v[14] = -v[14];
    result.v[15] = -v[15];
    return result;
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::operator*(typename Matrix4x4<T>::elem_type a) const {
    Matrix4x4<T> result;
    result.v[0] = v[0]*a;
    result.v[1] = v[1]*a;
    result.v[2] = v[2]*a;
    result.v[3] = v[3]*a;
    result.v[4] = v[4]*a;
    result.v[5] = v[5]*a;
    result.v[6] = v[6]*a;
    result.v[7] = v[7]*a;
    result.v[8] = v[8]*a;
    result.v[9] = v[9]*a;
    result.v[10] = v[10]*a;
    result.v[11] = v[11]*a;
    result.v[12] = v[12]*a;
    result.v[13] = v[13]*a;
    result.v[14] = v[14]*a;
    result.v[15] = v[15]*a;
    return result;
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& m) const {
    Matrix4x4<T> result;
    result.v[0] = v[0]+m.v[0];
    result.v[1] = v[1]+m.v[1];
    result.v[2] = v[2]+m.v[2];
    result.v[3] = v[3]+m.v[3];
    result.v[4] = v[4]+m.v[4];
    result.v[5] = v[5]+m.v[5];
    result.v[6] = v[6]+m.v[6];
    result.v[7] = v[7]+m.v[7];
    result.v[8] = v[8]+m.v[8];
    result.v[9] = v[9]+m.v[9];
    result.v[10] = v[10]+m.v[10];
    result.v[11] = v[11]+m.v[11];
    result.v[12] = v[12]+m.v[12];
    result.v[13] = v[13]+m.v[13];
    result.v[14] = v[14]+m.v[14];
    result.v[15] = v[15]+m.v[15];
    return result;
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& m) const {
    Matrix4x4<T> result;
    result.v[0] = v[0]-m.v[0];
    result.v[1] = v[1]-m.v[1];
    result.v[2] = v[2]-m.v[2];
    result.v[3] = v[3]-m.v[3];
    result.v[4] = v[4]-m.v[4];
    result.v[5] = v[5]-m.v[5];
    result.v[6] = v[6]-m.v[6];
    result.v[7] = v[7]-m.v[7];
    result.v[8] = v[8]-m.v[8];
    result.v[9] = v[9]-m.v[9];
    result.v[10] = v[10]-m.v[10];
    result.v[11] = v[11]-m.v[11];
    result.v[12] = v[12]-m.v[12];
    result.v[13] = v[13]-m.v[13];
    result.v[14] = v[14]-m.v[14];
    result.v[15] = v[15]-m.v[15];
    return result;
}
template <typename T> inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& m) const {
    Matrix4x4<T> result;
    result.e.a11 = e.a11*m.e.a11+e.a12*m.e.a21+e.a13*m.e.a31+e.a14*m.e.a41;
    result.e.a12 = e.a11*m.e.a12+e.a12*m.e.a22+e.a13*m.e.a32+e.a14*m.e.a42;
    result.e.a13 = e.a11*m.e.a13+e.a12*m.e.a23+e.a13*m.e.a33+e.a14*m.e.a43;
    result.e.a14 = e.a11*m.e.a14+e.a12*m.e.a24+e.a13*m.e.a34+e.a14*m.e.a44;
    result.e.a21 = e.a21*m.e.a11+e.a22*m.e.a21+e.a23*m.e.a31+e.a24*m.e.a41;
    result.e.a22 = e.a21*m.e.a12+e.a22*m.e.a22+e.a23*m.e.a32+e.a24*m.e.a42;
    result.e.a23 = e.a21*m.e.a13+e.a22*m.e.a23+e.a23*m.e.a33+e.a24*m.e.a43;
    result.e.a24 = e.a21*m.e.a14+e.a22*m.e.a24+e.a23*m.e.a34+e.a24*m.e.a44;
    result.e.a31 = e.a31*m.e.a11+e.a32*m.e.a21+e.a33*m.e.a31+e.a34*m.e.a41;
    result.e.a32 = e.a31*m.e.a12+e.a32*m.e.a22+e.a33*m.e.a32+e.a34*m.e.a42;
    result.e.a33 = e.a31*m.e.a13+e.a32*m.e.a23+e.a33*m.e.a33+e.a34*m.e.a43;
    result.e.a34 = e.a31*m.e.a14+e.a32*m.e.a24+e.a33*m.e.a34+e.a34*m.e.a44;
    result.e.a41 = e.a41*m.e.a11+e.a42*m.e.a21+e.a43*m.e.a31+e.a44*m.e.a41;
    result.e.a42 = e.a41*m.e.a12+e.a42*m.e.a22+e.a43*m.e.a32+e.a44*m.e.a42;
    result.e.a43 = e.a41*m.e.a13+e.a42*m.e.a23+e.a43*m.e.a33+e.a44*m.e.a43;
    result.e.a44 = e.a41*m.e.a14+e.a42*m.e.a24+e.a43*m.e.a34+e.a44*m.e.a44;
    return result;
}
template <typename T> inline Matrix4x4<T> operator*(typename Matrix4x4<T>::elem_type a, const Matrix4x4<T>& m) {
    Matrix4x4<T> result;
    result.v[0] = a*m.v[0];
    result.v[1] = a*m.v[1];
    result.v[2] = a*m.v[2];
    result.v[3] = a*m.v[3];
    result.v[4] = a*m.v[4];
    result.v[5] = a*m.v[5];
    result.v[6] = a*m.v[6];
    result.v[7] = a*m.v[7];
    result.v[8] = a*m.v[8];
    result.v[9] = a*m.v[9];
    result.v[10] = a*m.v[10];
    result.v[11] = a*m.v[11];
    result.v[12] = a*m.v[12];
    result.v[13] = a*m.v[13];
    result.v[14] = a*m.v[14];
    result.v[15] = a*m.v[15];
    return result;
}
template <typename T> inline Vector4D<T> operator*(const Vector4D<T>& v, const Matrix4x4<T>& m) {
    Vector4D<T> result;
    result.v[0] = v.v[0]*m.r.v[0].v[0]+v.v[1]*m.r.v[1].v[0]+v.v[2]*m.r.v[2].v[0]+v.v[3]*m.r.v[3].v[0];
    result.v[1] = v.v[0]*m.r.v[0].v[1]+v.v[1]*m.r.v[1].v[1]+v.v[2]*m.r.v[2].v[1]+v.v[3]*m.r.v[3].v[1];
    result.v[2] = v.v[0]*m.r.v[0].v[2]+v.v[1]*m.r.v[1].v[2]+v.v[2]*m.r.v[2].v[2]+v.v[3]*m.r.v[3].v[2];
    result.v[3] = v.v[0]*m.r.v[0].v[3]+v.v[1]*m.r.v[1].v[3]+v.v[2]*m.r.v[2].v[3]+v.v[3]*m.r.v[3].v[3];
    return result;
}
template <typename T> inline Vector3D<T> rotate(const Vector3D<T>& v, const Matrix4x4<T>& m) {
    Vector3D<T> result;
    result.v[0] = v.v[0]*m.r.v[0].v[0]+v.v[1]*m.r.v[1].v[0]+v.v[2]*m.r.v[2].v[0];
    result.v[1] = v.v[0]*m.r.v[0].v[1]+v.v[1]*m.r.v[1].v[1]+v.v[2]*m.r.v[2].v[1];
    result.v[2] = v.v[0]*m.r.v[0].v[2]+v.v[1]*m.r.v[1].v[2]+v.v[2]*m.r.v[2].v[2];
    return result;
}
template <typename T> inline Vector3D<T> transform(const Vector3D<T>& v, const Matrix4x4<T>& m) {
    Vector3D<T> result;
    result.v[0] = v.v[0]*m.r.v[0].v[0]+v.v[1]*m.r.v[1].v[0]+v.v[2]*m.r.v[2].v[0]+m.r.v[3].v[0];
    result.v[1] = v.v[0]*m.r.v[0].v[1]+v.v[1]*m.r.v[1].v[1]+v.v[2]*m.r.v[2].v[1]+m.r.v[3].v[1];
    result.v[2] = v.v[0]*m.r.v[0].v[2]+v.v[1]*m.r.v[1].v[2]+v.v[2]*m.r.v[2].v[2]+m.r.v[3].v[2];
    return result;
}

template <typename T> inline Quaternion<T> AxisToQuaternion(const Vector3D<T>& axis, typename Vector3D<T>::elem_type angle) {
    Vector4D<T> result;
    T norm = axis.Norm();
    if(norm<T(mmd_math_const_eps)) {
        result.q.MakeIdentity();
    } else {
        angle *= T(0.5);
        result.downgrade.vector3d = (math::sin(angle)/norm)*axis;
        result.downgrade.scalar = math::cos(angle);
    }
    return result.q;
}
template <typename T> inline Vector3D<T> QuaternionToXYZ(const Quaternion<T>& quaternion) {
    T ii = quaternion.i*quaternion.i;
    T jj = quaternion.j*quaternion.j;
    T kk = quaternion.k*quaternion.k;
    T ei = quaternion.e*quaternion.i;
    T ej = quaternion.e*quaternion.j;
    T ek = quaternion.e*quaternion.k;
    T ij = quaternion.i*quaternion.j;
    T ik = quaternion.i*quaternion.k;
    T jk = quaternion.j*quaternion.k;
    Vector3D<T> result;
    result.p.x = math::atan2(T(2)*(ei-jk),1-T(2)*(ii+jj));
    result.p.y = math::asin(T(2)*(ej+ik));
    result.p.z = math::atan2(T(2)*(ek-ij),1-T(2)*(jj+kk));
    return result;
}
template <typename T> inline Vector3D<T> QuaternionToXZY(const Quaternion<T>& quaternion) {
    T ii = quaternion.i*quaternion.i;
    T jj = quaternion.j*quaternion.j;
    T kk = quaternion.k*quaternion.k;
    T ei = quaternion.e*quaternion.i;
    T ej = quaternion.e*quaternion.j;
    T ek = quaternion.e*quaternion.k;
    T ij = quaternion.i*quaternion.j;
    T ik = quaternion.i*quaternion.k;
    T jk = quaternion.j*quaternion.k;
    Vector3D<T> result;
    result.p.x = math::atan2(T(2)*(ei+jk),1-T(2)*(ii+kk));
    result.p.y = math::atan2(T(2)*(ej+ik),1-T(2)*(jj+kk));
    result.p.z = math::asin(T(2)*(ek-ij));
    return result;
}
template <typename T> inline Vector3D<T> QuaternionToYXZ(const Quaternion<T>& quaternion) {
    T ii = quaternion.i*quaternion.i;
    T jj = quaternion.j*quaternion.j;
    T kk = quaternion.k*quaternion.k;
    T ei = quaternion.e*quaternion.i;
    T ej = quaternion.e*quaternion.j;
    T ek = quaternion.e*quaternion.k;
    T ij = quaternion.i*quaternion.j;
    T ik = quaternion.i*quaternion.k;
    T jk = quaternion.j*quaternion.k;
    Vector3D<T> result;
    result.p.x = math::asin(T(2)*(ei-jk));
    result.p.y = math::atan2(T(2)*(ej+ik),1-T(2)*(ii+jj));
    result.p.z = math::atan2(T(2)*(ek+ij),1-T(2)*(ii+kk));
    return result;
}
template <typename T> inline Vector3D<T> QuaternionToYZX(const Quaternion<T>& quaternion) {
    T ii = quaternion.i*quaternion.i;
    T jj = quaternion.j*quaternion.j;
    T kk = quaternion.k*quaternion.k;
    T ei = quaternion.e*quaternion.i;
    T ej = quaternion.e*quaternion.j;
    T ek = quaternion.e*quaternion.k;
    T ij = quaternion.i*quaternion.j;
    T ik = quaternion.i*quaternion.k;
    T jk = quaternion.j*quaternion.k;
    Vector3D<T> result;
    result.p.x = math::atan2(T(2)*(ei-jk),1-T(2)*(ii+kk));
    result.p.y = math::atan2(T(2)*(ej-ik),1-T(2)*(jj+kk));
    result.p.z = math::asin(T(2)*(ek+ij));
    return result;
}
template <typename T> inline Vector3D<T> QuaternionToZXY(const Quaternion<T>& quaternion) {
    T ii = quaternion.i*quaternion.i;
    T jj = quaternion.j*quaternion.j;
    T kk = quaternion.k*quaternion.k;
    T ei = quaternion.e*quaternion.i;
    T ej = quaternion.e*quaternion.j;
    T ek = quaternion.e*quaternion.k;
    T ij = quaternion.i*quaternion.j;
    T ik = quaternion.i*quaternion.k;
    T jk = quaternion.j*quaternion.k;
    Vector3D<T> result;
    result.p.x = math::asin(T(2)*(ei+jk));
    result.p.y = math::atan2(T(2)*(ej-ik),1-T(2)*(ii+jj));
    result.p.z = math::atan2(T(2)*(ek-ij),1-T(2)*(ii+kk));
    return result;
}
template <typename T> inline Vector3D<T> QuaternionToZYX(const Quaternion<T>& quaternion) {
    T ii = quaternion.i*quaternion.i;
    T jj = quaternion.j*quaternion.j;
    T kk = quaternion.k*quaternion.k;
    T ei = quaternion.e*quaternion.i;
    T ej = quaternion.e*quaternion.j;
    T ek = quaternion.e*quaternion.k;
    T ij = quaternion.i*quaternion.j;
    T ik = quaternion.i*quaternion.k;
    T jk = quaternion.j*quaternion.k;
    Vector3D<T> result;
    result.p.x = math::atan2(T(2)*(ei+jk),1-T(2)*(ii+jj));
    result.p.y = math::asin(T(2)*(ej-ik));
    result.p.z = math::atan2(T(2)*(ek+ij),1-T(2)*(jj+kk));
    return result;
}

template <typename T> inline Quaternion<T> XYZToQuaternion(const Vector3D<T>& euler) {
    T cx = math::cos(euler.p.x*T(0.5));
    T sx = math::sin(euler.p.x*T(0.5));
    T cy = math::cos(euler.p.y*T(0.5));
    T sy = math::sin(euler.p.y*T(0.5));
    T cz = math::cos(euler.p.z*T(0.5));
    T sz = math::sin(euler.p.z*T(0.5));
    Quaternion<T> result;
    result.e = cx*cy*cz-sx*sy*sz;
    result.i = sx*cy*cz+cx*sy*sz;
    result.j = cx*sy*cz-sx*cy*sz;
    result.k = sx*sy*cz+cx*cy*sz;
    return result;
}
template <typename T> inline Quaternion<T> XZYToQuaternion(const Vector3D<T>& euler) {
    T cx = math::cos(euler.p.x*T(0.5));
    T sx = math::sin(euler.p.x*T(0.5));
    T cy = math::cos(euler.p.y*T(0.5));
    T sy = math::sin(euler.p.y*T(0.5));
    T cz = math::cos(euler.p.z*T(0.5));
    T sz = math::sin(euler.p.z*T(0.5));
    Quaternion<T> result;
    result.e = cx*cy*cz+sx*sy*sz;
    result.i = sx*cy*cz-cx*sy*sz;
    result.j = cx*sy*cz-sx*cy*sz;
    result.k = cx*cy*sz+sx*sy*cz;
    return result;
}
template <typename T> inline Quaternion<T> YXZToQuaternion(const Vector3D<T>& euler) {
    T cx = math::cos(euler.p.x*T(0.5));
    T sx = math::sin(euler.p.x*T(0.5));
    T cy = math::cos(euler.p.y*T(0.5));
    T sy = math::sin(euler.p.y*T(0.5));
    T cz = math::cos(euler.p.z*T(0.5));
    T sz = math::sin(euler.p.z*T(0.5));
    Quaternion<T> result;
    result.e = cx*cy*cz+sx*sy*sz;
    result.i = sx*cy*cz+cx*sy*sz;
    result.j = cx*sy*cz-sx*cy*sz;
    result.k = cx*cy*sz-sx*sy*cz;
    return result;
}
template <typename T> inline Quaternion<T> YZXToQuaternion(const Vector3D<T>& euler) {
    T cx = math::cos(euler.p.x*T(0.5));
    T sx = math::sin(euler.p.x*T(0.5));
    T cy = math::cos(euler.p.y*T(0.5));
    T sy = math::sin(euler.p.y*T(0.5));
    T cz = math::cos(euler.p.z*T(0.5));
    T sz = math::sin(euler.p.z*T(0.5));
    Quaternion<T> result;
    result.e = cx*cy*cz-sx*sy*sz;
    result.i = sx*cy*cz+cx*sy*sz;
    result.j = cx*sy*cz+sx*cy*sz;
    result.k = cx*cy*sz-sx*sy*cz;
    return result;
}
template <typename T> inline Quaternion<T> ZXYToQuaternion(const Vector3D<T>& euler) {
    T cx = math::cos(euler.p.x*T(0.5));
    T sx = math::sin(euler.p.x*T(0.5));
    T cy = math::cos(euler.p.y*T(0.5));
    T sy = math::sin(euler.p.y*T(0.5));
    T cz = math::cos(euler.p.z*T(0.5));
    T sz = math::sin(euler.p.z*T(0.5));
    Quaternion<T> result;
    result.e = cx*cy*cz-sx*sy*sz;
    result.i = sx*cy*cz-cx*sy*sz;
    result.j = cx*sy*cz+sx*cy*sz;
    result.k = cx*cy*sz+sx*sy*cz;
    return result;
}
template <typename T> inline Quaternion<T> ZYXToQuaternion(const Vector3D<T>& euler) {
    T cx = math::cos(euler.p.x*T(0.5));
    T sx = math::sin(euler.p.x*T(0.5));
    T cy = math::cos(euler.p.y*T(0.5));
    T sy = math::sin(euler.p.y*T(0.5));
    T cz = math::cos(euler.p.z*T(0.5));
    T sz = math::sin(euler.p.z*T(0.5));
    Quaternion<T> result;
    result.e = cx*cy*cz+sx*sy*sz;
    result.i = sx*cy*cz-cx*sy*sz;
    result.j = cx*sy*cz+sx*cy*sz;
    result.k = cx*cy*sz-sx*sy*cz;
    return result;
}

template <typename T> class LerpProxy {
    typedef typename T::elem_type elem_type;
public:
    LerpProxy(const T& a, const T& b)
        : a(a), b(b) {}
    T operator[](elem_type l) const {
        if(l<elem_type(mmd_math_const_eps)) {
            return a;
        } else if(l>(elem_type(1.0-mmd_math_const_eps))) {
            return b;
        } else {
            return (elem_type(1)-l)*a+l*b;
        }
    }
private:
    LerpProxy& operator=(const LerpProxy&);
    const T& a;
    const T& b;
};
template <typename T> class NLerpProxy {
    typedef typename T::elem_type elem_type;
public:
    NLerpProxy(const T& a, const T& b)
        : a(a), b(b) {}
    T operator[](elem_type l) const {
        if(l<elem_type(mmd_math_const_eps)) {
            return a;
        } else if(l>(elem_type(1)-elem_type(mmd_math_const_eps))) {
            return b;
        } else {
            if(a*b<elem_type(0)) {
                return ((elem_type(1)-l)*a-l*b).Normalize();
            } else {
                return ((elem_type(1)-l)*a+l*b).Normalize();
            }
        }
    }
private:
    NLerpProxy& operator=(const NLerpProxy&);
    const T& a;
    const T& b;
};
template <typename T> class SLerpProxy {
    typedef typename T::elem_type elem_type;
public:
    SLerpProxy(const T& a, const T& b)
        : a(a), b(b) {}
    T operator[](elem_type l) const {
        elem_type comega = a*b;
        bool flip = comega<elem_type(0);
        if(comega<elem_type(0)) {
            comega = -comega;
        }
        elem_type omega = math::acos(comega);
        if(omega>elem_type(mmd_math_const_eps)) {
            elem_type rsomega = elem_type(1)/math::sin(omega);
            elem_type p = math::sin((elem_type(1)-l)*omega)*rsomega;
            l = math::sin(l*omega)*rsomega;
            if(flip) {
                l = -l;
            }
            return a*p+b*l;
        } else {
            return a;
        }
    }
private:
    SLerpProxy& operator=(const SLerpProxy&);
    const T& a;
    const T& b;
};
template <typename T> class SLerpProxy<Quaternion<T>> {
    typedef T elem_type;
public:
    SLerpProxy(const Quaternion<T>& a, const Quaternion<T>& b)
        : a(a), b(b) {}
    Quaternion<T> operator[](elem_type l) const {
        elem_type comega = a.e*b.e+a.i*b.i+a.j*b.j+a.k*b.k;
        bool flip = comega<elem_type(0);
        if(flip) {
            comega = -comega;
        }
        elem_type omega = math::acos(comega);
        if(omega>elem_type(mmd_math_const_eps)) {
            elem_type rsomega = elem_type(1)/math::sin(omega);
            elem_type p = math::sin((elem_type(1)-l)*omega)*rsomega;
            l = math::sin(l*omega)*rsomega;
            if(flip) {
                l = -l;
            }
            return a*p+b*l;
        } else {
            return a;
        }
    }
private:
    SLerpProxy& operator=(const SLerpProxy&);
    const Quaternion<T>& a;
    const Quaternion<T>& b;
};
template <typename T> inline LerpProxy<T> Lerp(const T& a, const T& b) {
    return LerpProxy<T>(a, b);
}
template <typename T> inline NLerpProxy<T> NLerp(const T& a, const T& b) {
    return NLerpProxy<T>(a, b);
}
template <typename T> inline SLerpProxy<T> SLerp(const T& a, const T& b) {
    return SLerpProxy<T>(a, b);
}
template <typename T, size_t presample_resolution> inline Bezier<T, presample_resolution>::Bezier() {
    c_0.p.x = c_0.p.y = T(0);
    c_1.p.x = c_1.p.y = T(3);
    is_linear_ = true;
}
template <typename T, size_t presample_resolution> inline Bezier<T, presample_resolution>::Bezier(const Vector2D<T>& c_0, const Vector2D<T>& c_1)
    : c_0(T(3)*c_0), c_1(T(3)*c_1) {
    presample();
}
template <typename T, size_t presample_resolution> inline T Bezier<T, presample_resolution>::operator()(T x) const {
    if(is_linear_) {
        return x;
    } else {
        if(x<T(0)) {
            return T(0);
        } else if(x>T(1)) {
            return T(1);
        } else {
            return interpolate(x);
        }
    }
}
template <typename T, size_t presample_resolution> inline T Bezier<T, presample_resolution>::operator[](T x) const {
    if(is_linear_) {
        return x;
    }
    x *= presample_resolution-1;
    size_t ix = (size_t)x;
    T r = x-ix;
    if(ix<presample_resolution-1) {
        return (T(1.0)-r)*presamples_[ix]+r*presamples_[ix+1];
    } else {
        return presamples_[presample_resolution-1];
    }
}
template <typename T, size_t presample_resolution> inline const Vector2D<T>& Bezier<T, presample_resolution>::GetC(size_t i) const {
    const T r(T(1)/T(3));
    if(i==0) {
        return c_0*r;
    } else {
        return c_1*r;
    }
}
template <typename T, size_t presample_resolution> inline void Bezier<T, presample_resolution>::SetC(const Vector2D<T>& c_0, const Vector2D<T>& c_1) {
    this->c_0 = c_0*T(3);
    this->c_1 = c_1*T(3);
    presample();
}
template <typename T, size_t presample_resolution> inline void Bezier<T, presample_resolution>::presample() {
    if((c_0.p.x==c_0.p.y)&&(c_1.p.x==c_1.p.y)) {
        is_linear_ = true;
    } else {
        is_linear_ = false;
        for(size_t i = 0;i<presample_resolution;++i) {
            T x = i/T(presample_resolution-1);
            presamples_[i] = interpolate(x);
        }
    }
}
template <typename T, size_t presample_resolution> inline T Bezier<T, presample_resolution>::interpolate(T x) const {
    T l(0);
    T r(1);
    T m, lm(0), rm;
    for(size_t i = 0;i<32;++i) {
        lm = (l+r)*T(0.5);
        rm = T(1)-lm;
        m = lm*(rm*(rm*c_0.p.x+lm*c_1.p.x)+lm*lm);
        if(abs(m-x)<T(mmd_math_const_eps)) {
            break;
        }
        if(m>x) {
            r = lm;
        } else {
            l = lm;
        }
    }
    rm = T(1)-lm;
    return lm*(rm*(rm*c_0.p.y+lm*c_1.p.y)+lm*lm);
}

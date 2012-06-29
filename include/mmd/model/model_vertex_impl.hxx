
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

//// class Model::Vertex

//// ctor
//template <template <typename V> class T> inline
//Model::Vertex<T>::Vertex(
//    typename T<Vector3f>::type coordinate,
//    typename T<Vector3f>::type normal,
//    typename T<Vector2f>::type uv_coord,
//    typename T<Vector4f>::type extra_uv_1,
//    typename T<Vector4f>::type extra_uv_2,
//    typename T<Vector4f>::type extra_uv_3,
//    typename T<Vector4f>::type extra_uv_4,
//    typename T<SkinningOperator>::type skinning_operator,
//    typename T<float>::type edge_scale
//) : coordinate_(coordinate),
//    normal_(normal),
//    uv_coord_(uv_coord),
//    extra_uv_coord_1_(extra_uv_1),
//    extra_uv_coord_2_(extra_uv_2),
//    extra_uv_coord_3_(extra_uv_3),
//    extra_uv_coord_4_(extra_uv_4),
//    skinning_operator_(skinning_operator),
//    edge_scale_(edge_scale)
//{}

template <template <typename V> class T>
template <template <typename V1> class T1> inline
Model::Vertex<T>::Vertex(Vertex<T1> &v)
  : coordinate_(v.coordinate_),
    normal_(v.normal_),
    uv_coord_(v.uv_coord_),
    extra_uv_coord_1_(v.extra_uv_1_),
    extra_uv_coord_2_(v.extra_uv_2_),
    extra_uv_coord_3_(v.extra_uv_3_),
    extra_uv_coord_4_(v.extra_uv_4_),
    skinning_operator_(v.skinning_operator_),
    edge_scale_(v.edge_scale_)
{}

//// vmember: coordinate
template <template <typename V> class T> inline
const Vector3f&
Model::Vertex<T>::GetCoordinate() const {
    return coordinate_;
}

template <template <typename V> class T> inline
void
Model::Vertex<T>::SetCoordinate(const Vector3f &coordinate) {
    coordinate_ = coordinate;
}

//// vmember: normal
template <template <typename V> class T> inline
const Vector3f&
Model::Vertex<T>::GetNormal() const {
    return normal_;
}

template <template <typename V> class T> inline
void
Model::Vertex<T>::SetNormal(const Vector3f &normal) {
    normal_ = normal;
}

//// vmember: uv_coordinate
template <template <typename V> class T> inline
const Vector2f&
Model::Vertex<T>::GetUVCoordinate() const {
    return uv_coord_;
}

template <template <typename V> class T> inline
void
Model::Vertex<T>::SetUVCoordinate(const Vector2f &uv_coord) {
    uv_coord_ = uv_coord;
}

//// vmember: extra_uv_coordinate
template <template <typename V> class T> inline
const Vector4f&
Model::Vertex<T>::GetExtraUVCoordinate(size_t index) const {
    switch(index) {
    default: case 0:
        return extra_uv_coord_1_;
    case 1:
        return extra_uv_coord_2_;
    case 2:
        return extra_uv_coord_3_;
    case 3:
        return extra_uv_coord_4_;
    }
}

template <template <typename V> class T> inline
void
Model::Vertex<T>::SetExtraUVCoordinate(size_t index, const Vector4f &uv_coord) {
    switch(index) {
    default: case 0:
        extra_uv_coord_1_ = uv_coord;
    case 1:
        extra_uv_coord_2_ = uv_coord;
    case 2:
        extra_uv_coord_3_ = uv_coord;
    case 3:
        extra_uv_coord_4_ = uv_coord;
    }
}

//// omember: skinning_operator
template <template <typename V> class T> inline
const Model::SkinningOperator&
Model::Vertex<T>::GetSkinningOperator() const {
    return skinning_operator_;
}

template <template <typename V> class T> inline
Model::SkinningOperator&
Model::Vertex<T>::GetSkinningOperator() {
    return skinning_operator_;
}

//// vmember: edge_scale
template <template <typename V> class T> inline
float
Model::Vertex<T>::GetEdgeScale() const {
    return edge_scale_;
}

template <template <typename V> class T> inline
void
Model::Vertex<T>::SetEdgeScale(float edge_scale) {
    edge_scale_ = edge_scale;
}


/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

//// class Model::RigidBody

//// vmember: name
inline const std::wstring&
Model::RigidBody::GetName() const {
    return name_;
}

inline void
Model::RigidBody::SetName(const std::wstring &name) {
    name_ = name;
}

//// vmember: name_en
inline const std::wstring&
Model::RigidBody::GetNameEn() const {
    return name_en_;
}

inline void
Model::RigidBody::SetNameEn(const std::wstring &name) {
    name_en_ = name;
}

//// vmember: associated_bone_index
inline size_t
Model::RigidBody::GetAssociatedBoneIndex() const {
    return associated_bone_;
}

inline void
Model::RigidBody::SetAssociatedBoneIndex(size_t index) {
    associated_bone_ = index;
}

//// vmember: collision_group
inline size_t
Model::RigidBody::GetCollisionGroup() const {
    return collision_group_;
}

inline void
Model::RigidBody::SetCollisionGroup(size_t group) {
    collision_group_ = group;
}

//// omember: collision_mask
inline const std::bitset<16>&
Model::RigidBody::GetCollisionMask() const {
    return collision_mask_;
}

inline std::bitset<16>&
Model::RigidBody::GetCollisionMask() {
    return collision_mask_;
}

//// vmember: shape
inline Model::RigidBody::RigidBodyShape
Model::RigidBody::GetShape() const {
    return shape_;
}

inline void
Model::RigidBody::SetShape(Model::RigidBody::RigidBodyShape shape) {
    shape_ = shape;
}

//// vmember: dimensions
inline const Vector3f&
Model::RigidBody::GetDimensions() const {
    return dimensions_;
}

inline void
Model::RigidBody::SetDimensions(const Vector3f &dimensions) {
    dimensions_ = dimensions;
}

//// vmember: position
inline const Vector3f&
Model::RigidBody::GetPosition() const {
    return position_;
}

inline void
Model::RigidBody::SetPosition(const Vector3f &position) {
    position_ = position;
}

//// vmember: rotation
inline const Vector3f&
Model::RigidBody::GetRotation() const {
    return rotation_;
}

inline void
Model::RigidBody::SetRotation(const Vector3f &rotation) {
    rotation_ = rotation;
}

//// vmember: mass
inline float
Model::RigidBody::GetMass() const {
    return mass_;
}

inline void
Model::RigidBody::SetMass(float mass) {
    mass_ = mass;
}

//// vmember: translate_damp
inline float
Model::RigidBody::GetTranslateDamp() const {
    return translate_damp_;
}

inline void
Model::RigidBody::SetTranslateDamp(float damp) {
translate_damp_ = damp;
}

//// vmember: rotate_damp
inline float
Model::RigidBody::GetRotateDamp() const {
    return rotate_damp_;
}

inline void
Model::RigidBody::SetRotateDamp(float damp) {
    rotate_damp_ = damp;
}

//// vmember: restitution
inline float
Model::RigidBody::GetRestitution() const {
    return restitution_;
}

inline void
Model::RigidBody::SetRestitution(float restitution) {
    restitution_ = restitution;
}

//// vmember: friction
inline float
Model::RigidBody::GetFriction() const {
    return friction_;
}

inline void
Model::RigidBody::SetFriction(float friction) {
    friction_ = friction;
}

//// vmember: type
inline Model::RigidBody::RigidBodyType
Model::RigidBody::GetType() const {
    return type_;
}

inline void
Model::RigidBody::SetType(Model::RigidBody::RigidBodyType type) {
    type_ = type;
}


/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

//// class Model::Constraint

//// vmember: name
inline const std::wstring&
Model::Constraint::GetName() const {
    return name_;
}

inline void
Model::Constraint::SetName(const std::wstring &name) {
    name_ = name;
}

//// vmember: name_en
inline const std::wstring&
Model::Constraint::GetNameEn() const {
    return name_en_;
}

inline void
Model::Constraint::SetNameEn(const std::wstring &name) {
    name_en_ = name;
}

//// vmember: associated_rigid_bodies
inline size_t
Model::Constraint::GetAssociatedRigidBodyIndex(size_t n) const {
    return associated_rigid_bodies_[n];
}

inline void
Model::Constraint::SetAssociatedRigidBodyIndex(size_t n, size_t index) {
    associated_rigid_bodies_[n] = index;
}

//// vmember: position
inline const Vector3f&
Model::Constraint::GetPosition() const {
    return position_;
}

inline void
Model::Constraint::SetPosition(const Vector3f &position) {
    position_ = position;
}

//// vmember: rotation
inline const Vector3f&
Model::Constraint::GetRotation() const {
    return rotation_;
}

inline void
Model::Constraint::SetRotation(const Vector3f &rotation) {
    rotation_ = rotation;
}

//// vmember: position_lo_limit
inline const Vector3f&
Model::Constraint::GetPositionLowLimit() const {
    return position_lo_limit_;
}

inline void
Model::Constraint::SetPositionLowLimit(const Vector3f &limit) {
    position_lo_limit_ = limit;
}

//// vmember: position_hi_limit
inline const Vector3f&
Model::Constraint::GetPositionHighLimit() const {
    return position_hi_limit_;
}

inline void
Model::Constraint::SetPositionHighLimit(const Vector3f &limit) {
    position_hi_limit_ = limit;
}

//// vmember: rotation_lo_limit
inline const Vector3f&
Model::Constraint::GetRotationLowLimit() const {
    return rotation_lo_limit_;
}

inline void
Model::Constraint::SetRotationLowLimit(const Vector3f &limit) {
    rotation_lo_limit_ = limit;
}

//// vmember: rotation_hi_limit
inline const Vector3f&
Model::Constraint::GetRotationHighLimit() const {
    return rotation_hi_limit_;
}

inline void
Model::Constraint::SetRotationHighLimit(const Vector3f &limit) {
    rotation_hi_limit_ = limit;
}

//// vmember: spring_translate
inline const Vector3f&
Model::Constraint::GetSpringTranslate() const {
    return spring_translate_;
}

inline void
Model::Constraint::SetSpringTranslate(const Vector3f &translate) {
    spring_translate_ = translate;
}

//// vmember: spring_rotate
inline const Vector3f&
Model::Constraint::GetSpringRotate() const {
    return spring_rotate_;
}

inline void
Model::Constraint::SetSpringRotate(const Vector3f &rotate) {
    spring_rotate_ = rotate;
}


/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

//// class Model::Bone

//// vmember: name
inline const std::wstring&
Model::Bone::GetName() const {
    return name_;
}

inline void
Model::Bone::SetName(const std::wstring &name) {
    name_ = name;
}

//// vmember: name_en
inline const std::wstring&
Model::Bone::GetNameEn() const {
    return name_en_;
}

inline void
Model::Bone::SetNameEn(const std::wstring &name_en) {
    name_en_ = name_en;
}

//// vmember: position
inline const Vector3f&
Model::Bone::GetPosition() const {
    return position_;
}

inline void
Model::Bone::SetPosition(const Vector3f &position) {
    position_ = position;
}

//// vmember: parent_index
inline size_t
Model::Bone::GetParentIndex() const {
    return parent_index_;
}

inline void
Model::Bone::SetParentIndex(size_t parent_index) {
    parent_index_ = parent_index;
}

//// vmember: transform_level
inline size_t
Model::Bone::GetTransformLevel() const {
    return transform_level_;
}

inline void
Model::Bone::SetTransformLevel(size_t transform_level) {
    transform_level_ = transform_level;
}

//// vmember: child_use_id
inline bool
Model::Bone::IsChildUseID() const {
    return child_bone_.child_use_id_;
}

inline void
Model::Bone::SetChildUseID(bool child_use_id) {
    child_bone_.child_use_id_ = child_use_id;
}

//// vmember: rotatable
inline bool
Model::Bone::IsRotatable() const {
    return rotatable_;
}

inline void
Model::Bone::SetRotatable(bool rotatable) {
    rotatable_ = rotatable;
}

//// vmember: movable
inline bool
Model::Bone::IsMovable() const {
    return movable_;
}

inline void
Model::Bone::SetMovable(bool movable) {
    movable_ = movable;
}

//// vmember: visible
inline bool
Model::Bone::IsVisible() const {
    return visible_;
}

inline void
Model::Bone::SetVisible(bool visible) {
    visible_ = visible;
}

//// vmember: controllable
inline bool
Model::Bone::IsControllable() const {
    return controllable_;
}

inline void
Model::Bone::SetControllable(bool controllable) {
    controllable_ = controllable;
}

//// vmember: has_ik
inline bool
Model::Bone::IsHasIK() const {
    return has_ik_;
}

inline void
Model::Bone::SetHasIK(bool has_ik) {
    has_ik_ = has_ik;
}

//// vmember: append_rotate
inline bool
Model::Bone::IsAppendRotate() const {
    return append_rotate_;
}

inline void
Model::Bone::SetAppendRotate(bool append_rotate) {
    append_rotate_ = append_rotate;
}

//// vmember: append_translate
inline bool
Model::Bone::IsAppendTranslate() const {
    return append_translate_;
}

inline void
Model::Bone::SetAppendTranslate(bool append_translate) {
    append_translate_ = append_translate;
}

//// vmember: rot_axis_fixed
inline bool
Model::Bone::IsRotAxisFixed() const {
    return rot_axis_fixed_;
}

inline void
Model::Bone::SetRotAxisFixed(bool rot_axis_fixed) {
    rot_axis_fixed_ = rot_axis_fixed;
}

//// vmember: use_local_axis
inline bool
Model::Bone::IsUseLocalAxis() const {
    return use_local_axis_;
}

inline void
Model::Bone::SetUseLocalAxis(bool use_local_axis) {
    use_local_axis_ = use_local_axis;
}

//// vmember: post_physice
inline bool
Model::Bone::IsPostPhysics() const {
    return post_physics_;
}

inline void
Model::Bone::SetPostPhysics(bool post_physics) {
    post_physics_ = post_physics;
}

//// vmember: receive_transform
inline bool
Model::Bone::IsReceiveTransform() const {
    return receive_transform_;
}

inline void
Model::Bone::SetReceiveTransform(bool receive_transform) {
    receive_transform_ = receive_transform;
}

//// vmember: child_index
inline size_t
Model::Bone::GetChildIndex() const {
    return child_bone_.descriptor_.index_;
}

inline void
Model::Bone::SetChildIndex(size_t child_index) {
    child_bone_.descriptor_.index_ = child_index;
}

//// vmember: child_offset
inline const Vector3f&
Model::Bone::GetChildOffset() const {
    return child_bone_.descriptor_.offset_;
}

inline void
Model::Bone::SetChildOffset(const Vector3f &offset) {
    child_bone_.descriptor_.offset_ = offset;
}

//// vmember: append_index
inline size_t
Model::Bone::GetAppendIndex() const {
    return append_bone_.index_;
}

inline void
Model::Bone::SetAppendIndex(size_t index) {
    append_bone_.index_ = index;
}

//// vmember: append_ratio
inline float
Model::Bone::GetAppendRatio() const {
    return append_bone_.ratio_;
}

inline void
Model::Bone::SetAppendRatio(float ratio) {
    append_bone_.ratio_ = ratio;
}

//// vmember: rot_axis
inline const Vector3f&
Model::Bone::GetRotAxis() const {
    return rot_axis_;
}

inline void
Model::Bone::SetRotAxis(const Vector3f &rot_axis) {
    rot_axis_ = rot_axis;
}

//// vmember: local_axis_x
inline const Vector3f&
Model::Bone::GetLocalAxisX() const {
    return local_axis_.axis_x_;
}

inline void
Model::Bone::SetLocalAxisX(const Vector3f &axis_x) {
    local_axis_.axis_x_ = axis_x;
}

//// vmember: local_axis_y
inline const Vector3f&
Model::Bone::GetLocalAxisY() const {
    return local_axis_.axis_y_;
}

inline void
Model::Bone::SetLocalAxisY(const Vector3f &axis_y) {
    local_axis_.axis_y_ = axis_y;
}

//// vmember: local_axis_z
inline const Vector3f&
Model::Bone::GetLocalAxisZ() const {
    return local_axis_.axis_z_;
}

inline void
Model::Bone::SetLocalAxisZ(const Vector3f &axis_z) {
    local_axis_.axis_z_ = axis_z;
}

//// vmember: export_key
inline size_t
Model::Bone::GetExportKey() const {
    return export_key_;
}

inline void
Model::Bone::SetExportKey(size_t export_key) {
    export_key_ = export_key;
}

//// vmember: ik_target_index
inline size_t
Model::Bone::GetIKTargetIndex() const {
    return ik_info_.ik_target_index_;
}

inline void
Model::Bone::SetIKTargetIndex(size_t index) {
    ik_info_.ik_target_index_ = index;
}

//// vmember: ccd_iterate_limit
inline size_t
Model::Bone::GetCCDIterateLimit() const {
    return ik_info_.ccd_iterate_limit_;
}

inline void
Model::Bone::SetCCDIterateLimit(size_t limit) {
    ik_info_.ccd_iterate_limit_ = limit;
}

//// vmember: ccd_angle_limit
inline float
Model::Bone::GetCCDAngleLimit() const {
    return ik_info_.ccd_angle_limit_;
}

inline void
Model::Bone::SetCCDAngleLimit(float limit) {
    ik_info_.ccd_angle_limit_ = limit;
}

//// vmember: ik_links
inline void
Model::Bone::ClearIK() {
    ik_info_.ik_links_.clear();
    /* has_ik_ = false; */
}

inline Model::Bone::IKLink&
Model::Bone::NewIKLink() {
    ik_info_.ik_links_.push_back(IKLink());
    return ik_info_.ik_links_.back();
}

inline size_t
Model::Bone::GetIKLinkNum() const {
    return ik_info_.ik_links_.size();
}

//// omember: ik_link
inline const Model::Bone::IKLink&
Model::Bone::GetIKLink(size_t index) const {
    return ik_info_.ik_links_[index];
}

inline Model::Bone::IKLink&
Model::Bone::GetIKLink(size_t index) {
    return ik_info_.ik_links_[index];
}

//// class Model::Bone::IKLink

//// vmember: link_index
inline size_t
Model::Bone::IKLink::GetLinkIndex() const {
    return index_;
}

inline void
Model::Bone::IKLink::SetLinkIndex(size_t index) {
    index_ = index;
}

//// vmember: has_limit
inline bool
Model::Bone::IKLink::IsHasLimit() const {
    return has_limit_;
}

inline void
Model::Bone::IKLink::SetHasLimit(bool has_limit) {
    has_limit_ = has_limit;
}

//// vmember: lo_limit
inline const
Vector3f& Model::Bone::IKLink::GetLoLimit() const {
    return limit_.lo_;
}

inline void
Model::Bone::IKLink::SetLoLimit(const Vector3f &limit) {
    limit_.lo_ = limit;
}

//// vmember: hi_limit
inline const
Vector3f& Model::Bone::IKLink::GetHiLimit() const {
    return limit_.hi_;
}

inline void
Model::Bone::IKLink::SetHiLimit(const Vector3f &limit) {
    limit_.hi_ = limit;
}


/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

const size_t Model::nil = size_t(-1);

//// class Model::SkinningOperator

//// vmember: skinning_type
inline Model::SkinningOperator::SkinningType
Model::SkinningOperator::GetSkinningType() const {
    return type_;
}

inline void
Model::SkinningOperator::SetSkinningType(
    Model::SkinningOperator::SkinningType type
) {
    type_ = type;
}

//// vmember: bone_id[BDEF1]
inline size_t
Model::SkinningOperator::Parameter::BDEF1::GetBoneID() const {
    return bone_id_;
}

inline void
Model::SkinningOperator::Parameter::BDEF1::SetBoneID(size_t index) {
    bone_id_ = index;
}

//// vmember: bone_id[BDEF2]
inline size_t
Model::SkinningOperator::Parameter::BDEF2::GetBoneID(size_t n) const {
    return bone_id_[n];
}

inline void
Model::SkinningOperator::Parameter::BDEF2::SetBoneID(size_t n, size_t index) {
    bone_id_[n] = index;
}

//// vmember: bone_weight[BDEF2]
inline float
Model::SkinningOperator::Parameter::BDEF2::GetBoneWeight() const {
    return weight_;
}

inline void
Model::SkinningOperator::Parameter::BDEF2::SetBoneWeight(float weight) {
    weight_ = weight;
}

//// vmember: bone_id[BDEF4]
inline size_t
Model::SkinningOperator::Parameter::BDEF4::GetBoneID(size_t n) const {
    return bone_id_[n];
}

inline void
Model::SkinningOperator::Parameter::BDEF4::SetBoneID(size_t n, size_t index) {
    bone_id_[n] = index;
}

//// vmember: bone_weight[BDEF4]
inline float
Model::SkinningOperator::Parameter::BDEF4::GetBoneWeight(size_t n) const {
    return weight_[n];
}

inline void
Model::SkinningOperator::Parameter::BDEF4::SetBoneWeight(size_t n, float weight) {
    weight_[n] = weight;
}

//// vmember: bone_id[SDEF]
inline size_t
Model::SkinningOperator::Parameter::SDEF::GetBoneID(size_t n) const {
    return bone_id_[n];
}

inline void
Model::SkinningOperator::Parameter::SDEF::SetBoneID(size_t n, size_t index) {
    bone_id_[n] = index;
}

//// vmember: bone_weight[SDEF]
inline float
Model::SkinningOperator::Parameter::SDEF::GetBoneWeight() const {
    return weight_;
}

inline void
Model::SkinningOperator::Parameter::SDEF::SetBoneWeight(float weight) {
    weight_ = weight;
}

//// vmember: C[SDEF]
inline const Vector3f&
Model::SkinningOperator::Parameter::SDEF::GetC() const {
    return c_;
}

inline void
Model::SkinningOperator::Parameter::SDEF::SetC(const Vector3f &c) {
    c_ = c;
}

//// vmember: R0
inline const Vector3f&
Model::SkinningOperator::Parameter::SDEF::GetR0() const {
    return r0_;
}

inline void
Model::SkinningOperator::Parameter::SDEF::SetR0(const Vector3f &r0) {
    r0_ = r0;
}

//// vmember: R1
inline const Vector3f&
Model::SkinningOperator::Parameter::SDEF::GetR1() const {
    return r1_;
}

inline void
Model::SkinningOperator::Parameter::SDEF::SetR1(const Vector3f &r1) {
    r1_ = r1;
}

//// omember: Get
inline const Model::SkinningOperator::Parameter::BDEF1&
Model::SkinningOperator::GetBDEF1() const {
    return parameter_.bdef1_;
}

inline const Model::SkinningOperator::Parameter::BDEF2&
Model::SkinningOperator::GetBDEF2() const {
    return parameter_.bdef2_;
}

inline const Model::SkinningOperator::Parameter::BDEF4&
Model::SkinningOperator::GetBDEF4() const {
    return parameter_.bdef4_;
}

inline const Model::SkinningOperator::Parameter::SDEF&
Model::SkinningOperator::GetSDEF() const {
    return parameter_.sdef_;
}

inline Model::SkinningOperator::Parameter::BDEF1&
Model::SkinningOperator::GetBDEF1() {
    return parameter_.bdef1_;
}

inline Model::SkinningOperator::Parameter::BDEF2&
Model::SkinningOperator::GetBDEF2() {
    return parameter_.bdef2_;
}

inline Model::SkinningOperator::Parameter::BDEF4&
Model::SkinningOperator::GetBDEF4() {
    return parameter_.bdef4_;
}

inline Model::SkinningOperator::Parameter::SDEF&
Model::SkinningOperator::GetSDEF() {
    return parameter_.sdef_;
}

//// class Model::Vertex

//// ctor
template <template <typename V> class T> inline
Model::Vertex<T>::Vertex(
    typename T<Vector3f>::type coordinate,
    typename T<Vector3f>::type normal,
    typename T<Vector2f>::type uv_coord,
    typename T<Vector4f>::type extra_uv_1,
    typename T<Vector4f>::type extra_uv_2,
    typename T<Vector4f>::type extra_uv_3,
    typename T<Vector4f>::type extra_uv_4,
    typename T<SkinningOperator>::type skinning_operator,
    typename T<float>::type edge_scale
) : coordinate_(coordinate),
    normal_(normal),
    uv_coord_(uv_coord),
    extra_uv_coord_1_(extra_uv_1),
    extra_uv_coord_2_(extra_uv_2),
    extra_uv_coord_3_(extra_uv_3),
    extra_uv_coord_4_(extra_uv_4),
    skinning_operator_(skinning_operator),
    edge_scale_(edge_scale)
{}

template <template <typename V> class T>
template <template <typename V1> class T1> inline
Model::Vertex<T>::Vertex(Vertex<T1>& v)
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

inline const Material& Model::Part::GetMaterial() const { return material_; }
inline Material& Model::Part::GetMaterial() { return material_; }

inline size_t Model::Part::GetBaseShift() const { return base_shift_; }
inline size_t Model::Part::GetTriangleNum() const { return triangle_num_; }
inline void Model::Part::SetBaseShift(size_t base_shift) { base_shift_ = base_shift; }
inline void Model::Part::SetTriangleNum(size_t triangle_num) { triangle_num_ = triangle_num; }

inline const std::wstring& Model::Bone::GetName() const { return name_; }
inline void Model::Bone::SetName(const std::wstring &name) { name_ = name; }
inline const std::wstring& Model::Bone::GetNameEn() const { return name_en_; }
inline void Model::Bone::SetNameEn(const std::wstring &name_en) { name_en_ = name_en; }
inline const Vector3f& Model::Bone::GetPosition() const { return position_; }
inline void Model::Bone::SetPosition(const Vector3f &position) { position_ = position; }
inline size_t Model::Bone::GetParentIndex() const { return parent_index_; }
inline void Model::Bone::SetParentIndex(size_t parent_index) { parent_index_ = parent_index; }
inline size_t Model::Bone::GetTransformLevel() const { return transform_level_; }
inline void Model::Bone::SetTransformLevel(size_t transform_level) { transform_level_ = transform_level; }

inline bool Model::Bone::IsChildUseID() const { return child_bone_.child_use_id_; }
inline bool Model::Bone::IsRotatable() const { return rotatable_; }
inline bool Model::Bone::IsMovable() const { return movable_; }
inline bool Model::Bone::IsVisible() const { return visible_; }
inline bool Model::Bone::IsControllable() const { return controllable_; }
inline bool Model::Bone::IsHasIK() const { return has_ik_; }
inline bool Model::Bone::IsAppendRotate() const { return append_rotate_; }
inline bool Model::Bone::IsAppendTranslate() const { return append_translate_; }
inline bool Model::Bone::IsRotAxisFixed() const { return rot_axis_fixed_; }
inline bool Model::Bone::IsUseLocalAxis() const { return use_local_axis_; }
inline bool Model::Bone::IsPostPhysics() const { return post_physics_; }
inline bool Model::Bone::IsReceiveTransform() const { return receive_transform_; }

inline void Model::Bone::SetChildUseID(bool child_use_id) { child_bone_.child_use_id_ = child_use_id; }
inline void Model::Bone::SetRotatable(bool rotatable) { rotatable_ = rotatable; }
inline void Model::Bone::SetMovable(bool movable) { movable_ = movable; }
inline void Model::Bone::SetVisible(bool visible) { visible_ = visible; }
inline void Model::Bone::SetControllable(bool controllable) { controllable_ = controllable; }
inline void Model::Bone::SetHasIK(bool has_ik) { has_ik_ = has_ik; }
inline void Model::Bone::SetAppendRotate(bool acquire_rotate) { append_rotate_ = acquire_rotate; }
inline void Model::Bone::SetAppendTranslate(bool acquire_translate) { append_translate_ = acquire_translate; }
inline void Model::Bone::SetRotAxisFixed(bool rot_axis_fixed) { rot_axis_fixed_ = rot_axis_fixed; }
inline void Model::Bone::SetUseLocalAxis(bool use_local_axis) { use_local_axis_ = use_local_axis; }
inline void Model::Bone::SetPostPhysics(bool post_physics) { post_physics_ = post_physics; }
inline void Model::Bone::SetReceiveTransform(bool receive_transform) { receive_transform_ = receive_transform; }

inline size_t Model::Bone::GetChildIndex() const { return child_bone_.descriptor_.index_; }
inline void Model::Bone::SetChildIndex(size_t child_index) { child_bone_.descriptor_.index_ = child_index; }

inline const Vector3f& Model::Bone::GetChildOffset() const { return child_bone_.descriptor_.offset_; }
inline void Model::Bone::SetChildOffset(const Vector3f &offset) { child_bone_.descriptor_.offset_ = offset; }

inline size_t Model::Bone::GetAppendIndex() const { return append_bone_.index_; }
inline void Model::Bone::SetAppendIndex(size_t index) { append_bone_.index_ = index; }
inline float Model::Bone::GetAppendRatio() const { return append_bone_.ratio_; }
inline void Model::Bone::SetAppendRatio(float ratio) { append_bone_.ratio_ = ratio; }

inline const Vector3f& Model::Bone::GetRotAxis() const { return rot_axis_; }
inline void Model::Bone::SetRotAxis(const Vector3f &rot_axis) { rot_axis_ = rot_axis; }

inline const Vector3f& Model::Bone::GetLocalAxisX() const { return local_axis_.axis_x_; }
inline void Model::Bone::SetLocalAxisX(const Vector3f &axis_x) { local_axis_.axis_x_ = axis_x; }
inline const Vector3f& Model::Bone::GetLocalAxisY() const { return local_axis_.axis_y_; }
inline void Model::Bone::SetLocalAxisY(const Vector3f &axis_y) { local_axis_.axis_y_ = axis_y; }
inline const Vector3f& Model::Bone::GetLocalAxisZ() const { return local_axis_.axis_z_; }
inline void Model::Bone::SetLocalAxisZ(const Vector3f &axis_z) { local_axis_.axis_z_ = axis_z; }

inline size_t Model::Bone::GetExportKey() const { return export_key_; }
inline void Model::Bone::SetExportKey(size_t export_key) { export_key_ = export_key; }

inline size_t Model::Bone::GetIKTargetIndex() const { return ik_info_.ik_target_index_; }
inline void Model::Bone::SetIKTargetIndex(size_t index) { ik_info_.ik_target_index_ = index; }

inline size_t Model::Bone::GetCCDIterateLimit() const { return ik_info_.ccd_iterate_limit_; }
inline void Model::Bone::SetCCDIterateLimit(size_t limit) { ik_info_.ccd_iterate_limit_ = limit; }
inline float Model::Bone::GetCCDAngleLimit() const { return ik_info_.ccd_angle_limit_; }
inline void Model::Bone::SetCCDAngleLimit(float limit) { ik_info_.ccd_angle_limit_ = limit; }

inline size_t Model::Bone::IKLink::GetLinkIndex() const { return index_; }
inline void Model::Bone::IKLink::SetLinkIndex(size_t index) { index_ = index; }
inline bool Model::Bone::IKLink::IsHasLimit() const { return has_limit_; }
inline void Model::Bone::IKLink::SetHasLimit(bool has_limit) { has_limit_ = has_limit; }
inline const Vector3f& Model::Bone::IKLink::GetLoLimit() const { return limit_.lo_; }
inline void Model::Bone::IKLink::SetLoLimit(const Vector3f &limit) { limit_.lo_ = limit; }
inline const Vector3f& Model::Bone::IKLink::GetHiLimit() const { return limit_.hi_; }
inline void Model::Bone::IKLink::SetHiLimit(const Vector3f &limit) { limit_.hi_ = limit; }

inline size_t Model::Bone::GetIKLinkNum() const { return ik_info_.ik_links_.size(); }
inline const Model::Bone::IKLink& Model::Bone::GetIKLink(size_t index) const { return ik_info_.ik_links_[index]; }
inline Model::Bone::IKLink& Model::Bone::GetIKLink(size_t index) { return ik_info_.ik_links_[index]; }
inline Model::Bone::IKLink& Model::Bone::NewIKLink() {
    ik_info_.ik_links_.push_back(IKLink());
    return ik_info_.ik_links_.back();
}

inline void Model::Bone::ClearIK() { ik_info_.ik_links_.clear(); has_ik_ = false; }

inline size_t Model::Morph::MorphData::GroupMorph::GetMorphIndex() const { return morph_index_; }
inline void Model::Morph::MorphData::GroupMorph::SetMorphIndex(size_t index) { morph_index_ = index; }

inline float Model::Morph::MorphData::GroupMorph::GetMorphRate() const { return morph_rate_; }
inline void Model::Morph::MorphData::GroupMorph::SetMorphRate(float rate) { morph_rate_ = rate; }

inline size_t Model::Morph::MorphData::VertexMorph::GetVertexIndex() const { return vertex_index_; }
inline void Model::Morph::MorphData::VertexMorph::SetVertexIndex(size_t index) { vertex_index_ = index; }

inline const Vector3f& Model::Morph::MorphData::VertexMorph::GetOffset() const { return offset_; }
inline void Model::Morph::MorphData::VertexMorph::SetOffset(const Vector3f &offset) { offset_ = offset; }

inline size_t Model::Morph::MorphData::BoneMorph::GetBoneIndex() const { return bone_index_; }
inline void Model::Morph::MorphData::BoneMorph::SetBoneIndex(size_t index) { bone_index_ = index; }

inline const Vector3f& Model::Morph::MorphData::BoneMorph::GetTranslation() const { return translation_; }
inline void Model::Morph::MorphData::BoneMorph::SetTranslation(const Vector3f &translation) { translation_ = translation; }

inline const Vector4f& Model::Morph::MorphData::BoneMorph::GetRotation() const { return rotation_; }
inline void Model::Morph::MorphData::BoneMorph::SetRotation(const Vector4f &rotation) { rotation_ = rotation; }

inline size_t Model::Morph::MorphData::UVMorph::GetVertexIndex() const { return vertex_index_; }
inline void Model::Morph::MorphData::UVMorph::SetVertexIndex(size_t index) { vertex_index_ = index; }

inline const Vector4f& Model::Morph::MorphData::UVMorph::GetOffset() const { return offset_; }
inline void Model::Morph::MorphData::UVMorph::SetOffset(const Vector4f &offset) { offset_ = offset; }

inline size_t Model::Morph::MorphData::MaterialMorph::GetMaterialIndex() const { return material_index_; }
inline void Model::Morph::MorphData::MaterialMorph::SetMaterialIndex(size_t index) { material_index_ = index; }

inline bool Model::Morph::MorphData::MaterialMorph::IsGlobal() const { return global_; }
inline void Model::Morph::MorphData::MaterialMorph::SetGlobal(bool global) { global_ = global; }

inline Model::Morph::MorphData::MaterialMorph::MaterialMorphMethod Model::Morph::MorphData::MaterialMorph::GetMethod() const { return method_; }
inline void Model::Morph::MorphData::MaterialMorph::SetMethod(Model::Morph::MorphData::MaterialMorph::MaterialMorphMethod method) { method_ = method; }

inline const Vector4f& Model::Morph::MorphData::MaterialMorph::GetDiffuse() const { return diffuse_; }
inline void Model::Morph::MorphData::MaterialMorph::SetDiffuse(const Vector3f &diffuse) { diffuse_.c = diffuse.c; }
inline void Model::Morph::MorphData::MaterialMorph::SetDiffuse(const Vector4f &diffuse) { diffuse_ = diffuse; }

inline const Vector4f& Model::Morph::MorphData::MaterialMorph::GetSpecular() const { return specular_; }
inline void Model::Morph::MorphData::MaterialMorph::SetSpecular(const Vector3f &specular) { specular_.c = specular.c; }
inline void Model::Morph::MorphData::MaterialMorph::SetSpecular(const Vector4f &specular) { specular_ = specular; }

inline const Vector4f& Model::Morph::MorphData::MaterialMorph::GetAmbient() const { return ambient_; }
inline void Model::Morph::MorphData::MaterialMorph::SetAmbient(const Vector3f &ambient) { ambient_.c = ambient.c; }
inline void Model::Morph::MorphData::MaterialMorph::SetAmbient(const Vector4f &ambient) { ambient_ = ambient; }

inline float Model::Morph::MorphData::MaterialMorph::GetShininess() const { return shininess_; }
inline void Model::Morph::MorphData::MaterialMorph::SetShininess(float shininess) { shininess_ = shininess; }

inline const Vector4f& Model::Morph::MorphData::MaterialMorph::GetEdgeColor() const { return edge_color_; }
inline void Model::Morph::MorphData::MaterialMorph::SetEdgeColor(const Vector3f &edge_color) { edge_color_.c = edge_color.c; }
inline void Model::Morph::MorphData::MaterialMorph::SetEdgeColor(const Vector4f &edge_color) { edge_color_ = edge_color; }

inline float Model::Morph::MorphData::MaterialMorph::GetEdgeSize() const { return edge_size_; }
inline void Model::Morph::MorphData::MaterialMorph::SetEdgeSize(float edge_size) { edge_size_ = edge_size; }

inline const Vector4f& Model::Morph::MorphData::MaterialMorph::GetTexture() const { return texture_; }
inline void Model::Morph::MorphData::MaterialMorph::SetTexture(const Vector3f &texture) { texture_.c = texture.c; }
inline void Model::Morph::MorphData::MaterialMorph::SetTexture(const Vector4f &texture) { texture_ = texture; }

inline const Vector4f& Model::Morph::MorphData::MaterialMorph::GetSubTexture() const { return sub_texture_; }
inline void Model::Morph::MorphData::MaterialMorph::SetSubTexture(const Vector3f &sub_texture) { sub_texture_.c = sub_texture.c; }
inline void Model::Morph::MorphData::MaterialMorph::SetSubTexture(const Vector4f &sub_texture) { sub_texture_ = sub_texture; }

inline const Vector4f& Model::Morph::MorphData::MaterialMorph::GetToonTexture() const { return toon_texture_; }
inline void Model::Morph::MorphData::MaterialMorph::SetToonTexture(const Vector3f &toon_texture) { toon_texture_.c = toon_texture.c; }
inline void Model::Morph::MorphData::MaterialMorph::SetToonTexture(const Vector4f &toon_texture) { toon_texture_ = toon_texture; }

inline Model::Morph::MorphData::GroupMorph& Model::Morph::MorphData::GetGroupMorph() { return group_morph_; }
inline Model::Morph::MorphData::VertexMorph& Model::Morph::MorphData::GetVertexMorph() { return vertex_morph_; }
inline Model::Morph::MorphData::BoneMorph& Model::Morph::MorphData::GetBoneMorph() { return bone_morph_; }
inline Model::Morph::MorphData::UVMorph& Model::Morph::MorphData::GetUVMorph() { return uv_morph_; }
inline Model::Morph::MorphData::MaterialMorph& Model::Morph::MorphData::GetMaterialMorph() { return material_morph_; }

inline const Model::Morph::MorphData::GroupMorph& Model::Morph::MorphData::GetGroupMorph() const { return group_morph_; }
inline const Model::Morph::MorphData::VertexMorph& Model::Morph::MorphData::GetVertexMorph() const { return vertex_morph_; }
inline const Model::Morph::MorphData::BoneMorph& Model::Morph::MorphData::GetBoneMorph() const { return bone_morph_; }
inline const Model::Morph::MorphData::UVMorph& Model::Morph::MorphData::GetUVMorph() const { return uv_morph_; }
inline const Model::Morph::MorphData::MaterialMorph& Model::Morph::MorphData::GetMaterialMorph() const { return material_morph_; }

inline const std::wstring& Model::Morph::GetName() const { return name_; }
inline void Model::Morph::SetName(const std::wstring &name) { name_ = name; }
inline const std::wstring& Model::Morph::GetNameEn() const { return name_en_; }
inline void Model::Morph::SetNameEn(const std::wstring &name_en) { name_en_ = name_en; }

inline Model::Morph::MorphCategory Model::Morph::GetCategory() const { return category_; }
inline void Model::Morph::SetCategory(Model::Morph::MorphCategory category) { category_ = category; }

inline Model::Morph::MorphType Model::Morph::GetType() const { return type_; }
inline void Model::Morph::SetType(Model::Morph::MorphType type) { type_ = type; }

inline size_t Model::Morph::GetMorphDataNum() const { return morph_data_.size(); }
inline const Model::Morph::MorphData& Model::Morph::GetMorphData(size_t index) const { return morph_data_[index]; }
inline Model::Morph::MorphData& Model::Morph::GetMorphData(size_t index) { return morph_data_[index]; }
inline Model::Morph::MorphData& Model::Morph::NewMorphData() {
    morph_data_.push_back(Model::Morph::MorphData());
    return morph_data_.back();
}

inline const std::wstring& Model::RigidBody::GetName() const { return name_; }
inline void Model::RigidBody::SetName(const std::wstring& name) { name_ = name; }
inline const std::wstring& Model::RigidBody::GetNameEn() const { return name_en_; }
inline void Model::RigidBody::SetNameEn(const std::wstring& name) { name_en_ = name; }

inline size_t Model::RigidBody::GetAssociatedBoneIndex() const { return associated_bone_; }
inline void Model::RigidBody::SetAssociatedBoneIndex(size_t index) { associated_bone_ = index; }

inline size_t Model::RigidBody::GetCollisionGroup() const { return collision_group_; }
inline void Model::RigidBody::SetCollisionGroup(size_t group) { collision_group_ = group; }
inline const std::bitset<16>& Model::RigidBody::GetCollisionMask() const { return collision_mask_; }
inline std::bitset<16>& Model::RigidBody::GetCollisionMask() { return collision_mask_; }

inline Model::RigidBody::RigidBodyShape Model::RigidBody::GetShape() const { return shape_; }
inline void Model::RigidBody::SetShape(Model::RigidBody::RigidBodyShape shape) { shape_ = shape; }
inline const Vector3f& Model::RigidBody::GetDimensions() const { return dimension_; }
inline void Model::RigidBody::SetDimensions(const Vector3f& dimensions) { dimension_ = dimensions; }

inline const Vector3f& Model::RigidBody::GetPosition() const { return position_; }
inline void Model::RigidBody::SetPosition(const Vector3f& position) { position_ = position; }
inline const Vector3f& Model::RigidBody::GetRotation() const { return rotation_; }
inline void Model::RigidBody::SetRotation(const Vector3f& rotation) { rotation_ = rotation; }

inline float Model::RigidBody::GetMass() const { return mass_; }
inline void Model::RigidBody::SetMass(float mass) { mass_ = mass; }

inline float Model::RigidBody::GetTranslateDamp() const { return translate_damp_; }
inline void Model::RigidBody::SetTranslateDamp(float damp) { translate_damp_ = damp; }
inline float Model::RigidBody::GetRotateDamp() const { return rotate_damp_; }
inline void Model::RigidBody::SetRotateDamp(float damp) { rotate_damp_ = damp; }

inline float Model::RigidBody::GetRestitution() const { return restitution_; }
inline void Model::RigidBody::SetRestitution(float restitution) { restitution_ = restitution; }
inline float Model::RigidBody::GetFriction() const { return friction_; }
inline void Model::RigidBody::SetFriction(float friction) { friction_ = friction; }

inline Model::RigidBody::RigidBodyType Model::RigidBody::GetType() const { return type_; }
inline void Model::RigidBody::SetType(Model::RigidBody::RigidBodyType type) { type_ = type; }

inline const std::wstring& Model::Constraint::GetName() const { return name_; }
inline void Model::Constraint::SetName(const std::wstring& name) { name_ = name; }
inline const std::wstring& Model::Constraint::GetNameEn() const { return name_en_; }
inline void Model::Constraint::SetNameEn(const std::wstring& name) { name_en_ = name; }

inline size_t Model::Constraint::GetAssociatedRigidBodyIndex(size_t n) const { return associated_rigid_bodies_[n]; }
inline void Model::Constraint::SetAssociatedRigidBodyIndex(size_t n, size_t index) { associated_rigid_bodies_[n] = index; }

inline const Vector3f& Model::Constraint::GetPosition() const { return position_; }
inline void Model::Constraint::SetPosition(const Vector3f& position) { position_ = position; }
inline const Vector3f& Model::Constraint::GetRotation() const { return rotation_; }
inline void Model::Constraint::SetRotation(const Vector3f& rotation) { rotation_ = rotation; }

inline const Vector3f& Model::Constraint::GetPositionLowLimit() const { return position_lo_limit_; }
inline void Model::Constraint::SetPositionLowLimit(const Vector3f& limit) { position_lo_limit_ = limit; }
inline const Vector3f& Model::Constraint::GetPositionHighLimit() const { return position_hi_limit_; }
inline void Model::Constraint::SetPositionHighLimit(const Vector3f& limit) { position_hi_limit_ = limit; }

inline const Vector3f& Model::Constraint::GetRotationLowLimit() const { return rotation_lo_limit_; }
inline void Model::Constraint::SetRotationLowLimit(const Vector3f& limit) { rotation_lo_limit_ = limit; }
inline const Vector3f& Model::Constraint::GetRotationHighLimit() const { return rotation_hi_limit_; }
inline void Model::Constraint::SetRotationHighLimit(const Vector3f& limit) { rotation_hi_limit_ = limit; }

inline const Vector3f& Model::Constraint::GetSpringTranslate() const { return spring_translate_; }
inline void Model::Constraint::SetSpringTranslate(const Vector3f& translate) { spring_translate_ = translate; }
inline const Vector3f& Model::Constraint::GetSpringRotate() const { return spring_rotate_; }
inline void Model::Constraint::SetSpringRotate(const Vector3f& rotate) { spring_rotate_ = rotate; }

inline void Model::SetExtraUVNumber(size_t uv_number) {
    while(uv_number<vertex_info_.extra_uv_coords_.size()) {
        vertex_info_.extra_uv_coords_.pop_back();
    }
    while(uv_number>vertex_info_.extra_uv_coords_.size()) {
        vertex_info_.extra_uv_coords_.push_back(std::vector<Vector4f>());
        std::vector<Vector4f> &e = vertex_info_.extra_uv_coords_.back();
        e.insert(e.end(), vertex_info_.coordinates_.size(), Vector4f());
    }
}

inline size_t Model::GetExtraUVNumber() const { return vertex_info_.extra_uv_coords_.size(); }

inline const std::wstring& Model::GetName() const { return name_; }
inline const std::wstring& Model::GetNameEn() const { return name_en_; }
inline const std::wstring& Model::GetDescription() const { return description_; }
inline const std::wstring& Model::GetDescriptionEn() const { return description_en_; }

inline void Model::SetName(const std::wstring &name) { name_ = name; }
inline void Model::SetDescription(const std::wstring &description) { description_ = description; }
inline void Model::SetNameEn(const std::wstring &name_en) { name_en_ = name_en; }
inline void Model::SetDescriptionEn(const std::wstring &description_en) { description_en_ = description_en; }

inline size_t Model::GetVertexNum() const { return vertex_info_.coordinates_.size(); }

inline Model::Vertex<cref> Model::GetVertex(size_t index) const {
    switch(GetExtraUVNumber()) {
    default:
    case 0:
        return Model::Vertex<cref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    case 1:
        return Model::Vertex<cref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], vertex_info_.extra_uv_coords_[0][index], make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    case 2:
        return Model::Vertex<cref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], vertex_info_.extra_uv_coords_[0][index], vertex_info_.extra_uv_coords_[1][index], make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    case 3:
        return Model::Vertex<cref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], vertex_info_.extra_uv_coords_[0][index], vertex_info_.extra_uv_coords_[1][index], vertex_info_.extra_uv_coords_[2][index], make_null_ref<Vector4f>(), vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    case 4:
        return Model::Vertex<cref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], vertex_info_.extra_uv_coords_[0][index], vertex_info_.extra_uv_coords_[1][index], vertex_info_.extra_uv_coords_[2][index], vertex_info_.extra_uv_coords_[3][index], vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    }
}

inline Model::Vertex<ref> Model::GetVertex(size_t index) {
    switch(GetExtraUVNumber()) {
    default:
    case 0:
        return Model::Vertex<ref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    case 1:
        return Model::Vertex<ref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], vertex_info_.extra_uv_coords_[0][index], make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    case 2:
        return Model::Vertex<ref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], vertex_info_.extra_uv_coords_[0][index], vertex_info_.extra_uv_coords_[1][index], make_null_ref<Vector4f>(), make_null_ref<Vector4f>(), vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    case 3:
        return Model::Vertex<ref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], vertex_info_.extra_uv_coords_[0][index], vertex_info_.extra_uv_coords_[1][index], vertex_info_.extra_uv_coords_[2][index], make_null_ref<Vector4f>(), vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    case 4:
        return Model::Vertex<ref>(vertex_info_.coordinates_[index], vertex_info_.normals_[index], vertex_info_.uv_coords_[index], vertex_info_.extra_uv_coords_[0][index], vertex_info_.extra_uv_coords_[1][index], vertex_info_.extra_uv_coords_[2][index], vertex_info_.extra_uv_coords_[3][index], vertex_info_.skinning_operators_[index], vertex_info_.edge_scales_[index]);
    }
}

inline Model::Vertex<ref> Model::NewVertex() {
    vertex_info_.coordinates_.push_back(Vector3f());
    vertex_info_.normals_.push_back(Vector3f());
    vertex_info_.uv_coords_.push_back(Vector2f());
    vertex_info_.skinning_operators_.push_back(SkinningOperator());
    vertex_info_.edge_scales_.push_back(0.0f);
    return GetVertex(GetVertexNum()-1);
}

inline size_t Model::GetTriangleNum() const { return triangles_.size(); }

inline const Vector3D<std::uint32_t>& Model::GetTriangle(size_t index) const { return triangles_[index]; }
inline Vector3D<std::uint32_t>& Model::GetTriangle(size_t index) { return triangles_[index]; }

inline Vector3D<std::uint32_t>& Model::NewTriangle() {
    triangles_.push_back(Vector3D<std::uint32_t>());
    return triangles_.back();
}

inline size_t Model::GetPartNum() const { return parts_.size(); }

inline const Model::Part& Model::GetPart(size_t index) const { return parts_[index]; }
inline Model::Part& Model::GetPart(size_t index) { return parts_[index]; }

inline Model::Part& Model::NewPart() {
    parts_.push_back(Part());
    return parts_.back();
}

inline size_t Model::GetBoneNum() const { return bones_.size(); }

inline const Model::Bone& Model::GetBone(size_t index) const { return bones_[index]; }
inline Model::Bone& Model::GetBone(size_t index) { return bones_[index]; }

inline Model::Bone& Model::NewBone() {
    bones_.push_back(Bone());
    return bones_.back();
}

inline const float* Model::GetCoordinatePointer() const {
    return &vertex_info_.coordinates_[0].v[0];
}
inline const float* Model::GetNormalPointer() const {
    return &vertex_info_.normals_[0].v[0];
}
inline const float* Model::GetUVCoordPointer() const {
    return &vertex_info_.uv_coords_[0].v[0];
}
inline const std::uint32_t* Model::GetTrianglePointer() const {
    return &triangles_[0].v[0];
}

inline size_t Model::GetMorphNum() const { return morphs_.size(); }
inline const Model::Morph& Model::GetMorph(size_t index) const { return morphs_[index]; }
inline Model::Morph& Model::GetMorph(size_t index) { return morphs_[index]; }
inline Model::Morph& Model::NewMorph() {
    morphs_.push_back(Model::Morph());
    return morphs_.back();
}

inline size_t Model::GetRigidBodyNum() const { return rigid_bodies_.size(); }
inline const Model::RigidBody& Model::GetRigidBody(size_t index) const { return rigid_bodies_[index]; }
inline Model::RigidBody& Model::GetRigidBody(size_t index) { return rigid_bodies_[index]; }
inline Model::RigidBody& Model::NewRigidBody() {
    rigid_bodies_.push_back(Model::RigidBody());
    return rigid_bodies_.back();
}

inline size_t Model::GetConstraintNum() const { return constraints_.size(); }
inline const Model::Constraint& Model::GetConstraint(size_t index) const { return constraints_[index]; }
inline Model::Constraint& Model::GetConstraint(size_t index) { return constraints_[index]; }
inline Model::Constraint& Model::NewConstraint() {
    constraints_.push_back(Model::Constraint());
    return constraints_.back();
}

inline void Model::Normalize() {
    for(std::vector<SkinningOperator>::iterator i=vertex_info_.skinning_operators_.begin();i!=vertex_info_.skinning_operators_.end();++i) {
        switch(i->GetSkinningType()) {
        case SkinningOperator::SKINNING_BDEF2:
            {
                float weight = i->GetBDEF2().GetBoneWeight();
                if(weight==0.0f) {
                    i->GetBDEF1().SetBoneID(i->GetBDEF2().GetBoneID(1));
                    i->SetSkinningType(SkinningOperator::SKINNING_BDEF1);
                } else if(weight==1.0f) {
                    i->GetBDEF1().SetBoneID(i->GetBDEF2().GetBoneID(0));
                    i->SetSkinningType(SkinningOperator::SKINNING_BDEF1);
                }
            }
            break;
        case SkinningOperator::SKINNING_SDEF:
            {
                size_t bone_0 = i->GetSDEF().GetBoneID(0);
                size_t bone_1 = i->GetSDEF().GetBoneID(1);
                float weight = i->GetSDEF().GetBoneWeight();
                if((GetBone(bone_0).GetParentIndex()!=bone_1)&&(GetBone(bone_1).GetParentIndex()!=bone_0)) {
                    if(weight==0.0f) {
                        i->GetBDEF1().SetBoneID(i->GetBDEF2().GetBoneID(1));
                        i->SetSkinningType(SkinningOperator::SKINNING_BDEF1);
                    } else if(weight==1.0f) {
                        i->GetBDEF1().SetBoneID(i->GetBDEF2().GetBoneID(0));
                        i->SetSkinningType(SkinningOperator::SKINNING_BDEF1);
                    } else {
                        i->SetSkinningType(SkinningOperator::SKINNING_BDEF2);
                    }
                }
            }
            break;
        case SkinningOperator::SKINNING_BDEF4:
        default: break;
        }
    }
}

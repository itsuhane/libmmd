
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

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

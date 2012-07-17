
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

//// class Model

//// property: extra_uv
inline void
Model::SetExtraUVNumber(size_t uv_number) {
    if(uv_number<vertex_info_.extra_uv_coords_.size()) {
        vertex_info_.extra_uv_coords_.resize(uv_number);
    } else if(uv_number>vertex_info_.extra_uv_coords_.size()) {
        vertex_info_.extra_uv_coords_.insert(
            vertex_info_.extra_uv_coords_.end(),
            uv_number-vertex_info_.extra_uv_coords_.size(),
            std::vector<Vector4f>(vertex_info_.coordinates_.size())
        );
    }
}

inline size_t
Model::GetExtraUVNumber() const {
    return vertex_info_.extra_uv_coords_.size();
}

//// vmember: name
inline const std::wstring&
Model::GetName() const {
    return name_;
}

inline void
Model::SetName(const std::wstring &name) {
    name_ = name;
}

//// vmember: name_en
inline const std::wstring&
Model::GetNameEn() const {
    return name_en_;
}

inline void
Model::SetNameEn(const std::wstring &name_en) {
    name_en_ = name_en;
}

//// vmember: description
inline const std::wstring&
Model::GetDescription() const {
    return description_;
}

inline void
Model::SetDescription(const std::wstring &description) {
    description_ = description;
}

//// vmember: description_en
inline const std::wstring&
Model::GetDescriptionEn() const {
    return description_en_;
}

inline void
Model::SetDescriptionEn(const std::wstring &description_en) {
    description_en_ = description_en;
}

//// omember: vertex
inline size_t
Model::GetVertexNum() const {
    return vertex_info_.coordinates_.size();
}

inline Model::Vertex<cref>
Model::GetVertex(size_t index) const
{
    switch(GetExtraUVNumber()) {
    default:
    case 0:
        return Model::Vertex<cref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    case 1:
        return Model::Vertex<cref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            vertex_info_.extra_uv_coords_[0][index],
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    case 2:
        return Model::Vertex<cref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            vertex_info_.extra_uv_coords_[0][index],
            vertex_info_.extra_uv_coords_[1][index],
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    case 3:
        return Model::Vertex<cref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            vertex_info_.extra_uv_coords_[0][index],
            vertex_info_.extra_uv_coords_[1][index],
            vertex_info_.extra_uv_coords_[2][index],
            make_null_ref<Vector4f>(),
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    case 4:
        return Model::Vertex<cref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            vertex_info_.extra_uv_coords_[0][index],
            vertex_info_.extra_uv_coords_[1][index],
            vertex_info_.extra_uv_coords_[2][index],
            vertex_info_.extra_uv_coords_[3][index],
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    }
}

inline Model::Vertex<ref>
Model::GetVertex(size_t index) {
    switch(GetExtraUVNumber()) {
    default:
    case 0:
        return Model::Vertex<ref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    case 1:
        return Model::Vertex<ref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            vertex_info_.extra_uv_coords_[0][index],
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    case 2:
        return Model::Vertex<ref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            vertex_info_.extra_uv_coords_[0][index],
            vertex_info_.extra_uv_coords_[1][index],
            make_null_ref<Vector4f>(),
            make_null_ref<Vector4f>(),
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    case 3:
        return Model::Vertex<ref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            vertex_info_.extra_uv_coords_[0][index],
            vertex_info_.extra_uv_coords_[1][index],
            vertex_info_.extra_uv_coords_[2][index],
            make_null_ref<Vector4f>(),
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    case 4:
        return Model::Vertex<ref>(
            vertex_info_.coordinates_[index],
            vertex_info_.normals_[index],
            vertex_info_.uv_coords_[index],
            vertex_info_.extra_uv_coords_[0][index],
            vertex_info_.extra_uv_coords_[1][index],
            vertex_info_.extra_uv_coords_[2][index],
            vertex_info_.extra_uv_coords_[3][index],
            vertex_info_.skinning_operators_[index],
            vertex_info_.edge_scales_[index]
        );
    }
}

inline Model::Vertex<ref>
Model::NewVertex() {
    vertex_info_.coordinates_.push_back(Vector3f());
    vertex_info_.normals_.push_back(Vector3f());
    vertex_info_.uv_coords_.push_back(Vector2f());
    for(size_t i=0;i<GetExtraUVNumber();++i) {
        vertex_info_.extra_uv_coords_[i].push_back(Vector4f());
    }
    vertex_info_.skinning_operators_.push_back(SkinningOperator());
    vertex_info_.edge_scales_.push_back(0.0f);
    return GetVertex(GetVertexNum()-1);
}

//// omember: triangle
inline size_t
Model::GetTriangleNum() const {
    return triangles_.size();
}

inline const Vector3D<std::uint32_t>&
Model::GetTriangle(size_t index) const {
    return triangles_[index];
}

inline Vector3D<std::uint32_t>&
Model::GetTriangle(size_t index) {
    return triangles_[index];
}

inline Vector3D<std::uint32_t>&
Model::NewTriangle() {
    triangles_.push_back(Vector3D<std::uint32_t>());
    return triangles_.back();
}

//// omember: part
inline size_t
Model::GetPartNum() const {
    return parts_.size();
}

inline const Model::Part&
Model::GetPart(size_t index) const {
    return parts_[index];
}

inline Model::Part&
Model::GetPart(size_t index) {
    return parts_[index];
}

inline Model::Part&
Model::NewPart() {
    parts_.push_back(Part());
    return parts_.back();
}

//// oember: bone
inline size_t
Model::GetBoneNum() const {
    return bones_.size();
}

inline const Model::Bone&
Model::GetBone(size_t index) const {
    return bones_[index];
}

inline Model::Bone&
Model::GetBone(size_t index) {
    return bones_[index];
}

inline Model::Bone&
Model::NewBone() {
    bones_.push_back(Bone());
    return bones_.back();
}

//// data accessors
inline const float*
Model::GetCoordinatePointer() const {
    return &vertex_info_.coordinates_[0].v[0];
}

inline const float*
Model::GetNormalPointer() const {
    return &vertex_info_.normals_[0].v[0];
}

inline const float*
Model::GetUVCoordPointer() const {
    return &vertex_info_.uv_coords_[0].v[0];
}

inline const std::uint32_t*
Model::GetTrianglePointer() const {
    return &triangles_[0].v[0];
}

//// omember: morph
inline size_t
Model::GetMorphNum() const {
    return morphs_.size();
}

inline const Model::Morph&
Model::GetMorph(size_t index) const {
    return morphs_[index];
}

inline Model::Morph&
Model::GetMorph(size_t index) {
    return morphs_[index];
}

inline Model::Morph&
Model::NewMorph() {
    morphs_.push_back(Model::Morph());
    return morphs_.back();
}

//// omember: rigid_body
inline size_t
Model::GetRigidBodyNum() const {
    return rigid_bodies_.size();
}

inline const Model::RigidBody&
Model::GetRigidBody(size_t index) const {
    return rigid_bodies_[index];
}

inline Model::RigidBody&
Model::GetRigidBody(size_t index) {
    return rigid_bodies_[index];
}

inline Model::RigidBody&
Model::NewRigidBody() {
    rigid_bodies_.push_back(Model::RigidBody());
    return rigid_bodies_.back();
}

//// omember: constraint
inline size_t
Model::GetConstraintNum() const {
    return constraints_.size();
}

inline const Model::Constraint&
Model::GetConstraint(size_t index) const {
    return constraints_[index];
}

inline Model::Constraint&
Model::GetConstraint(size_t index) {
    return constraints_[index];
}

inline Model::Constraint&
Model::NewConstraint() {
    constraints_.push_back(Model::Constraint());
    return constraints_.back();
}

//// Clear()
inline void
Model::Clear() {
    name_en_.clear();
    name_.clear();

    description_en_.clear();
    description_.clear();

    vertex_info_.coordinates_.clear();
    vertex_info_.normals_.clear();
    vertex_info_.uv_coords_.clear();
    vertex_info_.extra_uv_coords_.clear();
    vertex_info_.skinning_operators_.clear();
    vertex_info_.edge_scales_.clear();

    triangles_.clear();
    parts_.clear();
    bones_.clear();
    morphs_.clear();
    rigid_bodies_.clear();
    constraints_.clear();
}

//// Normalize()
inline void
Model::Normalize() {
    for(
        std::vector<SkinningOperator>::iterator i
            = vertex_info_.skinning_operators_.begin();
        i!=vertex_info_.skinning_operators_.end();
        ++i
    ) {
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
                if(
                    (GetBone(bone_0).GetParentIndex()!=bone_1)&&
                    (GetBone(bone_1).GetParentIndex()!=bone_0)
                ) {
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

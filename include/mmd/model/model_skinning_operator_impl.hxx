
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

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

//// omember: bdef1/bdef2/bdef4/sdef
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

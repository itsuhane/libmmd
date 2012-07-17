
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

/**
  Be awared that though indices are using type of size_t, it is impossible
  to use vertices more than number of 2^32-1, even on 64-bit systems.
**/

#ifndef __MODEL_HXX_4E94485D41E693D8A85A55A8383064F3_INCLUDED__
#define __MODEL_HXX_4E94485D41E693D8A85A55A8383064F3_INCLUDED__

namespace mmd {

    class Model {
    public:
        class SkinningOperator {
        public:
            enum SkinningType {
                SKINNING_BDEF1 = 0,
                SKINNING_BDEF2 = 1,
                SKINNING_BDEF4 = 2,
                SKINNING_SDEF = 3
            };

            union Parameter {
                class BDEF1 {
                public:
                    size_t GetBoneID() const;
                    void SetBoneID(size_t index);
                private:
                    size_t bone_id_;
                } bdef1_;

                class BDEF2 {
                public:
                    size_t GetBoneID(size_t n) const;
                    void SetBoneID(size_t n, size_t index);

                    float GetBoneWeight() const;
                    void SetBoneWeight(float weight);
                private:
                    size_t bone_id_[2];
                    float weight_;
                } bdef2_;

                class BDEF4 {
                public:
                    size_t GetBoneID(size_t n) const;
                    void SetBoneID(size_t n, size_t index);

                    float GetBoneWeight(size_t n) const;
                    void SetBoneWeight(size_t n, float weight);
                private:
                    size_t bone_id_[4];
                    float weight_[4];
                } bdef4_;

                class SDEF {
                public:
                    size_t GetBoneID(size_t n) const;
                    void SetBoneID(size_t n, size_t index);

                    float GetBoneWeight() const;
                    void SetBoneWeight(float weight);

                    const Vector3f &GetC() const;
                    void SetC(const Vector3f &c);

                    const Vector3f &GetR0() const;
                    void SetR0(const Vector3f &r0);

                    const Vector3f &GetR1() const;
                    void SetR1(const Vector3f &r1);

                private:
                    size_t bone_id_[2];
                    float weight_;
                    Vector3f c_;
                    Vector3f r0_;
                    Vector3f r1_;
                } sdef_;
            };

            SkinningType GetSkinningType() const;
            void SetSkinningType(SkinningType type);

            const Parameter::BDEF1 &GetBDEF1() const;
            const Parameter::BDEF2 &GetBDEF2() const;
            const Parameter::BDEF4 &GetBDEF4() const;
            const Parameter::SDEF &GetSDEF() const;

            Parameter::BDEF1 &GetBDEF1();
            Parameter::BDEF2 &GetBDEF2();
            Parameter::BDEF4 &GetBDEF4();
            Parameter::SDEF &GetSDEF();
        private:
            SkinningType type_;
            Parameter parameter_;
        };

        template <template <typename V> class T>
        class Vertex {
            friend class Model;
            template <template <typename V1> class T1>
            friend class Vertex;
        public:
            const Vector3f &GetCoordinate() const;
            void SetCoordinate(const Vector3f &coordinate);

            const Vector3f &GetNormal() const;
            void SetNormal(const Vector3f &normal);

            const Vector2f &GetUVCoordinate() const;
            void SetUVCoordinate(const Vector2f &uv_coord);

            const Vector4f &GetExtraUVCoordinate(size_t index) const;
            void SetExtraUVCoordinate(size_t index, const Vector4f &uv_coord);

            const SkinningOperator &GetSkinningOperator() const;
            SkinningOperator &GetSkinningOperator();

            float GetEdgeScale() const;
            void SetEdgeScale(float edge_scale);

            template <template <typename V1> class T1>
            Vertex(Vertex<T1> &v);
        private:
            Vertex(
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

            Vertex &operator=(const Vertex &v)/*=delete*/;

            typename T<Vector3f>::type coordinate_;
            typename T<Vector3f>::type normal_;
            typename T<Vector2f>::type uv_coord_;
            typename T<Vector4f>::type extra_uv_coord_1_;
            typename T<Vector4f>::type extra_uv_coord_2_;
            typename T<Vector4f>::type extra_uv_coord_3_;
            typename T<Vector4f>::type extra_uv_coord_4_;
            typename T<SkinningOperator>::type skinning_operator_;
            typename T<float>::type edge_scale_;
        };

        class Part {
        public:
            const Material &GetMaterial() const;
            Material &GetMaterial();

            size_t GetBaseShift() const;
            void SetBaseShift(size_t base_shift);

            size_t GetTriangleNum() const;
            void SetTriangleNum(size_t triangle_num);
        private:
            Material material_;
            size_t base_shift_;
            size_t triangle_num_;
        };

        class Bone {
        public:
            class IKLink {
            public:
                size_t GetLinkIndex() const;
                void SetLinkIndex(size_t index);
                bool IsHasLimit() const;
                void SetHasLimit(bool has_limit);
                const Vector3f &GetLoLimit() const;
                void SetLoLimit(const Vector3f &limit);
                const Vector3f &GetHiLimit() const;
                void SetHiLimit(const Vector3f &limit);
            private:
                size_t index_;
                bool has_limit_;
                struct AngleLimit {
                    Vector3f lo_;
                    Vector3f hi_;
                } limit_;
            };

            const std::wstring &GetName() const;
            void SetName(const std::wstring &name);
            const std::wstring &GetNameEn() const;
            void SetNameEn(const std::wstring &name_en);

            const Vector3f &GetPosition() const;
            void SetPosition(const Vector3f &position);

            size_t GetParentIndex() const;
            void SetParentIndex(size_t parent_index);

            size_t GetTransformLevel() const;
            void SetTransformLevel(size_t transform_level);

            bool IsChildUseID() const;
            bool IsRotatable() const;
            bool IsMovable() const;
            bool IsVisible() const;
            bool IsControllable() const;
            bool IsHasIK() const;
            bool IsAppendRotate() const;
            bool IsAppendTranslate() const;
            bool IsRotAxisFixed() const;
            bool IsUseLocalAxis() const;
            bool IsPostPhysics() const;
            bool IsReceiveTransform() const;

            void SetChildUseID(bool child_use_id);
            void SetRotatable(bool rotatable);
            void SetMovable(bool movable);
            void SetVisible(bool visible);
            void SetControllable(bool controllable);
            void SetHasIK(bool has_ik);
            void SetAppendRotate(bool append_rotate);
            void SetAppendTranslate(bool append_translate);
            void SetRotAxisFixed(bool rot_axis_fixed);
            void SetUseLocalAxis(bool use_local_axis);
            void SetPostPhysics(bool post_physics);
            void SetReceiveTransform(bool receive_transform);

            size_t GetChildIndex() const;
            void SetChildIndex(size_t child_index);

            const Vector3f &GetChildOffset() const;
            void SetChildOffset(const Vector3f &offset);

            size_t GetAppendIndex() const;
            void SetAppendIndex(size_t index);
            float GetAppendRatio() const;
            void SetAppendRatio(float ratio);

            const Vector3f &GetRotAxis() const;
            void SetRotAxis(const Vector3f &rot_axis);

            const Vector3f &GetLocalAxisX() const;
            void SetLocalAxisX(const Vector3f &axis_x);
            const Vector3f &GetLocalAxisY() const;
            void SetLocalAxisY(const Vector3f &axis_y);
            const Vector3f &GetLocalAxisZ() const;
            void SetLocalAxisZ(const Vector3f &axis_z);

            size_t GetExportKey() const;
            void SetExportKey(size_t export_key);

            size_t GetIKTargetIndex() const;
            void SetIKTargetIndex(size_t index);

            size_t GetCCDIterateLimit() const;
            void SetCCDIterateLimit(size_t limit);
            float GetCCDAngleLimit() const;
            void SetCCDAngleLimit(float limit);

            size_t GetIKLinkNum() const;
            const IKLink &GetIKLink(size_t index) const;
            IKLink &GetIKLink(size_t index);
            IKLink &NewIKLink();

            void ClearIK();
        private:
            std::wstring name_;
            std::wstring name_en_;

            Vector3f position_;
            size_t parent_index_;

            size_t transform_level_;

            bool rotatable_;
            bool movable_;
            bool visible_;
            bool controllable_;
            bool has_ik_;
            bool append_rotate_;
            bool append_translate_;
            bool rot_axis_fixed_;
            bool use_local_axis_;
            bool post_physics_;
            bool receive_transform_;

            struct ChildBone {
                bool child_use_id_;
                union Descriptor {
                    Vector3f offset_;
                    size_t index_;
                } descriptor_;
            } child_bone_;

            struct AppendBone {
                size_t index_;
                float ratio_;
            } append_bone_;

            Vector3f rot_axis_;

            struct LocalAxis {
                Vector3f axis_x_;
                Vector3f axis_y_;
                Vector3f axis_z_;
            } local_axis_;

            size_t export_key_;

            struct IKInfo {
                size_t ik_target_index_;
                size_t ccd_iterate_limit_;
                float ccd_angle_limit_;
                std::vector<IKLink> ik_links_;
            } ik_info_;
        };

        class Morph {
        public:
            union MorphData {
            public:
                class GroupMorph {
                public:
                    size_t GetMorphIndex() const;
                    void SetMorphIndex(size_t index);

                    float GetMorphRate() const;
                    void SetMorphRate(float rate);

                private:
                    size_t morph_index_;
                    float morph_rate_;
                };

                class VertexMorph {
                public:
                    size_t GetVertexIndex() const;
                    void SetVertexIndex(size_t index);

                    const Vector3f &GetOffset() const;
                    void SetOffset(const Vector3f &offset);

                private:
                    size_t vertex_index_;
                    Vector3f offset_;
                };

                class BoneMorph {
                public:
                    size_t GetBoneIndex() const;
                    void SetBoneIndex(size_t index);

                    const Vector3f &GetTranslation() const;
                    void SetTranslation(const Vector3f &translation);

                    const Vector4f &GetRotation() const;
                    void SetRotation(const Vector4f &rotation);

                private:
                    size_t bone_index_;
                    Vector3f translation_;
                    Vector4f rotation_;
                };

                class UVMorph {
                public:
                    size_t GetVertexIndex() const;
                    void SetVertexIndex(size_t index);

                    const Vector4f &GetOffset() const;
                    void SetOffset(const Vector4f &offset);

                private:
                    size_t vertex_index_;
                    Vector4f offset_;
                };

                class MaterialMorph {
                public:
                    enum MaterialMorphMethod {
                        MORPH_MAT_MUL = 0x00,
                        MORPH_MAT_ADD = 0x01
                    };

                    size_t GetMaterialIndex() const;
                    void SetMaterialIndex(size_t index);

                    bool IsGlobal() const;
                    void SetGlobal(bool global);

                    MaterialMorphMethod GetMethod() const;
                    void SetMethod(MaterialMorphMethod method);

                    const Vector4f &GetDiffuse() const;
                    void SetDiffuse(const Vector3f &diffuse);
                    void SetDiffuse(const Vector4f &diffuse);

                    const Vector4f &GetSpecular() const;
                    void SetSpecular(const Vector3f &specular);
                    void SetSpecular(const Vector4f &specular);

                    const Vector4f &GetAmbient() const;
                    void SetAmbient(const Vector3f &ambient);
                    void SetAmbient(const Vector4f &ambient);

                    float GetShininess() const;
                    void SetShininess(float shininess);

                    const Vector4f &GetEdgeColor() const;
                    void SetEdgeColor(const Vector3f &edge_color);
                    void SetEdgeColor(const Vector4f &edge_color);

                    float GetEdgeSize() const;
                    void SetEdgeSize(float edge_size);

                    const Vector4f &GetTexture() const;
                    void SetTexture(const Vector3f &texture);
                    void SetTexture(const Vector4f &texture);

                    const Vector4f &GetSubTexture() const;
                    void SetSubTexture(const Vector3f &sub_texture);
                    void SetSubTexture(const Vector4f &sub_texture);

                    const Vector4f &GetToonTexture() const;
                    void SetToonTexture(const Vector3f &toon_texture);
                    void SetToonTexture(const Vector4f &toon_texture);

                private:
                    size_t material_index_;
                    bool global_;
                    MaterialMorphMethod method_;
                    Vector4f diffuse_;
                    Vector4f specular_;
                    Vector4f ambient_;
                    float shininess_;
                    Vector4f edge_color_;
                    float edge_size_;
                    Vector4f texture_;
                    Vector4f sub_texture_;
                    Vector4f toon_texture_;
                };

                GroupMorph &GetGroupMorph();
                VertexMorph &GetVertexMorph();
                BoneMorph &GetBoneMorph();
                UVMorph &GetUVMorph();
                MaterialMorph &GetMaterialMorph();

                const GroupMorph &GetGroupMorph() const;
                const VertexMorph &GetVertexMorph() const;
                const BoneMorph &GetBoneMorph() const;
                const UVMorph &GetUVMorph() const;
                const MaterialMorph &GetMaterialMorph() const;
            private:
                GroupMorph group_morph_;
                VertexMorph vertex_morph_;
                BoneMorph bone_morph_;
                UVMorph uv_morph_;
                MaterialMorph material_morph_;
            };

            enum MorphCategory {
                MORPH_CAT_SYSTEM = 0x00,
                MORPH_CAT_EYEBROW = 0x01,
                MORPH_CAT_EYE = 0x02,
                MORPH_CAT_MOUTH = 0x03,
                MORPH_CAT_OTHER = 0x04
            };
            enum MorphType {
                MORPH_TYPE_GROUP = 0x00,
                MORPH_TYPE_VERTEX = 0x01,
                MORPH_TYPE_BONE = 0x02,
                MORPH_TYPE_UV = 0x03,
                MORPH_TYPE_EXT_UV_1 = 0x04,
                MORPH_TYPE_EXT_UV_2 = 0x05,
                MORPH_TYPE_EXT_UV_3 = 0x06,
                MORPH_TYPE_EXT_UV_4 = 0x07,
                MORPH_TYPE_MATERIAL = 0x08
            };
            const std::wstring &GetName() const;
            void SetName(const std::wstring &name);
            const std::wstring &GetNameEn() const;
            void SetNameEn(const std::wstring &name_en);

            MorphCategory GetCategory() const;
            void SetCategory(MorphCategory category);

            MorphType GetType() const;
            void SetType(MorphType type);

            size_t GetMorphDataNum() const;
            const MorphData &GetMorphData(size_t index) const;
            MorphData &GetMorphData(size_t index);
            MorphData &NewMorphData();
        private:
            std::wstring name_;
            std::wstring name_en_;
            MorphCategory category_;
            MorphType type_;
            std::vector<MorphData> morph_data_;
        };

        class RigidBody {
        public:
            enum RigidBodyShape {
                RIGID_SHAPE_SPHERE = 0x00,
                RIGID_SHAPE_BOX = 0x01,
                RIGID_SHAPE_CAPSULE = 0x02
            };

            enum RigidBodyType {
                RIGID_TYPE_KINEMATIC = 0x00,
                RIGID_TYPE_PHYSICS = 0x01,
                RIGID_TYPE_PHYSICS_STRICT = 0x02,
                RIGID_TYPE_PHYSICS_GHOST = 0x03
            };

            const std::wstring &GetName() const;
            void SetName(const std::wstring &name);
            const std::wstring &GetNameEn() const;
            void SetNameEn(const std::wstring &name);

            size_t GetAssociatedBoneIndex() const;
            void SetAssociatedBoneIndex(size_t index);

            size_t GetCollisionGroup() const;
            void SetCollisionGroup(size_t group);

            const std::bitset<16> &GetCollisionMask() const;
            std::bitset<16> &GetCollisionMask();

            RigidBodyShape GetShape() const;
            void SetShape(RigidBodyShape shape);

            const Vector3f &GetDimensions() const;
            void SetDimensions(const Vector3f &dimensions);

            const Vector3f &GetPosition() const;
            void SetPosition(const Vector3f &position);
            const Vector3f &GetRotation() const;
            void SetRotation(const Vector3f &rotation);

            float GetMass() const;
            void SetMass(float mass);

            float GetTranslateDamp() const;
            void SetTranslateDamp(float damp);
            float GetRotateDamp() const;
            void SetRotateDamp(float damp);

            float GetRestitution() const;
            void SetRestitution(float restitution);
            float GetFriction() const;
            void SetFriction(float friction);

            RigidBodyType GetType() const;
            void SetType(RigidBodyType type);
        private:
            std::wstring name_;
            std::wstring name_en_;

            size_t associated_bone_;

            size_t collision_group_;
            std::bitset<16> collision_mask_;

            RigidBodyShape shape_;
            Vector3f dimensions_;

            Vector3f position_;
            Vector3f rotation_;

            float mass_;
            float translate_damp_;
            float rotate_damp_;
            float restitution_;
            float friction_;

            RigidBodyType type_;
        };

        class Constraint {
        public:
            // enum ConstraintType { CONSTRAINT_6DOF = 0x00 };

            const std::wstring &GetName() const;
            void SetName(const std::wstring &name);
            const std::wstring &GetNameEn() const;
            void SetNameEn(const std::wstring &name);

            // ConstraintType GetType() const;
            // void SetType(ConstraintType type);

            size_t GetAssociatedRigidBodyIndex(size_t n) const;
            void SetAssociatedRigidBodyIndex(size_t n, size_t index);

            const Vector3f &GetPosition() const;
            void SetPosition(const Vector3f &position);
            const Vector3f &GetRotation() const;
            void SetRotation(const Vector3f &rotation);

            const Vector3f &GetPositionLowLimit() const;
            void SetPositionLowLimit(const Vector3f &limit);
            const Vector3f &GetPositionHighLimit() const;
            void SetPositionHighLimit(const Vector3f &limit);
            const Vector3f &GetRotationLowLimit() const;
            void SetRotationLowLimit(const Vector3f &limit);
            const Vector3f &GetRotationHighLimit() const;
            void SetRotationHighLimit(const Vector3f &limit);

            const Vector3f &GetSpringTranslate() const;
            void SetSpringTranslate(const Vector3f &translate);
            const Vector3f &GetSpringRotate() const;
            void SetSpringRotate(const Vector3f &rotate);

        private:
            std::wstring name_;
            std::wstring name_en_;

            size_t associated_rigid_bodies_[2];

            Vector3f position_;
            Vector3f rotation_;

            Vector3f position_lo_limit_;
            Vector3f position_hi_limit_;
            Vector3f rotation_lo_limit_;
            Vector3f rotation_hi_limit_;

            Vector3f spring_translate_;
            Vector3f spring_rotate_;
            // ConstraintType type_;
        };

        void SetExtraUVNumber(size_t uv_number);
        size_t GetExtraUVNumber() const;

        const std::wstring &GetName() const;
        void SetName(const std::wstring &name);

        const std::wstring &GetNameEn() const;
        void SetNameEn(const std::wstring &name_en);

        const std::wstring &GetDescription() const;
        void SetDescription(const std::wstring &description);

        const std::wstring &GetDescriptionEn() const;
        void SetDescriptionEn(const std::wstring &description_en);

        size_t GetVertexNum() const;
        Vertex<cref> GetVertex(size_t index) const;
        Vertex<ref> GetVertex(size_t index);
        Vertex<ref> NewVertex();

        size_t GetTriangleNum() const;
        const Vector3D<std::uint32_t> &GetTriangle(size_t index) const;
        Vector3D<std::uint32_t> &GetTriangle(size_t index);
        Vector3D<std::uint32_t> &NewTriangle();

        size_t GetPartNum() const;
        const Part &GetPart(size_t index) const;
        Part &GetPart(size_t index);
        Part &NewPart();

        size_t GetBoneNum() const;
        const Bone &GetBone(size_t index) const;
        Bone &GetBone(size_t index);
        Bone &NewBone();

        size_t GetMorphNum() const;
        const Morph &GetMorph(size_t index) const;
        Morph &GetMorph(size_t index);
        Morph &NewMorph();

        size_t GetRigidBodyNum() const;
        const RigidBody &GetRigidBody(size_t index) const;
        RigidBody &GetRigidBody(size_t index);
        RigidBody &NewRigidBody();

        size_t GetConstraintNum() const;
        const Constraint &GetConstraint(size_t index) const;
        Constraint &GetConstraint(size_t index);
        Constraint &NewConstraint();

        const float *GetCoordinatePointer() const;
        const float *GetNormalPointer() const;
        const float *GetUVCoordPointer() const;
        const std::uint32_t *GetTrianglePointer() const;

        void Clear();

        bool Validate() const;
        bool Validate(std::nothrow_t) const throw();

        void Normalize();
    private:
        std::wstring name_en_;
        std::wstring name_;

        std::wstring description_en_;
        std::wstring description_;

        struct VertexInfo {
            std::vector<Vector3f> coordinates_;
            std::vector<Vector3f> normals_;
            std::vector<Vector2f> uv_coords_;
            std::vector<std::vector<Vector4f>> extra_uv_coords_;
            std::vector<SkinningOperator> skinning_operators_;
            std::vector<float> edge_scales_;
        } vertex_info_;

        std::vector<Vector3D<std::uint32_t>> triangles_;
        std::vector<Part> parts_;
        std::vector<Bone> bones_;
        std::vector<Morph> morphs_;
        std::vector<RigidBody> rigid_bodies_;
        std::vector<Constraint> constraints_;
    };

#include "model_skinning_operator_impl.inl"
#include "model_vertex_impl.inl"
#include "model_part_impl.inl"
#include "model_bone_impl.inl"
#include "model_morph_impl.inl"
#include "model_rigid_body_impl.inl"
#include "model_constraint_impl.inl"
#include "model_impl.inl"

} /* End of namespace mmd */

#endif /* __MODEL_HXX_4E94485D41E693D8A85A55A8383064F3_INCLUDED__ */

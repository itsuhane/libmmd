
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __POSER_HXX_7DED36F61AFF63BB3D2971092CFA8757_INCLUDED__
#define __POSER_HXX_7DED36F61AFF63BB3D2971092CFA8757_INCLUDED__

namespace mmd {

    class Poser {
        friend class PhysicsReactor;
    public:
        struct PoseImage {
            std::vector<Vector3f> coordinates;
            std::vector<Vector3f> normals;
        } pose_image;


        Poser(Model &model);

        void ResetPosing();

        void SetBonePose(size_t index, const Motion::BonePose &bone_pose);
        void SetBonePose(
            const std::wstring &name, const Motion::BonePose &bone_pose
        );

        void SetMorphPose(size_t index, const Motion::MorphPose &morph_pose);
        void SetMorphPose(
            const std::wstring &name, const Motion::MorphPose &morph_pose
        );

        void PrePhysicsPosing();
        void PostPhysicsPosing();

        void Deform();

        const Model &GetModel() const;
        Model &GetModel();

    private:

        struct BoneImage {
            BoneImage();

            Vector4f rotation_;
            Vector3f translation_;

            Vector4f morph_rotation_;
            Vector3f morph_translation_;

            bool has_parent_;
            size_t parent_;

            bool has_append_;
            bool append_rotate_;
            bool append_translate_;

            size_t append_parent_;
            float append_ratio_;

            bool has_ik_;
            bool ik_link_;

            float ccd_angle_limit_;
            size_t ccd_iterate_limit_;

            std::vector<size_t> ik_links_;

            enum AxisFixType { FIX_NONE, FIX_X, FIX_Y, FIX_Z, FIX_ALL };
            enum AxisTransformOrder { ORDER_ZXY, ORDER_XYZ, ORDER_YZX };
            std::vector<AxisFixType> ik_fix_types_;
            std::vector<AxisTransformOrder> ik_transform_orders_;

            std::deque<bool> ik_link_limited_;
            std::vector<Vector3f> ik_link_limits_min_;
            std::vector<Vector3f> ik_link_limits_max_;

            size_t ik_target_;

            Vector4f pre_ik_rotation_;
            Vector4f ik_rotation_;

            Vector4f total_rotation_;
            Vector3f total_translation_;

            Vector3f local_offset_;
            Matrix4f global_offset_matrix_;
            Matrix4f global_offset_matrix_inv_;
            Matrix4f local_matrix_;

            Matrix4f skinning_matrix_;

            class TransformOrder {
            public:
                TransformOrder(const Model &model);
                bool operator() (size_t a, size_t b) const;
            private:
                const Model *model_;
            };
        };

        class MaterialImage {
        public:
            MaterialImage(float value);

            void Init(float value);

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

        std::vector<Vector3f> vertex_images_;
        std::vector<BoneImage> bone_images_;
        std::vector<MaterialImage> material_mul_images_;
        std::vector<MaterialImage> material_add_images_;

        std::vector<float> morph_rates_;

        void UpdateBoneTransform(size_t index);
        void UpdateBoneTransform(const std::vector<size_t> &list);

        void UpdateBoneSkinningMatrix(const std::vector<size_t> &list);

        void UpdateMorphTransform(size_t index, float rate);

        Model &model_;

        std::map<std::wstring, size_t> bone_name_map_;
        std::map<std::wstring, size_t> morph_name_map_;

        std::vector<size_t> pre_physics_bones_;
        std::vector<size_t> post_physics_bones_;

        Poser &operator=(Poser&);
    };

    class MotionPlayer {
    public:
        MotionPlayer(const Motion &motion, Poser &poser);
        void SeekFrame(size_t frame);
        void SeekTime(double time);

    private:
        MotionPlayer &operator=(const MotionPlayer&);

        std::vector<std::pair<std::wstring, size_t>> bone_map_;
        std::vector<std::pair<std::wstring, size_t>> morph_map_;

        const Motion &motion_;
        Poser &poser_;
    };

#include "poser_impl.inl"

} /* End of namespace mmd */

#endif /* __POSER_HXX_7DED36F61AFF63BB3D2971092CFA8757_INCLUDED__ */

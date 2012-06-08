
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

        void SetBonePose(size_t index, const Motion::BoneMotion &bone_motion);
        void SetBonePose(
            const std::wstring &name, const Motion::BoneMotion &bone_motion
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

        std::vector<BoneImage> bone_images_;

        void UpdateBoneTransform(size_t index);
        void UpdateBoneTransform(const std::vector<size_t> &list);

        void UpdateBoneSkinningMatrix(const std::vector<size_t> &list);

        Model &model_;

        std::map<std::wstring, size_t> bone_name_map_;

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
        class MotionModelMismatchTest {
        public:
            MotionModelMismatchTest(const Motion &motion);
            bool operator()(
                const std::pair<std::wstring, size_t> &match_pair
            ) const;
        private:
            const Motion *motion_;
        };

        std::vector<std::pair<std::wstring, size_t>> bone_map_;
        const Motion &motion_;
        Poser &poser_;
    };

#include "poser_impl.hxx"

} /* End of namespace mmd */

#endif /* __POSER_HXX_7DED36F61AFF63BB3D2971092CFA8757_INCLUDED__ */

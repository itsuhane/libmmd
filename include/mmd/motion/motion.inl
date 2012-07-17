
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __MOTION_HXX_C0BF94AFD10DFF18C63F0017F2E22111_INCLUDED__
#define __MOTION_HXX_C0BF94AFD10DFF18C63F0017F2E22111_INCLUDED__

namespace mmd {

    class Motion {
    public:
        class BonePose {
        public:
            BonePose(const Vector3f &translation, const Vector4f &rotation);
            const Vector3f &GetTranslation() const;
            const Vector4f &GetRotation() const;
        private:
            Vector3f translation_;
            Vector4f rotation_;
        };

        class MorphPose {
        public:
            MorphPose(float weight);
            float GetWeight() const;
        private:
            float weight_;
        };

        class BoneKeyframe {
        public:
            const Vector3f &GetTranslation() const;
            void SetTranslation(const Vector3f &translation);

            const Vector4f &GetRotation() const;
            void SetRotation(const Vector4f &rotation);

            const interpolator &GetXInterpolator() const;
            interpolator &GetXInterpolator();
            const interpolator &GetYInterpolator() const;
            interpolator &GetYInterpolator();
            const interpolator &GetZInterpolator() const;
            interpolator &GetZInterpolator();
            const interpolator &GetRInterpolator() const;
            interpolator &GetRInterpolator();

        private:
            Vector3f translation_;
            Vector4f rotation_;

            interpolator x_interpolator_;
            interpolator y_interpolator_;
            interpolator z_interpolator_;
            interpolator r_interpolator_;
        };

        class MorphKeyframe {
        public:
            float GetWeight() const;
            void SetWeight(float weight);

            const interpolator &GetWeightInterpolator() const;
            interpolator &GetWeightInterpolator();

        private:
            float weight_;
            interpolator w_interpolator_;
        };

        Motion();

        const std::wstring &GetName() const;
        void SetName(const std::wstring &name);

        const BoneKeyframe &GetBoneKeyframe(
            const std::wstring &bone_name, size_t frame
        ) const;
        BoneKeyframe &GetBoneKeyframe(
            const std::wstring &bone_name, size_t frame
        );

        BonePose GetBonePose(
            const std::wstring &bone_name, size_t frame
        ) const;
        BonePose GetBonePose(
            const std::wstring &bone_name, double time
        ) const;

        const MorphKeyframe &GetMorphKeyframe(
            const std::wstring &morph_name, size_t frame
        ) const;
        MorphKeyframe &GetMorphKeyframe(
            const std::wstring &morph_name, size_t frame
        );

        MorphPose GetMorphPose(
            const std::wstring &morph_name, size_t frame
        ) const;
        MorphPose GetMorphPose(
            const std::wstring &morph_name, double time
        ) const;

        void RegisterBone(const std::wstring &bone_name);
        void RegisterMorph(const std::wstring &morph_name);

        void UnregisterBone(const std::wstring &bone_name);
        void UnregisterMorph(const std::wstring &morph_name);

        bool IsBoneRegistered(const std::wstring &bone_name) const;
        bool IsMorphRegistered(const std::wstring &morph_name) const;

        size_t QueryBoneKeyframeForward(const std::wstring &bone_name, size_t frame) const;
        size_t QueryBoneKeyframeBackward(const std::wstring &bone_name, size_t frame) const;

        size_t QueryMorphKeyframeForward(const std::wstring &morph_name, size_t frame) const;
        size_t QueryMorphKeyframeBackward(const std::wstring &morph_name, size_t frame) const;

        size_t GetLength() const;
        void Clear();

    private:
        std::wstring name_;
        size_t length_;
        std::map<std::wstring, std::map<size_t, BoneKeyframe>> bone_motions_;
        std::map<std::wstring, std::map<size_t, MorphKeyframe>> morph_motions_;
    };

    class Pose {
    public:
        // TODO - pose related features
    private:
        std::map<std::string, Motion::BonePose> bone_poses_;
        std::map<std::string, Motion::MorphPose> morph_poses_;
    };

#include "motion_impl.inl"

} /* End of namespace mmd */

#endif /* __MOTION_HXX_C0BF94AFD10DFF18C63F0017F2E22111_INCLUDED__ */

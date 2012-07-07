
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
            typedef Bezier<float> interpolator_type;

            const Vector3f &GetTranslation() const;
            void SetTranslation(const Vector3f &translation);

            const Vector4f &GetRotation() const;
            void SetRotation(const Vector4f &rotation);

            const interpolator_type &GetXInterpolator() const;
            interpolator_type &GetXInterpolator();
            const interpolator_type &GetYInterpolator() const;
            interpolator_type &GetYInterpolator();
            const interpolator_type &GetZInterpolator() const;
            interpolator_type &GetZInterpolator();
            const interpolator_type &GetRInterpolator() const;
            interpolator_type &GetRInterpolator();

        private:
            Vector3f translation_;
            Vector4f rotation_;

            interpolator_type x_interpolator_;
            interpolator_type y_interpolator_;
            interpolator_type z_interpolator_;
            interpolator_type r_interpolator_;
        };

        class MorphKeyframe {
        public:
            typedef Bezier<float> interpolator_type;

            float GetWeight() const;
            void SetWeight(float weight);

            const interpolator_type &GetWeightInterpolator() const;
            interpolator_type &GetWeightInterpolator();

        private:
            float weight_;
            interpolator_type w_interpolator_;
        };

        class CameraKeyframe {
        public:
            typedef Bezier<float> interpolator_type;

            float GetFOV() const;
            void SetFOV(float fov);

            float GetFocalLength() const;
            void SetFocalLength(float focal_length);

            bool IsOrthographic() const;
            void SetOrthographic(bool orthographic);

            const Vector3f &GetPosition() const;
            void SetPosition(const Vector3f &position);

            const Vector3f &GetRotation() const;
            void SetRotation(const Vector3f &rotation);

        private:
            float fov_;
            float focal_length_;

            Vector3f position_;
            Vector3f rotation_;

            interpolator_type x_interpolator_;
            interpolator_type y_interpolator_;
            interpolator_type z_interpolator_;
            interpolator_type rx_interpolator_;
            interpolator_type ry_interpolator_;
            interpolator_type rz_interpolator_;

            bool orthographic_;
        };

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

        bool IsBoneRegistered(const std::wstring &bone_name) const;
        bool IsMorphRegistered(const std::wstring &morph_name) const;

    private:
        std::wstring name_;
        std::map<std::wstring, std::map<size_t, BoneKeyframe>> bone_motions_;
        std::map<std::wstring, std::map<size_t, MorphKeyframe>> morph_motions_;
    };

	class Pose {
	public:

	private:
		std::map<std::string, Motion::BonePose> bone_poses_;
		std::map<std::string, Motion::MorphPose> morph_poses_;
	};

#include "motion_impl.hxx"

} /* End of namespace mmd */

#endif /* __MOTION_HXX_C0BF94AFD10DFF18C63F0017F2E22111_INCLUDED__ */

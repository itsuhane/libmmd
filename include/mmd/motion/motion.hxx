
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __MOTION_HXX_C0BF94AFD10DFF18C63F0017F2E22111_INCLUDED__
#define __MOTION_HXX_C0BF94AFD10DFF18C63F0017F2E22111_INCLUDED__

namespace mmd {

    class Pose {
    public:
    private:
    };

    class Motion {
    public:
        struct BoneMotion {
        public:
            BoneMotion(const Vector3f& translation, const Vector4f& rotation) : translation_(translation), rotation_(rotation) {}
            const Vector3f& GetTranslation() const { return translation_; }
            const Vector4f& GetRotation() const { return rotation_; }
            void SetTranslation(const Vector3f& translation);
            void SetRotation(const Vector4f& rotation);
        private:
            Vector3f translation_;
            Vector4f rotation_;
        };

        struct BoneKeyframe {
        public:
            typedef Bezier<float> interpolator_type;

            const Vector3f& GetTranslation() const;
            void SetTranslation(const Vector3f &translation);

            const Vector4f& GetRotation() const;
            void SetRotation(const Vector4f &rotation);

            const interpolator_type& GetXInterpolator() const;
            interpolator_type& GetXInterpolator();
            const interpolator_type& GetYInterpolator() const;
            interpolator_type& GetYInterpolator();
            const interpolator_type& GetZInterpolator() const;
            interpolator_type& GetZInterpolator();
            const interpolator_type& GetRInterpolator() const;
            interpolator_type& GetRInterpolator();

        private:
            Vector3f translation_;
            Vector4f rotation_;

            interpolator_type x_interpolator_;
            interpolator_type y_interpolator_;
            interpolator_type z_interpolator_;
            interpolator_type r_interpolator_;
        };

        const std::wstring& GetName() const;
        void SetName(const std::wstring &name);

        const BoneKeyframe& GetBoneKeyframe(const std::wstring &bone_name, size_t frame) const;
        BoneKeyframe& GetBoneKeyframe(const std::wstring &bone_name, size_t frame);

        const BoneMotion GetBoneMotion(const std::wstring &bone_name, size_t frame) const;
        const BoneMotion GetBoneMotion(const std::wstring &bone_name, double time) const;
    // UNDONE
    //private:
        std::wstring name_;
        std::map<std::wstring, std::map<size_t, BoneKeyframe>> bone_motions_;
    };

#include "motion_impl.hxx"

} /* End of namespace mmd */

#endif /* __MOTION_HXX_C0BF94AFD10DFF18C63F0017F2E22111_INCLUDED__ */

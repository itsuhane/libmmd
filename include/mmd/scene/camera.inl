
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __CAMERA_HXX_F079C72EC406E0573B7F4C6C0BDB61E9_INCLUDED__
#define __CAMERA_HXX_F079C72EC406E0573B7F4C6C0BDB61E9_INCLUDED__

namespace mmd {
    
    class CameraMotion {
    public:
        class CameraPose {
        private:
            float fov_;
            float focal_length_;
            Vector3f position_;
            Vector3f rotation_;
            bool orthographic_;
        };

        class CameraKeyframe {
        public:
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

            interpolator x_interpolator_;
            interpolator y_interpolator_;
            interpolator z_interpolator_;
            interpolator rx_interpolator_;
            interpolator ry_interpolator_;
            interpolator rz_interpolator_;

            bool orthographic_;
        };

        CameraMotion();

        const CameraKeyframe &GetCameraKeyframe(size_t frame) const;
        CameraKeyframe &GetCameraKeyframe(size_t frame);

        CameraPose GetCameraPose(size_t frame) const;
        CameraPose GetCameraPose(double time) const;

        size_t GetLength() const;
        void Clear();

    private:
        size_t length_;
        std::map<size_t, CameraKeyframe> camera_motions_;
    };

#include "camera_impl.inl"

} /* End of namespace mmd */

#endif /* __CAMERA_HXX_F079C72EC406E0573B7F4C6C0BDB61E9_INCLUDED__ */

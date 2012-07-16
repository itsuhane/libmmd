
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

inline float
CameraMotion::CameraKeyframe::GetFOV() const {
    return fov_;
}

inline void
CameraMotion::CameraKeyframe::SetFOV(float fov) {
    fov_ = fov;
}

inline float
CameraMotion::CameraKeyframe::GetFocalLength() const {
    return focal_length_;
}

inline void
CameraMotion::CameraKeyframe::SetFocalLength(float focal_length) {
    focal_length_ = focal_length;
}

inline bool
CameraMotion::CameraKeyframe::IsOrthographic() const {
    return orthographic_;
}

inline void
CameraMotion::CameraKeyframe::SetOrthographic(bool orthographic) {
    orthographic_ = orthographic;
}

inline const Vector3f&
CameraMotion::CameraKeyframe::GetPosition() const {
    return position_;
}

inline void
CameraMotion::CameraKeyframe::SetPosition(const Vector3f &position) {
    position_ = position;
}

inline const Vector3f&
CameraMotion::CameraKeyframe::GetRotation() const {
    return rotation_;
}

inline void
CameraMotion::CameraKeyframe::SetRotation(const Vector3f &rotation) {
    rotation_ = rotation;
}

inline
CameraMotion::CameraMotion() : length_(0) {}

inline const CameraMotion::CameraKeyframe&
CameraMotion::GetCameraKeyframe(size_t frame) const {
    return camera_motions_.find(frame)->second;
}

inline CameraMotion::CameraKeyframe&
CameraMotion::GetCameraKeyframe(size_t frame) {
    if(frame>length_) {
        length_ = frame;
    }
    return camera_motions_[frame];
}

//inline CameraPose CameraMotion::GetCameraPose(size_t frame) const;
//inline CameraPose CameraMotion::GetCameraPose(double time) const;

inline size_t
CameraMotion::GetLength() const {
    return length_;
}

inline void
CameraMotion::Clear() {
    length_ = 0;
    camera_motions_.clear();
}


/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

inline
Motion::BonePose::BonePose(
    const Vector3f &translation, const Vector4f &rotation
) : translation_(translation), rotation_(rotation) {}

inline const Vector3f&
Motion::BonePose::GetTranslation() const {
    return translation_;
}

inline const Vector4f&
Motion::BonePose::GetRotation() const {
    return rotation_;
}

inline
Motion::MorphPose::MorphPose(float weight)
  : weight_(weight) {}

inline float
Motion::MorphPose::GetWeight() const {
    return weight_;
}

inline const Vector3f&
Motion::BoneKeyframe::GetTranslation() const {
    return translation_;
}

inline void
Motion::BoneKeyframe::SetTranslation(const Vector3f &translation) {
    translation_ = translation;
}

inline const Vector4f&
Motion::BoneKeyframe::GetRotation() const {
    return rotation_;
}

inline void
Motion::BoneKeyframe::SetRotation(const Vector4f &rotation) {
    rotation_ = rotation;
}

inline const interpolator&
Motion::BoneKeyframe::GetXInterpolator() const {
    return x_interpolator_;
}

inline interpolator&
Motion::BoneKeyframe::GetXInterpolator() {
    return x_interpolator_;
}

inline const interpolator&
Motion::BoneKeyframe::GetYInterpolator() const {
    return y_interpolator_;
}

inline interpolator&
Motion::BoneKeyframe::GetYInterpolator() {
    return y_interpolator_;
}

inline const interpolator&
Motion::BoneKeyframe::GetZInterpolator() const {
    return z_interpolator_;
}

inline interpolator&
Motion::BoneKeyframe::GetZInterpolator() {
    return z_interpolator_;
}

inline const interpolator&
Motion::BoneKeyframe::GetRInterpolator() const {
    return r_interpolator_;
}

inline interpolator&
Motion::BoneKeyframe::GetRInterpolator() {
    return r_interpolator_;
}

inline float
Motion::MorphKeyframe::GetWeight() const {
    return weight_;
}

inline void
Motion::MorphKeyframe::SetWeight(float weight) {
    weight_ = weight;
}

inline const interpolator&
Motion::MorphKeyframe::GetWeightInterpolator() const {
    return w_interpolator_;
}

inline interpolator&
Motion::MorphKeyframe::GetWeightInterpolator() {
    return w_interpolator_;
}

inline void
Motion::RegisterBone(const std::wstring &bone_name) {
    bone_motions_.insert(std::make_pair(bone_name, std::map<size_t, BoneKeyframe>()));
}

inline void
Motion::RegisterMorph(const std::wstring &morph_name) {
    morph_motions_.insert(std::make_pair(morph_name, std::map<size_t, MorphKeyframe>()));
}

inline void
Motion::UnregisterBone(const std::wstring &bone_name) {
    bone_motions_.erase(bone_name);
}

inline void
Motion::UnregisterMorph(const std::wstring &morph_name) {
    morph_motions_.erase(morph_name);
}

inline bool
Motion::IsBoneRegistered(const std::wstring &bone_name) const {
    return (bone_motions_.count(bone_name)>0);
}

inline bool
Motion::IsMorphRegistered(const std::wstring &morph_name) const {
    return (morph_motions_.count(morph_name)>0);
}

inline size_t
Motion::QueryBoneKeyframeForward(const std::wstring &bone_name, size_t frame) const {
    std::map<std::wstring, std::map<size_t, BoneKeyframe>>::const_iterator i = bone_motions_.find(bone_name);
    if(i!=bone_motions_.end()) {
        std::map<size_t, BoneKeyframe>::const_iterator j = i->second.lower_bound(frame);
        if(j!=i->second.end()) {
            return j->first;
        } else {
            return nil;
        }
    } else {
        return nil;
    }
}

inline size_t
Motion::QueryBoneKeyframeBackward(const std::wstring &bone_name, size_t frame) const {
    std::map<std::wstring, std::map<size_t, BoneKeyframe>>::const_iterator i = bone_motions_.find(bone_name);
    if(i!=bone_motions_.end()) {
        std::map<size_t, BoneKeyframe>::const_iterator j = i->second.upper_bound(frame);
        if(j!=i->second.begin()) {
            return (--j)->first;
        } else {
            return nil;
        }
    } else {
        return nil;
    }
}

inline size_t
Motion::QueryMorphKeyframeForward(const std::wstring &morph_name, size_t frame) const {
    std::map<std::wstring, std::map<size_t, MorphKeyframe>>::const_iterator i = morph_motions_.find(morph_name);
    if(i!=morph_motions_.end()) {
        std::map<size_t, MorphKeyframe>::const_iterator j = i->second.lower_bound(frame);
        if(j!=i->second.end()) {
            return j->first;
        } else {
            return nil;
        }
    } else {
        return nil;
    }
}

inline size_t
Motion::QueryMorphKeyframeBackward(const std::wstring &morph_name, size_t frame) const {
    std::map<std::wstring, std::map<size_t, MorphKeyframe>>::const_iterator i = morph_motions_.find(morph_name);
    if(i!=morph_motions_.end()) {
        std::map<size_t, MorphKeyframe>::const_iterator j = i->second.upper_bound(frame);
        if(j!=i->second.begin()) {
            return (--j)->first;
        } else {
            return nil;
        }
    } else {
        return nil;
    }
}

inline 
Motion::Motion() : length_(0) {}

inline const std::wstring&
Motion::GetName() const {
    return name_;
}

inline void
Motion::SetName(const std::wstring &name) {
    name_ = name;
}

inline const Motion::BoneKeyframe&
Motion::GetBoneKeyframe(const std::wstring &bone_name, size_t frame) const {
    return bone_motions_.find(bone_name)->second.find(frame)->second;
}

inline Motion::BoneKeyframe&
Motion::GetBoneKeyframe(const std::wstring &bone_name, size_t frame) {
    if(frame>length_) {
        length_ = frame;
    }
    return bone_motions_[bone_name][frame];
}

inline const Motion::MorphKeyframe&
Motion::GetMorphKeyframe(const std::wstring &morph_name, size_t frame) const {
    return morph_motions_.find(morph_name)->second.find(frame)->second;
}

inline Motion::MorphKeyframe&
Motion::GetMorphKeyframe(const std::wstring &morph_name, size_t frame) {
    if(frame>length_) {
        length_ = frame;
    }
    return morph_motions_[morph_name][frame];
}

inline size_t
Motion::GetLength() const {
    return length_;
}

inline void
Motion::Clear() {
    name_.clear();
    length_ = 0;
    bone_motions_.clear();
    morph_motions_.clear();
}

inline Motion::BonePose
Motion::GetBonePose(const std::wstring &bone_name, size_t frame) const {
    const std::map<size_t, BoneKeyframe>& keyframes
        = bone_motions_.find(bone_name)->second;

    if(keyframes.size()==0) {
        Vector4f rot;
        rot.q.MakeIdentity();
        return BonePose(Vector3f(), rot);
    }

    if(keyframes.begin()->first>=frame) {
        const BoneKeyframe& key = keyframes.begin()->second;
        return BonePose(key.GetTranslation(), key.GetRotation());
    } else {
        std::map<size_t, BoneKeyframe>::const_iterator i = keyframes.end();
        i--;
        if(i->first<=frame) {
            const BoneKeyframe& key = i->second;
            return BonePose(key.GetTranslation(), key.GetRotation());
        } else {
            std::map<size_t, BoneKeyframe>::const_iterator right_bound
                = keyframes.upper_bound(frame);
            size_t right_frame = right_bound->first;
            const BoneKeyframe& right_key = right_bound->second;
            right_bound--;
            size_t left_frame = right_bound->first;
            const BoneKeyframe& left_key = right_bound->second;

            if(left_frame==frame) {
                return BonePose(
                    left_key.GetTranslation(), left_key.GetRotation()
                );
            } else {
                float bary_pos = (
                    (float)(frame-left_frame)/(float)(right_frame-left_frame)
                );
                float lambda;

                const Vector3f& l_translation = left_key.GetTranslation();
                const Vector4f& l_rotation = left_key.GetRotation();
                const Vector3f& r_translation = right_key.GetTranslation();
                const Vector4f& r_rotation = right_key.GetRotation();

                Vector3f translation;
                Vector4f rotation;

                lambda = left_key.GetXInterpolator()[bary_pos];
                translation.p.x
                    = l_translation.p.x*(1-lambda)+r_translation.p.x*lambda;
                lambda = left_key.GetYInterpolator()[bary_pos];
                translation.p.y
                    = l_translation.p.y*(1-lambda)+r_translation.p.y*lambda;
                lambda = left_key.GetZInterpolator()[bary_pos];
                translation.p.z
                    = l_translation.p.z*(1-lambda)+r_translation.p.z*lambda;

                lambda = left_key.GetRInterpolator()[bary_pos];
                rotation = NLerp(l_rotation, r_rotation)[lambda];

                return BonePose(translation, rotation);
            }
        }
    }
}

inline Motion::BonePose
Motion::GetBonePose(const std::wstring &bone_name, double time) const {
    const std::map<size_t, BoneKeyframe>& keyframes
        = bone_motions_.find(bone_name)->second;

    if(keyframes.size()==0) {
        Vector4f rot;
        rot.q.MakeIdentity();
        return BonePose(Vector3f(), rot);
    }

    double dframe = time * 30.0;

    if(keyframes.begin()->first>=dframe) {
        const BoneKeyframe& key = keyframes.begin()->second;
        return BonePose(key.GetTranslation(), key.GetRotation());
    } else {
        std::map<size_t, BoneKeyframe>::const_iterator i = keyframes.end();
        i--;
        if(i->first<=dframe) {
            const BoneKeyframe& key = i->second;
            return BonePose(key.GetTranslation(), key.GetRotation());
        } else {
            std::map<size_t, BoneKeyframe>::const_iterator right_bound
                = keyframes.upper_bound(size_t(dframe));
            size_t right_frame = right_bound->first;
            const BoneKeyframe& right_key = right_bound->second;
            right_bound--;
            size_t left_frame = right_bound->first;
            const BoneKeyframe& left_key = right_bound->second;

            float bary_pos
                = (float)((dframe-left_frame)/(right_frame-left_frame));
            float lambda;

            const Vector3f& l_translation = left_key.GetTranslation();
            const Vector4f& l_rotation = left_key.GetRotation();
            const Vector3f& r_translation = right_key.GetTranslation();
            const Vector4f& r_rotation = right_key.GetRotation();

            Vector3f translation;
            Vector4f rotation;

            lambda = left_key.GetXInterpolator()[bary_pos];
            translation.p.x
                = l_translation.p.x*(1-lambda)+r_translation.p.x*lambda;
            lambda = left_key.GetYInterpolator()[bary_pos];
            translation.p.y
                = l_translation.p.y*(1-lambda)+r_translation.p.y*lambda;
            lambda = left_key.GetZInterpolator()[bary_pos];
            translation.p.z
                = l_translation.p.z*(1-lambda)+r_translation.p.z*lambda;

            lambda = left_key.GetRInterpolator()[bary_pos];
            rotation = NLerp(l_rotation, r_rotation)[lambda];

            return BonePose(translation, rotation);
        }
    }
}

inline Motion::MorphPose
Motion::GetMorphPose(const std::wstring &morph_name, size_t frame) const {
    const std::map<size_t, MorphKeyframe>& keyframes
        = morph_motions_.find(morph_name)->second;

    if(keyframes.size()==0) {
        return MorphPose(0.0f);
    }

    if(keyframes.begin()->first>=frame) {
        const MorphKeyframe& key = keyframes.begin()->second;
        return MorphPose(key.GetWeight());
    } else {
        std::map<size_t, MorphKeyframe>::const_iterator i = keyframes.end();
        i--;
        if(i->first<=frame) {
            const MorphKeyframe& key = i->second;
            return MorphPose(key.GetWeight());
        } else {
            std::map<size_t, MorphKeyframe>::const_iterator right_bound
                = keyframes.upper_bound(frame);
            size_t right_frame = right_bound->first;
            const MorphKeyframe& right_key = right_bound->second;
            right_bound--;
            size_t left_frame = right_bound->first;
            const MorphKeyframe& left_key = right_bound->second;

            if(left_frame==frame) {
                return MorphPose(left_key.GetWeight());
            } else {
                float bary_pos = (
                    (float)(frame-left_frame)/(float)(right_frame-left_frame)
                );

                float l_weight = left_key.GetWeight();
                float r_weight = right_key.GetWeight();
                float lambda = left_key.GetWeightInterpolator()[bary_pos];

                return MorphPose(l_weight*(1-lambda)+r_weight*lambda);
            }
        }
    }
}

inline Motion::MorphPose
Motion::GetMorphPose(const std::wstring &morph_name, double time) const {
    const std::map<size_t, MorphKeyframe>& keyframes
        = morph_motions_.find(morph_name)->second;

    if(keyframes.size()==0) {
        return MorphPose(0.0f);
    }

    double dframe = time * 30.0;

    if(keyframes.begin()->first>=dframe) {
        const MorphKeyframe& key = keyframes.begin()->second;
        return MorphPose(key.GetWeight());
    } else {
        std::map<size_t, MorphKeyframe>::const_iterator i = keyframes.end();
        i--;
        if(i->first<=dframe) {
            const MorphKeyframe& key = i->second;
            return MorphPose(key.GetWeight());
        } else {
            std::map<size_t, MorphKeyframe>::const_iterator right_bound
                = keyframes.upper_bound(size_t(dframe));
            size_t right_frame = right_bound->first;
            const MorphKeyframe& right_key = right_bound->second;
            right_bound--;
            size_t left_frame = right_bound->first;
            const MorphKeyframe& left_key = right_bound->second;

            float bary_pos
                = (float)((dframe-left_frame)/(right_frame-left_frame));

            float l_weight = left_key.GetWeight();
            float r_weight = right_key.GetWeight();
            float lambda = left_key.GetWeightInterpolator()[bary_pos];

            return MorphPose(l_weight*(1-lambda)+r_weight*lambda);
        }
    }
}


/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

inline void VmdReader::ReadMotion(Motion &motion) {
    try {
        file_.Reset();

        interprete::vmd_header header = file_.Read<interprete::vmd_header>();

        std::string magic = header.magic;
        if(magic!="Vocaloid Motion Data 0002") {
            throw exception(std::string("VmdReader::ReadMotion: File is not a VMD file."));
        }

        motion.Clear();

        motion.SetName(ShiftJISToUTF16String(header.name));

        size_t bone_motion_num = file_.Read<std::uint32_t>();

        for(size_t i=0;i<bone_motion_num;++i) {
            interprete::vmd_bone b = file_.Read<interprete::vmd_bone>();
            Motion::BoneKeyframe &keyframe = motion.GetBoneKeyframe(ShiftJISToUTF16String(b.bone_name), b.nframe);
            keyframe.SetTranslation(b.translation);
            keyframe.SetRotation(b.rotation);

            Vector2f c_0, c_1;
            const float r = 1.0f/127.0f;

            c_0.p.x = b.x_interpolator[0]*r;
            c_0.p.y = b.x_interpolator[4]*r;
            c_1.p.x = b.x_interpolator[8]*r;
            c_1.p.y = b.x_interpolator[12]*r;
            interpolator &x_interpolator = keyframe.GetXInterpolator();
            x_interpolator.SetC(c_0, c_1);

            c_0.p.x = b.y_interpolator[0]*r;
            c_0.p.y = b.y_interpolator[4]*r;
            c_1.p.x = b.y_interpolator[8]*r;
            c_1.p.y = b.y_interpolator[12]*r;
            interpolator &y_interpolator = keyframe.GetYInterpolator();
            y_interpolator.SetC(c_0, c_1);

            c_0.p.x = b.z_interpolator[0]*r;
            c_0.p.y = b.z_interpolator[4]*r;
            c_1.p.x = b.z_interpolator[8]*r;
            c_1.p.y = b.z_interpolator[12]*r;
            interpolator &z_interpolator = keyframe.GetZInterpolator();
            z_interpolator.SetC(c_0, c_1);

            c_0.p.x = b.r_interpolator[0]*r;
            c_0.p.y = b.r_interpolator[4]*r;
            c_1.p.x = b.r_interpolator[8]*r;
            c_1.p.y = b.r_interpolator[12]*r;
            interpolator &r_interpolator = keyframe.GetRInterpolator();
            r_interpolator.SetC(c_0, c_1);
        }

        size_t morph_motion_num = file_.Read<std::uint32_t>();
        
        for(size_t i=0;i<morph_motion_num;++i) {
            interprete::vmd_morph m = file_.Read<interprete::vmd_morph>();
            Motion::MorphKeyframe &keyframe = motion.GetMorphKeyframe(ShiftJISToUTF16String(m.morph_name), m.nframe);
            keyframe.SetWeight(m.weight);
        }

        camera_motion_shift_ = file_.GetPosition();

    } catch(std::exception& e) {
        throw exception(std::string("VmdReader::ReadMotion: Exception caught."), e);
    } catch(...) {
        throw exception(std::string("VmdReader::ReadMotion: Non-standard exception caught."));
    }
}

inline void VmdReader::ReadCameraMotion(CameraMotion &camera_motion) {
    if(camera_motion_shift_==nil) {
        Motion motion;
        ReadMotion(motion);
    } else if(file_.GetPosition()!=camera_motion_shift_) {
        file_.Seek(camera_motion_shift_);
    }
    camera_motion.Clear();
    if(file_.GetRemainedLength()==0) {
        return;
    }
    try {
        size_t camera_motion_num = file_.Read<std::uint32_t>();
        for(size_t i=0;i<camera_motion_num;++i) {
            interprete::vmd_camera c = file_.Read<interprete::vmd_camera>();
            CameraMotion::CameraKeyframe &keyframe = camera_motion.GetCameraKeyframe(c.nframe);
            keyframe.SetFOV(c.fov);
            keyframe.SetFocalLength(c.focal_length);
            keyframe.SetOrthographic(c.orthographic!=0);
            keyframe.SetPosition(c.position);
            keyframe.SetRotation(c.rotation);
        }
    } catch(std::exception& e) {
        throw exception(std::string("VmdReader::ReadCameraMotion: Exception caught."), e);
    } catch(...) {
        throw exception(std::string("VmdReader::ReadCameraMotion: Non-standard exception caught."));
    }
}

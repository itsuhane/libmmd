
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

/**
  Reference:
    ik.txt & ikx.txt
      - Possibly original implementation in MMD, released by Higuchi Yu.
        Listed at VPVP wiki, MMD Related Libraries:
          http://www6.atwiki.jp/vpvpwiki/pages/288.html
**/
inline Poser::Poser(Model &model) : model_(model) {

    /***** Create Pose Image *****/
    size_t vertex_num = model_.GetVertexNum();
    pose_image.coordinates.insert(pose_image.coordinates.end(), vertex_num, Vector3f());
    pose_image.normals.insert(pose_image.normals.end(), vertex_num, Vector3f());

    /***** Create Vertex Images *****/
    vertex_images_.insert(vertex_images_.end(), vertex_num, Vector3f());

    /***** Create Bone Images *****/
    size_t bone_num = model_.GetBoneNum();
    bone_images_.insert(bone_images_.end(), bone_num, BoneImage());

    for(size_t i=0;i<bone_num;++i) {
        const Model::Bone& bone = model_.GetBone(i);
        bone_name_map_[bone.GetName()] = i;

        BoneImage& image = bone_images_[i];

        image.global_offset_matrix_.r.v[3].downgrade.vector3d = -bone.GetPosition();
        image.global_offset_matrix_inv_.r.v[3].downgrade.vector3d = bone.GetPosition();

        image.parent_ = bone.GetParentIndex();
        if(image.parent_<bone_num) {
            image.has_parent_ = true;
            image.local_offset_ = bone.GetPosition()-model_.GetBone(image.parent_).GetPosition();
        } else {
            image.has_parent_ = false;
            image.local_offset_ = bone.GetPosition();
        }

        image.append_rotate_ = bone.IsAppendRotate();
        image.append_translate_ = bone.IsAppendTranslate();
        image.has_append_ = false;
        if(image.append_rotate_||image.append_translate_) {
            image.append_parent_ = bone.GetAppendIndex();
            if(image.append_parent_<bone_num) {
                image.has_append_ = true;
                image.append_ratio_ = bone.GetAppendRatio();
            }
        }

        image.has_ik_ = bone.IsHasIK();
        if(image.has_ik_) {
            size_t ik_link_num = bone.GetIKLinkNum();
            image.ik_links_.insert(image.ik_links_.end(), ik_link_num, 0);
            image.ik_fix_types_.insert(image.ik_fix_types_.end(), ik_link_num, BoneImage::FIX_NONE);
            image.ik_transform_orders_.insert(image.ik_transform_orders_.end(), ik_link_num, BoneImage::ORDER_YZX);
            image.ik_link_limited_.insert(image.ik_link_limited_.end(), ik_link_num, false);
            image.ik_link_limits_min_.insert(image.ik_link_limits_min_.end(), ik_link_num, Vector3f());
            image.ik_link_limits_max_.insert(image.ik_link_limits_max_.end(), ik_link_num, Vector3f());

            for(size_t j=0;j<ik_link_num;++j) {
                const Model::Bone::IKLink& ik_link = bone.GetIKLink(j);
                image.ik_links_[j] = ik_link.GetLinkIndex();
                image.ik_link_limited_[j] = ik_link.IsHasLimit();
                if(image.ik_link_limited_[j]) {
                    for(size_t k=0;k<3;++k) {
                        image.ik_link_limits_min_[j].v[k] = std::min(ik_link.GetLoLimit().v[k], ik_link.GetHiLimit().v[k]);
                        image.ik_link_limits_max_[j].v[k] = std::max(ik_link.GetLoLimit().v[k], ik_link.GetHiLimit().v[k]);
                    }
                    if(image.ik_link_limits_min_[j].p.x>-mmd_math_const_pi*0.5f&&image.ik_link_limits_max_[j].p.x<mmd_math_const_pi*0.5f) {
                        image.ik_transform_orders_[j] = BoneImage::ORDER_ZXY;
                    } else if(image.ik_link_limits_min_[j].p.y>-mmd_math_const_pi*0.5f&&image.ik_link_limits_max_[j].p.y<mmd_math_const_pi*0.5f) {
                        image.ik_transform_orders_[j] = BoneImage::ORDER_XYZ;
                    }
                    if((abs(image.ik_link_limits_min_[j].p.x)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.x)<mmd_math_const_eps)&&(abs(image.ik_link_limits_min_[j].p.y)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.y)<mmd_math_const_eps)&&(abs(image.ik_link_limits_min_[j].p.z)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.z)<mmd_math_const_eps)) {
                        image.ik_fix_types_[j] = BoneImage::FIX_ALL;
                    } else if((abs(image.ik_link_limits_min_[j].p.y)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.y)<mmd_math_const_eps)&&(abs(image.ik_link_limits_min_[j].p.z)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.z)<mmd_math_const_eps)) {
                        image.ik_fix_types_[j] = BoneImage::FIX_X;
                    } else if((abs(image.ik_link_limits_min_[j].p.x)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.x)<mmd_math_const_eps)&&(abs(image.ik_link_limits_min_[j].p.z)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.z)<mmd_math_const_eps)) {
                        image.ik_fix_types_[j] = BoneImage::FIX_Y;
                    } else if((abs(image.ik_link_limits_min_[j].p.x)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.x)<mmd_math_const_eps)&&(abs(image.ik_link_limits_min_[j].p.y)<mmd_math_const_eps)&&(abs(image.ik_link_limits_max_[j].p.y)<mmd_math_const_eps)) {
                        image.ik_fix_types_[j] = BoneImage::FIX_Z;
                    }
                }
                bone_images_[image.ik_links_[j]].ik_link_ = true;
            }
            image.ccd_angle_limit_ = bone.GetCCDAngleLimit();
            image.ccd_iterate_limit_ = std::min(bone.GetCCDIterateLimit(), size_t(256));
            image.ik_target_ = bone.GetIKTargetIndex();
        }

        if(bone.IsPostPhysics()) {
            post_physics_bones_.push_back(i);
        } else {
            pre_physics_bones_.push_back(i);
        }
    }

    BoneImage::TransformOrder order(model_);
    std::sort(pre_physics_bones_.begin(), pre_physics_bones_.end(), order);
    std::sort(post_physics_bones_.begin(), post_physics_bones_.end(), order);

    /***** Create Material Images *****/
    size_t material_num = model_.GetPartNum();
    material_mul_images_.insert(material_mul_images_.end(), material_num, MaterialImage(1.0f));
    material_add_images_.insert(material_add_images_.end(), material_num, MaterialImage(0.0f));

    /***** Create Morph Rates *****/
    size_t morph_num = model_.GetMorphNum();
    morph_rates_.insert(morph_rates_.end(), morph_num, 0.0f);

    for(size_t i=0;i<morph_num;++i) {
        const Model::Morph& morph = model_.GetMorph(i);
        morph_name_map_[morph.GetName()] = i;
    }

    /***** 1st Posing *****/
    ResetPosing();
    Deform();
}

inline void Poser::ResetPosing() {
    for(std::vector<float>::iterator i=morph_rates_.begin();i!=morph_rates_.end();++i) {
        *i = 0;
    }
    for(std::vector<BoneImage>::iterator i=bone_images_.begin();i!=bone_images_.end();++i) {
        i->rotation_.q.MakeIdentity();
        i->translation_.MakeZero();
    }
    PrePhysicsPosing();
    PostPhysicsPosing();
}

inline void Poser::UpdateBoneTransform(size_t index) {
    BoneImage& image = bone_images_[index];
    image.total_rotation_.q = image.morph_rotation_.q*image.rotation_.q;
    image.total_translation_ = image.morph_translation_+image.translation_;

    if(image.has_append_) {
        if(image.append_rotate_) {
            image.total_rotation_.q = image.total_rotation_.q*SLerp(Quaternionf::Identity(), bone_images_[image.append_parent_].total_rotation_.q)[image.append_ratio_];
        }
        if(image.append_translate_) {
            image.total_translation_ = image.total_translation_+image.append_ratio_*bone_images_[image.append_parent_].total_translation_;
        }
    }

    if(image.ik_link_) {
        image.pre_ik_rotation_ = image.total_rotation_;
        image.total_rotation_.q = image.ik_rotation_.q*image.total_rotation_.q;
    }

    image.local_matrix_ = image.total_rotation_.q.ToRotateMatrix();
    image.local_matrix_.r.v[3].downgrade.vector3d = image.total_translation_+image.local_offset_;

    if(image.has_parent_) {
        image.local_matrix_ = image.local_matrix_*bone_images_[image.parent_].local_matrix_;
    }

    if(image.has_ik_) {
        struct __ {
            static float Nabs(float x) {
                if(x>=0.0f) {
                    return 1.0f;
                } else {
                    return -1.0f;
                }
            }

            static Vector3f LimitEulerAngle(const Vector3f& euler, const Vector3f& euler_min, const Vector3f& euler_max, bool ikt) {
                Vector3f result = euler;
                for(size_t i=0;i<3;++i) {
                    if(result.v[i] < euler_min.v[i]) {
                        float tf= 2 * euler_min.v[i] - result.v[i];
                        if(tf <= euler_max.v[i] && ikt) result.v[i] = tf;
                        else result.v[i] = euler_min.v[i];
                    }
                    if(result.v[i] > euler_max.v[i]) {
                        float tf= 2 * euler_max.v[i] - result.v[i];
                        if(tf >= euler_min.v[i] && ikt) result.v[i] = tf;
                        else result.v[i] = euler_max.v[i];
                    }
                }
                return result;
            }
        };

        Vector3f ik_error;

        size_t ik_link_num = image.ik_links_.size();
        for(size_t i=0;i<ik_link_num;++i) {
            bone_images_[image.ik_links_[i]].ik_rotation_.q.MakeIdentity();
        }
        Vector3f ik_position = image.local_matrix_.r.v[3].downgrade.vector3d;
        for(size_t i=0;i<ik_link_num;++i) {
            UpdateBoneTransform(image.ik_links_[ik_link_num-i-1]);
        }
        UpdateBoneTransform(image.ik_target_);
        Vector3f target_position = bone_images_[image.ik_target_].local_matrix_.r.v[3].downgrade.vector3d;
        ik_error = ik_position-target_position;
        if(ik_error*ik_error<mmd_math_const_eps) {
            return;
        }
        size_t ikt = image.ccd_iterate_limit_/2;
        for(size_t i=0;i<image.ccd_iterate_limit_;++i) {
            for(size_t j=0;j<ik_link_num;++j) {
                if(image.ik_fix_types_[j]!=BoneImage::FIX_ALL) {
                    BoneImage& ik_image = bone_images_[image.ik_links_[j]];
                    Vector3f ik_link_position = ik_image.local_matrix_.r.v[3].downgrade.vector3d;
                    Vector3f target_direction = ik_link_position-target_position;
                    Vector3f ik_direction = ik_link_position-ik_position;

                    target_direction = target_direction.Normalize();
                    ik_direction = ik_direction.Normalize();

                    Vector3f ik_rotate_axis;
                    ik_rotate_axis.t = target_direction.t*ik_direction.t;
                    for(size_t k=0;k<3;++k) {
                        if(std::abs(ik_rotate_axis.v[k])<mmd_math_const_eps) {
                            ik_rotate_axis.v[k] = (float)mmd_math_const_eps;
                        }
                    }
                    Matrix4f localization_matrix;
                    if(ik_image.has_parent_) {
                        localization_matrix = bone_images_[ik_image.parent_].local_matrix_;
                    } else {
                        localization_matrix.MakeIdentity();
                    }
                    if(image.ik_link_limited_[j]&&image.ik_fix_types_[j]!=BoneImage::FIX_NONE&&i<ikt) {
                        switch(image.ik_fix_types_[j]) {
                        case BoneImage::FIX_X:
                            {
                                ik_rotate_axis.p.x = __::Nabs(ik_rotate_axis*localization_matrix.r.v[0].downgrade.vector3d);
                                ik_rotate_axis.p.y = ik_rotate_axis.p.z = 0.0f;
                                break;
                            }
                        case BoneImage::FIX_Y:
                            {
                                ik_rotate_axis.p.y = __::Nabs(ik_rotate_axis*localization_matrix.r.v[1].downgrade.vector3d);
                                ik_rotate_axis.p.x = ik_rotate_axis.p.z = 0.0f;
                                break;
                            }
                        case BoneImage::FIX_Z:
                            {
                                ik_rotate_axis.p.z = __::Nabs(ik_rotate_axis*localization_matrix.r.v[2].downgrade.vector3d);
                                ik_rotate_axis.p.x = ik_rotate_axis.p.y = 0.0f;
                                break;
                            }
                        case BoneImage::FIX_ALL: case BoneImage::FIX_NONE: default: { break; }
                        }
                    } else {
                        ik_rotate_axis = rotate(ik_rotate_axis, localization_matrix.Transpose());
                        ik_rotate_axis = ik_rotate_axis.Normalize();
                    }
                    float ik_rotate_angle = std::min(math::acos(math::clamp(target_direction*ik_direction,-1.0f,1.0f)), image.ccd_angle_limit_*(j+1));
                    ik_image.ik_rotation_.q = AxisToQuaternion(ik_rotate_axis, ik_rotate_angle)*ik_image.ik_rotation_.q;
                    if(image.ik_link_limited_[j]) {
                        Quaternionf local_rotation = ik_image.ik_rotation_.q*ik_image.pre_ik_rotation_.q;
                        switch(image.ik_transform_orders_[j]) {
                        case BoneImage::ORDER_ZXY:
                            {
                                Vector3f euler_angle = QuaternionToZXY(local_rotation);
                                euler_angle = __::LimitEulerAngle(euler_angle, image.ik_link_limits_min_[j], image.ik_link_limits_max_[j], i<ikt);
                                local_rotation = ZXYToQuaternion(euler_angle);
                                break;
                            }
                        case BoneImage::ORDER_XYZ:
                            {
                                Vector3f euler_angle = QuaternionToXYZ(local_rotation);
                                euler_angle = __::LimitEulerAngle(euler_angle, image.ik_link_limits_min_[j], image.ik_link_limits_max_[j], i<ikt);
                                local_rotation = XYZToQuaternion(euler_angle);
                                break;
                            }
                        case BoneImage::ORDER_YZX:
                            {
                                Vector3f euler_angle = QuaternionToYZX(local_rotation);
                                euler_angle = __::LimitEulerAngle(euler_angle, image.ik_link_limits_min_[j], image.ik_link_limits_max_[j], i<ikt);
                                local_rotation = YZXToQuaternion(euler_angle);
                                break;
                            }
                        }
                        ik_image.ik_rotation_.q = local_rotation*ik_image.pre_ik_rotation_.q.Inverse();
                    }
                    for(size_t k=0;k<=j;++k) {
                        BoneImage& link_image = bone_images_[image.ik_links_[j-k]];
                        link_image.total_rotation_.q = link_image.ik_rotation_.q*link_image.pre_ik_rotation_.q;
                        link_image.local_matrix_ = link_image.total_rotation_.q.ToRotateMatrix();
                        link_image.local_matrix_.r.v[3].downgrade.vector3d = link_image.total_translation_+link_image.local_offset_;
                        if(link_image.has_parent_) {
                            link_image.local_matrix_ = link_image.local_matrix_*bone_images_[link_image.parent_].local_matrix_;
                        }
                    }
                    UpdateBoneTransform(image.ik_target_);
                    target_position = bone_images_[image.ik_target_].local_matrix_.r.v[3].downgrade.vector3d;
                }
            }
            ik_error = ik_position-target_position;
            if(ik_error*ik_error<float(mmd_math_const_eps)) {
                return;
            }
        }
    }
}

inline void Poser::UpdateBoneTransform(const std::vector<size_t> &list) {
    size_t n = list.size();
    for(size_t i=0;i<n;++i) {
        UpdateBoneTransform(list[i]);
    }
}

inline void Poser::UpdateBoneSkinningMatrix(const std::vector<size_t> &list) {
    size_t n = list.size();
    for(size_t i=0;i<n;++i) {
        Poser::BoneImage& image = bone_images_[list[i]];
        image.skinning_matrix_ = image.global_offset_matrix_*image.local_matrix_;
    }
}

inline void Poser::UpdateMorphTransform(size_t index, float rate) {
    if(rate<mmd_math_const_eps) {
        return;
    }
    const Model::Morph &morph = model_.GetMorph(index);
    switch(morph.GetType()) {
    case Model::Morph::MORPH_TYPE_GROUP:
        for(size_t i=0;i<morph.GetMorphDataNum();++i) {
            const Model::Morph::MorphData::GroupMorph &data = morph.GetMorphData(i).GetGroupMorph();
            UpdateMorphTransform(data.GetMorphIndex(), data.GetMorphRate()*rate);
        }
        break;
    case Model::Morph::MORPH_TYPE_VERTEX:
        for(size_t i=0;i<morph.GetMorphDataNum();++i) {
            const Model::Morph::MorphData::VertexMorph &data = morph.GetMorphData(i).GetVertexMorph();
            Vector3f &vertex_image = vertex_images_[data.GetVertexIndex()];
            vertex_image = vertex_image+data.GetOffset()*rate;
        }
        break;
    case Model::Morph::MORPH_TYPE_BONE:
        for(size_t i=0;i<morph.GetMorphDataNum();++i) {
            const Model::Morph::MorphData::BoneMorph &data = morph.GetMorphData(i).GetBoneMorph();
            BoneImage &bone_image = bone_images_[data.GetBoneIndex()];
            bone_image.morph_translation_ = bone_image.morph_translation_+data.GetTranslation()*rate;
            bone_image.morph_rotation_.q = bone_image.morph_rotation_.q*SLerp(Quaternionf::Identity(), data.GetRotation().q)[rate];
        }
        break;
    case Model::Morph::MORPH_TYPE_MATERIAL:
        break;
    default:
        break;
    }
}

inline void Poser::PrePhysicsPosing() {
    for(std::vector<Vector3f>::iterator i = vertex_images_.begin();i!=vertex_images_.end();++i) {
        i->MakeZero();
    }
    for(std::vector<BoneImage>::iterator i = bone_images_.begin();i!=bone_images_.end();++i) {
        i->morph_translation_.MakeZero();
        i->morph_rotation_.q.MakeIdentity();

        i->local_matrix_.MakeIdentity();

        i->pre_ik_rotation_.q.MakeIdentity();
        i->ik_rotation_.q.MakeIdentity();

        i->total_rotation_.q.MakeIdentity();
        i->total_translation_.MakeZero();
    }
    for(std::vector<MaterialImage>::iterator i = material_mul_images_.begin();i!=material_mul_images_.end();++i) {
        i->Init(1.0f);
    }
    for(std::vector<MaterialImage>::iterator i = material_add_images_.begin();i!=material_add_images_.end();++i) {
        i->Init(0.0f);
    }
    for(size_t i=0;i<morph_rates_.size();++i) {
        UpdateMorphTransform(i, morph_rates_[i]);
    }
    UpdateBoneTransform(pre_physics_bones_);
    UpdateBoneSkinningMatrix(pre_physics_bones_);
}

inline void Poser::PostPhysicsPosing() {
    UpdateBoneTransform(post_physics_bones_);
    UpdateBoneSkinningMatrix(post_physics_bones_);
}

inline void Poser::Deform() {
    size_t vertex_num = model_.GetVertexNum();
    //for(size_t i=0;i<vertex_num;++i) {
    //    Model::Vertex<ref> vertex = model_.GetVertex(i);
    //    pose_image.coordinates[i] = ;
    //    pose_image.normals[i] = ;
    //}

    for(size_t i=0;i<vertex_num;++i) {
        Model::Vertex<ref> vertex = model_.GetVertex(i);
        const Model::SkinningOperator& op = vertex.GetSkinningOperator();
        const Vector3f &coordinate = vertex.GetCoordinate()+vertex_images_[i];
        const Vector3f &normal = vertex.GetNormal();
        switch(op.GetSkinningType()) {
        case Model::SkinningOperator::SKINNING_BDEF1:
            {
                const Matrix4f &mat = bone_images_[op.GetBDEF1().GetBoneID()].skinning_matrix_;
                pose_image.coordinates[i] = transform(coordinate, mat);
                pose_image.normals[i] = rotate(normal, mat);
            }
            break;
        case Model::SkinningOperator::SKINNING_SDEF:
        case Model::SkinningOperator::SKINNING_BDEF2: default:
            {
                const Matrix4f &mat_0 = bone_images_[op.GetBDEF2().GetBoneID(0)].skinning_matrix_;
                const Matrix4f &mat_1 = bone_images_[op.GetBDEF2().GetBoneID(1)].skinning_matrix_;
                Matrix4f mat = Lerp(mat_1, mat_0)[op.GetBDEF2().GetBoneWeight()];
                pose_image.coordinates[i] = transform(coordinate, mat);
                pose_image.normals[i] = rotate(normal, mat);
            }
            break;
        case Model::SkinningOperator::SKINNING_BDEF4:
            {
                const Matrix4f &mat_0 = bone_images_[op.GetBDEF4().GetBoneID(0)].skinning_matrix_;
                const Matrix4f &mat_1 = bone_images_[op.GetBDEF4().GetBoneID(1)].skinning_matrix_;
                const Matrix4f &mat_2 = bone_images_[op.GetBDEF4().GetBoneID(2)].skinning_matrix_;
                const Matrix4f &mat_3 = bone_images_[op.GetBDEF4().GetBoneID(3)].skinning_matrix_;
                Matrix4f mat = mat_0*op.GetBDEF4().GetBoneWeight(0)+mat_1*op.GetBDEF4().GetBoneWeight(1)+mat_2*op.GetBDEF4().GetBoneWeight(2)+mat_3*op.GetBDEF4().GetBoneWeight(3);
                pose_image.coordinates[i] = transform(coordinate, mat);
                pose_image.normals[i] = rotate(normal, mat);
            }
            break;
        //case Model::SkinningOperator::SKINNING_SDEF:
        //    {
        //        const Matrix4f &mat_0 = bone_images_[op.GetSDEF().GetBoneID(0)].skinning_matrix_;
        //        const Matrix4f &mat_1 = bone_images_[op.GetSDEF().GetBoneID(1)].skinning_matrix_;
        //        const Vector3f &c = op.GetSDEF().GetC();
        //        const Vector3f &r0 = op.GetSDEF().GetR0();
        //        const Vector3f &r1 = op.GetSDEF().GetR1();
        //        float weight = op.GetSDEF().GetBoneWeight();
        //        Vector3f rr0 = transform(r0, mat_0);
        //        Vector3f rr1 = transform(r1, mat_1);
        //        Vector3f nc0 = transform(c, mat_0);
        //        Vector3f nc1 = transform(c, mat_1);
        //        Vector3f lr = Lerp(rr1, rr0)[weight];
        //        Vector3f nc = Lerp(nc1, nc0)[weight];
        //        Vector3f rc = lr;
        //        Matrix4f mat = SLerp(Quaternionf::Identity(), bone_images_[op.GetSDEF().GetBoneID(1)].total_rotation_.q)[weight].ToRotateMatrix()*bone_images_[op.GetSDEF().GetBoneID(0)].local_matrix_;
        //        pose_image.coordinates[i] = rotate(coordinate-c, mat)+rc;
        //        pose_image.normals[i] = rotate(normal, mat);
        //    }
        //    break;
        // UNDONE
        }
    }
}

inline const Model& Poser::GetModel() const { return model_; }
inline Model& Poser::GetModel() { return model_; }

inline void Poser::SetBonePose(size_t index, const Motion::BonePose& bone_pose) {
    bone_images_[index].translation_ = bone_pose.GetTranslation();
    bone_images_[index].rotation_ = bone_pose.GetRotation();
}

inline void Poser::SetBonePose(const std::wstring &name, const Motion::BonePose& bone_pose) {
    std::map<std::wstring, size_t>::iterator i = bone_name_map_.find(name);
    if(i!=bone_name_map_.end()) {
        SetBonePose(i->second, bone_pose);
    }
}

inline void Poser::SetMorphPose(size_t index, const Motion::MorphPose &morph_pose) {
    morph_rates_[index] = morph_pose.GetWeight();
}

inline void Poser::SetMorphPose(const std::wstring &name, const Motion::MorphPose &morph_pose) {
    std::map<std::wstring, size_t>::iterator i = morph_name_map_.find(name);
    if(i!=morph_name_map_.end()) {
        SetMorphPose(i->second, morph_pose);
    }
}

inline Poser::BoneImage::BoneImage() : ik_link_(false) {
    rotation_.q.MakeIdentity();
    translation_.MakeZero();

    morph_rotation_.q.MakeIdentity();
    morph_translation_.MakeZero();

    global_offset_matrix_.MakeIdentity();
    global_offset_matrix_inv_.MakeIdentity();
}

inline Poser::BoneImage::TransformOrder::TransformOrder(const Model &model) : model_(&model) {}

inline bool Poser::BoneImage::TransformOrder::operator()(size_t a, size_t b) const {
    if(model_->GetBone(a).GetTransformLevel()<model_->GetBone(b).GetTransformLevel()) {
        return true;
    } else if(model_->GetBone(a).GetTransformLevel()>model_->GetBone(b).GetTransformLevel()) {
        return false;
    } else {
        return a<b;
    }
}

inline Poser::MaterialImage::MaterialImage(float value) {
    Init(value);
}

inline void Poser::MaterialImage::Init(float value) {
    Vector4f seed;
    seed.v[0] = seed.v[1] = seed.v[2] = seed.v[3] = shininess_ = edge_size_ = value;
    diffuse_ = specular_ = ambient_ = edge_color_ = texture_ = sub_texture_ = toon_texture_ = seed;
}

inline MotionPlayer::MotionPlayer(const Motion& motion, Poser& poser) : motion_(motion), poser_(poser) {
    const Model& model = poser_.GetModel();
    for(size_t i=0;i<model.GetBoneNum();++i) {
        const std::wstring &name = model.GetBone(i).GetName();
        if(motion_.IsBoneRegistered(name)) {
            bone_map_.push_back(std::make_pair(name, i));
        }
    }

    for(size_t i=0;i<model.GetMorphNum();++i) {
        const std::wstring &name = model.GetMorph(i).GetName();
        if(motion_.IsMorphRegistered(name)) {
            morph_map_.push_back(std::make_pair(name, i));
        }
    }
}

inline void MotionPlayer::SeekFrame(size_t frame) {
    for(std::vector<std::pair<std::wstring, size_t>>::iterator i=morph_map_.begin();i!=morph_map_.end();++i) {
        poser_.SetMorphPose(i->second, motion_.GetMorphPose(i->first, frame));
    }
    for(std::vector<std::pair<std::wstring, size_t>>::iterator i=bone_map_.begin();i!=bone_map_.end();++i) {
        poser_.SetBonePose(i->second, motion_.GetBonePose(i->first, frame));
    }
}

inline void MotionPlayer::SeekTime(double time) {
    for(std::vector<std::pair<std::wstring, size_t>>::iterator i=morph_map_.begin();i!=morph_map_.end();++i) {
        poser_.SetMorphPose(i->second, motion_.GetMorphPose(i->first, time));
    }
    for(std::vector<std::pair<std::wstring, size_t>>::iterator i=bone_map_.begin();i!=bone_map_.end();++i) {
        poser_.SetBonePose(i->second, motion_.GetBonePose(i->first, time));
    }
}


/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

/**
  Reference:
    PMX Specification, which could be found in 'Lib/' directory of PMDEditor.
**/
inline
PmxReader::PmxReader(FileReader &file) : file_(file) {}

inline void
PmxReader::ReadModel(Model &model) {
    try {
        file_.Reset();

        interprete::pmx_header header = file_.Read<interprete::pmx_header>();
        std::uint8_t file_flags_size = file_.Read<std::uint8_t>();

        std::string magic = header.magic;
        if(magic!="PMX "||header.version!=2.0f||file_flags_size!=8) {
            throw exception(
                std::string("PmxReader: File is not a PMX 2.0 file_.")
            );
        }

        model.Clear();

        bool utf8_encoding = file_.Read<std::uint8_t>()>0;

        size_t extra_UV_number = file_.Read<std::uint8_t>();
        model.SetExtraUVNumber(extra_UV_number);

        size_t vertex_index_size = file_.Read<std::uint8_t>();
        size_t texture_index_size = file_.Read<std::uint8_t>();
        size_t material_index_size = file_.Read<std::uint8_t>();
        size_t bone_index_size = file_.Read<std::uint8_t>();
        size_t morph_index_size = file_.Read<std::uint8_t>();
        size_t rigid_body_index_size = file_.Read<std::uint8_t>();

        model.SetName(file_.ReadString(utf8_encoding));
        model.SetNameEn(file_.ReadString(utf8_encoding));
        model.SetDescription(file_.ReadString(utf8_encoding));
        model.SetDescriptionEn(file_.ReadString(utf8_encoding));

        size_t vertex_num = (size_t)file_.Read<std::int32_t>();
        for(size_t i=0;i<vertex_num;++i) {
            interprete::pmx_vertex_basic pv
                = file_.Read<interprete::pmx_vertex_basic>();

            Model::Vertex<ref> vertex = model.NewVertex();
            Model::SkinningOperator &op = vertex.GetSkinningOperator();

            vertex.SetCoordinate(pv.coordinate);
            vertex.SetNormal(pv.normal);
            vertex.SetUVCoordinate(pv.uv_coordinate);

            for(size_t ei=0;ei<extra_UV_number;++ei) {
                Vector4f euv = file_.Read<Vector4f>();
                vertex.SetExtraUVCoordinate(ei, euv);
            }

            op.SetSkinningType(
                (Model::SkinningOperator::SkinningType)file_.Read<std::int8_t>()
            );
            switch(op.GetSkinningType()) {
            case Model::SkinningOperator::SKINNING_BDEF1:
                op.GetBDEF1().SetBoneID(file_.ReadIndex(bone_index_size));
                break;
            case Model::SkinningOperator::SKINNING_BDEF2:
                op.GetBDEF2().SetBoneID(0, file_.ReadIndex(bone_index_size));
                op.GetBDEF2().SetBoneID(1, file_.ReadIndex(bone_index_size));
                op.GetBDEF2().SetBoneWeight(file_.Read<float>());
                break;
            case Model::SkinningOperator::SKINNING_BDEF4:
                for(size_t j=0;j<4;++j) {
                    op.GetBDEF4().SetBoneID(j, file_.ReadIndex(bone_index_size));
                }
                for(size_t j=0;j<4;++j) {
                    op.GetBDEF4().SetBoneWeight(j, file_.Read<float>());
                }
                break;
            case Model::SkinningOperator::SKINNING_SDEF:
                op.GetSDEF().SetBoneID(0, file_.ReadIndex(bone_index_size));
                op.GetSDEF().SetBoneID(1, file_.ReadIndex(bone_index_size));
                op.GetSDEF().SetBoneWeight(file_.Read<float>());
                op.GetSDEF().SetC(file_.Read<Vector3f>());
                op.GetSDEF().SetR0(file_.Read<Vector3f>());
                op.GetSDEF().SetR1(file_.Read<Vector3f>());
                break;
            default:
                throw exception(
                    std::string("PmxReader: Invalid skinning specification")
                );
            }

            vertex.SetEdgeScale(file_.Read<float>());
        }

        size_t triangle_num = (size_t)file_.Read<std::int32_t>()/3;
        for(size_t i=0;i<triangle_num;++i) {
            Vector3D<std::uint32_t> &triangle = model.NewTriangle();
            for(size_t j=0;j<3;++j) {
                triangle.v[j] = (std::uint32_t)file_.ReadIndex(vertex_index_size);
            }
        }

        TextureRegistry &registry = MMD::GetMMD().GetTextureRegistry();
        std::wstring model_file_loc = file_.GetLocation();
        size_t texture_num = (size_t)file_.Read<std::int32_t>();
        std::vector<const Texture*> texture_list(texture_num);
        for(size_t i=0;i<texture_num;++i) {
            texture_list[i]
                = &registry.GetTexture(
                    file_.ReadString(utf8_encoding), model_file_loc
                );
        }

        size_t part_num = (size_t)file_.Read<std::int32_t>();
        size_t part_base_shift = 0;
        for(size_t i=0;i<part_num;++i) {
            Model::Part & part = model.NewPart();
            Material &material = part.GetMaterial();

            material.SetName(file_.ReadString(utf8_encoding));
            material.SetNameEn(file_.ReadString(utf8_encoding));

            interprete::pmx_material_basic pm
                = file_.Read<interprete::pmx_material_basic>();

            material.SetDiffuseColor(pm.diffuse);
            material.SetSpecularColor(pm.specular);
            material.SetShininess(pm.shininess);
            material.SetAmbientColor(pm.ambient);

            material.SetDrawDoubleFace(
                (pm.draw_flag&interprete::PMX_MATERIAL_DRAW_DOUBLE_FACE)!=0
            );
            material.SetDrawGroundShadow(
                (pm.draw_flag&interprete::PMX_MATERIAL_DRAW_GROUND_SHADOW)!=0
            );
            material.SetCastSelfShadow(
                (pm.draw_flag&interprete::PMX_MATERIAL_CAST_SELF_SHADOW)!=0
            );
            material.SetDrawSelfShadow(
                (pm.draw_flag&interprete::PMX_MATERIAL_DRAW_SELF_SHADOW)!=0
            );
            material.SetDrawEdge(
                (pm.draw_flag&interprete::PMX_MATERIAL_DRAW_EDGE)!=0
            );

            material.SetEdgeColor(pm.edge_color);
            material.SetEdgeSize(pm.edge_size);

            size_t texture_index = file_.ReadIndex(texture_index_size);
            if(texture_index<texture_list.size()) {
                material.SetTexture(texture_list[texture_index]);
            }

            size_t sub_texture_index = file_.ReadIndex(texture_index_size);
            if(sub_texture_index<texture_list.size()) {
                material.SetSubTexture(texture_list[sub_texture_index]);
            }
            material.SetSubTextureType(
                (Material::SubTextureTypeEnum)file_.Read<std::uint8_t>()
            );

            bool use_global_toon = file_.Read<std::uint8_t>()>0;
            if(use_global_toon) {
                size_t global_toon_index = file_.Read<std::uint8_t>();
                material.SetToon(&registry.GetGlobalToon(global_toon_index));
            } else {
                size_t toon_index = file_.ReadIndex(texture_index_size);
                if(toon_index<texture_list.size()) {
                    material.SetToon(texture_list[toon_index]);
                }
            }

            material.SetMetaInfo(file_.ReadString(utf8_encoding));

            size_t part_triangle_num = (size_t)file_.Read<std::int32_t>()/3;
            part.SetBaseShift(part_base_shift);
            part.SetTriangleNum(part_triangle_num);

            part_base_shift+=part_triangle_num;
        }

        size_t bone_num = (size_t)file_.Read<std::int32_t>();
        for(size_t i=0;i<bone_num;++i) {
            Model::Bone &bone = model.NewBone();
            bone.SetName(file_.ReadString(utf8_encoding));
            bone.SetNameEn(file_.ReadString(utf8_encoding));
            bone.SetPosition(file_.Read<Vector3f>());
            size_t parent_index = file_.ReadIndex(bone_index_size);
            if(parent_index<bone_num) {
                bone.SetParentIndex(parent_index);
            } else {
                bone.SetParentIndex((size_t)(-1));
            }
            bone.SetTransformLevel((size_t)file_.Read<std::int32_t>());
            std::uint16_t flag = file_.Read<std::uint16_t>();

            bone.SetChildUseID((flag&interprete::PMX_BONE_CHILD_USE_ID)!=0);
            bone.SetRotatable((flag&interprete::PMX_BONE_ROTATABLE)!=0);
            bone.SetMovable((flag&interprete::PMX_BONE_MOVABLE)!=0);
            bone.SetVisible((flag&interprete::PMX_BONE_VISIBLE)!=0);
            bone.SetControllable((flag&interprete::PMX_BONE_CONTROLLABLE)!=0);
            bone.SetHasIK((flag&interprete::PMX_BONE_HAS_IK)!=0);
            bone.SetAppendRotate((flag&interprete::PMX_BONE_ACQUIRE_ROTATE)!=0);
            bone.SetAppendTranslate(
                (flag&interprete::PMX_BONE_ACQUIRE_TRANSLATE)!=0
            );
            bone.SetRotAxisFixed((flag&interprete::PMX_BONE_ROT_AXIS_FIXED)!=0);
            bone.SetUseLocalAxis((flag&interprete::PMX_BONE_USE_LOCAL_AXIS)!=0);
            bone.SetPostPhysics((flag&interprete::PMX_BONE_POST_PHYSICS)!=0);
            bone.SetReceiveTransform(
                (flag&interprete::PMX_BONE_RECEIVE_TRANSFORM)!=0
            );

            if(bone.IsChildUseID()) {
                bone.SetChildIndex(file_.ReadIndex(bone_index_size));
            } else {
                bone.SetChildOffset(file_.Read<Vector3f>());
            }
            if(bone.IsAppendRotate()||bone.IsAppendTranslate()) {
                bone.SetAppendIndex(file_.ReadIndex(bone_index_size));
                bone.SetAppendRatio(file_.Read<float>());
            }
            if(bone.IsRotAxisFixed()) {
                bone.SetRotAxis(file_.Read<Vector3f>());
            }
            if(bone.IsUseLocalAxis()) {
                Vector3f local_x = file_.Read<Vector3f>();
                Vector3f local_z = file_.Read<Vector3f>();
                Vector3f local_y;
                local_y.t = local_z.t*local_x.t;
                local_z.t = local_x.t*local_y.t;
                bone.SetLocalAxisX(local_x.Normalize());
                bone.SetLocalAxisY(local_y.Normalize());
                bone.SetLocalAxisZ(local_z.Normalize());
            }
            if(bone.IsReceiveTransform()) {
                bone.SetExportKey((size_t)file_.Read<std::int32_t>());
            }
            if(bone.IsHasIK()) {
                bone.SetIKTargetIndex(file_.ReadIndex(bone_index_size));
                bone.SetCCDIterateLimit((size_t)file_.Read<std::int32_t>());
                bone.SetCCDAngleLimit(file_.Read<float>());
                size_t ik_link_num = (size_t)file_.Read<std::int32_t>();
                for(size_t j=0;j<ik_link_num;++j) {
                    Model::Bone::IKLink &link = bone.NewIKLink();
                    link.SetLinkIndex(file_.ReadIndex(bone_index_size));
                    link.SetHasLimit(file_.Read<std::int8_t>()!=0);
                    if(link.IsHasLimit()) {
                        link.SetLoLimit(file_.Read<Vector3f>());
                        link.SetHiLimit(file_.Read<Vector3f>());
                    }
                }
            }
        }

        size_t morph_num = (size_t)file_.Read<std::int32_t>();
        size_t base_morph_index = nil;
        for(size_t i=0;i<morph_num;++i) {
            Model::Morph &morph = model.NewMorph();
            morph.SetName(file_.ReadString(utf8_encoding));
            morph.SetNameEn(file_.ReadString(utf8_encoding));
            morph.SetCategory(
                (Model::Morph::MorphCategory)file_.Read<std::uint8_t>()
            );
            if(morph.GetCategory()==Model::Morph::MORPH_CAT_SYSTEM) {
                base_morph_index = i;
            }
            morph.SetType((Model::Morph::MorphType)file_.Read<std::uint8_t>());
            size_t morph_data_num = (size_t)file_.Read<std::int32_t>();
            switch(morph.GetType()) {
            case Model::Morph::MORPH_TYPE_GROUP:
                for(size_t j=0;j<morph_data_num;++j) {
                    Model::Morph::MorphData &morph_data = morph.NewMorphData();
                    morph_data.GetGroupMorph().SetMorphIndex(
                        file_.ReadIndex(morph_index_size)
                    );
                    morph_data.GetGroupMorph().SetMorphRate(file_.Read<float>());
                }
                break;
            case Model::Morph::MORPH_TYPE_VERTEX:
                for(size_t j=0;j<morph_data_num;++j) {
                    Model::Morph::MorphData &morph_data = morph.NewMorphData();
                    morph_data.GetVertexMorph().SetVertexIndex(
                        file_.ReadIndex(vertex_index_size)
                    );
                    morph_data.GetVertexMorph().SetOffset(file_.Read<Vector3f>());
                }
                break;
            case Model::Morph::MORPH_TYPE_BONE:
                for(size_t j=0;j<morph_data_num;++j) {
                    Model::Morph::MorphData &morph_data = morph.NewMorphData();
                    morph_data.GetBoneMorph().SetBoneIndex(
                        file_.ReadIndex(bone_index_size)
                    );
                    morph_data.GetBoneMorph().SetTranslation(
                        file_.Read<Vector3f>()
                    );
                    morph_data.GetBoneMorph().SetRotation(file_.Read<Vector4f>());
                }
                break;
            case Model::Morph::MORPH_TYPE_UV:
            case Model::Morph::MORPH_TYPE_EXT_UV_1:
            case Model::Morph::MORPH_TYPE_EXT_UV_2:
            case Model::Morph::MORPH_TYPE_EXT_UV_3:
            case Model::Morph::MORPH_TYPE_EXT_UV_4:
                for(size_t j=0;j<morph_data_num;++j) {
                    Model::Morph::MorphData &morph_data = morph.NewMorphData();
                    morph_data.GetUVMorph().SetVertexIndex(
                        file_.ReadIndex(vertex_index_size)
                    );
                    morph_data.GetUVMorph().SetOffset(file_.Read<Vector4f>());
                }
                break;
            case Model::Morph::MORPH_TYPE_MATERIAL:
                for(size_t j=0;j<morph_data_num;++j) {
                    Model::Morph::MorphData &morph_data = morph.NewMorphData();
                    size_t mm_index = file_.ReadIndex(material_index_size);
                    if(mm_index<model.GetBoneNum()) {
                        morph_data.GetMaterialMorph().SetMaterialIndex(mm_index);
                        morph_data.GetMaterialMorph().SetGlobal(false);
                    } else {
                        morph_data.GetMaterialMorph().SetMaterialIndex(0);
                        morph_data.GetMaterialMorph().SetGlobal(true);
                    }
                    interprete::pmx_material_morph pmm
                        = file_.Read<interprete::pmx_material_morph>();
                    morph_data.GetMaterialMorph().SetMethod(
                        (Model::Morph::MorphData::MaterialMorph::MaterialMorphMethod)
                            pmm.offset_type
                    );
                    morph_data.GetMaterialMorph().SetDiffuse(pmm.diffuse);
                    morph_data.GetMaterialMorph().SetSpecular(pmm.specular);
                    morph_data.GetMaterialMorph().SetAmbient(pmm.ambient);
                    morph_data.GetMaterialMorph().SetShininess(pmm.shininess);
                    morph_data.GetMaterialMorph().SetEdgeColor(pmm.edge_color);
                    morph_data.GetMaterialMorph().SetEdgeSize(pmm.edge_size);
                    morph_data.GetMaterialMorph().SetTexture(pmm.texture_shift);
                    morph_data.GetMaterialMorph().SetSubTexture(
                        pmm.sub_texture_shift
                    );
                    morph_data.GetMaterialMorph().SetToonTexture(pmm.toon_shift);
                }
                break;
            default:
                throw exception(std::string("PmxReader: Unknown morph type."));
            }
        }

        if(base_morph_index!=nil) {
            // TODO : rectify system-reserved category
        }

        size_t entry_item_num = (size_t)file_.Read<std::int32_t>();

        // UNDONE
        for(size_t i=0;i<entry_item_num;++i) {
            std::wstring entry_item_name = file_.ReadString(utf8_encoding);
            std::wstring entry_item_name_en = file_.ReadString(utf8_encoding);
            bool is_special = (file_.Read<std::uint8_t>()==1);
            _unused(is_special);
            size_t element_num = (size_t)file_.Read<std::int32_t>();
            for(size_t j=0;j<element_num;++j) {
                bool is_morph = (file_.Read<std::uint8_t>()==1);
                if(is_morph) {
                    size_t morph_index = file_.ReadIndex(morph_index_size);
                    _unused(morph_index);
                } else {
                    size_t bone_index = file_.ReadIndex(bone_index_size);
                    _unused(bone_index);
                }
            }
        }

        size_t rigid_body_num = (size_t)file_.Read<std::int32_t>();
        for(size_t i=0;i<rigid_body_num;++i) {
            Model::RigidBody& rigid_body = model.NewRigidBody();
            rigid_body.SetName(file_.ReadString(utf8_encoding));
            rigid_body.SetNameEn(file_.ReadString(utf8_encoding));
            rigid_body.SetAssociatedBoneIndex(file_.ReadIndex(bone_index_size));
            interprete::pmx_rigid_body rb
                = file_.Read<interprete::pmx_rigid_body>();

            rigid_body.SetCollisionGroup(rb.collision_group);
            rigid_body.GetCollisionMask() = rb.collision_mask;
            rigid_body.SetShape((Model::RigidBody::RigidBodyShape)rb.shape);
            rigid_body.SetDimensions(rb.dimensions);

            rigid_body.SetPosition(rb.position);
            rigid_body.SetRotation(rb.rotation);

            rigid_body.SetMass(rb.mass);
            rigid_body.SetTranslateDamp(rb.translate_damp);
            rigid_body.SetRotateDamp(rb.rotate_damp);
            rigid_body.SetRestitution(rb.restitution);
            rigid_body.SetFriction(rb.friction);

            rigid_body.SetType((Model::RigidBody::RigidBodyType)rb.type);
        }

        size_t constraint_num = (size_t)file_.Read<std::int32_t>();
        for(size_t i=0;i<constraint_num;++i) {
            Model::Constraint& constraint = model.NewConstraint();
            constraint.SetName(file_.ReadString(utf8_encoding));
            constraint.SetNameEn(file_.ReadString(utf8_encoding));
            size_t dof_type = file_.Read<std::uint8_t>();
            if(dof_type==0) {
                constraint.SetAssociatedRigidBodyIndex(
                    0, file_.ReadIndex(rigid_body_index_size)
                );
                constraint.SetAssociatedRigidBodyIndex(
                    1, file_.ReadIndex(rigid_body_index_size)
                );
                interprete::pmx_constraint c
                    = file_.Read<interprete::pmx_constraint>();
                constraint.SetPosition(c.position);
                constraint.SetRotation(c.rotation);
                constraint.SetPositionLowLimit(c.position_limit[0]);
                constraint.SetPositionHighLimit(c.position_limit[1]);
                constraint.SetRotationLowLimit(c.rotation_limit[0]);
                constraint.SetRotationHighLimit(c.rotation_limit[1]);
                constraint.SetSpringTranslate(c.stiffness[0]);
                constraint.SetSpringRotate(c.stiffness[1]);
            } else {
                throw exception(
                    std::string(
                        "PmxReader: Only 6DOF spring joints are supported."
                    )
                );
            }
        }
        model.Normalize();
    } catch(std::exception& e) {
        throw exception(std::string("PmxReader: Exception caught."), e);
    } catch(...) {
        throw exception(
            std::string("PmxReader: Non-standard exception caught.")
        );
    }
}

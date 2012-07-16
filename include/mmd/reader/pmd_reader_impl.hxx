
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

/**
  Reference:
    Toorisugari no Kioku - http://blog.goo.ne.jp/torisu_tetosuki/
**/

inline
PmdReader::PmdReader(FileReader &file) : file_(file) {}

inline void
PmdReader::ReadModel(Model &model) {
    try {
        file_.Reset();

        interprete::pmd_model_header header
            = file_.Read<interprete::pmd_model_header>();

        std::string magic(header.magic);
        if(magic!="Pmd"||header.version!=1.0f) {
            throw exception(std::string("PmdReader: File is not a PMD file_."));
        }

        model.Clear();

        model.SetName(ShiftJISToUTF16String(header.info.name));
        model.SetDescription(ShiftJISToUTF16String(header.info.description));

        size_t vertex_num = file_.Read<std::uint32_t>();
        for(size_t i=0;i<vertex_num;++i) {
            interprete::pmd_vertex pv = file_.Read<interprete::pmd_vertex>();

            Model::Vertex<ref> vertex = model.NewVertex();
            Model::SkinningOperator &op = vertex.GetSkinningOperator();

            vertex.SetCoordinate(pv.coordinate);
            vertex.SetNormal(pv.normal);
            vertex.SetUVCoordinate(pv.uv_coordinate);
            vertex.SetEdgeScale((pv.non_edge_flag>0)?0.0f:1.0f);

            op.SetSkinningType(Model::SkinningOperator::SKINNING_BDEF2);
            op.GetBDEF2().SetBoneID(0, (size_t)pv.skinning_bone_id[0]);
            op.GetBDEF2().SetBoneID(1, (size_t)pv.skinning_bone_id[1]);
            op.GetBDEF2().SetBoneWeight(pv.skinning_weight*0.01f);
        }

        size_t triangle_num = file_.Read<std::uint32_t>()/3;
        for(size_t i=0;i<triangle_num;++i) {
            Vector3D<std::uint32_t> &triangle = model.NewTriangle();
            for(size_t j=0;j<3;++j) {
                triangle.v[j] = file_.Read<std::uint16_t>();
            }
        }

        TextureRegistry &registry = MMD::GetMMD().GetTextureRegistry();
        std::wstring model_file_loc = file_.GetLocation();

        size_t part_num = file_.Read<std::uint32_t>();
        size_t part_base_shift = 0;

        std::vector<size_t> toon_texture_ids;

        for(size_t i=0;i<part_num;++i) {
            interprete::pmd_material pm = file_.Read<interprete::pmd_material>();

            Model::Part &part = model.NewPart();
            Material &material = part.GetMaterial();

            material.SetDiffuseColor(pm.diffuse);
            material.SetShininess(pm.shininess);
            material.SetSpecularColor(pm.specular);
            material.SetAmbientColor(pm.ambient);

            material.SetDrawDoubleFace(pm.diffuse.c.a<1.0f);
            material.SetDrawGroundShadow(pm.edge_flag!=0);
            material.SetCastSelfShadow(pm.diffuse.c.a>0.98f);
            material.SetDrawSelfShadow(pm.diffuse.c.a>0.98f);
            material.SetDrawEdge(pm.edge_flag!=0);

            Vector4f black_color;
            black_color.c.r = black_color.c.g = black_color.c.b = 0.0f;
            black_color.c.a = 1.0f;
            material.SetEdgeColor(black_color);
            material.SetEdgeSize(1.0f);

            std::wstring tex_path_string = NativeToUTF16String(pm.texture_name);
            if(tex_path_string.size()>0) {
                size_t dlm_pos = tex_path_string.find(L'*');
                if(dlm_pos!=std::wstring::npos) {
                    std::wstring tex_path = tex_path_string.substr(0, dlm_pos);
                    std::wstring sph_path = tex_path_string.substr(dlm_pos+1);
                    if(tex_path.size()>0) {
                        material.SetTexture(
                            &registry.GetTexture(tex_path, model_file_loc)
                        );
                    }
                    if(sph_path.size()>0) {
                        material.SetSubTexture(
                            &registry.GetTexture(sph_path, model_file_loc)
                        );
                        if(::tolower(*sph_path.rbegin())==L'a') {
                            material.SetSubTextureType(
                                Material::MAT_SUB_TEX_SPA
                            );
                        } else {
                            material.SetSubTextureType(
                                Material::MAT_SUB_TEX_SPH
                            );
                        }
                    }
                } else {
                    size_t ext_dlm_pos = tex_path_string.find_last_of(L'.');
                    if(ext_dlm_pos!=std::wstring::npos) {
                        std::wstring ext = tex_path_string.substr(ext_dlm_pos+1);
                        std::transform(
                            ext.begin(), ext.end(), ext.begin(), ::tolower
                        );
                        if((ext!=L"sph")&&(ext!=L"spa")) {
                            material.SetTexture(
                                &registry.GetTexture(
                                    tex_path_string, model_file_loc
                                )
                            );
                        } else {
                            material.SetSubTexture(
                                &registry.GetTexture(
                                    tex_path_string, model_file_loc
                                )
                            );
                            if(*ext.rbegin()==L'a') {
                                material.SetSubTextureType(
                                    Material::MAT_SUB_TEX_SPA
                                );
                            } else {
                                material.SetSubTextureType(
                                    Material::MAT_SUB_TEX_SPH
                                );
                            }
                        }
                    } else {
                        material.SetTexture(
                            &registry.GetTexture(
                                tex_path_string, model_file_loc
                            )
                        );
                    }
                }
            }

            toon_texture_ids.push_back(pm.toon_id);

            size_t part_triangle_num = pm.vertex_num/3;
            part.SetBaseShift(part_base_shift);
            part.SetTriangleNum(part_triangle_num);

            part_base_shift += part_triangle_num;
        }

        size_t bone_num = file_.Read<std::uint16_t>();
        std::vector<interprete::pmd_bone> raw_bones(bone_num);
        for(size_t i=0;i<bone_num;++i) {
            raw_bones[i] = file_.Read<interprete::pmd_bone>();
        }

        // TODO - [1] We need to verify bone topology.

        std::set<size_t> ik_bone_ids;

        size_t ik_num = file_.Read<std::uint16_t>();
        std::vector<interprete::pmd_raw_ik> raw_iks(ik_num);
        for(size_t i=0;i<ik_num;++i) {
            raw_iks[i].preamble = file_.Read<interprete::pmd_ik_preamble>();
            ik_bone_ids.insert(raw_iks[i].preamble.ik_bone_index);
            for(size_t j=0;j<raw_iks[i].preamble.ik_chain_length;++j) {
                raw_iks[i].chain.push_back(file_.Read<std::uint16_t>());
            }
        }

        std::sort(raw_iks.begin(), raw_iks.end());

        size_t center_bone_index = nil;

        for(size_t i=0; i<bone_num; ++i) {
            Model::Bone &bone = model.NewBone();
            const interprete::pmd_bone &raw_bone = raw_bones[i];
            bone.SetName(ShiftJISToUTF16String(raw_bone.name));
            if(bone.GetName()==L"\x30BB\x30F3\x30BF\x30FC") {
                center_bone_index = i;
            }
            bone.SetPosition(raw_bone.position);

            // TODO - workaround here, need fix, see [1].
            if(i!=(size_t)(raw_bone.parent_id)) {
                bone.SetParentIndex(raw_bone.parent_id);
            } else {
                bone.SetParentIndex(nil);
            }

            bone.SetTransformLevel(0);

            bone.SetChildUseID(true);
            bone.SetChildIndex(raw_bone.child_id);

            bone.SetRotatable(true);

            interprete::pmd_bone_types type
                = (interprete::pmd_bone_types)raw_bone.type;

            bone.SetHasIK(
                (type==interprete::PMD_BONE_IK)||(ik_bone_ids.count(i)>0)
            );
            bone.SetMovable(
                (type==interprete::PMD_BONE_ROTATE_AND_TRANSLATE)||
                bone.IsHasIK()
            );
            bone.SetVisible(
                (type!=interprete::PMD_BONE_IK_TO)&&
                (type!=interprete::PMD_BONE_INVISIBLE)&&
                (type!=interprete::PMD_BONE_ROTATE_RATIO)
            );
            bone.SetControllable(true);
            bone.SetAppendRotate(
                (type==interprete::PMD_BONE_ROTATE_EFFECT)||
                (type==interprete::PMD_BONE_ROTATE_RATIO)
            );
            bone.SetAppendTranslate(false);
            bone.SetRotAxisFixed(type==interprete::PMD_BONE_TWIST);
            bone.SetUseLocalAxis(false);
            bone.SetPostPhysics(false);
            bone.SetReceiveTransform(false);

            if(bone.IsAppendRotate()) {
                if(type==interprete::PMD_BONE_ROTATE_EFFECT) {
                    bone.SetAppendIndex(raw_bone.ik_number);
                    bone.SetAppendRatio(1.0f);
                    bone.SetTransformLevel(2);
                } else {
                    bone.SetChildUseID(false);
                    bone.SetChildOffset(Vector3f::Zero());
                    bone.SetAppendIndex(raw_bone.child_id);
                    bone.SetAppendRatio(raw_bone.ik_number*0.01f);
                }
            }

            if(bone.IsHasIK()) {
                bone.SetTransformLevel(1);
            }

            if(bone.IsRotAxisFixed()) {
                size_t child_id = raw_bone.child_id;
                if(child_id>=bone_num) {
                    child_id = 0;
                }
                bone.SetRotAxis(
                    (raw_bones[child_id].position-bone.GetPosition()).Normalize()
                );
                if(bone.IsChildUseID()) {
                    bone.SetChildUseID(false);
                    bone.SetChildOffset(Vector3f::Zero());
                }
            }
        }

        Vector3f lo_limit = Vector3f::Zero();
        Vector3f hi_limit = Vector3f::Zero();
        lo_limit.p.x = -(float)mmd_math_const_pi;
        hi_limit.p.x = -0.5f/180.0f*(float)mmd_math_const_pi;

        for(size_t i=0;i<bone_num;++i) {
            if(ik_bone_ids.count(i)>0) {
                size_t associated_ik_count = 0;
                for(size_t j=0;j<ik_num;++j) {
                    if(i==(size_t)raw_iks[j].preamble.ik_bone_index) {
                        const interprete::pmd_raw_ik &raw_ik = raw_iks[j];
                        Model::Bone* bone;
                        if(associated_ik_count==0) {
                            bone = &(model.GetBone(i));
                        } else {
                            const Model::Bone& original_bone = model.GetBone(i);

                            bone = &(model.NewBone());

                            *bone = original_bone;

                            bone->SetName(L"[IK]"+original_bone.GetName());
                            bone->SetNameEn(L"[IK]"+original_bone.GetNameEn());

                            bone->SetParentIndex(i);
                            bone->SetChildUseID(false);
                            bone->SetChildOffset(Vector3f::Zero());
                            bone->SetVisible(false);

                            bone->ClearIK();
                            bone->SetHasIK(true);
                        }

                        bone->SetIKTargetIndex(
                            raw_ik.preamble.ik_target_bone_index
                        );
                        bone->SetCCDIterateLimit(
                            raw_ik.preamble.ccd_iterate_limit
                        );
                        bone->SetCCDAngleLimit(
                            raw_ik.preamble.ccd_angle_limit*4.0f
                        );

                        for(size_t k=0;k<raw_ik.preamble.ik_chain_length;++k) {
                            Model::Bone::IKLink &link = bone->NewIKLink();
                            link.SetLinkIndex(raw_ik.chain[k]);
                            const std::wstring link_name
                                = model.GetBone(link.GetLinkIndex()).GetName();
                            if(
                                (link_name==L"\x5DE6\x3072\x3056")||
                                (link_name==L"\x53F3\x3072\x3056")
                            ) {
                                link.SetHasLimit(true);
                                link.SetLoLimit(lo_limit);
                                link.SetHiLimit(hi_limit);
                            } else {
                                link.SetHasLimit(false);
                            }
                        }

                        associated_ik_count++;
                    }
                }
            }
        }

        // TODO - need verification

        for(size_t i=0;i<bone_num;++i) {
            bool stable = true;
            for(size_t j=0;j<bone_num;++j) {
                Model::Bone& bone = model.GetBone(j);
                size_t transform_level = bone.GetTransformLevel();
                size_t parent_id = bone.GetParentIndex();
                while(parent_id<bone_num) {
                    size_t parent_transform_level
                        = model.GetBone(parent_id).GetTransformLevel();
                    if(transform_level<parent_transform_level) {
                        transform_level = parent_transform_level;
                        stable = false;
                    }
                    parent_id = model.GetBone(parent_id).GetParentIndex();
                }
                bone.SetTransformLevel(transform_level);
            }
            if(stable) {
                break;
            }
        }

        size_t face_num = file_.Read<std::uint16_t>();
        size_t base_morph_index = nil;
        for(size_t i=0;i<face_num;++i) {
            Model::Morph &morph = model.NewMorph();
            interprete::pmd_face_preamble fp
                = file_.Read<interprete::pmd_face_preamble>();
            morph.SetName(ShiftJISToUTF16String(fp.name));
            morph.SetCategory((Model::Morph::MorphCategory)fp.face_type);
            if(morph.GetCategory()==Model::Morph::MORPH_CAT_SYSTEM) {
                base_morph_index = i;
            }
            morph.SetType(Model::Morph::MORPH_TYPE_VERTEX);
            for(size_t j=0;j<fp.vertex_num;++j) {
                Model::Morph::MorphData::VertexMorph &vertex_morph_data
                    = morph.NewMorphData().GetVertexMorph();
                vertex_morph_data.SetVertexIndex(file_.Read<std::uint32_t>());
                vertex_morph_data.SetOffset(file_.Read<Vector3f>());
            }
        }

        if(base_morph_index!=nil) {
            const Model::Morph& base_morph = model.GetMorph(base_morph_index);
            for(size_t i=0;i<face_num;++i) {
                if(i==base_morph_index) {
                    continue;
                }
                Model::Morph &morph = model.GetMorph(i);
                for(size_t j=0;j<morph.GetMorphDataNum();++j) {
                    Model::Morph::MorphData::VertexMorph& vertex_morph_data
                        = morph.GetMorphData(j).GetVertexMorph();
                    size_t morph_data_vertex_index
                        = vertex_morph_data.GetVertexIndex();
                    vertex_morph_data.SetVertexIndex(
                        base_morph.GetMorphData(
                            morph_data_vertex_index
                        ).GetVertexMorph().GetVertexIndex()
                    );
                }
            }
        }

        // UNDONE
        size_t face_disp_list_num = file_.Read<std::uint8_t>();
        for(size_t i=0;i<face_disp_list_num;++i) {
            file_.Read<std::uint16_t>();
        }

        size_t bone_name_list_num = file_.Read<std::uint8_t>();
        for(size_t i=0;i<bone_name_list_num;++i) {
            file_.Read<mmd_string<50>>();
        }

        size_t bone_disp_num = file_.Read<std::uint32_t>();
        for(size_t i=0;i<bone_disp_num;++i) {
            file_.Read<std::uint16_t>();
            file_.Read<std::uint8_t>();
        }

        // UNDONE
        if(file_.GetRemainedLength()==0) {
            goto PMD_READER_READ_LEGACY_30;
        }
        {
            bool has_info_en = (file_.Read<std::uint8_t>()==1);
            if(has_info_en) {
                interprete::pmd_model_info info_en
                    = file_.Read<interprete::pmd_model_info>();
                model.SetNameEn(ShiftJISToUTF16String(info_en.name));
                model.SetDescriptionEn(
                    ShiftJISToUTF16String(info_en.description)
                );

                for(size_t i=0;i<bone_num;++i) {
                    Model::Bone& bone = model.GetBone(i);
                    bone.SetNameEn(
                        ShiftJISToUTF16String(file_.Read<mmd_string<20>>())
                    );
                }

                if(model.GetMorphNum()>0) {
                    model.GetMorph(0).SetNameEn(model.GetMorph(0).GetName());
                }
                for(size_t i=1;i<model.GetMorphNum();++i) {
                    Model::Morph& morph = model.GetMorph(i);
                    morph.SetNameEn(
                        ShiftJISToUTF16String(file_.Read<mmd_string<20>>())
                    );
                }

                // UNDONE
                for(size_t i=0;i<bone_name_list_num;++i) {
                    file_.Read<mmd_string<50>>();
                }
            }
        }

        if(file_.GetRemainedLength()==0) {
            goto PMD_READER_READ_LEGACY_30;
        }

        {
            std::vector<const Texture*> custom_textures;
            for(size_t i=0;i<10;++i) {
                custom_textures.push_back(
                    &(registry.GetTexture(
                        ShiftJISToUTF16String(
                            file_.Read<mmd_string<100>>()
                        ), model_file_loc)
                    )
                );
            }

            for(size_t i=0;i<model.GetPartNum();++i) {
                Material& material = model.GetPart(i).GetMaterial();
                if(toon_texture_ids[i]<10) {
                    material.SetToon(custom_textures[toon_texture_ids[i]]);
                } else {
                    material.SetToon(&(registry.GetGlobalToon(nil)));
                }
            }
        }

        if(file_.GetRemainedLength()==0) {
            goto PMD_READER_READ_LEGACY_50;
        }

        {
            size_t rigid_body_num = file_.Read<std::uint32_t>();
            for(size_t i=0;i<rigid_body_num;++i) {
                Model::RigidBody& rigid_body = model.NewRigidBody();
                interprete::pmd_rigid_body rb
                    = file_.Read<interprete::pmd_rigid_body>();
                rigid_body.SetName(ShiftJISToUTF16String(rb.name));
                if(rb.bone_index<bone_num) {
                    rigid_body.SetAssociatedBoneIndex(rb.bone_index);
                } else {
                    if(center_bone_index==nil) {
                        rigid_body.SetAssociatedBoneIndex(0);
                    } else {
                        rigid_body.SetAssociatedBoneIndex(center_bone_index);
                    }
                }
                rigid_body.SetCollisionGroup(rb.collision_group);
                rigid_body.GetCollisionMask() = rb.collision_mask;
                rigid_body.SetShape((Model::RigidBody::RigidBodyShape)rb.shape);
                rigid_body.SetDimensions(rb.dimensions);
                rigid_body.SetPosition(
                    model.GetBone(
                        rigid_body.GetAssociatedBoneIndex()
                    ).GetPosition()+rb.position
                );
                rigid_body.SetRotation(rb.rotation);
                rigid_body.SetMass(rb.mass);
                rigid_body.SetTranslateDamp(rb.translate_damp);
                rigid_body.SetRotateDamp(rb.rotate_damp);
                rigid_body.SetRestitution(rb.restitution);
                rigid_body.SetFriction(rb.friction);
                if(rb.bone_index<bone_num) {
                    rigid_body.SetType((Model::RigidBody::RigidBodyType)rb.type);
                } else {
                    rigid_body.SetType(
                        Model::RigidBody::RIGID_TYPE_PHYSICS_GHOST
                    );
                }
            }
        }
        {
            size_t constraint_num = file_.Read<std::uint32_t>();
            for(size_t i=0;i<constraint_num;++i) {
                Model::Constraint& constraint = model.NewConstraint();
                interprete::pmd_constraint c
                    = file_.Read<interprete::pmd_constraint>();
                constraint.SetName(ShiftJISToUTF16String(c.name));
                constraint.SetAssociatedRigidBodyIndex(
                    0, c.associated_rigid_body[0]
                );
                constraint.SetAssociatedRigidBodyIndex(
                    1, c.associated_rigid_body[1]
                );
                constraint.SetPosition(c.position);
                constraint.SetRotation(c.rotation);
                constraint.SetPositionLowLimit(c.position_limit[0]);
                constraint.SetPositionHighLimit(c.position_limit[1]);
                constraint.SetRotationLowLimit(c.rotation_limit[0]);
                constraint.SetRotationHighLimit(c.rotation_limit[1]);
                constraint.SetSpringTranslate(c.stiffness[0]);
                constraint.SetSpringRotate(c.stiffness[1]);
            }
        }
        goto PMD_READER_READ_SUCCEED;

PMD_READER_READ_LEGACY_30:
        for(size_t i=0;i<model.GetPartNum();++i) {
            Material& material = model.GetPart(i).GetMaterial();
            material.SetToon(&(registry.GetGlobalToon(toon_texture_ids[i])));
        }
PMD_READER_READ_LEGACY_50:
PMD_READER_READ_SUCCEED:
        model.Normalize();
    } catch(std::exception& e) {
        throw exception(std::string("PmdReader: Exception caught."), e);
    } catch(...) {
        throw exception(
            std::string("PmdReader: Non-standard exception caught.")
        );
    }
}

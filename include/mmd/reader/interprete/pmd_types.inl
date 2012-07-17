
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __PMD_TYPES_HXX_DDFEA67D0DA18CE85D883BD7FB15E107_INCLUDED__
#define __PMD_TYPES_HXX_DDFEA67D0DA18CE85D883BD7FB15E107_INCLUDED__

namespace mmd {

    namespace interprete {

#include "../../util/pack.inc"
        struct PACKED pmd_model_info {
            mmd_string<20> name;
            mmd_string<256> description;
        };

        struct PACKED pmd_model_header {
            mmd_string<3> magic;
            float version;
            pmd_model_info info;
        };

        struct PACKED pmd_vertex {
            Vector3f coordinate;
            Vector3f normal;
            Vector2f uv_coordinate;
            std::int16_t skinning_bone_id[2];
            std::uint8_t skinning_weight;
            std::uint8_t non_edge_flag;
        };

        struct PACKED pmd_material {
            Vector4f diffuse;
            float shininess;
            Vector3f specular;
            Vector3f ambient;
            std::int8_t toon_id;
            std::uint8_t edge_flag;
            std::uint32_t vertex_num;
            mmd_string<20> texture_name;
        };

        enum pmd_bone_types {
            PMD_BONE_ROTATE = 0,
            PMD_BONE_ROTATE_AND_TRANSLATE = 1,
            PMD_BONE_IK = 2,
            PMD_BONE_UNKNOWN = 3,
            PMD_BONE_IK_LINK = 4,
            PMD_BONE_ROTATE_EFFECT = 5,
            PMD_BONE_IK_TO = 6,
            PMD_BONE_INVISIBLE = 7,
            PMD_BONE_TWIST = 8,
            PMD_BONE_ROTATE_RATIO = 9
        };

        struct PACKED pmd_bone {
            mmd_string<20> name;
            std::int16_t parent_id;
            std::int16_t child_id;
            std::uint8_t type;
            std::int16_t ik_number;
            Vector3f position;
        };

        struct PACKED pmd_ik_preamble {
            std::int16_t ik_bone_index;
            std::int16_t ik_target_bone_index;
            std::uint8_t ik_chain_length;
            std::uint16_t ccd_iterate_limit;
            float ccd_angle_limit;
        };

        struct PACKED pmd_face_preamble {
            mmd_string<20> name;
            std::uint32_t vertex_num;
            std::uint8_t face_type;
        };

        struct PACKED pmd_rigid_body {
            mmd_string<20> name;
            std::uint16_t bone_index;
            std::uint8_t collision_group;
            std::uint16_t collision_mask;
            std::uint8_t shape;
            Vector3f dimensions;
            Vector3f position;
            Vector3f rotation;
            float mass;
            float translate_damp;
            float rotate_damp;
            float restitution;
            float friction;
            std::uint8_t type;
        };

        struct PACKED pmd_constraint {
            mmd_string<20> name;
            std::uint32_t associated_rigid_body[2];
            Vector3f position;
            Vector3f rotation;
            Vector3f position_limit[2];
            Vector3f rotation_limit[2];
            Vector3f stiffness[2];
        };
#include "../../util/unpack.inc"

        struct pmd_raw_ik {
            interprete::pmd_ik_preamble preamble;
            std::vector<size_t> chain;
            bool operator<(const pmd_raw_ik& ik) const {
                size_t a = 0;
                size_t b = 0;
                if(chain.size()>0) {
                    a = chain[0];
                }
                if(ik.chain.size()>0) {
                    b = ik.chain[0];
                }
                return a<b;
            }
        };

    } /* End of namespace interprete */

} /* End of namespace mmd */

#endif /* __PMD_TYPES_HXX_DDFEA67D0DA18CE85D883BD7FB15E107_INCLUDED__ */

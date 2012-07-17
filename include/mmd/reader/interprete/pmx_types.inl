
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __PMX_TYPES_HXX_24255BF963509586D5BEEFE6256D085B_INCLUDED__
#define __PMX_TYPES_HXX_24255BF963509586D5BEEFE6256D085B_INCLUDED__

namespace mmd {

    namespace interprete {

#include "../../util/pack.inc"
        struct PACKED pmx_header {
            mmd_string<4> magic;
            float version;
        };

        struct PACKED pmx_vertex_basic {
            Vector3f coordinate;
            Vector3f normal;
            Vector2f uv_coordinate;
        };

        enum pmx_material_draw_flags {
            PMX_MATERIAL_DRAW_DOUBLE_FACE = 0x01,
            PMX_MATERIAL_DRAW_GROUND_SHADOW = 0x02,
            PMX_MATERIAL_CAST_SELF_SHADOW = 0x04,
            PMX_MATERIAL_DRAW_SELF_SHADOW = 0x08,
            PMX_MATERIAL_DRAW_EDGE = 0x10
        };

        struct PACKED pmx_material_basic {
            Vector4f diffuse;
            Vector3f specular;
            float shininess;
            Vector3f ambient;
            std::uint8_t draw_flag;
            Vector4f edge_color;
            float edge_size;
        };

        enum pmx_bone_flags {
            PMX_BONE_CHILD_USE_ID = 0x0001,
            PMX_BONE_ROTATABLE = 0x0002,
            PMX_BONE_MOVABLE = 0x0004,
            PMX_BONE_VISIBLE = 0x0008,
            PMX_BONE_CONTROLLABLE = 0x0010,
            PMX_BONE_HAS_IK = 0x0020,
            PMX_BONE_ACQUIRE_ROTATE = 0x0100,
            PMX_BONE_ACQUIRE_TRANSLATE = 0x0200,
            PMX_BONE_ROT_AXIS_FIXED = 0x0400,
            PMX_BONE_USE_LOCAL_AXIS = 0x0800,
            PMX_BONE_POST_PHYSICS = 0x1000,
            PMX_BONE_RECEIVE_TRANSFORM = 0x2000
        };

        struct PACKED pmx_material_morph {
            std::uint8_t offset_type;
            Vector4f diffuse;
            Vector3f specular;
            float shininess;
            Vector3f ambient;
            Vector4f edge_color;
            float edge_size;
            Vector4f texture_shift;
            Vector4f sub_texture_shift;
            Vector4f toon_shift;
        };

        struct PACKED pmx_rigid_body {
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

        struct PACKED pmx_constraint {
            Vector3f position;
            Vector3f rotation;
            Vector3f position_limit[2];
            Vector3f rotation_limit[2];
            Vector3f stiffness[2];
        };

#include "../../util/unpack.inc"

    } /* End of namespace interprete */

} /* End of namespace mmd */

#endif /* __PMX_TYPES_HXX_24255BF963509586D5BEEFE6256D085B_INCLUDED__ */

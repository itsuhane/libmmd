
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __VMD_TYPES_HXX_66D2CB2DDEF06343109E0EC2F1F1A3A3_INCLUDED__
#define __VMD_TYPES_HXX_66D2CB2DDEF06343109E0EC2F1F1A3A3_INCLUDED__

namespace mmd {

    namespace interprete {

#include "../../util/pack.inc"
        struct PACKED vmd_header {
            mmd_string<30> magic;
            mmd_string<20> name;
        };

        struct PACKED vmd_bone {
            mmd_string<15> bone_name;
            std::uint32_t nframe;
            Vector3f translation;
            Vector4f rotation;
            std::int8_t x_interpolator[16];
            std::int8_t y_interpolator[16];
            std::int8_t z_interpolator[16];
            std::int8_t r_interpolator[16];
        };

        struct PACKED vmd_morph {
            mmd_string<15> morph_name;
            std::uint32_t nframe;
            float weight;
        };

        struct PACKED vmd_camera {
            std::uint32_t nframe;
            float focal_length;
            Vector3f position;
            Vector3f rotation;
            std::int8_t interpolator[24];
            float fov;
            std::uint8_t orthographic;
        };

        struct PACKED vmd_light {
            std::uint32_t nframe;
            Vector3f color;
            Vector3f position;
        };

        struct PACKED vmd_self_shadow {
            std::uint32_t nframe;
            std::uint8_t mode;
            float distance;
        };
#include "../../util/unpack.inc"

    } /* End of namespace interprete */

} /* End of namespace mmd */

#endif /* __VMD_TYPES_HXX_66D2CB2DDEF06343109E0EC2F1F1A3A3_INCLUDED__ */

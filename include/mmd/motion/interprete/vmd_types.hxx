
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

#include "../../util/pack.hxx"
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
#include "../../util/unpack.hxx"

    } /* End of namespace interprete */

} /* End of namespace mmd */

#endif /* __VMD_TYPES_HXX_66D2CB2DDEF06343109E0EC2F1F1A3A3_INCLUDED__ */


/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

/**
  Notes:
    In together use with Windows API, <windef.h> has defined macro 'min' and
    'max'. This will result in conflict with STL.
    Define NOMINMAX for your preprocessor to avoid windef.h's definition.
**/

#ifndef __MMD_H_7F46DEA0A2C1F5902D557E3545B096B5_INCLUDED__
#define __MMD_H_7F46DEA0A2C1F5902D557E3545B096B5_INCLUDED__

#ifdef _MSC_VER
#pragma warning( push )
/*
  Some compile warnings are intentionally disabled for MSVC:
    C4100 :
     "'xxx': unreferenced formal parameter"
    C4103 :
     "alignment changed after including header, maybe due to missing
      #pragma pack(pop)"
      This warning is generated due to the use of packing directives with
      "pack.inl" and "unpack.inl"
    C4996 :
     "'xxx': This function or variable may be unsafe. Consider using xxx
      instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online
      help for details."
*/
#pragma warning( disable : 4100 4103 4189 4514 4571 4710 4819 4820 4996 )
#endif

#include "util/macro.inc"

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>

// VC++ is broken
#ifdef MMD_USE_CSTDINT
#include <cstdint>
#endif

#include <algorithm>

#include <bitset>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <exception>

#ifndef MMD_WINDOWS
#include <iconv.h>
#endif

#include "util/dwarf.inl"
#include "util/math.inl"

namespace mmd {
    typedef Quaternion<float> Quaternionf;
    typedef Vector2D<float> Vector2f;
    typedef Vector3D<float> Vector3f;
    typedef Vector4D<float> Vector4f;
    typedef Matrix4x4<float> Matrix4f;

    typedef Bezier<float> interpolator;

    namespace {
        const size_t nil = size_t(-1);
    }

} /* End of namespace mmd */

#include "util/texture.inl"
#include "material/material.inl"

#include "model/model.inl"
#include "motion/motion.inl"
#include "motion/poser.inl"

#include "motion/physics.inl"

#include "scene/camera.inl"

namespace mmd {
    class MMD {
    public:
        static MMD &GetMMD();
        TextureRegistry &GetTextureRegistry();
    private:
        MMD();
        TextureRegistry texture_registry_;
    };
}

#include "reader/model_reader.inl"
#include "reader/motion_reader.inl"
#include "reader/pose_reader.inl"
#include "reader/camera_motion_reader.inl"
#include "reader/light_motion_reader.inl"

#include "reader/pmd_reader.inl"
#include "reader/pmx_reader.inl"
#include "reader/vmd_reader.inl"

namespace mmd {
#include "mmd_facility_impl.inl"
    namespace {
        MMD &mmd = MMD::GetMMD();
    }
} /* End of namespace mmd */

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* __MMD_H_7F46DEA0A2C1F5902D557E3545B096B5_INCLUDED__ */

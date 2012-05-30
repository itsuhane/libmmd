
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
      "pack.hxx" and "unpack.hxx"
    C4996 :
     "'xxx': This function or variable may be unsafe. Consider using xxx
      instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online
      help for details."
*/
#pragma warning( disable : 4100 4103 4189 4514 4571 4710 4819 4820 4996 )
#endif

#include "util/macro.hxx"

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>

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

#ifndef MMD_HAS_EXPERIMENTAL_CXX0X
#include <type_traits>
#endif
#include <exception>

#ifndef MMD_WINDOWS
#include <iconv.h>
#endif

#include "util/dwarf.hxx"
#include "util/math.hxx"

namespace mmd {
    typedef Quaternion<float> Quaternionf;
    typedef Vector2D<float> Vector2f;
    typedef Vector3D<float> Vector3f;
    typedef Vector4D<float> Vector4f;
    typedef Matrix4x4<float> Matrix4f;
} /* End of namespace mmd */

#include "util/texture.hxx"
#include "model/material.hxx"

#include "model/model.hxx"
#include "motion/motion.hxx"
#include "motion/poser.hxx"

#include "motion/physics.hxx"

namespace mmd {
    class MMD {
    public:
        static MMD& GetMMD();
        TextureRegistry& GetTextureRegistry();
    private:
        MMD();
        TextureRegistry texture_registry_;
    };
}

#include "model/model_reader.hxx"
#include "model/pmd_reader.hxx"
#include "model/pmx_reader.hxx"

#include "motion/motion_reader.hxx"
#include "motion/vmd_reader.hxx"

namespace mmd {
    Model* ReadModel(FileReader& file);
#include "mmd_facility_impl.hxx"
    namespace {
        const MMD& mmd = MMD::GetMMD();
    }
} /* End of namespace mmd */

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* __MMD_H_7F46DEA0A2C1F5902D557E3545B096B5_INCLUDED__ */

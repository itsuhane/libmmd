
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __MMD_H_7F46DEA0A2C1F5902D557E3545B096B5_INCLUDED__
#define __MMD_H_7F46DEA0A2C1F5902D557E3545B096B5_INCLUDED__

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4100 4103 4189 4514 4571 4710 4819 4820 4996 )
#endif

#include <cmath>
#include <cstdio>
#include <cstring>

#ifndef _MSC_VER
#include <cstdint>
#else
#if _MSC_VER>=1600
#include <cstdint>
#endif
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
    class MMDNG {
    public:
        static MMDNG& GetMMDNG();
        TextureRegistry& GetTextureRegistry();
        NullPhysicsReactor& GetNullReactor();
    private:
        MMDNG();
        TextureRegistry texture_registry_;
        NullPhysicsReactor null_reactor_;
    };
}

#include "model/model_reader.hxx"
#include "model/pmd_reader.hxx"
#include "model/pmx_reader.hxx"

#include "motion/motion_reader.hxx"
#include "motion/vmd_reader.hxx"

namespace mmd {
    Model* ReadModel(const std::string &filename);
#include "mmd_facility_impl.hxx"
} /* End of namespace mmd */

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* __MMD_H_7F46DEA0A2C1F5902D557E3545B096B5_INCLUDED__ */

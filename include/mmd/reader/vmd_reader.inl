
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __VMD_READER_HXX_E08EF07ADE305D11E317E0378D09DC07_INCLUDED__
#define __VMD_READER_HXX_E08EF07ADE305D11E317E0378D09DC07_INCLUDED__

#include "interprete/vmd_types.inl"

namespace mmd {

    class VmdReader : public MotionReader, public CameraMotionReader, public LightMotionReader {
    public:
        VmdReader(FileReader &file) : file_(file), camera_motion_shift_(nil), light_motion_shift_(nil) {}
        /*virtual*/ void ReadMotion(Motion &motion);
        /*virtual*/ void ReadCameraMotion(CameraMotion &camera_motion);
    private:
        FileReader &file_;
        mutable size_t camera_motion_shift_;
        mutable size_t light_motion_shift_;
    };

#include "vmd_reader_impl.inl"

} /* End of namespace mmd */

#endif /* __VMD_READER_HXX_E08EF07ADE305D11E317E0378D09DC07_INCLUDED__ */

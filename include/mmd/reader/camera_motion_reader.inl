
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __CAMERA_MOTION_READER_HXX_A8CC4469A39D3E629D1199DCF11993F9_INCLUDED__
#define __CAMERA_MOTION_READER_HXX_A8CC4469A39D3E629D1199DCF11993F9_INCLUDED__

namespace mmd {

    class CameraMotionReader {
    public:
        virtual void ReadCameraMotion(CameraMotion &camera_motion) = 0;
    };

} /* End of namespace mmd */

#endif /* __CAMERA_MOTION_READER_HXX_A8CC4469A39D3E629D1199DCF11993F9_INCLUDED__ */

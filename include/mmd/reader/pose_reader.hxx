
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __POSE_READER_HXX_D3E3A9A1A6DF49578DE44748C1CE401A_INCLUDED__
#define __POSE_READER_HXX_D3E3A9A1A6DF49578DE44748C1CE401A_INCLUDED__

namespace mmd {

    class PoseReader {
    public:
        virtual void ReadPose(Pose &pose) = 0;
    };

} /* End of namespace mmd */

#endif /* __POSE_READER_HXX_D3E3A9A1A6DF49578DE44748C1CE401A_INCLUDED__ */

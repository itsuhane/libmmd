
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __MOTION_READER_HXX_1EB05C30DD869F3F4B7FCA087324CC42_INCLUDED__
#define __MOTION_READER_HXX_1EB05C30DD869F3F4B7FCA087324CC42_INCLUDED__

namespace mmd {

    class MotionReader {
    public:
        virtual void ReadMotion(Motion &motion) = 0;
    };

} /* End of namespace mmd */

#endif /* __MOTION_READER_HXX_1EB05C30DD869F3F4B7FCA087324CC42_INCLUDED__ */

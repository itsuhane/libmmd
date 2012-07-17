
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __MODEL_READER_HXX_42C143FA40A6B6812FEC3E7239AD5306_INCLUDED__
#define __MODEL_READER_HXX_42C143FA40A6B6812FEC3E7239AD5306_INCLUDED__

namespace mmd {

    class ModelReader {
    public:
        virtual void ReadModel(Model &model) = 0;
    };

} /* End of namespace mmd */

#endif /* __MODEL_READER_HXX_42C143FA40A6B6812FEC3E7239AD5306_INCLUDED__ */

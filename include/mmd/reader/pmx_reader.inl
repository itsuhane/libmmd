
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __PMX_READER_HXX_BE1BD64A729DD364EF966DB405558176_INCLUDED__
#define __PMX_READER_HXX_BE1BD64A729DD364EF966DB405558176_INCLUDED__

#include "interprete/pmx_types.inl"

namespace mmd {

    class PmxReader : public ModelReader {
    public:
        PmxReader(FileReader &file);
        /*virtual*/ void ReadModel(Model &model);
    private:
        FileReader &file_;
    };

#include "pmx_reader_impl.inl"

} /* End of namespace mmd */

#endif /* __PMX_READER_HXX_BE1BD64A729DD364EF966DB405558176_INCLUDED__ */

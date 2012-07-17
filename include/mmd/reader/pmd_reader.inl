
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __PMD_READER_HXX_E170DC44E36CE685148149AD8165DD4C_INCLUDED__
#define __PMD_READER_HXX_E170DC44E36CE685148149AD8165DD4C_INCLUDED__

#include "interprete/pmd_types.inl"

namespace mmd {

    class PmdReader : public ModelReader {
    public:
        PmdReader(FileReader &file);
        /*virtual*/ void ReadModel(Model &model);
    private:
        FileReader &file_;
    };

#include "pmd_reader_impl.inl"

} /* End of namespace mmd */

#endif /* __PMD_READER_HXX_E170DC44E36CE685148149AD8165DD4C_INCLUDED__ */

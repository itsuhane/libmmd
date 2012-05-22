
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __MACRO_HXX_9D858C264DDD1162ECC2FD3FA20D5B09_INCLUDED__
#define __MACRO_HXX_9D858C264DDD1162ECC2FD3FA20D5B09_INCLUDED__

// For non-clang compilers
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if defined(_WIN32)
#define MMD_WINDOWS
#endif

// Yes Microsoft's compiler is broken.
#if !defined(_MSC_VER) || _MSC_VER>=1600
#define MMD_USE_CSTDINT
#endif

// RTTI might be used to provide some fancy feature, but not now.
#if defined(_CPPRTTI) || defined(__GXX_RTTI) || __has_feature(cxx_rtti)
#define MMD_HAS_RTTI
#endif

// We may try some new feature introduced in C++11, but not now.
#if _MSC_VER>=1600 || defined(__GXX_EXPERIMENTAL_CXX0X__)
#define MMD_HAS_EXPERIMENTAL_CXX0X
#endif

#ifndef _unused
#define _unused(x) ((void)x)
#endif

#endif /* __MACRO_HXX_9D858C264DDD1162ECC2FD3FA20D5B09_INCLUDED__ */

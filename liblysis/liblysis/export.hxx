#pragma once

#if defined(LIBLYSIS_STATIC)
#  define LIBLYSIS_SYMEXPORT
#elif defined(LIBLYSIS_STATIC_BUILD)
#  define LIBLYSIS_SYMEXPORT
#elif defined(LIBLYSIS_SHARED)
#  ifdef _WIN32
#    define LIBLYSIS_SYMEXPORT __declspec (dllimport)
#  else
#    define LIBLYSIS_SYMEXPORT
#  endif
#elif defined(LIBLYSIS_SHARED_BUILD)
#  ifdef _WIN32
#    define LIBLYSIS_SYMEXPORT __declspec (dllexport)
#  else
#    define LIBLYSIS_SYMEXPORT
#  endif
#else
// If none of the above macros are defined, then we assume we are being used by
// some third-party build system that doesn't signal the library type.
//
#  error define LIBLYSIS_STATIC or LIBLYSIS_SHARED preprocessor macro to signal liblysis library type being linked.
#endif

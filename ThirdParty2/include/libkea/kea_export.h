
#ifndef KEA_EXPORT_H
#define KEA_EXPORT_H

#ifdef KEA_STATIC_DEFINE
#  define KEA_EXPORT
#  define KEA_NO_EXPORT
#else
#  ifndef KEA_EXPORT
#    ifdef kea_EXPORTS
        /* We are building this library */
#      define KEA_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KEA_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KEA_NO_EXPORT
#    define KEA_NO_EXPORT 
#  endif
#endif

#ifndef KEA_DEPRECATED
#  define KEA_DEPRECATED __declspec(deprecated)
#endif

#ifndef KEA_DEPRECATED_EXPORT
#  define KEA_DEPRECATED_EXPORT KEA_EXPORT KEA_DEPRECATED
#endif

#ifndef KEA_DEPRECATED_NO_EXPORT
#  define KEA_DEPRECATED_NO_EXPORT KEA_NO_EXPORT KEA_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KEA_NO_DEPRECATED
#    define KEA_NO_DEPRECATED
#  endif
#endif

#endif /* KEA_EXPORT_H */

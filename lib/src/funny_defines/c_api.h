//
// Created by iliya on 4/18/26.
//

#pragma once

#ifdef LIBRARY_BUILDING
    #define IMPLEMENT(body) body
#else
    #define IMPLEMENT(body) ;
#endif

#ifdef __cplusplus
    #define EXTERN_PREFIX extern "C" {
    #define EXTERN_POSTFIX };

    #define _toc(type, obj) reinterpret_cast<ccls(type)>(obj)
    #define _itoc(type, obj) reinterpret_cast<ccls(type)>(new type(obj))

    #define _tocpp(type, obj) reinterpret_cast<type*>(obj)
    #define _tocppc(type, obj) reinterpret_cast<const type*>(obj)
    #define _tocppi(type, obj) (*_tocpp(type, obj))
    #define _tocppci(type, obj) (*_tocppc(type, obj))
#else
    #define EXTERN_PREFIX
    #define EXTERN_POSTFIX
#endif


#define chnd(type) CHandleOf##type
#define ccls(type) CHandleOf##type *

#define make_capi(type) typedef struct chnd(type) chnd(type)

#define make_cast_to(type, to) \
ccls(to) cast_to(ccls(type) obj) IMPLEMENT({ \
    auto cpp = _tocpp(type, obj); \
    auto real_cast = dynamic_cast<to*>(cpp); \
    return _toc(to, real_cast) \
})

#define make_cast_from(type, from) \
ccls(type) cast_to(ccls(from) obj) IMPLEMENT({ \
    auto cpp = _tocpp(from, obj); \
    auto real_cast = dynamic_cast<type*>(cpp); \
    return _toc(type, real_cast) \
})

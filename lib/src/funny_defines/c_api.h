//
// Created by iliya on 4/18/26.
//

#ifndef FUNNY_DEFINES_C_API_H
#define FUNNY_DEFINES_C_API_H

#ifdef __cplusplus
    #define EXTERN_PREFIX extern "C" {
    #define EXTERN_POSTFIX };

    #define _toc(type, obj) reinterpret_cast<ccls(type)>(obj)
    #define _tocc(type, obj) reinterpret_cast<const ccls(type)>(obj)
    #define _itoc(type, obj) reinterpret_cast<ccls(type)>(&(obj))
    #define _itocc(type, obj) reinterpret_cast<const ccls(type)>(&(obj))
    #define _rvtoc(type, obj) reinterpret_cast<ccls(type)>(new type(obj))
    #define _rvtocc(type, obj) reinterpret_cast<const ccls(type)>(new type(obj))

    #define _tocpp(type, obj) reinterpret_cast<type*>(obj)
    #define _tocppc(type, obj) reinterpret_cast<const type*>(obj)
    #define _tocppi(type, obj) (*_tocpp(type, obj))
    #define _tocppci(type, obj) (*_tocppc(type, obj))
#else
    #define EXTERN_PREFIX
    #define EXTERN_POSTFIX
#endif


#define chof(type) CHandleOf##type
#define ccls(type) CHandleOf##type *

#define make_capi(type) typedef struct chof(type) chof(type)

#endif // FUNNY_DEFINES_C_API_H

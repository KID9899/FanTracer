//
// Created by iliya on 4/18/26.
//

#ifndef FUNNY_DEFINES_CLASSES_H
#define FUNNY_DEFINES_CLASSES_H

#define AllowCopy(type) \
inline type(const type & other) noexcept = default; \
inline type& operator=(const type& other) noexcept = default;


#define AllowMove(type) \
inline type(type && other) noexcept = default; \
inline type& operator=(type&& other) noexcept = default;


#define DefaultBinOpDecl(type, op) \
type operator op(type lhs, const type& rhs) noexcept;

#define DefaultBinOpImpl(type, op) \
type operator op(type lhs, const type& rhs) noexcept { \
    lhs op##= rhs; \
    return lhs; \
}


#define LeftBinOpDecl(type1, type2, op) \
type1 operator op(type1 lhs, type2 rhs) noexcept;

#define LeftBinOpImpl(type1, type2, op) \
type1 operator op(type1 lhs, type2 rhs) noexcept { \
    lhs op##= rhs; \
    return lhs; \
}

#define CommutativeOpDecl(rtype, type1, type2, op) \
rtype operator op(type2 lhs, type1 rhs) noexcept;

#define CommutativeOpImpl(rtype, type1, type2, op) \
rtype operator op(type2 lhs, type1 rhs) noexcept { \
    return rhs op lhs; \
}

#endif // FUNNY_DEFINES_CLASSES_H

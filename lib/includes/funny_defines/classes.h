//
// Created by iliya on 4/18/26.
//

#ifndef FUNNY_DEFINES_CLASSES_H
#define FUNNY_DEFINES_CLASSES_H

#define AllowCopyDecl(type) \
type(const type & other) noexcept; \
type& operator=(const type& other) noexcept;

#define AllowCopyImpl(type) \
type::type(const type & other) noexcept = default; \
type& type::operator=(const type& other) noexcept = default;


#define AllowMoveDecl(type) \
type(type && other) noexcept; \
type& operator=(type&& other) noexcept;

#define AllowMoveImpl(type) \
type::type(type && other) noexcept = default; \
type& type::operator=(type&& other) noexcept = default;


#define DestructorDecl(type) ~type() noexcept;
#define DestructorImpl(type) type::~type() noexcept = default;


#define DefaultBinOpDecl(type, op) \
type operator op(const type& lhs, const type& rhs) noexcept;

#define DefaultBinOpImpl(type, op) \
type operator op(const type& lhs, const type& rhs) noexcept { \
    type result = lhs; \
    result op##= rhs; \
    return result; \
}


#define LeftBinOpDecl(type1, type2, op) \
type1 operator op(const type1& lhs, const type2& rhs) noexcept;

#define LeftBinOpImpl(type1, type2, op) \
type1 operator op(const type1& lhs, const type2& rhs) noexcept { \
    type1 result = lhs; \
    result op##= rhs; \
    return result; \
}

#define CommutativeOpDecl(rtype, type1, type2, op) \
rtype operator op(const type2& lhs, const type1& rhs) noexcept;

#define CommutativeOpImpl(rtype, type1, type2, op) \
rtype operator op(const type2& lhs, const type1& rhs) noexcept { \
    return rhs op lhs; \
}

#endif // FUNNY_DEFINES_CLASSES_H

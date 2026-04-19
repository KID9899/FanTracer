//
// Created by iliya on 4/18/26.
//

#pragma once

#define AllowCopy(type) \
type(const type & other) noexcept = default; \
type& operator=(const type& other) noexcept = default;

#define AllowMove(type) \
type(type && other) noexcept = default; \
type& operator=(type&& other) noexcept = default;

#define Destructor(type) ~type() noexcept = default;

#define DefaultBinOp(type, op) \
type operator op(const type& lhs, const type& rhs) noexcept { \
    type result = lhs; \
    result op##= rhs; \
    return result; \
}

#define LeftBinOp(type1, type2, op) \
type1 operator op(const type1& lhs, const type2& rhs) noexcept { \
    type1 result = lhs; \
    result op##= rhs; \
    return result; \
}

#define CommutativeOp(rtype, type1, type2, op) \
rtype operator op(const type2& lhs, const type1& rhs) noexcept { \
    return rhs op lhs; \
}

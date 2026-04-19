//
// Created by iliya on 4/18/26.
//

#include "funny_defines/c_api.h"

#ifndef TRACER_C_API_GEOMETRY_VECTOR3D_HPP
#define TRACER_C_API_GEOMETRY_VECTOR3D_HPP

EXTERN_PREFIX

make_capi(Vector3d);

ccls(Vector3d) Vector3d_make(float x, float y, float z) IMPLEMENT({ return _toc(Vector3d, new Vector3d(x, y, z)); })
void Vector3d_destroy(ccls(Vector3d) self) IMPLEMENT({ delete _tocpp(Vector3d, self); });

float Vector3d_getX(ccls(Vector3d) self) IMPLEMENT({ return _tocpp(Vector3d, self)->getX(); });
float Vector3d_getY(ccls(Vector3d) self) IMPLEMENT({ return _tocpp(Vector3d, self)->getY(); });
float Vector3d_getZ(ccls(Vector3d) self) IMPLEMENT({ return _tocpp(Vector3d, self)->getZ(); });

float Vector3d_hypot(ccls(Vector3d) self) IMPLEMENT({ return _tocpp(Vector3d, self)->hypot(); });
float Vector3d_length(ccls(Vector3d) self) IMPLEMENT({ return _tocpp(Vector3d, self)->length(); });


ccls(Vector3d) Vector3d_add_op(ccls(Vector3d) self, ccls(Vector3d) other) IMPLEMENT({ return _itoc(Vector3d, _tocppci(Vector3d, self) + _tocppci(Vector3d, other)); });
ccls(Vector3d) Vector3d_sub_op(ccls(Vector3d) self, ccls(Vector3d) other) IMPLEMENT({ return _itoc(Vector3d, _tocppci(Vector3d, self) - _tocppci(Vector3d, other)); });
ccls(Vector3d) Vector3d_mul_op(ccls(Vector3d) self, const float scalar  ) IMPLEMENT({ return _itoc(Vector3d, _tocppci(Vector3d, self) * scalar                  ); });
ccls(Vector3d) Vector3d_div_op(ccls(Vector3d) self, const float scalar  ) IMPLEMENT({ return _itoc(Vector3d, _tocppci(Vector3d, self) / scalar                  ); });
ccls(Vector3d) Vector3d_neg_op(ccls(Vector3d) self                      ) IMPLEMENT({ return _itoc(Vector3d, -_tocppci(Vector3d, self)                          ); });

float Vector3d_dot(ccls(Vector3d) self, ccls(Vector3d) other) IMPLEMENT({ return _tocppci(Vector3d, self) * _tocppci(Vector3d, other); });

EXTERN_POSTFIX

#endif // TRACER_C_API_GEOMETRY_VECTOR3D_HPP

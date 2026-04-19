//
// Created by iliya on 4/18/26.
//

#include "funny_defines/c_api.h"

#ifdef LIBRARY_BUILDING
#include "vector3d.h"
#endif

EXTERN_PREFIX

make_capi(Vector3d);

ccls(Vector3d) Vector3d_make(double x, double y, double z) IMPLEMENT({ return _toc(Vector3d, new Vector3d(x, y, z)); })
void Vector3d_destroy(ccls(Vector3d) self) IMPLEMENT({ delete _tocpp(Vector3d, self); });

double Vector3d_getX(ccls(Vector3d) self) IMPLEMENT({ return _tocpp(Vector3d, self)->getX(); });
double Vector3d_getY(ccls(Vector3d) self) IMPLEMENT({ return _tocpp(Vector3d, self)->getY(); });
double Vector3d_getZ(ccls(Vector3d) self) IMPLEMENT({ return _tocpp(Vector3d, self)->getZ(); });

ccls(Vector3d) Vector3d_add_op(ccls(Vector3d) self, ccls(Vector3d) other) IMPLEMENT({ return _itoc(Vector3d, _tocppci(Vector3d, self) + _tocppci(Vector3d, other)); });
ccls(Vector3d) Vector3d_sub_op(ccls(Vector3d) self, ccls(Vector3d) other) IMPLEMENT({ return _itoc(Vector3d, _tocppci(Vector3d, self) - _tocppci(Vector3d, other)); });
ccls(Vector3d) Vector3d_mul_op(ccls(Vector3d) self, const double scalar ) IMPLEMENT({ return _itoc(Vector3d, _tocppci(Vector3d, self) * scalar                  ); });
ccls(Vector3d) Vector3d_neg_op(ccls(Vector3d) self                      ) IMPLEMENT({ return _itoc(Vector3d, -_tocppci(Vector3d, self)                          ); });

double Vector3d_dot(ccls(Vector3d) self, ccls(Vector3d) other) IMPLEMENT({ return _tocppci(Vector3d, self) * _tocppci(Vector3d, other); });

EXTERN_POSTFIX

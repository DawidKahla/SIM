#ifndef PAW_3D_PROJECTION_H
#define PAW_3D_PROJECTION_H
#include "PAW_Matrix.h"
#include <stdlib.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif


PAW_Vector project_3D_to_2D(const PAW_Vector* const point_position);
PAW_Matrix projection_matrix(const float left, const float right, const float top, const float bottom, const float near, const float far);
#ifdef __cplusplus
}
#endif
#endif // PAW_3D_PROJECTION_H

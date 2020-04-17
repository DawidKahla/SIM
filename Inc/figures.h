#ifndef FIGURES_H
#define FIGURES_H

#include "PAW_Scene.h"
#include "PAW_Figure.h"
#include "PAW_Line.h"

#ifdef __cplusplus
extern "C" {
#endif

void PAW_MakeFeatherFromFigure(PAW_Figure* figure);

void PAW_MakeStarFromFigure(PAW_Figure* const figure, const PAW_Vector position,
		const float radius, const uint32_t color);

void PAW_MakeDonutFromFigure(PAW_Figure* const figure, PAW_Vector* const position,
		const float radius1, const float radius2, const uint32_t color);

#ifdef __cplusplus
}
#endif

#endif //FIGURES_H

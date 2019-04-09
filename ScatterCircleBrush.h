//
// ScatterCircleBrush.h
//
// The header file for SingleLineBrush. 
//

#ifndef SCATTERCIRCLEBRUSH_H
#define SCATTERCIRCLEBRUSH_H

#include "ImpBrush.h"

class ScatterCircleBrush : public ImpBrush
{
public:
	ScatterCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};
#endif
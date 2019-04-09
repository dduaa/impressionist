//
// CircleBrush.h
//
// The header file for SingleLineBrush. 
//

#ifndef CIRCLEBRUSH_H
#define CIRCLEBRUSH_H

#include "ImpBrush.h"

class CircleBrush : public ImpBrush
{
public:
	CircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	//void DrawCircle(const Point source, const Point target, float radius);
	char* BrushName(void);
};

#endif
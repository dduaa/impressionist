#ifndef SMOOTHBRUSH_H
#define SMOOTHBRUSH_H

#include "ImpBrush.h"

class SmoothBrush : public ImpBrush
{
public:
	SmoothBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif
//
// SingleLineBrush.h
//
// The header file for SingleLineBrush. 
//

#ifndef SINGLELINEBRUSH_H
#define SINGLELINEBRUSH_H

#include "ImpBrush.h"

class SingleLineBrush : public ImpBrush
{
public:
	SingleLineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif
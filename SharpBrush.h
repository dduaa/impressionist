//
// BlurBrush.h
//
// The header file for Point Brush. 
//

#ifndef SHARPBRUSH_H
#define SHARPBRUSH_H

#include "ImpBrush.h"

class SharpBrush : public ImpBrush
{
public:
	SharpBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);
	~SharpBrush() {
	}
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void processSharp(int, int, GLubyte*);
	char* BrushName(void);

};

#endif
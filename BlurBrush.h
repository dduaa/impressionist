//
// BlurBrush.h
//
// The header file for Point Brush. 
//

#ifndef BLURBRUSH_H
#define BLURBRUSH_H

#include "ImpBrush.h"

class BlurBrush : public ImpBrush
{
public:
	BlurBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);
	~BlurBrush() {
	}
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void processBlur(int,int,GLubyte*);
	char* BrushName(void);
	
};

#endif
#ifndef LUMINANCEBRUSH_H
#define LUMINANCEBRUSH_H

#include "ImpBrush.h"

class LuminanceBrush : public ImpBrush
{
public:
	LuminanceBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);
	~LuminanceBrush() {
	}
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void processLumi(int, int, GLubyte*);
	char* BrushName(void);

};

#endif
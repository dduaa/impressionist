#pragma once
#ifndef WAVEBRUSH_H
#define WAVEBRUSH_H

#include "ImpBrush.h"

class WaveBrush : public ImpBrush
{
public:
	WaveBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void processWave(int, int, GLubyte*);
	char* BrushName(void);
};

#endif
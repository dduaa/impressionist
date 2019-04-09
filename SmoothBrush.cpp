#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SmoothBrush.h"

extern float frand();

SmoothBrush::SmoothBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void SmoothBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	glPointSize((float)size);
	BrushMove(source, target);
}

void SmoothBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POINTS);
	SetColor(source);

	glVertex2d(target.x, target.y);

	glEnd();
}

void SmoothBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}



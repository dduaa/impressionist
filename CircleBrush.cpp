//
// CircleBrush.cpp
//
// The implementation of CircleBrush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
extern float frand();
CircleBrush::CircleBrush(ImpressionistDoc * pDoc, char * name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	//glLineWidth((float)pDoc->getLineWidth());
	//glLineWidth(1);
	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize()>1 ? pDoc->getSize() : 1;
	double radius = size / 2.0;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLE_FAN);
	SetColor(source);

	glVertex2f((GLfloat)target.x, (GLfloat)target.y);

	for (int angle = 0; angle < 360; angle++)
	{
		double x = target.x + radius * cos((double)(angle)*PI / 180);
		double y = target.y + radius * sin((double)(angle)*PI / 180);
		//printf("x is %f, y is %f\n", x, y);
		glVertex2f((GLfloat)x, (GLfloat)y);
	}

	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
}


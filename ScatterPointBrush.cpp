//
// ScatterPointBrush.cpp
//
// The implementation of ScatterPointBrush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatterPointBrush.h"
extern float frand();
ScatterPointBrush::ScatterPointBrush(ImpressionistDoc * pDoc, char * name) :
	ImpBrush(pDoc, name)
{
}

void ScatterPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	glPointSize(1);
	BrushMove(source, target);
}

void ScatterPointBrush::BrushMove(const Point source, const Point target)
{
	// original point would be a square
	// treat it as a m * n matrix, mask these m*n points randomly
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatterPointBrush::BrushMove  document is NULL\n");
		return;
	}
	int size =  pDoc->getSize();
	
	glBegin(GL_POINTS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	SetColor(source);
	glVertex2f((GLfloat)target.x, (GLfloat)target.y);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int percent = rand() % 9 + 1;
			int mask = rand() % percent;
			if (mask == 1) {
				int x = source.x - size / 2 + i;
				int y = source.y - size / 2 + j;
				SetColor(Point(x, y));
				glVertex2d((GLfloat)x, (GLfloat)y);
			}
		}
	}

	glEnd();
}

void ScatterPointBrush::BrushEnd(const Point source, const Point target)
{
}



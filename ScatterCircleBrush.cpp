//
// ScatterCircleBrush.cpp
//
// The implementation of CircleBrush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatterCircleBrush.h"
extern float frand();
ScatterCircleBrush::ScatterCircleBrush(ImpressionistDoc * pDoc, char * name) :
	ImpBrush(pDoc, name)
{
}

void ScatterCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glLineWidth((float)pDoc->getLineWidth());

	BrushMove(source, target);
}

void ScatterCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}
	int size = pDoc->getSize();
	float radius = (float)size / 2;
	int angle = pDoc->getLineAngle();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			//mask or not
			int total = size * size;
			int mask = rand() % (total);
			if (mask == 0 || mask == 1 || mask == 2) {
				int newY = source.y - size / 2 + j;
				int newX = source.x - size / 2 + i;

				SetColor(Point(newX, newY));
				glVertex2f(GLfloat(target.x - size / 2 + i), GLfloat(target.y - size / 2 + j));
				for (double angle = 0; angle < 360; angle++)
				{
					double x = target.x - size / 2 + i + radius * cos((double)(angle)*PI / 180);
					double y = target.y - size / 2 + j + radius * sin((double)(angle)*PI / 180);
					glVertex2f((GLfloat)x, (GLfloat)y);
				}
			}
		}
	}

	SetColor(source);


	glEnd();
}

void ScatterCircleBrush::BrushEnd(const Point source, const Point target)
{
}


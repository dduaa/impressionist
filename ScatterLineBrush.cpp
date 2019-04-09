//
// ScatterLineBrush.cpp
//
// The implementation of CircleBrush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatterLineBrush.h"
extern float frand();
static Point pre(-1, -1);
ScatterLineBrush::ScatterLineBrush(ImpressionistDoc * pDoc, char * name) :
	ImpBrush(pDoc, name)
{
}

void ScatterLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glLineWidth((float)pDoc->getLineWidth());

	BrushMove(source, target);
}

void ScatterLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatterLineBrush::BrushMove  document is NULL\n");
		return;
	}
	int size = pDoc->getSize();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_LINES);
	SetColor(source);
	glVertex2f((GLfloat )target.x,(GLfloat)target.y);
	int angle = pDoc->getLineAngle();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			//mask or not
			int total = size * size;
			int mask = rand() % (total);
			if (mask == 0 || mask == 1 || mask == 2) {
				int newY =(int)( source.y - size / 2);
				int newX = (int)(source.x - size / 2+i);
				if (pDoc->getDirection() == DIRECTION_GRADIENT) {
				//gradient
				double deltaX;
				double deltaY;
				int pos = newY * pDoc->m_nWidth + newX;
				pos = (pos < 0) ? 0 : pos;
				pos = (pos >pDoc->m_nWidth*pDoc->m_nHeight) ? pDoc->m_nWidth*pDoc->m_nHeight : pos;
				if ((pDoc->m_pUI->getAnotherGradient() == true) && (pDoc->m_ucAnother != NULL)) {
					deltaX = pDoc->m_anoGx[pos];
					deltaY = pDoc->m_anoGy[pos];
				}
				else {
					deltaX = pDoc->m_Gx[pos];
					deltaY = pDoc->m_Gy[pos];
				}
				angle = (int)(atan2(deltaY, deltaX) * 180 / PI+90);
				// range of atan2 is -pi to pi;
				angle = (angle < 0) ? (angle + 360) : angle;
				//printf("gradient %d", angle);
				}
				else if (pDoc->getDirection() == DIRECTION_BRUSH_DIRECTION) {
					// brush direction
					bool isFirst = (pre.x == -1) && (pre.y == -1);
					bool diffPoint = (target.x != pre.x) || (target.y != pre.y);
					if (isFirst == false && diffPoint == true) {
						double deltaX = target.x - pre.x;
						double deltaY = target.y - pre.y;
						angle = (int)(atan2(deltaY, deltaX) * 180 / PI) % 360;
						//angle = (angle < 0) ? (angle + 360) : angle;
						//printf("brush direction %d", angle);
					}
					pre.x = target.x;
					pre.y = target.y;
				}
				SetColor(Point((int)( source.x - size / 2 + i), (int)(source.y - size / 2 + j)));
				glVertex2d(target.x - size / 2 + i - 0.5*size*cos(angle*PI / 180),
					target.y - size / 2 + j - 0.5*size*sin(angle*PI / 180));
				glVertex2d(target.x - size / 2 + i + 0.5*size*cos(angle*PI / 180),
					target.y - size / 2 + j + 0.5*size*sin(angle*PI / 180));
			}
			
		}
	}


	glEnd();
}

void ScatterLineBrush::BrushEnd(const Point source, const Point target)
{
}



//
// SingleLineBrush.cpp
//
// The implementation of SingleLineBrush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SingleLineBrush.h"
extern float frand();

//static variables for brush direction to store globally
static Point pre(-1,-1);

SingleLineBrush::SingleLineBrush(ImpressionistDoc * pDoc, char * name) :
	ImpBrush(pDoc, name)
{
}

void SingleLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glLineWidth((float)pDoc->getLineWidth());

	BrushMove(source, target);
}

void SingleLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("SingleLineBrush::BrushMove  document is NULL\n");
		return;
	}
	float size = (float) pDoc->getSize();
	int angle = pDoc->getLineAngle();
	
	if (pDoc->getDirection() == DIRECTION_GRADIENT) {
		//gradient
		double deltaX;
		double deltaY;
		int pos = source.y * pDoc->m_nWidth + source.x;
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
		angle = (int) (atan2(deltaY, deltaX) * 180 / PI + 90);
		// range of atan2 is -pi to pi;
		angle = (angle < 0) ? (angle + 360) : angle;
		//printf("gradient %d", angle);
	}
	else if(pDoc->getDirection() == DIRECTION_BRUSH_DIRECTION){
		// brush direction
		bool isFirst = (pre.x == -1) && (pre.y == -1);
		bool diffPoint = (target.x!=pre.x) || (target.y!=pre.y);
		if (isFirst == false && diffPoint == true) {
			double deltaX = target.x - pre.x;
			double deltaY = target.y - pre.y;
			angle = (int) (atan2(deltaY, deltaX) * 180 / PI)%360;
			//angle = (angle < 0) ? (angle + 360) : angle;
			//printf("brush direction %d", angle);
		}
		pre.x = target.x;
		pre.y = target.y;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	SetColor(source);


	glVertex2d(target.x- 0.5*size*cos(angle*PI / 180),
			target.y- 0.5*size*sin(angle*PI / 180));
	glVertex2d(target.x + 0.5*size*cos(angle*PI / 180),
		target.y + 0.5*size*sin(angle*PI / 180));

	glEnd();
}

void SingleLineBrush::BrushEnd(const Point source, const Point target)
{
}



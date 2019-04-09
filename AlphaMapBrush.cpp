#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "AlphaMapbrush.h"

extern float frand();

AlphaMapBrush::AlphaMapBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void AlphaMapBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	glPointSize(1);
	BrushMove(source, target);
}

void AlphaMapBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ALphaMapBrush::BrushMove  document is NULL\n");
		return;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POINTS);
	GLubyte color[4];
	memcpy(color, pDoc->GetOriginalPixel(source), 3);
	
	int x = target.x - pDoc->m_alpha_width / 2;
	int y = target.y - pDoc->m_alpha_height / 2;
	for (int i = 0; i < pDoc->m_alpha_width; i++) {
		for (int j = 0; j < pDoc->m_alpha_height; j++) {
			int k = rand() % 3;
			color[3] = pDoc->m_ucAlpha[3*(j*pDoc->m_alpha_width+i)+k];
			glColor4ubv(color);
			glVertex2d(x + i, y + j);
		}
	}
	glEnd();
	glFlush();
}

void AlphaMapBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}




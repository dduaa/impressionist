#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LuminanceBrush.h"

extern float frand();

LuminanceBrush::LuminanceBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LuminanceBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	glPointSize(1);
	BrushMove(source, target);
}

void LuminanceBrush::BrushMove(const Point source, const Point target)
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

	GLubyte color[4];
	int size = pDoc->getSize();
	int newX = source.x - size / 2;
	int newY = source.y - size / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int x = source.x - size / 2 + i;
			int y = source.y - size / 2 + j;
			processLumi(x, y, color);
			glVertex2d((GLfloat)x, (GLfloat)y);
		}
	}
	glEnd();
}

void LuminanceBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void LuminanceBrush::processLumi(int x, int y, GLubyte* color)
{
	ImpressionistDoc* pDoc = GetDocument();
	int height = pDoc->m_nHeight;
	int width = pDoc->m_nWidth;
	memcpy(color, pDoc->GetOriginalPixel(x,y), 3);

	//printf("alpha%f", );
	color[3] = 255;
	color[0] = (GLubyte)(pDoc->toLuminance(color[0], color[1], color[2]));
	//color[0] = color[0] * (GLubyte)(pDoc->m_pUI->getColorSpaceR());
	color[1] = color[0];
	//*(GLubyte)(pDoc->m_pUI->getColorSpaceG());
	color[2] = color[0];
	//*(GLubyte)(pDoc->m_pUI->getColorSpaceB());
	glColor4ubv(color);
}



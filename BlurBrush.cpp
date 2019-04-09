#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "blurbrush.h"

extern float frand();

BlurBrush::BlurBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void BlurBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	glPointSize((float)size);
	BrushMove(source, target);
}

void BlurBrush::BrushMove(const Point source, const Point target)
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
			processBlur(x,y, color);
			glVertex2d((GLfloat)x, (GLfloat)y);
		}
	}
	glEnd();
}

void BlurBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void BlurBrush::processBlur(int x,int y,GLubyte* color)
{
	ImpressionistDoc* pDoc = GetDocument();
	int height = pDoc->m_nHeight;
	int width = pDoc->m_nWidth;
	double Guassian[9] = { 0.0625, 0.125, 0.0625,0.125,0.25,0.125,0.0625,0.125,0.0625 };
	Filter<double> Gua = Filter<double>(Guassian, 3, 3);

	GLubyte* temp = pDoc->getChannelR();
	color[0] =(GLubyte) Gua.conv2(temp, width, height, x, y);
	temp = pDoc->getChannelG();
	color[1] = (GLubyte)Gua.conv2(temp, width, height, x, y);
	temp = pDoc->getChannelB();
	color[2] = (GLubyte)Gua.conv2(temp, width, height, x, y);
	color[3] = (GLubyte)(pDoc->getAlpha() * 255);
	glColor4ubv(color);
}



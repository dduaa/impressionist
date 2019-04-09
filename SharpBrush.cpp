#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SharpBrush.h"

extern float frand();

SharpBrush::SharpBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void SharpBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	
	glPointSize(1);
	BrushMove(source, target);
}

void SharpBrush::BrushMove(const Point source, const Point target)
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
	int newX = source.x - size/2;
	int newY = source.y - size / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int x = source.x - size / 2 + i;
			int y = source.y - size / 2 + j;
			processSharp(x,y, color);
			glVertex2d((GLfloat)x, (GLfloat)y);
		}
	}
	glEnd();
}

void SharpBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void SharpBrush::processSharp(int x, int y, GLubyte* color)
{
	ImpressionistDoc* pDoc = GetDocument();
	int height = pDoc->m_nHeight;
	int width = pDoc->m_nWidth;
	double sharp[9] = { 0,-1,0,-1,5,-1,0,-1,0};
	Filter<double> SharpFilter = Filter<double>(sharp, 3, 3);

	GLubyte* temp = pDoc->getChannelR();
	color[0] = (GLubyte) SharpFilter.conv2(temp, width, height, x, y);
	color[0] = color[0] > 255 ? 255 : color[0];
	temp = pDoc->getChannelG();
	color[1] = (GLubyte) SharpFilter.conv2(temp, width, height, x, y);
	color[1] = color[1] > 255 ? 255 : color[1];
	temp = pDoc->getChannelB();
	color[2] = (GLubyte) SharpFilter.conv2(temp, width, height, x, y);
	color[2] = color[2] > 255 ? 255 : color[2];
	color[3] = (GLubyte)(pDoc->getAlpha() * 255);
	glColor4ubv(color);
}



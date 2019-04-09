#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "WaveBrush.h"

extern float frand();

WaveBrush::WaveBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void WaveBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	glPointSize(1);
	BrushMove(source, target);
}

void WaveBrush::BrushMove(const Point source, const Point target)
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
			processWave(x, y, color);
			glVertex2d((GLfloat)x, (GLfloat)y);
		}
	}
	glEnd();
}

void WaveBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void WaveBrush::processWave(int x, int y, GLubyte* color)
{
	ImpressionistDoc* pDoc = GetDocument();
	int height = pDoc->m_nHeight;
	int width = pDoc->m_nWidth;
	double distX = double(x) - ((double)width) / 2;
	distX = abs(distX);

	double value = distX /(3*PI);
	value = 0.5*(1 + cos(value)) * (pow(3, -2 * distX / (double)width));
	GLubyte* temp = pDoc->getChannelR();
	color[0] =(GLubyte) (temp[y * width + x] * value);
	temp = pDoc->getChannelG();
	color[1] = (GLubyte)(temp[y * width + x] * value);
	temp = pDoc->getChannelB();
	color[2] = (GLubyte)(temp[y * width + x] * value);
	color[3] = (GLubyte)(pDoc->getAlpha() * 255);
	glColor4ubv(color);
}



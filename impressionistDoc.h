// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include "filter.h"

class ImpressionistUI;

class ImpressionistDoc
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image
	int		loadEdgeImage(char*);
	int		dissolveImage(char*);
	int		loadAlpha(char*);
	int		muralImage(char*);
	int		loadAnotherImage(char*);
	int		loadVideo(char*);
	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	int		getSize();						// get the UI size
	void	setSize(int size);				// set the UI size
	char*	getImageName();					// get the current image name

	int getLineAngle() const;
	void setLineAngle(int);
	int getLineWidth() const;
	void setLineWidth(int);
	int getBrushType() const;
	int getDirection() const;
	void setDirection(int);
	double getAlpha() const;
	void setAlpha(double d);
	void setRightStart(Point);
	void setRightEnd(Point);
	void rightMouseSize();
	void rightMousseAngle();
	int getSpaceSize() const;
	int getThreshold()const;

	int getPaintlyStyle() const;
	int getPaintlyStroke() const;
	int getPaintlyThresh() const;
	double getPaintlyCur() const;
	double getPaintlyBlur() const;
	double getPaintlyGridSize() const;
	int getPaintlyMinStr() const;
	int getPaintlyMaxStr() const;
	double getPaintlyAlpha() const;
	int getPaintlyLayers() const;
	int getPaintlyLevel() const;
	double getPaintlyJr() const;
	double getPaintlyJg() const;
	double getPaintlyJb() const;
	double getPaintlyJh() const;
	double getPaintlyJs() const;
	double getPaintlyJv() const;

	void setPaintlyStyle(int);
	void setPaintlyStroke(int);
	void setPaintlyThresh(int);
	void setPaintlyCur(double);
	void setPaintlyBlur(double);
	void setPaintlyGridSize(double);
	void setPaintlyMinStr(int);
	void setPaintlyMaxStr(int);
	void setPaintlyAlpha(double);
	void setPaintlyLayers(int);
	void setPaintlyLevel(int);
	void setPaintlyJr(double);
	void setPaintlyJg(double);
	void setPaintlyJb(double);
	void setPaintlyJh(double);
	void setPaintlyJs(double);
	void setPaintlyJv(double);

	unsigned char* getChannelR();
	unsigned char* getChannelG();
	unsigned char* getChannelB();
	void swapImage();
	void doItButton(int);
	//void runButton(int);
	void showAnother(int type = IMAGE_ANO);
	void showOri(int type);
	int getFilterWidth() const;
	void setFilterHeigth(int);
	int getFilterHeight() const;
	void setFilterWidth(int);
	bool getFilterNorm()const;
	
	void undo();

	// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth,
		m_nHeight;
	int				m_nfilterWidth,
		m_nfilterHeight;
	int m_alpha_width;
	int m_alpha_height;
	// Dimensions of the paint window.
	int				m_nPaintWidth,
		m_nPaintHeight;
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucDisBitmap;
	unsigned char*	m_ucBitmapR;
	unsigned char*	m_ucBitmapG;
	unsigned char*	m_ucBitmapB;
	unsigned char* m_ucAlpha;

	unsigned char*	m_ucPainting;
	unsigned char*	m_savePainting;
	unsigned char*  m_ucEdge;
	unsigned char* m_ucInputEdge;
	unsigned char* m_ucAnother;
	unsigned char* m_ucSmooth;
	unsigned char* m_ucGray;

	double* m_Gx;
	double* m_Gy;
	double* m_G;
	double* m_anoGx;
	double* m_anoGy;
	double* m_anoG;
	double* m_Smooth;

	double* m_filter;
	//double* m_ucAlphaMap;
	// The current active brush.
	ImpBrush*			m_pCurrentBrush;
	// Size of the brush.
	int m_nSize;
	int m_nBrushType;
	int m_nDirectionTpye;

	int m_nStyle;
	int m_nStroke;

	ImpressionistUI*	m_pUI;
	// for right mouse operation
	Point rightStart;
	Point rightEnd;

	// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel(int x, int y);
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel(const Point p);
	void gradient(unsigned char* source, double* Gx, double* Gy, double* G);

	void mean(unsigned char* source, double* M);
	GLubyte* edgeMap(int thr = 100);
	GLubyte * smoothMap();
	void saveCurrentPaint();
	GLubyte toGray(GLubyte*);
	GLubyte toGray(double, double, double);
	GLubyte toLuminance(double, double, double);
	void toGrayImage(GLubyte*, GLubyte*);
	void applyFilter();

	/*debug function
	void printImage(double* image) {
		if (image == NULL) {
			printf("edge is null");
			return;
		}
		for (int i = 0; i < m_nWidth; i++) {
			for (int j = 0; j < m_nHeight; j++) {
				printf("%f ", image[j*m_nWidth+i]);
			}
			printf("\n");
		}
		printf("image matrix");
	}*/
private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
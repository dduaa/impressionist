// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "ScatterPointBrush.h"
#include "SingleLineBrush.h"
#include "ScatterLineBrush.h"
#include "CircleBrush.h"
#include "ScatterCircleBrush.h"
#include "blurbrush.h"
#include "SharpBrush.h"
#include "WaveBrush.h"
#include "LuminanceBrush.h"
#include "AlphaMapbrush.h"
#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc()
{
	// Set NULL image name as init. 
	m_imageName[0] = '\0';

	m_alpha_width = 0;
	m_alpha_height = 0;
	m_nStyle=0;
	m_nStroke=0;
	m_nWidth = -1;
	m_nHeight = -1;
	m_nfilterWidth=0,
	m_nfilterHeight=0;
	m_ucBitmap = NULL;
	m_ucDisBitmap = NULL;
	m_ucBitmapR = NULL;
	m_ucBitmapG = NULL;
	m_ucBitmapB = NULL;
	m_ucPainting = NULL;
	m_savePainting = NULL;
	m_ucEdge = NULL;
	m_ucInputEdge = NULL;
	m_ucSmooth = NULL;
	m_ucAnother = NULL;
	m_ucGray = NULL;
	m_Gx = NULL;
	m_Gy = NULL;
	m_G = NULL;
	m_anoGx = NULL;
	m_anoGy = NULL;
	m_anoG = NULL;
	m_Smooth = NULL;
	//m_ucAlphaMap = NULL;
	m_filter = NULL;
	m_ucAlpha = NULL;
	// create one instance of each brush
	ImpBrush::c_nBrushCount = NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes = new ImpBrush*[ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS] = new PointBrush(this, "Points");

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]
		= new SingleLineBrush(this, "Lines");

	ImpBrush::c_pBrushes[BRUSH_CIRCLES]
		= new CircleBrush(this, "Circles");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]
		= new ScatterPointBrush(this, "Scattered Points");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]
		= new ScatterLineBrush(this, "Scattered Lines");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]
		= new ScatterCircleBrush(this, "Scattered Circles");
	ImpBrush::c_pBrushes[BRUSH_BLUR]
		= new BlurBrush(this, "Blur");
	ImpBrush::c_pBrushes[BRUSH_SHARP]
		= new SharpBrush(this, "Sharp");
	ImpBrush::c_pBrushes[BRUSH_WAVE]
		= new WaveBrush(this, "Texture");
	ImpBrush::c_pBrushes[BRUSH_LUMI]
		= new LuminanceBrush(this, "Luminance");
	ImpBrush::c_pBrushes[BRUSH_LUMI]
		= new LuminanceBrush(this, "BRUSH_ALPHA");
	
	
	

	// make one of the brushes current
	m_pCurrentBrush = ImpBrush::c_pBrushes[0];
	m_nBrushType = 0;
	m_nDirectionTpye = 0;
}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui)
{
	m_pUI = ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName()
{
	return m_imageName;
}


//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush = ImpBrush::c_pBrushes[type];
	m_nBrushType = type;
	if (type == BRUSH_LINES || type == BRUSH_SCATTERED_LINES) {
		m_pUI->m_BrushLineAngleSlider->activate();
		m_pUI->m_BrushLineWidthSlider->activate();
		m_pUI->m_AnotherGradientButton->activate();
		m_pUI->m_EdgeClippingButton->activate();
		m_pUI->m_DirectionTypeChoice->activate();
	}
	else {
		if(type== BRUSH_LUMI){
			m_pUI->m_BrushAlphaSlider->deactivate();
		}
		m_pUI->m_BrushLineAngleSlider->deactivate();
		m_pUI->m_BrushLineWidthSlider->deactivate();
		m_pUI->m_AnotherGradientButton->deactivate();
		m_pUI->m_EdgeClippingButton->deactivate();
		m_pUI->m_DirectionTypeChoice->deactivate();
	}
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}
void ImpressionistDoc::setSize(int size)
{
	m_pUI->setSize(size);
}

int ImpressionistDoc::getFilterWidth() const
{
	return m_nfilterWidth;
}
void ImpressionistDoc::setFilterHeigth(int size)
{
	 m_nfilterHeight=size;
}
int ImpressionistDoc::getFilterHeight() const
{
	return m_nfilterHeight;
}
void ImpressionistDoc::setFilterWidth(int size)
{
	m_nfilterWidth=(size);
}

bool ImpressionistDoc::getFilterNorm() const
{
	return m_pUI->getFilterNormal();
}

int ImpressionistDoc::getLineAngle() const
{
	return m_pUI->getLineAngle();
}
void ImpressionistDoc::setLineAngle(int angle) {
	m_pUI->setLineAngle(angle);
}
int ImpressionistDoc::getLineWidth() const {
	return m_pUI->getLineWidth();
}
void ImpressionistDoc::setLineWidth(int width) {
	m_pUI->setLineWidth(width);
}

int ImpressionistDoc::getBrushType() const
{
	return m_nBrushType;
}

int ImpressionistDoc::getDirection() const
{
	return m_pUI->getDitectionType();
}

void ImpressionistDoc::setDirection(int directionType)
{
	m_nDirectionTpye = directionType;
	if (m_nDirectionTpye == DIRECTION_SLIDER) {
		m_pUI->m_BrushLineAngleSlider->activate();
		m_pUI->m_AnotherGradientButton->activate();
	}
	else if (m_nDirectionTpye == DIRECTION_GRADIENT) {
		m_pUI->m_BrushLineAngleSlider->activate();
		m_pUI->m_AnotherGradientButton->activate();
	}
	else {
		m_pUI->m_AnotherGradientButton->deactivate();
		m_pUI->m_BrushLineAngleSlider->deactivate();
	}
	m_pUI->setDirectionType(directionType);

}

double ImpressionistDoc::getAlpha() const
{
	return m_pUI->getAlpha();
}

void ImpressionistDoc::setAlpha(double d)
{
	m_pUI->setAlpha(d);
}

void ImpressionistDoc::setRightStart(Point target)
{
	rightStart.x = target.x;
	rightStart.y = target.y;
}

void ImpressionistDoc::setRightEnd(Point target)
{
	rightEnd.x = target.x;
	rightEnd.y = target.y;
}

void ImpressionistDoc::rightMouseSize()
{
	int deltaX = rightStart.x - rightEnd.y;
	int deltaY = rightStart.y - rightEnd.y;
	int size = (int)sqrt(deltaX *deltaX + deltaY*deltaY);
	m_pUI->setSize(size);
}

void ImpressionistDoc::rightMousseAngle()
{
	int deltaX = -rightStart.x + rightEnd.y;
	int deltaY = -rightStart.y + rightEnd.y;
	int angle = (int)(atan2(deltaY, deltaX) * 180 / PI);
	angle = angle >= 0 ? angle : angle + 360;
	m_pUI->setLineAngle(angle);
}

int ImpressionistDoc::getSpaceSize() const
{
	return m_pUI->getSpacing();
}

int ImpressionistDoc::getThreshold() const
{
	return m_pUI->getThresh();
}

int ImpressionistDoc::getPaintlyStyle() const
{
	return m_pUI->getPaintlyStyle();
}

int ImpressionistDoc::getPaintlyStroke() const
{
	return m_pUI->getPaintlyStroke();
}
int ImpressionistDoc::getPaintlyThresh() const {
	return m_pUI->getPaintlyThresh();
}
double ImpressionistDoc::getPaintlyCur() const {
	return m_pUI->getPaintlyCur();
}
double ImpressionistDoc::getPaintlyBlur() const {
	return m_pUI->getPaintlyBlur();
}
double ImpressionistDoc::getPaintlyGridSize() const {
	return m_pUI->getPaintlyGridSize();
}
int ImpressionistDoc::getPaintlyMinStr() const {
	return m_pUI->getPaintlyMinStr();
}
int ImpressionistDoc::getPaintlyMaxStr() const {
	return m_pUI->getPaintlyMaxStr();
}
double ImpressionistDoc::getPaintlyAlpha() const {
	return m_pUI->getPaintlyAlpha();
}
int ImpressionistDoc::getPaintlyLayers() const {
	return m_pUI->getPaintlyLayers();
}
int ImpressionistDoc::getPaintlyLevel() const {
	return m_pUI->getPaintlyLevel();
}
double ImpressionistDoc::getPaintlyJr() const {
	return m_pUI->getPaintlyJr();
}
double ImpressionistDoc::getPaintlyJg() const {
	return m_pUI->getPaintlyJg();
}
double ImpressionistDoc::getPaintlyJb() const {
	return m_pUI->getPaintlyJb();
}
double ImpressionistDoc::getPaintlyJh() const {
	return m_pUI->getPaintlyJh();
}
double ImpressionistDoc::getPaintlyJs() const {
	return m_pUI->getPaintlyJs();
}
double ImpressionistDoc::getPaintlyJv() const {
	return m_pUI->getPaintlyJv();
}

void ImpressionistDoc::setPaintlyStyle(int type)
{
	m_pUI->setPaintlyStyle(type);
	//m_pCurrentBrush = ImpBrush::c_pBrushes[type];
	m_nStyle = type;
	if (type == STYLE_CU) {
		m_pUI->m_paintly_ThresholdSlider->activate();
		m_pUI->m_paintly_CurvatureSlider->activate();
		m_pUI->m_paintly_BlurSlider->activate();
		m_pUI->m_paintly_GridSizeSlider->activate();
		m_pUI->m_paintlyMinSlider->activate();
		m_pUI->m_paintlyMaxSlider->activate();
		m_pUI->m_paintlyAlphaSlider->activate();
		m_pUI->m_paintlyLayersSlider->activate();
		m_pUI->m_paintlyLevelSlider->activate();
		m_pUI->m_paintlyJrSlider->activate();
		m_pUI->m_paintlyJgSlider->activate();
		m_pUI->m_paintlyJbSlider->activate();
		m_pUI->m_paintlyJhSlider->activate();
		m_pUI->m_paintlyJsSlider->activate();
		m_pUI->m_paintlyJySlider->activate();
		m_pUI->m_StrokeTypeChoice->activate();
	}
	else {
		if (type == STYLE_IM) {
			m_pUI->m_paintly_ThresholdSlider->value(100);
			m_pUI->m_paintly_CurvatureSlider->value(1.00);
			m_pUI->m_paintly_BlurSlider->value(0.5);
			m_pUI->m_paintly_GridSizeSlider->value(1.0);
			m_pUI->m_paintlyMinSlider->value(4);
			m_pUI->m_paintlyMaxSlider->value(16);
			m_pUI->m_paintlyAlphaSlider->value(1.0);
			m_pUI->m_paintlyLayersSlider->value(3);
			m_pUI->m_paintlyLevelSlider->value(3);
			m_pUI->m_paintlyJrSlider->value(0);
			m_pUI->m_paintlyJgSlider->value(0);
			m_pUI->m_paintlyJbSlider->value(0);
			m_pUI->m_paintlyJhSlider->value(0);
			m_pUI->m_paintlyJsSlider->value(0);
			m_pUI->m_paintlyJySlider->value(0);
			m_pUI->m_StrokeTypeChoice->value(STROKE_CURVE);
			m_pUI->setPaintlyThresh(100);
			m_pUI->setPaintlyCur(1.00);
			m_pUI->setPaintlyBlur(0.5);
			m_pUI->setPaintlyGridSize(1.0);
			m_pUI->setPaintlyMinStr(4);
			m_pUI->setPaintlyMaxStr(16);
			m_pUI->setPaintlyAlpha(1.0);
			m_pUI->setPaintlyLayers(3);
			m_pUI->setPaintlyLevel(3);
			m_pUI->setPaintlyJr(0.0);
			m_pUI->setPaintlyJg(0.0);
			m_pUI->setPaintlyJb(0.0);
			m_pUI->setPaintlyJh(0.0);
			m_pUI->setPaintlyJs(0.0);
			m_pUI->setPaintlyJv(0.0);
		}else if (type == STYLE_EX) {
			m_pUI->m_paintly_ThresholdSlider->value(50);
			m_pUI->m_paintly_CurvatureSlider->value(0.25);
			m_pUI->m_paintly_BlurSlider->value(0.5);
			m_pUI->m_paintly_GridSizeSlider->value(1.0);
			m_pUI->m_paintlyMinSlider->value(10);
			m_pUI->m_paintlyMaxSlider->value(16);
			m_pUI->m_paintlyAlphaSlider->value(0.7);
			m_pUI->m_paintlyLayersSlider->value(3);
			m_pUI->m_paintlyLevelSlider->value(3);
			m_pUI->m_paintlyJrSlider->value(0);
			m_pUI->m_paintlyJgSlider->value(0);
			m_pUI->m_paintlyJbSlider->value(0);
			m_pUI->m_paintlyJhSlider->value(0);
			m_pUI->m_paintlyJsSlider->value(0);
			m_pUI->m_paintlyJySlider->value(0.5);
			m_pUI->m_StrokeTypeChoice->value(STROKE_CURVE);
			m_pUI->setPaintlyThresh(50);
			m_pUI->setPaintlyCur(0.25);
			m_pUI->setPaintlyBlur(0.5);
			m_pUI->setPaintlyGridSize(1.0);
			m_pUI->setPaintlyMinStr(10);
			m_pUI->setPaintlyMaxStr(16);
			m_pUI->setPaintlyAlpha(0.7);
			m_pUI->setPaintlyLayers(3);
			m_pUI->setPaintlyLevel(3);
			m_pUI->setPaintlyJr(0.0);
			m_pUI->setPaintlyJg(0.0);
			m_pUI->setPaintlyJb(0.0);
			m_pUI->setPaintlyJh(0.0);
			m_pUI->setPaintlyJs(0.0);
			m_pUI->setPaintlyJv(0.5);

		}else if (type == STYLE_CO){
			m_pUI->m_paintly_ThresholdSlider->value(200);
			m_pUI->m_paintly_CurvatureSlider->value(1.00);
			m_pUI->m_paintly_BlurSlider->value(0.5);
			m_pUI->m_paintly_GridSizeSlider->value(1.0);
			m_pUI->m_paintlyMinSlider->value(4);
			m_pUI->m_paintlyMaxSlider->value(16);
			m_pUI->m_paintlyAlphaSlider->value(0.5);
			m_pUI->m_paintlyLayersSlider->value(3);
			m_pUI->m_paintlyLevelSlider->value(3);
			m_pUI->m_paintlyJrSlider->value(0.3);
			m_pUI->m_paintlyJgSlider->value(0.3);
			m_pUI->m_paintlyJbSlider->value(0.3);
			m_pUI->m_paintlyJhSlider->value(0);
			m_pUI->m_paintlyJsSlider->value(0);
			m_pUI->m_paintlyJySlider->value(0);
			m_pUI->m_StrokeTypeChoice->value(STROKE_CURVE);
			m_pUI->setPaintlyThresh(200);
			m_pUI->setPaintlyCur(1.0);
			m_pUI->setPaintlyBlur(0.5);
			m_pUI->setPaintlyGridSize(1.0);
			m_pUI->setPaintlyMinStr(4);
			m_pUI->setPaintlyMaxStr(16);
			m_pUI->setPaintlyAlpha(0.5);
			m_pUI->setPaintlyLayers(3);
			m_pUI->setPaintlyLevel(3);
			m_pUI->setPaintlyJr(0.30);
			m_pUI->setPaintlyJg(0.30);
			m_pUI->setPaintlyJb(0.30);
			m_pUI->setPaintlyJh(0.0);
			m_pUI->setPaintlyJs(0.0);
			m_pUI->setPaintlyJv(0.0);

		}
		else if (type == STYLE_PO) {
			m_pUI->m_paintly_ThresholdSlider->value(100);
			m_pUI->m_paintly_CurvatureSlider->value(1.00);
			m_pUI->m_paintly_BlurSlider->value(0.5);
			m_pUI->m_paintly_GridSizeSlider->value(1.0);
			m_pUI->m_paintlyMinSlider->value(0);
			m_pUI->m_paintlyMaxSlider->value(0);
			m_pUI->m_paintlyAlphaSlider->value(1.0);
			m_pUI->m_paintlyLayersSlider->value(2);
			m_pUI->m_paintlyLevelSlider->value(2);
			m_pUI->m_paintlyJrSlider->value(0);
			m_pUI->m_paintlyJgSlider->value(0);
			m_pUI->m_paintlyJbSlider->value(0);
			m_pUI->m_paintlyJhSlider->value(0.3);
			m_pUI->m_paintlyJsSlider->value(0);
			m_pUI->m_paintlyJySlider->value(1.0);
			m_pUI->m_StrokeTypeChoice->value(STROKE_CURVE);
			m_pUI->setPaintlyThresh(100);
			m_pUI->setPaintlyCur(1.0);
			m_pUI->setPaintlyBlur(0.5);
			m_pUI->setPaintlyGridSize(1.0);
			m_pUI->setPaintlyMinStr(0);
			m_pUI->setPaintlyMaxStr(0);
			m_pUI->setPaintlyAlpha(1);
			m_pUI->setPaintlyLayers(2);
			m_pUI->setPaintlyLevel(2);
			m_pUI->setPaintlyJr(0.0);
			m_pUI->setPaintlyJg(0.0);
			m_pUI->setPaintlyJb(0.0);
			m_pUI->setPaintlyJh(0.30);
			m_pUI->setPaintlyJs(0.0);
			m_pUI->setPaintlyJv(1.0);
		}
		m_pUI->setPaintlyStroke(STROKE_CURVE);
		m_pUI->m_StrokeTypeChoice->deactivate();
		m_pUI->m_paintly_ThresholdSlider->deactivate();
		m_pUI->m_paintly_CurvatureSlider->deactivate();
		m_pUI->m_paintly_BlurSlider->deactivate();
		m_pUI->m_paintly_GridSizeSlider->deactivate();
		m_pUI->m_paintlyMinSlider->deactivate();
		m_pUI->m_paintlyMaxSlider->deactivate();
		m_pUI->m_paintlyAlphaSlider->deactivate();
		m_pUI->m_paintlyLayersSlider->deactivate();
		m_pUI->m_paintlyLevelSlider->deactivate();
		m_pUI->m_paintlyJrSlider->deactivate();
		m_pUI->m_paintlyJgSlider->deactivate();
		m_pUI->m_paintlyJbSlider->deactivate();
		m_pUI->m_paintlyJhSlider->deactivate();
		m_pUI->m_paintlyJsSlider->deactivate();
		m_pUI->m_paintlyJySlider->deactivate();
	}
}
void ImpressionistDoc::setPaintlyStroke(int d)
{
	m_nStroke = d;
	m_pUI->setPaintlyStroke(d);
}
void ImpressionistDoc::setPaintlyThresh(int d)
{
	m_pUI->setPaintlyThresh(d);
}
void ImpressionistDoc::setPaintlyCur(double d)
{
	m_pUI->setPaintlyCur(d);
}
void ImpressionistDoc::setPaintlyBlur(double d)
{
	m_pUI->setPaintlyBlur(d);
}
void ImpressionistDoc::setPaintlyGridSize(double d)
{
	m_pUI->setPaintlyGridSize(d);
}
void ImpressionistDoc::setPaintlyMinStr(int d)
{
	m_pUI->setPaintlyMinStr(d);
}
void ImpressionistDoc::setPaintlyMaxStr(int d)
{
	m_pUI->setPaintlyMaxStr(d);
}
void ImpressionistDoc::setPaintlyAlpha(double d)
{
	m_pUI->setPaintlyAlpha(d);
}
void ImpressionistDoc::setPaintlyLayers(int d)
{
	m_pUI->setPaintlyLayers(d);
}
void ImpressionistDoc::setPaintlyLevel(int d)
{
	m_pUI->setPaintlyLevel(d);
}
void ImpressionistDoc::setPaintlyJr(double d)
{
	m_pUI->setPaintlyJr(d);
}
void ImpressionistDoc::setPaintlyJg(double d)
{
	m_pUI->setPaintlyJg(d);
}
void ImpressionistDoc::setPaintlyJb(double d)
{
	m_pUI->setPaintlyJb(d);
}
void ImpressionistDoc::setPaintlyJh(double d)
{
	m_pUI->setPaintlyJh(d);
}
void ImpressionistDoc::setPaintlyJs(double d)
{
	m_pUI->setPaintlyJs(d);
}
void ImpressionistDoc::setPaintlyJv(double d)
{
	m_pUI->setPaintlyJv(d);
}

unsigned char* ImpressionistDoc::getChannelR()
{
	return m_ucBitmapR;
}
unsigned char* ImpressionistDoc::getChannelG()
{
	return m_ucBitmapG;
}
unsigned char* ImpressionistDoc::getChannelB()
{
	return m_ucBitmapB;
}
void ImpressionistDoc::swapImage()
{
	unsigned char* swap = m_pUI->m_origView->getOriView();
	m_ucBitmap = m_ucPainting;
	m_ucPainting = swap;
	m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_origView->refresh();
	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_paintView->refresh();
}

void ImpressionistDoc::doItButton(int type)
{
	if (m_ucEdge != NULL)
		delete[] m_ucEdge;
	m_ucEdge = new GLubyte[3*m_nWidth*m_nHeight];
	edgeMap(m_pUI->getThresh());	

	m_pUI->m_origView->OriViewType = IMAGE_EDGE;
	m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_origView->refresh();

	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_paintView->refresh();
}


void ImpressionistDoc::showAnother(int type)
{
	m_pUI->m_origView->OriViewType = type;
	m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_origView->refresh();

	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_paintView->refresh();
}

void ImpressionistDoc::showOri(int type)
{
	m_pUI->m_origView->OriViewType = type;
	m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_origView->refresh();

	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_paintView->refresh();
}

void ImpressionistDoc::undo()
{
	if (m_savePainting == NULL) {
		fl_message("cannot undo now");
		return;
	}
	if (m_ucPainting != NULL) {
		delete[] m_ucPainting;
		m_ucPainting = m_savePainting;
		m_savePainting = NULL;
		m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);
		m_pUI->m_origView->refresh();
		m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);
		m_pUI->m_paintView->refresh();
	}
}




//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname)
{
	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}
	//it is(R, G, B) tuples in row - major order
	// reflect the fact of loading the new image
	m_nWidth = width;
	m_nPaintWidth = width;
	m_nHeight = height;
	m_nPaintHeight = height;

	// release old storage
	if (m_ucBitmap) delete[] m_ucBitmap;
	// r g b channel
	if (m_ucDisBitmap) delete[] m_ucDisBitmap;
	if (m_ucBitmapR) delete[] m_ucBitmapR;
	if (m_ucBitmapG) delete[] m_ucBitmapG;
	if (m_ucBitmapB) delete[] m_ucBitmapB;
	
	if (m_ucPainting) delete[] m_ucPainting;
	if (m_savePainting) delete[] m_savePainting;
	if (m_ucInputEdge) delete[] m_savePainting;
	
	if (m_ucEdge) delete[] m_ucEdge;
	if (m_ucSmooth) delete[] m_ucSmooth;
	if (m_ucAnother) delete[] m_ucAnother;
	if (m_Gx) delete[] m_Gx;
	if (m_Gy) delete[] m_Gy;
	if (m_G) delete[] m_G;
	if (m_Smooth) delete[] m_Smooth;
	if (m_ucGray) delete[] m_ucGray;
	

	m_ucBitmap = data;
	m_pUI->m_origView->OriViewType = IMAGE_ORIGINAL;

	// allocate space for draw view
	m_ucPainting = new unsigned char[width*height * 3];
	memset(m_ucPainting, 0, width*height * 3);
	m_ucBitmapR = new unsigned char[width*height];
	m_ucBitmapG = new unsigned char[width*height];
	m_ucBitmapB = new unsigned char[width*height];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int pos = j*width + i;
			m_ucBitmapR[pos] = m_ucBitmap[3*pos];
			m_ucBitmapG[pos] = m_ucBitmap[3 * pos+1];
			m_ucBitmapB[pos] = m_ucBitmap[3 * pos+2];
		}
	}
	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
		m_pUI->m_mainWindow->y(),
		width * 2,
		height + 25);

	//prepare for gradient and edge
	m_G = new double[width*height];
	m_Smooth = new double[width*height];
	m_Gx = new double[width*height];
	m_Gy = new double[width*height];
	m_ucGray = new GLubyte[width * height];
	gradient(m_ucBitmap, m_Gx, m_Gy, m_G);
	//printImage(m_G);
	//printImage(m_Gx);
	//printImage(m_Gy);
	mean(m_ucBitmap, m_Smooth);
	m_ucEdge = new GLubyte[3*width*height];
	//
	edgeMap(m_pUI->getThresh());
	m_ucSmooth = new GLubyte[3 * width*height];
	
	smoothMap();
	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);
	m_pUI->m_paintView->refresh();


	return 1;
}
int ImpressionistDoc::loadVideo(char* iname) {

	return 1;
}

int ImpressionistDoc::loadAlpha(char* iname)
{
	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if (iname != NULL) {
		if ((data = readBMP(iname, width, height)) == NULL)
		{
			fl_alert("Can't load bitmap file");
			return 0;
		}
		if (width != m_nWidth || height != m_nHeight) {
			fl_alert("different dimension");
			return 0;
		}
	}

	m_alpha_width = width;
	m_alpha_height = height;

	//load the bit map
	if (m_ucAlpha) delete[] m_ucAlpha;
	m_ucAlpha = data;

	return 1;
}
//---
//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname)
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

int ImpressionistDoc::loadEdgeImage(char* iname)
{
	unsigned char*	data;
	int				width,
	height;
	if (iname != NULL) {
		if ((data = readBMP(iname, width, height)) == NULL)
		{
			fl_alert("Can't load bitmap file");
			return 0;
		}
		if (width != m_nWidth || height != m_nHeight) {
			fl_alert("different dimension");
			return 0;
		}
	}
	if (m_ucInputEdge != NULL)
		delete[]m_ucInputEdge;
	this->m_ucInputEdge = data;
	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas()
{

	// Release old storage
	if (m_ucPainting)
	{
		delete[] m_ucPainting;

		// allocate space for draw view
		m_ucPainting = new unsigned char[m_nPaintWidth*m_nPaintHeight * 3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight * 3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();

	}

	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nWidth)
		x = m_nWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nHeight)
		y = m_nHeight - 1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel(const Point p)
{
	return GetOriginalPixel(p.x, p.y);
}

void ImpressionistDoc::gradient(unsigned char* source, double* Gx, double* Gy, double* G)
{
	int height = m_nPaintHeight;
	int width = m_nPaintWidth;
	// to gray value first

	toGrayImage(source, m_ucGray);
	// smooth first then apply the filter
	//2. guassian
	double Guassian[9] = { 0.0625, 0.125, 0.0625,0.125,0.25,0.125,0.0625,0.125,0.0625 };
	Filter<double> Gua = Filter<double>(Guassian, 3, 3);
	//Gua.printFilter();
	GLubyte* afterGuassian = new GLubyte[height * width];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			afterGuassian[j*width + i] = (GLubyte)Gua.conv2(m_ucGray, width, height, i, j);
		}
	}

	double sobelX[9] = { -1,0,1,-2,0,2,-1,0,1 };
	Filter<double> sX = Filter<double>(sobelX, 3, 3);
	//sX.printFilter();
	double sobelY[9] = { -1,-2,-1,0,0,0,1,2,1 };
	Filter<double> sY = Filter<double>(sobelY, 3, 3);
	//sY.printFilter();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Gx[j*width + i] = sX.conv2(afterGuassian, width, height, i, j);
			Gy[j*width + i] = sY.conv2(afterGuassian, width, height, i, j);
			double res= sqrt((double)Gy[j*width + i] *(double)Gy[j*width + i] +
				(double)Gx[j*width + i] *(double)Gx[j*width + i]);
			//printf("%d ", res);
			G[j*width + i] = res;
		}
		//printf("\n");
	}
	if (afterGuassian != NULL)
		delete[] afterGuassian;

}

void ImpressionistDoc::mean(unsigned char * source, double * M)
{
	// smooth first then apply the filter
	int height = m_nPaintHeight;
	int width = m_nPaintWidth;
	//1. median filter
	double Guassian[9] = { 0.0625, 0.125, 0.0625,0.125,0.25,0.125,0.0625,0.125,0.0625 };
	Filter<double> Gua = Filter<double>(Guassian, 3, 3);

	for (int i = 0; i < m_nPaintWidth; i++) {
		for (int j = 0; j < m_nPaintHeight; j++) {
			M[j*width + i] = Gua.conv2(source, height, width, i, j);
		}
	}
}

GLubyte * ImpressionistDoc::edgeMap(int thr)
{
	if (m_ucEdge == NULL)
		return NULL;

	int position = 0;
	
	for (int i = 0; i < m_nPaintWidth; i++) {
		for (int j = 0; j < m_nPaintHeight; j++) {
			position = j*m_nPaintWidth + i;
			GLubyte temp = (m_G[position] > thr) ? 255 : 0;
			m_ucEdge[3 * position] = temp;
			m_ucEdge[3 * position + 1] = temp;
			m_ucEdge[3 * position + 2] = temp;
		}
	}
	return m_ucEdge;
}
GLubyte * ImpressionistDoc::smoothMap()
{
	if (m_ucSmooth == NULL)
		return NULL;

	int position = 0;
	double Guassian[9] = { 0.0625, 0.125, 0.0625,0.125,0.25,0.125,0.0625,0.125,0.0625 };
	Filter<double> Gua = Filter<double>(Guassian, 3, 3);

	
	for (int i = 0; i < m_nPaintWidth; i++) {
		for (int j = 0; j < m_nPaintHeight; j++) {
			position = j*m_nPaintWidth + i;
			GLubyte* temp = getChannelR();
			m_ucSmooth[3 * position] = (GLubyte)Gua.conv2(temp, m_nPaintWidth, m_nPaintHeight, i, j);
			temp = getChannelG();
			m_ucSmooth[3 * position + 1] = (GLubyte)Gua.conv2(temp, m_nPaintWidth, m_nPaintHeight, i, j);
			temp = getChannelB();
			m_ucSmooth[3 * position + 2] = (GLubyte)Gua.conv2(temp, m_nPaintWidth, m_nPaintHeight, i,j);
		}
	}
	return m_ucSmooth;
}

void ImpressionistDoc::saveCurrentPaint()
{
	if (m_savePainting != NULL) {
		delete[] m_savePainting;
	}
	m_savePainting = new unsigned char[m_nHeight*m_nWidth * 3];
	memcpy(m_savePainting, m_ucPainting, m_nHeight*m_nWidth * 3);
}

GLubyte ImpressionistDoc::toGray(GLubyte* p)
{
	//luma = { 0.299, 0.587, 0.114, 1.0 };
	double res =  0.299 * (double)p[0] 
		+ 0.587 * (double)p[0]+ 
		0.114 * (double)p[2];
	return (res <= 255) ? ((GLubyte)res) : 255;
}

GLubyte ImpressionistDoc::toGray(double R, double G, double B)
{
	double res = 0.299 * R + 0.587 * G + 0.114 * B;
	res = res > 0 ? res : 0;
	return (res <= 255) ? ((GLubyte)res) : 255;
}

GLubyte ImpressionistDoc::toLuminance(double R, double G, double B)
{
	//https://en.wikipedia.org/wiki/Relative_luminance
	double res = 0.299 * R + 0.7152 * G + 0.0722 * B;
	res = res > 0 ? res : 0;
	return (res <= 255) ? ((GLubyte)res) : 255;
}

void ImpressionistDoc::toGrayImage(GLubyte* origin, GLubyte* gray)
{
	if (origin == NULL || gray == NULL) {
		printf("bugs in Doc.cpp toGrayImage.");
		return;
	}
	for (int i = 0; i < m_nPaintWidth; i++) {
		for (int j = 0; j < m_nPaintHeight; j++) {
			int index = j*m_nPaintWidth + i;
			double R = origin[3 * index];
			double G = origin[3 * index+1];
			double B = origin[3 * index+2];
			gray[index] = toGray( R,G,B);
		}
	}
}
void ImpressionistDoc::applyFilter()
{
	int total = m_nfilterWidth*m_nfilterHeight;
	double* localFil =new double [total];
	if (this->getFilterNorm() == true) {
		double sum = 0;
		for (int i = 0; i < total; i++) {
			sum = sum + m_filter[i];
		}
		if(sum!=0)
			for (int i = 0; i < total; i++) {
				localFil[i] =  m_filter[i]/sum;
			}
	}
	else {
		for (int i = 0; i < total; i++) {
			localFil[i] = m_filter[i];
		}
	}
	Filter<double> local_f = Filter<double>(localFil, m_nfilterWidth, m_nfilterHeight);
	delete[] localFil;
	for (int i = 0; i < m_nWidth; ++i)
	{
		for (int j = 0; j < m_nHeight; ++j)
		{
			int index = 3 * (j * m_nWidth + i);
			m_ucPainting[index] =(GLubyte) local_f.conv2(m_ucBitmapR, m_nWidth, m_nHeight, i, j);
			m_ucPainting[index + 1] = (GLubyte)local_f.conv2(m_ucBitmapG, m_nWidth, m_nHeight, i, j);
			m_ucPainting[index + 2] = (GLubyte)local_f.conv2(m_ucBitmapB, m_nWidth, m_nHeight, i, j);
		}
	}
	m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_origView->refresh();
	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_paintView->refresh();
}
int ImpressionistDoc::loadAnotherImage(char* iname) {
	unsigned char*	data;
	int				width,
		height;
	if (iname != NULL) {
		if ((data = readBMP(iname, width, height)) == NULL)
		{
			fl_alert("Can't load bitmap file");
			return 0;
		}
		else if (width != m_nWidth || height != m_nHeight) {
			fl_alert("different dimension");
			return 0;
		}
	}
	if (m_ucAnother != NULL)
		delete[] m_ucAnother;
	if (m_anoGy != NULL)
		delete[] m_anoGy;
	if (m_anoGx != NULL)
		delete[] m_anoGx;
	if (m_anoG != NULL)
		delete[] m_anoG;

	m_ucAnother = data;
	m_anoG = new double[width*height];
	m_anoGx = new double[width*height];
	m_anoGy = new double[width*height];
	gradient(m_ucAnother, m_anoGx, m_anoGy, m_anoG);
	return 1;
}
int ImpressionistDoc::dissolveImage(char* iname)
{
	unsigned char*	data;
	int				width,
		height;
	if (iname != NULL) {
		if (m_ucBitmap == NULL) {
			fl_alert("no current image");
			return 0;
		}
		else if ((data = readBMP(iname, width, height)) == NULL)
		{
			fl_alert("Can't load bitmap file");
			return 0;
		}
		else if (width != m_nWidth || height != m_nHeight) {
			fl_alert("different dimension");
			return 0;

		}
		
	}
	if (m_ucDisBitmap != NULL)
		delete[] m_ucDisBitmap;

	m_ucDisBitmap = data;
	double localOpacity = m_pUI->getAlpha();
	for (int j = 0; j < m_nWidth*m_nHeight; j++) {
		m_ucDisBitmap[j] = (GLubyte)
			(localOpacity *(double)m_ucBitmap[j] + (1.0 - localOpacity) *(double)m_ucDisBitmap[j]);
	}

	m_pUI->m_origView->OriViewType = IMAGE_DIS;
	m_pUI->m_origView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_origView->refresh();

	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);
	m_pUI->m_paintView->refresh();
	return 1;
}
int ImpressionistDoc::muralImage(char* iname)
{
	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}
	else if (width != m_nWidth || height != m_nHeight) {
		fl_alert("different dimension");
		return 0;

	}
	//it is(R, G, B) tuples in row - major order
	// reflect the fact of loading the new image
	m_nWidth = width;
	m_nPaintWidth = width;
	m_nHeight = height;
	m_nPaintHeight = height;

	// release old storage
	if (m_ucBitmap) delete[] m_ucBitmap;
	// r g b channel
	//if (m_ucDisBitmap) delete[] m_ucDisBitmap;
	if (m_ucBitmapR) delete[] m_ucBitmapR;
	if (m_ucBitmapG) delete[] m_ucBitmapG;
	if (m_ucBitmapB) delete[] m_ucBitmapB;

	//if (m_ucPainting) delete[] m_ucPainting;  preserve what has been drawn for mural
	//if (m_savePainting) delete[] m_savePainting;
	if (m_ucInputEdge) delete[] m_ucInputEdge;

	if (m_ucEdge) delete[] m_ucEdge;
	if (m_ucSmooth) delete[] m_ucSmooth;
	if (m_ucAnother) delete[] m_ucAnother;
	if (m_Gx) delete[] m_Gx;
	if (m_Gy) delete[] m_Gy;
	if (m_G) delete[] m_G;
	if (m_Smooth) delete[] m_Smooth;
	if (m_ucGray) delete[] m_ucGray;


	m_ucBitmap = data;
	m_pUI->m_origView->OriViewType = IMAGE_ORIGINAL;

	// allocate space for draw view
	//m_ucPainting = new unsigned char[width*height * 3];
	//memset(m_ucPainting, 0, width*height * 3);
	m_ucBitmapR = new unsigned char[width*height];
	m_ucBitmapG = new unsigned char[width*height];
	m_ucBitmapB = new unsigned char[width*height];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int pos = j*width + i;
			m_ucBitmapR[pos] = m_ucBitmap[3 * pos];
			m_ucBitmapG[pos] = m_ucBitmap[3 * pos + 1];
			m_ucBitmapB[pos] = m_ucBitmap[3 * pos + 2];
		}
	}
	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
		m_pUI->m_mainWindow->y(),
		width * 2,
		height + 25);

	//prepare for gradient and edge
	m_G = new double[width*height];
	m_Smooth = new double[width*height];
	m_Gx = new double[width*height];
	m_Gy = new double[width*height];
	m_ucGray = new GLubyte[width * height];
	gradient(m_ucBitmap, m_Gx, m_Gy, m_G);
	//printImage(m_G);
	//printImage(m_Gx);
	//printImage(m_Gy);
	mean(m_ucBitmap, m_Smooth);
	m_ucEdge = new GLubyte[3 * width*height];
	//
	edgeMap(m_pUI->getThresh());
	m_ucSmooth = new GLubyte[3 * width*height];

	smoothMap();
	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);
	m_pUI->m_paintView->refresh();


	return 1;
}
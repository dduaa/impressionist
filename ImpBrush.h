#ifndef IMPBRUSH_H
#define IMPBRUSH_H

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>
#include <math.h>
#define PI 3.14159265
#include "Filter.h"
// Each brush type has an associated constant.
enum
{
	IMAGE_ORIGINAL = 0,
	IMAGE_EDGE,
	IMAGE_DIS,
	IMAGE_ANO,
	NUM_ORI_IMAGE_TYPE // Make sure this stays at the end!
};
enum
{
	BRUSH_POINTS = 0,
	BRUSH_LINES,
	BRUSH_CIRCLES,
	BRUSH_SCATTERED_POINTS,
	BRUSH_SCATTERED_LINES,
	BRUSH_SCATTERED_CIRCLES,
	BRUSH_BLUR,
	BRUSH_SHARP,
	BRUSH_WAVE,
	BRUSH_LUMI,
	BRUSH_ALPHA,
	NUM_BRUSH_TYPE // Make sure this stays at the end!
};


enum
{
	STYLE_IM = 0,
	STYLE_EX,
	STYLE_CO,
	STYLE_PO,
	STYLE_CU,
	NUM_STYLE_TYPE // Make sure this stays at the end!
};

enum
{
	STROKE_CURVE = 0,
	STROKE_BS,
	STROKE_CIRCLE,
	STROKE_CLIP,
	STROKE_LINE,
	NUM_STROKE_TYPE // Make sure this stays at the end!
};

enum
{
	DIRECTION_SLIDER = 0,
	DIRECTION_GRADIENT,
	DIRECTION_BRUSH_DIRECTION,
	NUM_DIR_TYPE // Make sure this stays at the end!
};

class ImpressionistDoc; // Pre-declaring class

class Point 
{
public:
	Point() {};
	Point(int xx, int yy) { x = xx; y = yy; };

	int x, y;
};

class ImpBrush 
{
protected:
	ImpBrush::ImpBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

public:
	// The implementation of your brush should realize these virtual functions
	virtual void BrushBegin( const Point source, const Point target ) = 0;
	virtual void BrushMove( const Point source, const Point target ) = 0;
	virtual void BrushEnd( const Point source, const Point target ) = 0;

	// according to the source image and the position, determine the draw color
	void SetColor( const Point source );

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the brush (not used in this version).
	char* BrushName( void );
	
	static int			c_nBrushCount;	// How many brushes we have,
	static ImpBrush**	c_pBrushes;		// and what they are.

private:
	ImpressionistDoc*	m_pDoc;

	// Brush's name (not used in this version).
	char*				m_pBrushName;
};

#endif
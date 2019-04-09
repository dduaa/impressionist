//
// originalview.h
//
// The header file for original view of the input images
//

#ifndef ORIGINALVIEW_H
#define ORIGINALVIEW_H

#include <FL/Fl.H>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>

#include "ImpBrush.h"

class ImpressionistDoc;



class OriginalView : public Fl_Gl_Window
{
public:
	OriginalView(int x, int y, int w, int h, const char *l);
	
	void draw();
	void refresh();
	void showCursor(int);
	void changeCursor(Point);
	unsigned char* getOriView()const {
		return currentViewType;
	}
	void resizeWindow(int width, int height);

	ImpressionistDoc*	m_pDoc;
	static int OriViewType;

private:
	int	m_nWindowWidth, 
		m_nWindowHeight;
	Point cursor;
	unsigned char* currentViewType=NULL;
};

#endif
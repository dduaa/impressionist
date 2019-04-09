//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include "CircleBrush.h"




#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6
#define PAINT_BUTTON		7
#define RUN_BUTTON			8

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent = 0;
static Point	coord;
static Point	drop;

PaintView::PaintView(int			x,
	int			y,
	int			w,
	int			h,
	const char*	l)
	: Fl_Gl_Window(x, y, w, h, l)
{
	m_nWindowWidth = w;
	m_nWindowHeight = h;

}


void PaintView::draw()
{
#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
#endif // !MESA

	if (!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable(GL_DEPTH_TEST);

		ortho();

		glClear(GL_COLOR_BUFFER_BIT);
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y = 0;

	m_nWindowWidth = w();
	m_nWindowHeight = h();

	int drawWidth, drawHeight;
	drawWidth = min(m_nWindowWidth, m_pDoc->m_nPaintWidth);
	drawHeight = min(m_nWindowHeight, m_pDoc->m_nPaintHeight);

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if (startrow < 0) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting +
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth = drawWidth;
	m_nDrawHeight = drawHeight;

	m_nStartRow = startrow;
	m_nEndRow = startrow + drawHeight;
	m_nStartCol = scrollpos.x;
	m_nEndCol = m_nStartCol + drawWidth;

	if (m_pDoc->m_ucPainting && !isAnEvent)
	{
		RestoreContent();

	}

	if (m_pDoc->m_ucPainting && isAnEvent)
	{

		// Clear it after processing.
		isAnEvent = 0;

		Point source(coord.x + m_nStartCol, m_nEndRow - coord.y);
		Point target(coord.x, m_nWindowHeight - coord.y);

		// This is the event handler
		switch (eventToDo)
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->saveCurrentPaint();
			m_pDoc->m_pCurrentBrush->BrushBegin(source, target);
			m_pDoc->m_pUI->m_origView->changeCursor(Point(source.x, m_nWindowHeight-source.y));
			//printf("source X %d\n", source.x);
			//printf("source Y %d\n", source.y);
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentBrush->BrushMove(source, target);
			m_pDoc->m_pUI->m_origView->changeCursor(coord);
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd(source, target);

			SaveCurrentContent();
			RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
			m_pDoc->setRightStart(target);
			break;
		case RIGHT_MOUSE_DRAG:
			RestoreContent();
			m_pDoc->setRightEnd(target);
			glLineWidth(1);
			glEnable(GL_LINE_SMOOTH);
			glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0); // red color
			glVertex2d(m_pDoc->rightStart.x, m_pDoc->rightStart.y);
			glVertex2d(m_pDoc->rightEnd.x, m_pDoc->rightEnd.y);
			glEnd();
			break;
		case RIGHT_MOUSE_UP:
			m_pDoc->setRightEnd(target);
			if (m_pDoc->getBrushType() == BRUSH_LINES || m_pDoc->getBrushType() == BRUSH_SCATTERED_LINES) {
				m_pDoc->rightMouseSize();
				m_pDoc->rightMousseAngle();
			}
			break;
		case PAINT_BUTTON:
			m_pDoc->saveCurrentPaint();
			PaintButtonPressed();
			SaveCurrentContent();
			RestoreContent();
			break;
		case RUN_BUTTON:
			m_pDoc->saveCurrentPaint();
			RunButtonPressed();
			SaveCurrentContent();
			RestoreContent();
			
			break;
		default:
			printf("Unknown event!!\n");
			break;
		}
	}

	glFlush();

#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
#endif // !MESA

}


int PaintView::handle(int event)
{
	switch (event)
	{
	case FL_ENTER:
		redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo = RIGHT_MOUSE_DOWN;
		else
			eventToDo = LEFT_MOUSE_DOWN;
		isAnEvent = 1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo = RIGHT_MOUSE_DRAG;
		else
			eventToDo = LEFT_MOUSE_DRAG;
		isAnEvent = 1;
		redraw();
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo = RIGHT_MOUSE_UP;
		else
			eventToDo = LEFT_MOUSE_UP;
		isAnEvent = 1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		m_pDoc->m_pUI->m_origView->changeCursor(coord);
		break;
	default:
		return 0;
		break;

	}
	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);

	glReadPixels(0,
		m_nWindowHeight - m_nDrawHeight,
		m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pPaintBitstart);
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i(0, m_nWindowHeight - m_nDrawHeight);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);
	glDrawPixels(m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pPaintBitstart);

	//	glDrawBuffer(GL_FRONT);
}

void PaintView::PaintButtonPress()
{
	isAnEvent = 1;
	eventToDo = PAINT_BUTTON;
	redraw();
	
}
void PaintView::RunButtonPress()
{
	isAnEvent = 1;
	eventToDo = RUN_BUTTON;
	redraw();

}



void PaintView::PaintButtonPressed()
{
	redraw();
	if (m_pDoc->m_ucPainting)
	{
		int space = m_pDoc->m_pUI->getSpacing();
		if (space == 0) {
			std::cout << "paint erre";
		}
		int width = m_pDoc->m_nWidth;
		int height = m_pDoc->m_nHeight;
		int oriSize = (int)(m_pDoc->getSize());
		
		if (m_pDoc->m_pUI->getSizeRand() == true) {
			
			//use vector to store all points and then shuffle for random order
			//https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
			std::vector<Point> collection;
			for (int i = 0; i < width; i += space)
			{
				for (int j = 0; j < height; j += space)
				{
					int randx = rand() % space - space/2;
					int randy = rand() % space - space / 2;
					collection.push_back(Point(i+randx,j+randy));
				}
			}
			std::random_shuffle(collection.begin(),collection.end());
			int num = collection.size();
			for (int i = 0; i <num;i++)
			{
					m_pDoc->setSize((rand() % oriSize) + 1);
					m_pDoc->m_pCurrentBrush->BrushBegin(collection[i], collection[i]);
					m_pDoc->m_pCurrentBrush->BrushEnd(collection[i], collection[i]);
			}
			//
		}
		else {
			for (int i = 0; i < width; i += space)
			{
				for (int j = 0; j < height; j += space)
				{
					m_pDoc->m_pCurrentBrush->BrushBegin(Point(i, j), Point(i, j));
					m_pDoc->m_pCurrentBrush->BrushEnd(Point(i, j), Point(i, j));
				}
			}
		}
		if (m_pDoc->m_pUI->getEdgeClip() == true) {
			unsigned char* data = m_pDoc->m_ucInputEdge;
			if (data == NULL)
				data = m_pDoc->m_ucEdge;
			for (int i = 0; i < width; i += space)
			{
				for (int j = 0; j < height; j += space)
				{
					if (data[3 * (j*width + i)]) {
						m_pDoc->m_pCurrentBrush->BrushBegin(Point(i, j), Point(i, j));
						m_pDoc->m_pCurrentBrush->BrushEnd(Point(i, j), Point(i, j));
					}
				}
			}
		}
		m_pDoc->setSize(oriSize);
	}
	
}

void PaintView::generateBlur()
{
	int width = m_pDoc->m_nWidth;
	int height = m_pDoc->m_nHeight;
	int blur = (int) (m_pDoc->getPaintlyBlur() * 6);
//	if (m_pDoc->m_ucSmooth != NULL)
//		delete[] m_pDoc->m_ucSmooth;
//	m_pDoc->m_ucSmooth = new GLubyte[3 * width*height];
	//blur first with the blur size
	//blur = 3;
	double* Guassian = new double[blur*blur];
	double sigma = 1.0;
	double r, s = 2.0 * sigma * sigma;
	double sum = 0;
	for (int i = 0; i < blur; i++) {
		for (int j = 0; j < blur; j++) {
			double x = i - blur / 2;
			double y = j - blur / 2;
			r = sqrt(x * x + y * y);
			Guassian[j*blur + i] = (exp(-(r * r) / s)) / (M_PI * s);
			sum += Guassian[j*blur + i];
		}
	}
	for (int i = 0; i < blur; i++) {
		for (int j = 0; j < blur; j++) {
			Guassian[j*blur + i] /=	sum;
			//std::cout << Guassian[j*blur + i] << " ";
		}
		//std::cout << std::endl;
	}
	Filter<double> Gua = Filter<double>(Guassian, blur, blur);
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int position = j*m_pDoc->m_nPaintWidth + i;
			GLubyte* temp = m_pDoc->getChannelR();
			m_pDoc->m_ucSmooth[3 * position] = (GLubyte)Gua.conv2(temp, m_pDoc->m_nPaintWidth, m_pDoc->m_nPaintHeight, i, j);
			temp = m_pDoc->getChannelG();
			m_pDoc->m_ucSmooth[3 * position + 1] = (GLubyte)Gua.conv2(temp, m_pDoc->m_nPaintWidth, m_pDoc->m_nPaintHeight, i, j);
			temp = m_pDoc->getChannelB();
			m_pDoc->m_ucSmooth[3 * position + 2] = (GLubyte)Gua.conv2(temp, m_pDoc->m_nPaintWidth, m_pDoc->m_nPaintHeight, i, j);
		}
	}
	delete[] Guassian;
}

void PaintView::RunButtonPressed()
{
	//https://mrl.nyu.edu/publications/painterly98/hertzmann-siggraph98.pdf
	//redraw();
	if (m_pDoc->m_ucPainting)
	{
		delete[] m_pDoc->m_ucPainting;
		
		int width = m_pDoc->m_nPaintWidth;
		int height = m_pDoc->m_nPaintHeight;
		m_pDoc->m_ucPainting = new GLubyte[width*height * 3];
		for (int i = 0; i < width*height * 3; i++)
			m_pDoc->m_ucPainting[i] = 0;

		m_pDoc->m_pUI->m_paintView->refresh();
		//generate the blur image;
		generateBlur();
		int minS = m_pDoc->getPaintlyMinStr();
		int maxS = m_pDoc->getPaintlyMaxStr();
		//double pAlpha = m_pDoc->getPaintlyAlpha() ;
		
		int level = m_pDoc->getPaintlyLevel() ;
		double Jr = m_pDoc->getPaintlyJr() ;
		double Jg = m_pDoc->getPaintlyJg() ;
		double Jb = m_pDoc->getPaintlyJb() ;
		double Jh = m_pDoc->getPaintlyJh() ;
		double Js = m_pDoc->getPaintlyJs() ;
		double Jv = m_pDoc->getPaintlyJv() ;

		int layer = m_pDoc->getPaintlyLayers();
		int interval = (maxS - minS) / layer;
		interval = (interval > 0) ? interval : 1;
		
		//The basic approach is paint a rough sketch with a big brush, 
		//and then refine it with a smaller brush. 
		for (int i = maxS; i >= minS; i = i-interval) {
			paintLayer(m_pDoc->m_ucPainting, m_pDoc->m_ucSmooth, i);
		}

	}
}

void PaintView::paintLayer(GLubyte * canvas, GLubyte *reference, int brushSize)
{
	//std::cout << "layer" << std::endl;
	int width = m_pDoc->m_nWidth;
	int height = m_pDoc->m_nHeight;
	double gridFactor = m_pDoc->getPaintlyGridSize();
	int grid = int(gridFactor * brushSize/2);
	int thr = m_pDoc->getPaintlyThresh();
	double* di = new double[width*height];
	std::vector<Point> collection;
	difference(di, canvas, reference, width, height);

	for (int i = 0; i < width; i=i+grid) {
		for (int j = 0; j < height; j=j+ grid) {
			
			double error = 0;
			double localMax = -10;
			int localX = 0;
			int localY = 0;
			for (int x = -grid/2; x < grid/2 ; x++) {
				for (int y = -grid/2; y < grid/2 ; y++) {
					if (((y + j) >= height) || ((y + j) < 0) || ((x + i) >= width) || ((x + i) < 0))
						continue;
					error = error + di[(y + j)*width + (x + i)];
					if (localMax <di[(y + j)*width + (x + i)]) {
						localMax = di[(y + j)*width + (x + i)];
						localX = x+i;
						localY = y+j;
					}
				}
			}
			error = error;// (pow(grid, 2));

			if (error > thr) {
				collection.push_back(Point(localX, localY));
			}
		}
	}

	std::random_shuffle(collection.begin(), collection.end());
	int num = collection.size();
	//brushSize = (brushSize >= 1) ? brushSize : 1;
	int oriSize = (int)(m_pDoc->getSize());
	double oriAlpha = m_pDoc->getAlpha();
	m_pDoc->setSize(brushSize);
	m_pDoc->setAlpha(m_pDoc->getPaintlyAlpha());
	//std::cout << stroke <<" "<<num<< std::endl;
	for (int i = 0; i <num; i++)
	{
		if (m_pDoc->getPaintlyStroke()== STROKE_CURVE) {
			std::vector<Point> p;
			makeCurved(p,collection[i],brushSize/2);

			std::random_shuffle(p.begin(), p.end());
			//std::cout << "p size"<<p.size()<<std::endl;
			for (int k = 0; k < p.size(); k++) {
				m_pDoc->setBrushType(BRUSH_CIRCLES);
				m_pDoc->setSize(brushSize);
				m_pDoc->m_pCurrentBrush->BrushBegin(p[k], p[k]);
				m_pDoc->m_pCurrentBrush->BrushEnd(p[k], p[k]);
			}
			
		}
		else if (m_pDoc->getPaintlyStroke() == STROKE_CIRCLE) {
			m_pDoc->setBrushType(BRUSH_CIRCLES);
			m_pDoc->m_pCurrentBrush->BrushBegin(collection[i], collection[i]);
			m_pDoc->m_pCurrentBrush->BrushEnd(collection[i], collection[i]);
			//printf("circle");
		}
		else if (m_pDoc->getPaintlyStroke() == STROKE_BS) {
			std::vector<Point> p;
			makeCurved(p, collection[i], brushSize / 2);

			std::random_shuffle(p.begin(), p.end());
			//std::cout << "p size"<<p.size()<<std::endl;
			for (int k = 0; k < p.size(); k++) {
				m_pDoc->setBrushType(BRUSH_CIRCLES);
				GLubyte color[4];
				memcpy(color, m_pDoc->GetOriginalPixel(p[k]), 3);

				//printf("alpha%f", pDoc->getAlpha());
				color[0] = color[0] * (GLubyte)(m_pDoc->m_pUI->getColorSpaceR());
				color[1] = color[1] * (GLubyte)(m_pDoc->m_pUI->getColorSpaceG());
				color[2] = color[2] * (GLubyte)(m_pDoc->m_pUI->getColorSpaceB());
				color[3] = (GLubyte)(m_pDoc->getAlpha() * 255);
				glColor4ubv(color);
				m_pDoc->m_pCurrentBrush->BrushBegin(p[k], p[k]);
				m_pDoc->m_pCurrentBrush->BrushEnd(p[k], p[k]);
				
			}
		}

	}
	delete[] di;
	m_pDoc->setSize(oriSize);
	m_pDoc->setAlpha(oriAlpha);
	//printf("hi");
}

void PaintView::difference(double * di, GLubyte * canvas,GLubyte* refer,int width,int height)
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int position = j*width + i;
			di[position] = difference(canvas,refer,position);
		}
	}
}

double PaintView::difference(GLubyte * canvas, GLubyte * refer,int position)
{
	double res = pow(abs(canvas[3 * position + 0] - refer[3 * position + 0]), 2) +
		pow(abs(canvas[3 * position + 1] - refer[3 * position + 1]), 2) +
		pow(abs(canvas[3 * position + 2] - refer[3 * position + 2]), 2);

	res = sqrt(res);
	if (res > 255)
		res = 255;
	return res;
}

void PaintView::makeCurved(std::vector<Point>& p,Point& s,int brushSize)
{
	//std::cout << "curve" << std::endl;
	int x0 = s.x; int y0 = s.y;
	int pos = x0 + y0*m_pDoc->m_nWidth;
	//GLubyte color[3] = { m_pDoc->m_ucSmooth[3*pos],		m_pDoc->m_ucSmooth[3*pos+1],		m_pDoc->m_ucSmooth[3*pos+2] };
	p.push_back(Point(x0, y0));
	int lastX = 0; int lastY = 0;
	for (int i = 1; i <= m_pDoc->getPaintlyMaxStr(); i++) {
		if (i > m_pDoc->getPaintlyMinStr()) {
			int DiPaint = m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3] - m_pDoc->m_ucPainting[(y0*m_pDoc->m_nWidth + x0) * 3]
				+ m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3 + 1] - m_pDoc->m_ucPainting[(y0*m_pDoc->m_nWidth + x0) * 3 + 1]
				+ m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3 + 2] - m_pDoc->m_ucPainting[(y0*m_pDoc->m_nWidth + x0) * 3 + 2];
			int  DiStroke = m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3] - m_pDoc->m_ucSmooth[3 * pos]
				+ m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3 + 1] - m_pDoc->m_ucSmooth[3 * pos+1]
				+ m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3 + 2] - m_pDoc->m_ucSmooth[3 * pos+2];
			DiStroke = abs(DiStroke);
			DiPaint = abs(DiPaint);
			int DiPaint1 = pow(m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3] - m_pDoc->m_ucPainting[(y0*m_pDoc->m_nWidth + x0) * 3],2)
					+ pow(m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3 + 1] - m_pDoc->m_ucPainting[(y0*m_pDoc->m_nWidth + x0) * 3 + 1],2)
					+ pow(m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3 + 2] - m_pDoc->m_ucPainting[(y0*m_pDoc->m_nWidth + x0) * 3 + 2],2);
				int DiStroke1 = pow(m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3] - m_pDoc->m_ucSmooth[3 * pos],2)
					+ pow(m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3 + 1] - m_pDoc->m_ucSmooth[3 * pos+1],2)
					+ pow(m_pDoc->m_ucSmooth[(y0*m_pDoc->m_nWidth + x0) * 3 + 2] - m_pDoc->m_ucSmooth[3 * pos+2],2);
					
			if (DiPaint1<DiStroke1)
				return;
		}
		
		
		// get unit vector of gradient and then compute a normal direction
		int dy = m_pDoc->m_Gx[x0+y0*m_pDoc->m_nWidth];
		int dx = - m_pDoc->m_Gy[x0 + y0*m_pDoc->m_nWidth];
		if (dx == 0 && dy == 0)
			return;
		// reverse if necessary
		if (lastX*dx + lastY*dy < 0) {
			dx = -dx;
			dy = -dy;
		}
		
		//filter the stroke direction
		double fc = m_pDoc->getPaintlyCur();
		double tdx = fc * dx + (1 - fc) * lastX;
		double tdy = fc * dy + (1 - fc) * lastY;
		
		double X= (double)(tdx) / (sqrt((double)(tdx*tdx + tdy*tdy)));
		double Y= (double)(tdy) / (sqrt((double)(tdx*tdx + tdy*tdy)));
		x0 = x0+(brushSize * X);
		y0 = y0+(brushSize * Y);
		lastX = (int)tdx; lastY = (int)tdy;
		if (x0 < 0 || y0 < 0 || x0>=m_pDoc->m_nPaintWidth||y0>=m_pDoc->m_nPaintHeight)
			return;
		p.push_back(Point(x0, y0));
	}
}



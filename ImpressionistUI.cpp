//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the
project.  You can copy and paste these into your code and then change them to
make them look how you want.  Descriptions for all of the widgets here can be found
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------

//----To install a window--------------------------
Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
myWindow->user_data((void*)(this));	// record self to be used by static callback functions

// install menu bar
myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
{ "&File",		0, 0, 0, FL_SUBMENU },
{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
{ 0 },
{ "&Edit",		0, 0, 0, FL_SUBMENU },
{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
{ 0 },
{ "&Help",		0, 0, 0, FL_SUBMENU },
{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
{ 0 },
{ 0 }
};
myMenubar->menu(myMenuItems);
m_mainWindow->end();

//----The window callback--------------------------
// One of the callbacks
void ImpressionistUI::cb_load(Fl_Menu_* o, void* v)
{
ImpressionistDoc *pDoc=whoami(o)->getDocument();

char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
if (newfile != NULL) {
pDoc->loadImage(newfile);
}
}


//------------Slider---------------------------------------

//----To install a slider--------------------------
Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
mySlider->user_data((void*)(this));	// record self to be used by static callback functions
mySlider->type(FL_HOR_NICE_SLIDER);
mySlider->labelfont(FL_COURIER);
mySlider->labelsize(12);
mySlider->minimum(1);
mySlider->maximum(40);
mySlider->step(1);
mySlider->value(m_nMyValue);
mySlider->align(FL_ALIGN_RIGHT);
mySlider->callback(cb_MyValueSlides);

//----The slider callback--------------------------
void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
{
((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
}


//------------Choice---------------------------------------

//----To install a choice--------------------------
Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
{"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
{"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
{"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
{0}
};
myChoice->menu(myChoiceMenu);
myChoice->callback(cb_myChoice);

//-----The choice callback-------------------------
void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
{
ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
ImpressionistDoc* pDoc=pUI->getDocument();

int type=(int)v;

pDoc->setMyType(type);
}


//------------Button---------------------------------------

//---To install a button---------------------------
Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
myButton->user_data((void*)(this));   // record self to be used by static callback functions
myButton->callback(cb_myButton);

//---The button callback---------------------------
void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
{
ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
ImpressionistDoc* pDoc = pUI->getDocument();
pDoc->startPainting();
}


//---------Light Button------------------------------------

//---To install a light button---------------------
Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
myLightButton->callback(cb_myLightButton);

//---The light button callback---------------------
void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
{
ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

if (pUI->myBool==TRUE) pUI->myBool=FALSE;
else pUI->myBool=TRUE;
}

//----------Int Input--------------------------------------

//---To install an int input-----------------------
Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
myInput->user_data((void*)(this));   // record self to be used by static callback functions
myInput->callback(cb_myInput);

//---The int input callback------------------------
void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
{
((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)
{
	return ((ImpressionistUI*)(o->parent()->user_data()));
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}

void ImpressionistUI::cb_load_edge_image(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Edge File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadEdgeImage(newfile);
	}
}

void ImpressionistUI::cb_load_video(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadVideo(newfile);
	}
}

void ImpressionistUI::cb_load_alpha(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("alpha File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAlpha(newfile);
	}
}

void ImpressionistUI::cb_dissolve_image(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Dissolve another File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->dissolveImage(newfile);

	}
}

void ImpressionistUI::cb_load_ori_image(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	if (pDoc == NULL)
		return;
	pDoc->m_pUI->m_origView->OriViewType = IMAGE_ORIGINAL;
	
}

void ImpressionistUI::cb_load_ano_image(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("another File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAnotherImage(newfile);

	}
}

void ImpressionistUI::cb_load_mural_image(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("mural File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->muralImage(newfile);

	}
}

void ImpressionistUI::cb_faster(Fl_Menu_ * o, void * v)
{
}

void ImpressionistUI::cb_safer(Fl_Menu_ * o, void * v)
{
}
void ImpressionistUI::cb_undo(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	pDoc->undo();
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp");
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v)
{
	whoami(o)->m_brushDialog->show();
}
void ImpressionistUI::cb_paintly(Fl_Menu_ * o, void * v)
{
	whoami(o)->m_PainlyDialog->show();
}
void ImpressionistUI::cb_filter(Fl_Menu_* o, void* v)
{
	whoami(o)->m_filterDialog->show();
}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v)
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();
	whoami(o)->m_filterDialog->hide();
}



//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v)
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	int type = (int)v;
	pDoc->setBrushType(type);
}

void ImpressionistUI::cb_colorChange(Fl_Widget * o, void * v)
{
	int confirm = fl_color_chooser("Color",m_dR,m_dG,m_dB);
	//https://www.fltk.org/doc-1.3/group__group__comdlg.html#ga6241252ca65bc163d046b4f900a5ebad
}

void ImpressionistUI::cb_directionChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	pDoc->setDirection((int)v);
}

void ImpressionistUI::cb_paintly_styleChoice(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	pDoc->setPaintlyStyle((int)v);
}

void ImpressionistUI::cb_paintly_strokeChoice(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	pDoc->setPaintlyStroke((int)v);
}

void ImpressionistUI::cb_paint_button(Fl_Widget * o, void * v)
{
	
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	pUI->m_paintView->PaintButtonPress();
}



//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize = int(((Fl_Slider *)o)->value());
}
void ImpressionistUI::cb_LineAngleSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle = (int(((Fl_Slider *)o)->value()));
}

void ImpressionistUI::cb_LineWidthSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth = (int(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_another_gradient_button(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	if (pDoc->m_ucAnother != NULL) {
		if (pUI->m_banotherGrad == true) {
			pUI->m_AnotherGradientButton->value(0);
		}
		else {
			pUI->m_AnotherGradientButton->value(1);
		}
		pUI->m_banotherGrad = !(pUI->m_banotherGrad);
	}
	else
		pUI->m_AnotherGradientButton->value(0);

}
void ImpressionistUI::cb_edge_clip_button(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	if (pDoc->m_ucEdge != NULL) {
		if (pUI->m_bedgeClip == true) {
			pUI->m_EdgeClippingButton->value(0);
		}
		else {
			pUI->m_EdgeClippingButton->value(1);
		}
		pUI->m_bedgeClip = !(pUI->m_bedgeClip);
	}
	else
		pUI->m_EdgeClippingButton->value(0);

}
void ImpressionistUI::cb_filter_normal_button(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	if (pDoc->m_filter != NULL) {
		if (pUI->m_bfilterNormal == true) {
			pUI->m_filterNormalizeButton->value(0);
		}
		else {
			pUI->m_filterNormalizeButton->value(1);
		}
		pUI->m_bfilterNormal = !(pUI->m_bfilterNormal);
	}
	else
		pUI->m_filterNormalizeButton->value(0);

}


void ImpressionistUI::cb_apply_button(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)o->user_data();
	pUI->m_pDoc->applyFilter();
}

void ImpressionistUI::cb_fill_button(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)o->user_data();
	pUI->fillFilter(pUI);
	pUI->m_filterDialog->show();
}

// for paint control sliders
void ImpressionistUI::cb_paint_thre_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Threshold = (int(((Fl_Slider *)o)->value()));
}

void ImpressionistUI::cb_paint_cur_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Curvature = (double(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_paint_blur_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Blur = (double(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_paint_gridSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_GridSize = (double(((Fl_Slider *)o)->value()));
}

void ImpressionistUI::cb_paint_min_strokeSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_min_stroke = (int(((Fl_Slider *)o)->value()));
}

void ImpressionistUI::cb_paint_max_strokeSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_max_stroke = (int(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_paint_alphaSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_alpha = (double(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_paint_layerSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_layer = (int(((Fl_Slider *)o)->value()));
}

void ImpressionistUI::cb_paint_levelSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_R0_level = (int(((Fl_Slider *)o)->value()));
}

void ImpressionistUI::cb_Jr_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Jr = (double(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_Jg_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Jg = (double(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_Jb_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Jb = (double(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_Jh_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Jh = (double(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_Js_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Js = (double(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_Jv_Slides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_paintly_Jv = (double(((Fl_Slider *)o)->value()));
}

void ImpressionistUI::fillFilter(ImpressionistUI* pUI)
{
	int width = atoi(pUI->m_nfilterWidthInput->value());
	int height = atoi(pUI->m_nfilterHeightInput->value());
	if (width <= 0 || height <= 0)
		return;
	if (width ==1  && height ==1)
		return;
	//we think 1*`1 filter is meaningless
	double* filter = pUI->m_pDoc->m_filter;
	if (filter != NULL) {
		if (pUI->m_pDoc->getFilterWidth() == 1 && pUI->m_pDoc->getFilterHeight() == 1) {
			delete filter;		
		}
		else {
			delete[] filter;
		}
		pUI->m_pDoc->m_filter = NULL;
	}
	pUI->m_pDoc->m_filter = new double[width*height];
	Fl_Window*	m_filterInputDialog = new Fl_Window(width * 50, height * 40, "Filter Input");
	m_filterInputDialog->user_data((void*)(this));
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			Fl_Float_Input *input = new Fl_Float_Input((i + 1) * 12 + i * 30, (j + 1) * 12 + j * 20, 30, 20, "");
			input->value("1.0");
			int index = j*width + i;
			pUI->m_pDoc->m_filter[index] = atof(input->value());
		}
	}
	m_filterInputDialog->end();

	m_filterInputDialog->show();
	pUI->m_pDoc->setFilterWidth(width);
	pUI->m_pDoc->setFilterHeigth(height);
}

void ImpressionistUI::cb_threshSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_nThresh = (int(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_alphaSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_alpha = (float(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_SizeRandButton(Fl_Widget * o, void * v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	if (pUI->m_bSizeRand == true) {
		pUI->m_SizeRandButton->value(0);
		pUI->m_bSizeRand = false;
	}
	else {
		pUI->m_SizeRandButton->value(1);
		pUI->m_bSizeRand = true;
	}

}
void ImpressionistUI::cb_spaceSlides(Fl_Widget * o, void * v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSpace = (int(((Fl_Slider *)o)->value()));
}
void ImpressionistUI::cb_swap_image(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->swapImage();

}

void ImpressionistUI::cb_show_edge_image(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->doItButton(IMAGE_EDGE);
	pDoc->m_pUI->m_origView->refresh();

}
void ImpressionistUI::cb_show_ano_image(Fl_Menu_ * o, void * v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->showAnother(IMAGE_ANO);
	pDoc->m_pUI->m_origView->refresh();
}
void ImpressionistUI::cb_show_ori_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->showOri(IMAGE_ORIGINAL);
	pDoc->m_pUI->m_origView->refresh();
}

void ImpressionistUI::cb_do_it_button(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());
	ImpressionistDoc * pDoc = pUI->getDocument();
	pDoc->doItButton(IMAGE_EDGE);
	pDoc->m_pUI->m_origView->refresh();
}
void ImpressionistUI::cb_run_button(Fl_Widget * o, void * v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc * pDoc = pUI->getDocument();
	pDoc->clearCanvas();
	pUI->m_paintView->RunButtonPress();
}
//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w, h);
	m_origView->size(w, h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	int size = m_nSize;
	return size;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize(int size)
{
	m_nSize = size;

	if (size <= 40)
		m_BrushSizeSlider->value(m_nSize);
}

int ImpressionistUI::getLineAngle() const
{
	return m_nLineAngle;

}

void ImpressionistUI::setLineAngle(int angle)
{
	m_nLineAngle = angle;
	if (angle <= 359)
		m_BrushLineAngleSlider->value(m_nLineAngle);
}

int ImpressionistUI::getPaintlyStyle() const
{
	return m_paintly_style;
}

int ImpressionistUI::getPaintlyStroke() const
{
	return m_paintly_stroke;
}

int ImpressionistUI::getPaintlyThresh() const
{
	return m_paintly_Threshold;
}

double ImpressionistUI::getPaintlyCur() const
{
	return m_paintly_Curvature;
}

double ImpressionistUI::getPaintlyBlur() const
{
	return m_paintly_Blur;
}

double ImpressionistUI::getPaintlyGridSize() const
{
	return m_paintly_GridSize;
}

int ImpressionistUI::getPaintlyMinStr() const
{
	return m_paintly_min_stroke;
}

int ImpressionistUI::getPaintlyMaxStr() const
{
	return m_paintly_max_stroke;
}

double ImpressionistUI::getPaintlyAlpha() const
{
	return m_paintly_alpha;
}

int ImpressionistUI::getPaintlyLayers() const
{
	return m_paintly_layer;
}

int ImpressionistUI::getPaintlyLevel() const
{
	return m_paintly_R0_level;
}

double ImpressionistUI::getPaintlyJr() const
{
	return m_paintly_Jr;
}

double ImpressionistUI::getPaintlyJg() const
{
	return m_paintly_Jg;
}

double ImpressionistUI::getPaintlyJb() const
{
	return m_paintly_Jb;
}

double ImpressionistUI::getPaintlyJh() const
{
	return m_paintly_Jh;
}

double ImpressionistUI::getPaintlyJs() const
{
	return m_paintly_Js;
}

double ImpressionistUI::getPaintlyJv() const
{
	return m_paintly_Jv;
}

int ImpressionistUI::getLineWidth() const
{
	return m_nLineWidth;
}

void ImpressionistUI::setLineWidth(int width)
{
	m_nLineWidth = width;
	if (width <= 40)
		m_BrushLineWidthSlider->value(m_nLineWidth);
}

bool ImpressionistUI::getAnotherGradient()
{
	return m_banotherGrad;
}

int ImpressionistUI::getThresh() const
{
	return m_nThresh;
}

double ImpressionistUI::getAlpha() const
{
	return m_alpha;
}

void ImpressionistUI::setAlpha(double new_alpha)
{
	m_alpha = new_alpha;
	if (m_alpha <= 1)
		m_BrushAlphaSlider->value(m_alpha);
}

int ImpressionistUI::getDitectionType()
{
	return m_nDirectionType;
}

void ImpressionistUI::setDirectionType(int type)
{
	m_nDirectionType = type;
}

bool ImpressionistUI::getSizeRand() const
{
	return m_bSizeRand;
}

int ImpressionistUI::getSpacing() const
{
	return this->m_nSpace;
}

bool ImpressionistUI::getEdgeClip() const
{
	return this->m_bedgeClip;
}
bool ImpressionistUI::getFilterNormal() const
{
	return this->m_bfilterNormal;
}



double ImpressionistUI::getColorSpaceR() const
{
	return m_dR;
}
double ImpressionistUI::getColorSpaceG() const
{
	return m_dG;
}
double ImpressionistUI::getColorSpaceB() const
{
	return m_dB;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
	{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
	{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
	{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes },
	{ "&Paintly...",	FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_paintly },
	{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },

	{ "&Colors...",	FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_colorChange },
	{ "&filter...", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_filter },
	{ "&Paintly...", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_brushes, 0, FL_MENU_DIVIDER },

	{ "Load Edge Image...",	FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_load_edge_image },
	{ "Load Video...",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_load_video },
	{ "Load Another Image...", FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_ano_image,},
	{ "Mural Image...", FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_load_mural_image, },
	{ "Load alpha Image...", FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_load_alpha, },
	{ "dissolve Another Image...", FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_dissolve_image, 0, FL_MENU_DIVIDER },


	{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
	{ 0 },

	{ "&Display",		0, 0, 0, FL_SUBMENU },
	{ "&Original Image",	FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_show_ori_image },
	{ "&Edge Image",	FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_show_edge_image },
	{ "&Another Image",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_show_ano_image },
	{ "&Swap views", FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_swap_image },
	{ 0 },
	{ "&Options",		0, 0, 0, FL_SUBMENU },
	{ "&Faster",FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_faster },
	{ "&Safer",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_safer },
	{ "&Undo",	FL_ALT + 'u', (Fl_Callback *)ImpressionistUI::cb_undo },
	{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
	{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
	{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE + 1] = {
	{ "Points",			FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS },
	{ "Lines",				FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES },
	{ "Circles",			FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES },
	{ "Scattered Points",	FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS },
	{ "Scattered Lines",	FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES },
	{ "Scattered Circles",	FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES },
	{ "Blur",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_BLUR },
	{ "Sharp",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SHARP },
	{ "Wave",	FL_ALT + 't', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_WAVE },
	{ "Luminance",	FL_ALT + 't', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LUMI },
	{ "AlphaMap",	FL_ALT + 't', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_ALPHA },
	{ 0 }
};

// stroke direction choice menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionTypeMenu[NUM_DIR_TYPE + 1] = {
	{ "Slider/Right Mouse",			FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_SLIDER, },
	{ "Gradient",				FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_GRADIENT },
	{ "Brush Direction",			FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_BRUSH_DIRECTION },
	{ 0 }
};

Fl_Menu_Item ImpressionistUI::styleTypeMenu[NUM_STYLE_TYPE + 1] = {
	{ "Impressionist",			FL_ALT + 'i', (Fl_Callback *)ImpressionistUI::cb_paintly_styleChoice, (void *)STYLE_IM, },
	{ "Expressionist",				FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_paintly_styleChoice, (void *)STYLE_EX },
	{ "Color wash",			FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_paintly_styleChoice, (void *)STYLE_CO },
	{ "Pointillist",			FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_paintly_styleChoice, (void *)STYLE_PO, },
	{ "Cumstomize",				FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_paintly_styleChoice, (void *)STYLE_CU },
	{ 0 }
};

Fl_Menu_Item ImpressionistUI::strokeTypeMenu[NUM_STROKE_TYPE + 1] = {
	{ "Curve Brush",			FL_ALT + 'r', (Fl_Callback *)ImpressionistUI::cb_paintly_strokeChoice, (void *)STROKE_CURVE, },
	{ "BSpline Brush",				FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_paintly_strokeChoice, (void *)STROKE_BS },
	{ "Circle Brush",			FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_paintly_strokeChoice, (void *)STROKE_CIRCLE },
	{ "Clip Line Brush",			FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_paintly_strokeChoice, (void *)STROKE_CLIP, },
	{ "Line Brush",				FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_paintly_strokeChoice, (void *)STROKE_LINE },
	{ 0 }
};

double ImpressionistUI::m_dR = 1.0;
double ImpressionistUI::m_dG = 1.0;
double ImpressionistUI::m_dB = 1.0;
//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
	m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
											// install menu bar
	m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
	m_menubar->menu(menuitems);

	// Create a group that will hold two sub windows inside the main
	// window
	Fl_Group* group = new Fl_Group(0, 25, 600, 275);

	// install paint view window
	m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
	m_paintView->box(FL_DOWN_FRAME);

	// install original view window
	m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
	m_origView->box(FL_DOWN_FRAME);
	m_origView->deactivate();

	group->end();
	Fl_Group::current()->resizable(group);
	m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_banotherGrad = false;
	m_bedgeClip = false;
	m_nThresh = 200;
	m_nDirectionType = 0;
	m_alpha = 1.0;
	m_bSizeRand = true;
	m_nSpace = 4;
	m_bfilterNormal = false;
	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
	// Add a brush type choice to the dialog
	m_BrushTypeChoice = new Fl_Choice(50, 10, 150, 25, "&Brush");
	m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushTypeChoice->menu(brushTypeMenu);
	m_BrushTypeChoice->callback(cb_brushChoice);

	m_ClearCanvasButton = new Fl_Button(240, 10, 150, 25, "&Clear Canvas");
	m_ClearCanvasButton->user_data((void*)(this));
	m_ClearCanvasButton->callback(cb_clear_canvas_button);

	m_DirectionTypeChoice = new Fl_Choice(120, 45, 150, 25, "&Stroke Direction");
	m_DirectionTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
	m_DirectionTypeChoice->menu(strokeDirectionTypeMenu);
	m_DirectionTypeChoice->callback(cb_directionChoice);
	m_DirectionTypeChoice->deactivate();


	// Add brush size slider to the dialog 
	m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
	m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushSizeSlider->labelfont(FL_COURIER);
	m_BrushSizeSlider->labelsize(12);
	m_BrushSizeSlider->minimum(1);
	m_BrushSizeSlider->maximum(40);
	m_BrushSizeSlider->step(1);
	m_BrushSizeSlider->value(m_nSize);
	m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
	m_BrushSizeSlider->callback(cb_sizeSlides);

	m_BrushLineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
	m_BrushLineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushLineWidthSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushLineWidthSlider->labelfont(FL_COURIER);
	m_BrushLineWidthSlider->labelsize(12);
	m_BrushLineWidthSlider->minimum(1);
	m_BrushLineWidthSlider->maximum(40);
	m_BrushLineWidthSlider->step(1);
	m_BrushLineWidthSlider->value(m_nLineWidth);
	m_BrushLineWidthSlider->align(FL_ALIGN_RIGHT);
	m_BrushLineWidthSlider->callback(cb_LineWidthSlides);
	m_BrushLineWidthSlider->deactivate();

	m_BrushLineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
	m_BrushLineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushLineAngleSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushLineAngleSlider->labelfont(FL_COURIER);
	m_BrushLineAngleSlider->labelsize(12);
	m_BrushLineAngleSlider->minimum(0);
	m_BrushLineAngleSlider->maximum(359);
	m_BrushLineAngleSlider->step(1);
	m_BrushLineAngleSlider->value(m_nLineAngle);
	m_BrushLineAngleSlider->align(FL_ALIGN_RIGHT);
	m_BrushLineAngleSlider->callback(cb_LineAngleSlides);
	m_BrushLineAngleSlider->deactivate();

	m_BrushAlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
	m_BrushAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushAlphaSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushAlphaSlider->labelfont(FL_COURIER);
	m_BrushAlphaSlider->labelsize(12);
	m_BrushAlphaSlider->minimum(0.00);
	m_BrushAlphaSlider->maximum(1.00);
	m_BrushAlphaSlider->step(0.01);
	m_BrushAlphaSlider->value(m_alpha);
	m_BrushAlphaSlider->align(FL_ALIGN_RIGHT);
	m_BrushAlphaSlider->callback(cb_alphaSlides);

	m_EdgeClippingButton = new Fl_Light_Button(50, 200, 150, 25, "&Edge Clipping");
	m_EdgeClippingButton->user_data((void*)(this));
	m_EdgeClippingButton->callback(cb_edge_clip_button);

	m_AnotherGradientButton = new Fl_Light_Button(240, 200, 150, 25, "&Another Gradient");
	m_AnotherGradientButton->user_data((void*)(this));
	m_AnotherGradientButton->callback(cb_another_gradient_button);
	m_AnotherGradientButton->deactivate();

	m_BrushSpacingSlider = new Fl_Value_Slider(10, 250, 150, 20, "Spacing");
	m_BrushSpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushSpacingSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushSpacingSlider->labelfont(FL_COURIER);
	m_BrushSpacingSlider->labelsize(12);
	m_BrushSpacingSlider->minimum(1);
	m_BrushSpacingSlider->maximum(16);
	m_BrushSpacingSlider->step(1);
	m_BrushSpacingSlider->value(m_nSpace);
	m_BrushSpacingSlider->align(FL_ALIGN_RIGHT);
	m_BrushSpacingSlider->callback(cb_spaceSlides);

	m_SizeRandButton = new Fl_Light_Button(230, 250, 100, 25, "&Size Rand");
	m_SizeRandButton->user_data((void*)(this));
	m_SizeRandButton->callback(cb_SizeRandButton);

	m_PaintButton = new Fl_Button(330, 250, 50, 25, "&Paint");
	m_PaintButton->user_data((void*)(this));
	m_PaintButton->callback(cb_paint_button);

	m_EdgeThreshSlider = new Fl_Value_Slider(10, 300, 180, 20, "Edge Threshold");
	m_EdgeThreshSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_EdgeThreshSlider->type(FL_HOR_NICE_SLIDER);
	m_EdgeThreshSlider->labelfont(FL_COURIER);
	m_EdgeThreshSlider->labelsize(12);
	m_EdgeThreshSlider->minimum(0);
	m_EdgeThreshSlider->maximum(500);
	m_EdgeThreshSlider->step(3);
	m_EdgeThreshSlider->value(m_nThresh);
	m_EdgeThreshSlider->align(FL_ALIGN_RIGHT);
	m_EdgeThreshSlider->callback(cb_threshSlides);

	m_DoItButton = new Fl_Button(330, 300, 50, 25, "&Do it");
	m_DoItButton->user_data((void*)(this));
	m_DoItButton->callback(cb_do_it_button);
	m_brushDialog->end();


	m_filterDialog = new Fl_Window(400, 325, "Filter Dialog");
	m_nfilterWidthInput = new Fl_Int_Input(10, 80, 300, 20, "filter width");
	m_nfilterWidthInput->labelfont(FL_COURIER);
	m_nfilterWidthInput->labelsize(12);
	m_nfilterWidthInput->value("1");

	m_nfilterHeightInput = new Fl_Int_Input(10, 110, 300, 20, "filter height");
	m_nfilterHeightInput->labelfont(FL_COURIER);
	m_nfilterHeightInput->labelsize(12);
	m_nfilterHeightInput->value("1");

	m_filterNormalizeButton = new Fl_Light_Button(240, 200, 150, 25, "&Normalized");
	m_filterNormalizeButton->user_data((void*)(this));
	m_filterNormalizeButton->callback(cb_filter_normal_button);

	m_fillButton = new Fl_Button(330, 250, 50, 25, "&Fill filter");
	m_fillButton->user_data((void*)(this));
	m_fillButton->callback(cb_fill_button);

	m_ApplyButton = new Fl_Button(330, 300, 50, 25, "&Apply filter");
	m_ApplyButton->user_data((void*)(this));
	m_ApplyButton->callback(cb_apply_button);
	m_filterDialog->end();


	//for paintly
	
	
	m_paintly_Threshold=100;
	m_paintly_Curvature=1.0;
	m_paintly_Blur=0.5;
	m_paintly_GridSize=1.0;
	m_paintly_min_stroke=4;
	m_paintly_max_stroke=16;
	m_paintly_alpha=1.0;
	m_paintly_layer=3;
	m_paintly_R0_level=3;
	m_paintly_Jr=0;
	m_paintly_Jg=0;
	m_paintly_Jb=0;
	m_paintly_Jh=0;
	m_paintly_Js=0;
	m_paintly_Jv=0;
	m_PainlyDialog = new Fl_Window(500, 500, "Painly Dialog");

	m_StyleTypeChoice = new Fl_Choice(50, 10, 150, 25, "&Style");
	m_StyleTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
	m_StyleTypeChoice->menu(styleTypeMenu);
	m_StyleTypeChoice->callback(cb_paintly_styleChoice);
	m_StyleTypeChoice->value(0);

	m_RunButton = new Fl_Button(240, 10, 150, 25, "&Run");
	m_RunButton->user_data((void*)(this));
	m_RunButton->callback(cb_run_button);

	m_StrokeTypeChoice = new Fl_Choice(120, 45, 150, 25, "&Stroke");
	m_StrokeTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
	m_StrokeTypeChoice->menu(strokeTypeMenu);
	m_StrokeTypeChoice->callback(cb_paintly_strokeChoice);
	m_StrokeTypeChoice->deactivate();
	this->setPaintlyStyle(0);
	this->setPaintlyStroke(0);

	m_paintly_ThresholdSlider = new Fl_Value_Slider(10, 80, 300, 20, "Threshold");
	m_paintly_ThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintly_ThresholdSlider->type(FL_HOR_NICE_SLIDER);
	m_paintly_ThresholdSlider->labelfont(FL_COURIER);
	m_paintly_ThresholdSlider->labelsize(12);
	m_paintly_ThresholdSlider->minimum(0);
	m_paintly_ThresholdSlider->maximum(250);
	m_paintly_ThresholdSlider->step(1);
	m_paintly_ThresholdSlider->value(m_paintly_Threshold);
	m_paintly_ThresholdSlider->align(FL_ALIGN_RIGHT);
	m_paintly_ThresholdSlider->callback(cb_paint_thre_Slides);
	m_paintly_ThresholdSlider->deactivate();

	m_paintly_CurvatureSlider = new Fl_Value_Slider(10, 110, 300, 20, "Curvature");
	m_paintly_CurvatureSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintly_CurvatureSlider->type(FL_HOR_NICE_SLIDER);
	m_paintly_CurvatureSlider->labelfont(FL_COURIER);
	m_paintly_CurvatureSlider->labelsize(12);
	m_paintly_CurvatureSlider->minimum(0);
	m_paintly_CurvatureSlider->maximum(1.0);
	m_paintly_CurvatureSlider->step(0.01);
	m_paintly_CurvatureSlider->value(m_paintly_Curvature);
	m_paintly_CurvatureSlider->align(FL_ALIGN_RIGHT);
	m_paintly_CurvatureSlider->callback(cb_paint_cur_Slides);
	m_paintly_CurvatureSlider->deactivate();

	m_paintly_BlurSlider = new Fl_Value_Slider(10, 140, 300, 20, "Blur");
	m_paintly_BlurSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintly_BlurSlider->type(FL_HOR_NICE_SLIDER);
	m_paintly_BlurSlider->labelfont(FL_COURIER);
	m_paintly_BlurSlider->labelsize(12);
	m_paintly_BlurSlider->minimum(0);
	m_paintly_BlurSlider->maximum(1);
	m_paintly_BlurSlider->step(0.01);
	m_paintly_BlurSlider->value(m_paintly_Blur);
	m_paintly_BlurSlider->align(FL_ALIGN_RIGHT);
	m_paintly_BlurSlider->callback(cb_paint_blur_Slides);
	m_paintly_BlurSlider->deactivate();

	m_paintly_GridSizeSlider = new Fl_Value_Slider(10, 170, 300, 20, "Grid Size");
	m_paintly_GridSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintly_GridSizeSlider->type(FL_HOR_NICE_SLIDER);
	m_paintly_GridSizeSlider->labelfont(FL_COURIER);
	m_paintly_GridSizeSlider->labelsize(12);
	m_paintly_GridSizeSlider->minimum(0.00);
	m_paintly_GridSizeSlider->maximum(1.00);
	m_paintly_GridSizeSlider->step(0.01);
	m_paintly_GridSizeSlider->value(m_paintly_GridSize);
	m_paintly_GridSizeSlider->align(FL_ALIGN_RIGHT);
	m_paintly_GridSizeSlider->callback(cb_paint_gridSlides);
	m_paintly_GridSizeSlider->deactivate();

	m_paintlyMinSlider = new Fl_Value_Slider(10, 200, 300, 20, "MinStroke");
	m_paintlyMinSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyMinSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyMinSlider->labelfont(FL_COURIER);
	m_paintlyMinSlider->labelsize(12);
	m_paintlyMinSlider->minimum(0);
	m_paintlyMinSlider->maximum(30);
	m_paintlyMinSlider->step(1);
	m_paintlyMinSlider->value(m_paintly_min_stroke);
	m_paintlyMinSlider->align(FL_ALIGN_RIGHT);
	m_paintlyMinSlider->callback(cb_paint_min_strokeSlides);
	m_paintlyMinSlider->deactivate();

	m_paintlyMaxSlider = new Fl_Value_Slider(10, 230, 300, 20, "MaxStroke");
	m_paintlyMaxSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyMaxSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyMaxSlider->labelfont(FL_COURIER);
	m_paintlyMaxSlider->labelsize(12);
	m_paintlyMaxSlider->minimum(0);
	m_paintlyMaxSlider->maximum(30);
	m_paintlyMaxSlider->step(1);
	m_paintlyMaxSlider->value(m_paintly_max_stroke);
	m_paintlyMaxSlider->align(FL_ALIGN_RIGHT);
	m_paintlyMaxSlider->callback(cb_paint_max_strokeSlides);
	m_paintlyMaxSlider->deactivate();

	m_paintlyAlphaSlider = new Fl_Value_Slider(10, 260, 300, 20, "Alpha");
	m_paintlyAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyAlphaSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyAlphaSlider->labelfont(FL_COURIER);
	m_paintlyAlphaSlider->labelsize(12);
	m_paintlyAlphaSlider->minimum(0);
	m_paintlyAlphaSlider->maximum(1.00);
	m_paintlyAlphaSlider->step(0.01);
	m_paintlyAlphaSlider->value(m_paintly_alpha);
	m_paintlyAlphaSlider->align(FL_ALIGN_RIGHT);
	m_paintlyAlphaSlider->callback(cb_paint_alphaSlides);
	m_paintlyAlphaSlider->deactivate();

	m_paintlyLayersSlider = new Fl_Value_Slider(10, 290, 300, 20, "Layers");
	m_paintlyLayersSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyLayersSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyLayersSlider->labelfont(FL_COURIER);
	m_paintlyLayersSlider->labelsize(12);
	m_paintlyLayersSlider->minimum(1);
	m_paintlyLayersSlider->maximum(5);
	m_paintlyLayersSlider->step(1);
	m_paintlyLayersSlider->value(m_paintly_layer);
	m_paintlyLayersSlider->align(FL_ALIGN_RIGHT);
	m_paintlyLayersSlider->callback(cb_paint_layerSlides);
	m_paintlyLayersSlider->deactivate();

	m_paintlyLevelSlider = new Fl_Value_Slider(10, 320, 300, 20, "R0 level");
	m_paintlyLevelSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyLevelSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyLevelSlider->labelfont(FL_COURIER);
	m_paintlyLevelSlider->labelsize(12);
	m_paintlyLevelSlider->minimum(0);
	m_paintlyLevelSlider->maximum(5);
	m_paintlyLevelSlider->step(1);
	m_paintlyLevelSlider->value(m_paintly_R0_level);
	m_paintlyLevelSlider->align(FL_ALIGN_RIGHT);
	m_paintlyLevelSlider->callback(cb_paint_levelSlides);
	m_paintlyLevelSlider->deactivate();

	m_paintlyJrSlider = new Fl_Value_Slider(10, 350, 300, 20, "Jr");
	m_paintlyJrSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyJrSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyJrSlider->labelfont(FL_COURIER);
	m_paintlyJrSlider->labelsize(12);
	m_paintlyJrSlider->minimum(0.00);
	m_paintlyJrSlider->maximum(1.00);
	m_paintlyJrSlider->step(0.01);
	m_paintlyJrSlider->value(m_paintly_Jr);
	m_paintlyJrSlider->align(FL_ALIGN_RIGHT);
	m_paintlyJrSlider->callback(cb_Jr_Slides);
	m_paintlyJrSlider->deactivate();

	m_paintlyJgSlider = new Fl_Value_Slider(10, 380, 300, 20, "Jg");
	m_paintlyJgSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyJgSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyJgSlider->labelfont(FL_COURIER);
	m_paintlyJgSlider->labelsize(12);
	m_paintlyJgSlider->minimum(0.00);
	m_paintlyJgSlider->maximum(1.00);
	m_paintlyJgSlider->step(0.01);
	m_paintlyJgSlider->value(m_paintly_Jg);
	m_paintlyJgSlider->align(FL_ALIGN_RIGHT);
	m_paintlyJgSlider->callback(cb_alphaSlides);
	m_paintlyJgSlider->deactivate();

	m_paintlyJbSlider = new Fl_Value_Slider(10, 410, 300, 20, "Jb");
	m_paintlyJbSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyJbSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyJbSlider->labelfont(FL_COURIER);
	m_paintlyJbSlider->labelsize(12);
	m_paintlyJbSlider->minimum(0.00);
	m_paintlyJbSlider->maximum(1.00);
	m_paintlyJbSlider->step(0.01);
	m_paintlyJbSlider->value(m_paintly_Jb);
	m_paintlyJbSlider->align(FL_ALIGN_RIGHT);
	m_paintlyJbSlider->callback(cb_Jb_Slides);
	m_paintlyJbSlider->deactivate();

	m_paintlyJhSlider = new Fl_Value_Slider(10, 170, 300, 20, "Jh");
	m_paintlyJhSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyJhSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyJhSlider->labelfont(FL_COURIER);
	m_paintlyJhSlider->labelsize(12);
	m_paintlyJhSlider->minimum(0.00);
	m_paintlyJhSlider->maximum(1.00);
	m_paintlyJhSlider->step(0.01);
	m_paintlyJhSlider->value(m_paintly_Jh);
	m_paintlyJhSlider->align(FL_ALIGN_RIGHT);
	m_paintlyJhSlider->callback(cb_Jh_Slides);
	m_paintlyJhSlider->deactivate();

	m_paintlyJsSlider = new Fl_Value_Slider(10, 440, 300, 20, "Js");
	m_paintlyJsSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyJsSlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyJsSlider->labelfont(FL_COURIER);
	m_paintlyJsSlider->labelsize(12);
	m_paintlyJsSlider->minimum(0.00);
	m_paintlyJsSlider->maximum(1.00);
	m_paintlyJsSlider->step(0.01);
	m_paintlyJsSlider->value(m_paintly_Js);
	m_paintlyJsSlider->align(FL_ALIGN_RIGHT);
	m_paintlyJsSlider->callback(cb_Js_Slides);
	m_paintlyJsSlider->deactivate();

	m_paintlyJySlider = new Fl_Value_Slider(10, 470, 300, 20, "Jv");
	m_paintlyJySlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_paintlyJySlider->type(FL_HOR_NICE_SLIDER);
	m_paintlyJySlider->labelfont(FL_COURIER);
	m_paintlyJySlider->labelsize(12);
	m_paintlyJySlider->minimum(0.00);
	m_paintlyJySlider->maximum(1.00);
	m_paintlyJySlider->step(0.01);
	m_paintlyJySlider->value(m_paintly_Jv);
	m_paintlyJySlider->align(FL_ALIGN_RIGHT);
	m_paintlyJySlider->callback(cb_Jv_Slides);
	m_paintlyJySlider->deactivate();


	m_PainlyDialog->end();



}
void ImpressionistUI::setPaintlyStyle(int type)
{
	m_paintly_style = type;
	m_StyleTypeChoice->value(type);
}

void ImpressionistUI::setPaintlyStroke(int type)
{
	m_paintly_stroke = type;
	m_StrokeTypeChoice->value(type);
}

void ImpressionistUI::setPaintlyThresh(int type)
{
	m_paintly_Threshold = type;
	m_paintly_ThresholdSlider->value(type);
}

void ImpressionistUI::setPaintlyCur(double d )
{
	m_paintly_Curvature = d;
	m_paintly_CurvatureSlider->value(d);
}

void ImpressionistUI::setPaintlyBlur(double d )
{
	m_paintly_Blur = d;
	m_paintly_BlurSlider->value(d);
	
}
void ImpressionistUI::setPaintlyGridSize(double d )
{
	m_paintly_GridSize = d;
	m_paintly_GridSizeSlider->value(d);
	
}

void ImpressionistUI::setPaintlyMinStr(int d)
{
	m_paintly_min_stroke = d;
	m_paintlyMinSlider->value(d);
	
}

void ImpressionistUI::setPaintlyMaxStr(int d)
{
	m_paintly_max_stroke = d;
	m_paintlyMaxSlider->value(d);
	
}

void ImpressionistUI::setPaintlyAlpha(double d )
{
	m_paintly_alpha = d;
	m_paintlyAlphaSlider->value(d);
	
}

void ImpressionistUI::setPaintlyLayers(int d)
{
	m_paintly_layer = d;
	m_paintlyLayersSlider->value(d);
	
}

void ImpressionistUI::setPaintlyLevel(int d)
{
	m_paintly_R0_level = d;
	m_paintlyLevelSlider->value(d);
	
}

void ImpressionistUI::setPaintlyJr(double d)
{
	m_paintly_Jr = d;
	m_paintlyJrSlider->value(d);
	
}

void ImpressionistUI::setPaintlyJg(double d)
{
	m_paintly_Jg = d;
	m_paintlyJgSlider->value(d);
}

void ImpressionistUI::setPaintlyJb(double d)
{
	m_paintly_Jb = d;
	m_paintlyJbSlider->value(d);
}

void ImpressionistUI::setPaintlyJh(double d)
{
	m_paintly_Jh = d;
	m_paintlyJhSlider->value(d);
}

void ImpressionistUI::setPaintlyJs(double d)
{
	m_paintly_Js = d;
	m_paintlyJsSlider->value(d);
}

void ImpressionistUI::setPaintlyJv(double d)
{
	m_paintly_Jv = d;
	m_paintlyJySlider->value(d);
}

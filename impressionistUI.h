//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Float_Input.H>
#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
	PaintView*			m_paintView;
	OriginalView*		m_origView;
	
	// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Slider*			m_BrushSizeSlider;
	Fl_Button*          m_ClearCanvasButton;
	
	
	//add by ourselves

	Fl_Choice*			m_DirectionTypeChoice;
	Fl_Slider*			m_BrushLineWidthSlider;
	Fl_Slider*			m_BrushLineAngleSlider;
	Fl_Slider*			m_BrushAlphaSlider;
	Fl_Light_Button*    m_EdgeClippingButton;
	Fl_Light_Button*    m_AnotherGradientButton;
	Fl_Slider*			m_BrushSpacingSlider;
	Fl_Light_Button*    m_SizeRandButton;
	Fl_Button*          m_PaintButton;
	Fl_Slider*          m_EdgeThreshSlider;
	Fl_Button*          m_DoItButton;
	//for filter dialog
	Fl_Window*			m_filterDialog;
	Fl_Light_Button*    m_filterNormalizeButton;
	Fl_Button*          m_filterApplyButton;
	Fl_Int_Input*       m_nfilterWidthInput;
	Fl_Int_Input*		m_nfilterHeightInput;
	Fl_Button*          m_ApplyButton;
	Fl_Button*			m_fillButton;
	Fl_Window*			m_PainlyDialog;
	Fl_Choice*			m_StyleTypeChoice;
	Fl_Choice*			m_StrokeTypeChoice;
	Fl_Slider*			m_paintly_ThresholdSlider;
	Fl_Slider*			m_paintly_CurvatureSlider;
	Fl_Slider*			m_paintly_BlurSlider;
	Fl_Slider*			m_paintly_GridSizeSlider;
	Fl_Slider*			m_paintlyMinSlider;
	Fl_Slider*			m_paintlyMaxSlider;
	Fl_Slider*			m_paintlyAlphaSlider;
	Fl_Slider*			m_paintlyLayersSlider;
	Fl_Slider*			m_paintlyLevelSlider;
	Fl_Slider*			m_paintlyJrSlider;
	Fl_Slider*			m_paintlyJgSlider;
	Fl_Slider*			m_paintlyJbSlider;
	Fl_Slider*			m_paintlyJhSlider;
	Fl_Slider*			m_paintlyJsSlider;
	Fl_Slider*			m_paintlyJySlider;
	Fl_Button*          m_RunButton;
	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);
	int getLineAngle() const;
	void setLineAngle(int);
	int getLineWidth() const;
	void setLineWidth(int);
	bool getAnotherGradient();
	int getThresh() const;
	double getAlpha() const;
	void setAlpha(double);
	int getDitectionType();
	void setDirectionType(int);
	bool getSizeRand() const;
	int getSpacing() const;
	bool getEdgeClip() const;
	double getColorSpaceR() const;
	double getColorSpaceG() const;
	double getColorSpaceB() const;
	bool getFilterNormal() const;
	void fillFilter(ImpressionistUI*);

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
	void setPaintlyThresh(int) ;
	void setPaintlyCur(double) ;
	void setPaintlyBlur(double) ;
	void setPaintlyGridSize(double) ;
	void setPaintlyMinStr(int) ;
	void setPaintlyMaxStr(int) ;
	void setPaintlyAlpha(double) ;
	void setPaintlyLayers(int) ;
	void setPaintlyLevel(int) ;
	void setPaintlyJr(double) ;
	void setPaintlyJg(double) ;
	void setPaintlyJb(double) ;
	void setPaintlyJh(double) ;
	void setPaintlyJs(double) ;
	void setPaintlyJv(double) ;
private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

									// All attributes here
	int		m_nSize;
	int m_nLineAngle;
	int m_nLineWidth;
	bool m_banotherGrad;
	bool m_bedgeClip;
	int m_nThresh;
	double m_alpha;
	int m_nDirectionType;
	bool m_bSizeRand;
	bool m_bfilterNormal;
	int m_nSpace;
	static double m_dR;
	static double m_dG;
	static double m_dB;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE + 1];
	static Fl_Menu_Item     strokeDirectionTypeMenu[NUM_DIR_TYPE + 1];
	static Fl_Menu_Item		styleTypeMenu[NUM_STYLE_TYPE + 1];
	static Fl_Menu_Item     strokeTypeMenu[NUM_STROKE_TYPE + 1];
	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);

	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_paintly(Fl_Menu_* o, void* v);
	static void	cb_filter(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void cb_colorChange(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);


	//I add here for basic one
	static void	cb_load_edge_image(Fl_Menu_* o, void* v);
	static void	cb_load_video(Fl_Menu_* o, void* v);
	static void	cb_load_alpha(Fl_Menu_* o, void* v);
	static void cb_show_ori_image(Fl_Menu_* o, void* v);
	static void	cb_dissolve_image(Fl_Menu_* o, void* v);
	static void	cb_show_edge_image(Fl_Menu_* o, void* v);
	static void	cb_load_ori_image(Fl_Menu_* o, void* v);
	static void	cb_load_ano_image(Fl_Menu_* o, void* v);
	static void	cb_load_mural_image(Fl_Menu_* o, void* v);
	static void	cb_show_ano_image(Fl_Menu_* o, void* v);
	static void	cb_faster(Fl_Menu_* o, void* v);
	static void	cb_safer(Fl_Menu_* o, void* v);
	static void	cb_undo(Fl_Menu_* o, void* v);
	static void	cb_directionChoice(Fl_Widget* o, void* v);
	static void	cb_paintly_styleChoice(Fl_Widget* o, void* v);
	static void	cb_paintly_strokeChoice(Fl_Widget* o, void* v);
	static void	cb_paint_button(Fl_Widget* o, void* v);
	static void	cb_run_button(Fl_Widget* o, void* v);
	
	static void	cb_LineAngleSlides(Fl_Widget* o, void* v);
	static void	cb_LineWidthSlides(Fl_Widget* o, void* v);
	static void cb_another_gradient_button(Fl_Widget* o, void* v);
	static void cb_edge_clip_button(Fl_Widget* o, void* v);
	static void cb_threshSlides(Fl_Widget* o, void* v);
	static void cb_alphaSlides(Fl_Widget* o, void* v);
	static void cb_SizeRandButton(Fl_Widget* o, void* v);
	static void cb_spaceSlides(Fl_Widget* o, void* v);
	static void cb_swap_image(Fl_Menu_* o, void* v);
	static void cb_do_it_button(Fl_Widget* o, void* v);
	//static void cb_run_button(Fl_Widget* o, void* v);
	static void cb_filter_normal_button(Fl_Widget* o, void* v);
	static void cb_apply_button(Fl_Widget* o, void* v);
	static void cb_fill_button(Fl_Widget* o, void* v);


	static void cb_paint_thre_Slides(Fl_Widget* o, void* v);
	static void cb_paint_cur_Slides(Fl_Widget* o, void* v);
	static void cb_paint_blur_Slides(Fl_Widget* o, void* v);
	static void cb_paint_gridSlides(Fl_Widget* o, void* v);
	static void cb_paint_min_strokeSlides(Fl_Widget* o, void* v);
	static void cb_paint_max_strokeSlides(Fl_Widget* o, void* v);
	static void cb_paint_alphaSlides(Fl_Widget* o, void* v);
	static void cb_paint_layerSlides(Fl_Widget* o, void* v);
	static void cb_paint_levelSlides(Fl_Widget* o, void* v);
	static void cb_Jr_Slides(Fl_Widget* o, void* v);
	static void cb_Jg_Slides(Fl_Widget* o, void* v);
	static void cb_Jb_Slides(Fl_Widget* o, void* v);
	static void cb_Jh_Slides(Fl_Widget* o, void* v);
	static void cb_Js_Slides(Fl_Widget* o, void* v);
	static void cb_Jv_Slides(Fl_Widget* o, void* v);
	int m_paintly_style;
	int m_paintly_stroke;
	int m_paintly_Threshold;
	double m_paintly_Curvature;
	double m_paintly_Blur;
	double m_paintly_GridSize;
	int m_paintly_min_stroke;
	int m_paintly_max_stroke;
	double m_paintly_alpha;
	int m_paintly_layer;
	int m_paintly_R0_level;
	double m_paintly_Jr;
	double m_paintly_Jg;
	double m_paintly_Jb;
	double m_paintly_Jh;
	double m_paintly_Js;
	double m_paintly_Jv;
	//for paintly dialog
	
};


#endif
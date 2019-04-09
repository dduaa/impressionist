//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount = 0;
ImpBrush**	ImpBrush::c_pBrushes = NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc,
	char*				name) :
	m_pDoc(pDoc),
	m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor(const Point source)
{
	//transparency here
	ImpressionistDoc* pDoc = GetDocument();
	GLubyte color[4];
	memcpy(color, pDoc->GetOriginalPixel(source), 3);

	//printf("alpha%f", pDoc->getAlpha());
	color[0] = color[0]* (GLubyte)(  pDoc->m_pUI->getColorSpaceR());
	color[1] = color[1] * (GLubyte)(pDoc->m_pUI->getColorSpaceG());
	color[2] = color[2] * (GLubyte)(pDoc->m_pUI->getColorSpaceB());
	color[3] = (GLubyte)(pDoc->getAlpha() * 255);
	glColor4ubv(color);
	
	/*GLubyte color[3]; 

	memcpy(color, pDoc->GetOriginalPixel(source), 3);

	glColor3ubv(color);
	*/
}
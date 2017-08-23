#include "StdAfx.h"
#include "Element2D.h"


namespace netnodeds
{

void Element2D::_001OnDraw(netnodedsView * pview, CDC * pgraphics)
{
	
}

void Element2D::_001OnLButtonDown(netnodedsView * pview, gen::message::sender_object * pobj)
{
	SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
/*	netnodedsApp * papp = (netnodedsApp *) AfxGetApp();
	BaseView * pviewGeneric = papp->GetView(this);
	netnodedsView * pview = dynamic_cast < netnodedsView * > (pviewGeneric);
	if(pview != NULL)
	{
	}*/
}
void Element2D::_001OnLButtonUp(netnodedsView * pview, gen::message::sender_object * pobj)
{
	SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
}

void Element2D::_001OnMouseMove(netnodedsView * pview, gen::message::sender_object * pobj)
{
	SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
}

bool Element2D::hit_test(int x, int y)
{
	return x >= m_pt.x && x <= m_pt.x + m_size.cx &&
	y >= m_pt.y && y <= m_pt.y + m_size.cy;
}

void Element2D::_001OnCalcLayout(CDC * pgraphics)
{
}


} // namespace netnodeds
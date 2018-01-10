#include "StdAfx.h"
#include "Element2D.h"


namespace devedge
{

void Element2D::_001OnDraw(devedgeView * pview, CDC * pgraphics)
{
	
}

void Element2D::_001OnLButtonDown(devedgeView * pview, gen::message::sender_object * pobj)
{
	SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
/*	devedgeApp * papp = (devedgeApp *) AfxGetApp();
	BaseView * pviewGeneric = papp->GetView(this);
	devedgeView * pview = dynamic_cast < devedgeView * > (pviewGeneric);
	if(pview != NULL)
	{
	}*/
}
void Element2D::_001OnLButtonUp(devedgeView * pview, gen::message::sender_object * pobj)
{
	SCAST_PTR(igui::win::message::mouse, pmouse, pobj);
}

void Element2D::_001OnMouseMove(devedgeView * pview, gen::message::sender_object * pobj)
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


} // namespace devedge
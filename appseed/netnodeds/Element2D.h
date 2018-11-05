#pragma once

#include "KeyboardFocus.h"

class netnodedsView;

namespace netnodeds
{


class CLASS_DECL_CA2_DEVEDGE Element2D : 
	virtual public KeyboardFocus
{
public:
	point	m_pt;
	size	m_size;

	BaseRect m_rectView;

	virtual void _001OnCalcLayout(CDC * pdc);
	virtual void _001OnDraw(netnodedsView * pview, CDC * pdc);

	virtual bool hit_test(int x, int y);

	virtual void _001OnLButtonDown(netnodedsView * pview, gen::message::sender_object * pobj);
	virtual void _001OnLButtonUp(netnodedsView * pview, gen::message::sender_object * pobj);
	virtual void _001OnMouseMove(netnodedsView * pview, gen::message::sender_object * pobj);

};



} // namespace netnodeds
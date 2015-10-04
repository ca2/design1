#include "StdAfx.h"
#include "Element2D.h"


namespace netnodeds
{

void KeyboardFocus::_001OnKeyboardFocusTimer(netnodeds_view * pview, int iTimer)
{
	
}

void KeyboardFocus::_001OnChar(netnodeds_view * pview, gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::key, pkey, pobj);
}

void KeyboardFocus::_001OnSysChar(netnodeds_view * pview, gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::key, pkey, pobj);
}

} // namespace netnodeds
#pragma once

class netnodedsView;

namespace netnodeds
{


class CLASS_DECL_CA2_DEVEDGE KeyboardFocus : public gen::signalizable
{
public:
	virtual void _001OnKeyboardFocusTimer(netnodedsView * pview, int iTimer);
   virtual void _001OnChar(netnodedsView * pview, gen::signal_object * pobj);
   virtual void _001OnSysChar(netnodedsView * pview, gen::signal_object * pobj);
};



} // namespace netnodeds
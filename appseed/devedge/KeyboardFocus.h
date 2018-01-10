#pragma once

class devedgeView;

namespace devedge
{


class CLASS_DECL_CA2_DEVEDGE KeyboardFocus : public gen::::message::receiver
{
public:
	virtual void _001OnKeyboardFocusTimer(devedgeView * pview, int iTimer);
   virtual void _001OnChar(devedgeView * pview, gen::message::sender_object * pobj);
   virtual void _001OnSysChar(devedgeView * pview, gen::message::sender_object * pobj);
};



} // namespace devedge
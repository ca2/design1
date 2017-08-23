#pragma once

class netnodedsView;

namespace netnodeds
{


class CLASS_DECL_CA2_DEVEDGE KeyboardFocus : public gen::::message::receiver
{
public:
	virtual void _001OnKeyboardFocusTimer(netnodedsView * pview, int iTimer);
   virtual void _001OnChar(netnodedsView * pview, gen::message::sender_object * pobj);
   virtual void _001OnSysChar(netnodedsView * pview, gen::message::sender_object * pobj);
};



} // namespace netnodeds
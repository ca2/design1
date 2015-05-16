#include "framework.h"


namespace syllomatter
{


   frame::frame(::aura::application * papp) :
      ::object(papp),
      simple_child_frame(papp),
      form_child_frame(papp),
      m_imagelist(papp)
   {
      
      m_iAnimateStep = 0;

      WfiEnableFullScreen();

   }


   frame::~frame()
   {

   }


   void frame::_001OnCreate(::signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);
     
      m_bTimerOn = false;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

      m_imagelist.create(16, 16, 0, 10, 10);
      m_imagelist.add_matter_icon("system/language_change.ico");

      
   }


   bool frame::pre_create_window(::user::create_struct& cs)
   {

      if( !simple_frame_window::pre_create_window(cs) )
         return FALSE;

      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;

      return TRUE;

   }


#ifdef DEBUG
   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // frame message handlers




   void frame::SetAnimatedStatusBarText(const char * lpcsz)
   {
      m_strAnimatedStatusBarText = lpcsz;
      if(m_strAnimatedStatusBarText.is_empty())
      {
         KillTimer(3);
      }
      else
      {
         SetTimer(3, 500, NULL);
      }
   }

   void frame::AnimateStatusBar()
   {
      if(m_strAnimatedStatusBarText.is_empty())
         return;

      strsize iLen = m_strAnimatedStatusBarText.get_length();
      m_iAnimateStep++;
      if(m_iAnimateStep > iLen)
         m_iAnimateStep = 0;


      //   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
   }


   void frame::ShowControlBars(bool bShow)
   {
      uint32_t nShow;
      if(bShow)
      {
         nShow = SW_SHOW;
      }
      else
      {
         nShow = SW_HIDE;
      }

      /*   m_toolbar.ShowWindow(nShow);
      m_toolbarView.ShowWindow(nShow);
      //   m_statusbar.ShowWindow(nShow);
      m_menubar.ShowWindow(nShow);
      m_dialogbar.ShowWindow(nShow);*/

   }



   void frame::OnHoverAction()
   {
      ShowWindow(SW_RESTORE);
   }


} // namespace syllomatter




#include "framework.h"


namespace netnodeds 
{


   main_frame::main_frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp)
   {

      m_iAnimateStep = 0;

      WfiEnableFullScreen();

   }


   main_frame::~main_frame()
   {
   }

   void main_frame::_001OnCreate(::signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   }

   void main_frame::install_message_handling(::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CLOSE,          pinterface, this, &main_frame::_001OnClose);
   }


   bool main_frame::pre_create_window(::user::create_struct& cs)
   {
      
      if( !simple_frame_window::pre_create_window(cs) )
         return FALSE;
      
      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;

      return TRUE;

   }


#ifdef DEBUG
   void main_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //DEBUG

   
   void main_frame::OnTimer(uint32_t nIDEvent) 
   {
      static float theta;
      if(nIDEvent == 3)
      {
         //AnimateStatusBar();
      }
      else if(nIDEvent == 8913)
      {
      }
      else if(nIDEvent == 4033)
      {
   // OpenGL animation code goes here
            
            //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
            //glClear( GL_COLOR_BUFFER_BIT );
            
            /*glPushMatrix();
            glRotatef( theta, 0.0f, 1.0f, 1.0f );
            glBegin( GL_TRIANGLES );
            glColor3f( 1.0f, 0.0f, 0.0f ); glVertgenf( 0.0f, 1.0f );
            glColor3f( 0.0f, 1.0f, 0.0f ); glVertgenf( 0.87f, -0.5f );
            glColor3f( 0.0f, 0.0f, 1.0f ); glVertgenf( -0.87f, -0.5f );
            glEnd();
            glPopMatrix();*/
            
            //SwapBuffers( m_hdcOpenGL );
            
            theta += 2.0f;
         
      }
      //simple_frame_window::OnTimer(nIDEvent);
   }

   void main_frame::SetAnimatedStatusBarText(const char * lpcsz)
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

   void main_frame::AnimateStatusBar()
   {
      if(m_strAnimatedStatusBarText.is_empty())
         return;

      strsize iLen = m_strAnimatedStatusBarText.get_length();
      m_iAnimateStep++;
      if(m_iAnimateStep > iLen)
         m_iAnimateStep = 0;


   //   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
   }


   void main_frame::ShowControlBars(bool bShow)
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

   
   bool main_frame::is_application_main_window()
   {
      return true;
   }


} // namespace netnodeds



#include "framework.h"


namespace biteditor
{


   frame::frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp),
      m_imagelist(papp)
   {
      
      

      WfiEnableFullScreen();

   }

   
   frame::~frame()
   {

   }


   void frame::install_message_routing(::message::sender * pinterface)
   {
      simple_frame_window::install_message_routing(pinterface);
      IGUI_MSG_LINK(WM_CREATE   , pinterface, this, &frame::_001OnCreate);
      IGUI_MSG_LINK(WM_CLOSE    , pinterface, this, &frame::_001OnClose);
   }

   void frame::_001OnCreate(::message::message *pobj)
   {

      pobj->previous();

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   }

   void frame::_001OnClose(::message::message *pobj)
   {

      for(int iTemplate = 0; iTemplate < Application.document_manager()->get_template_count(); iTemplate++)
      {
         sp(::user::impact_system) ptemplate = Application.document_manager()->get_template(iTemplate);
         for(int iDocument = 0; iDocument < ptemplate->get_document_count(); iDocument++)
         {
            sp(::user::document) pdocument = ptemplate->get_document(iDocument);
            if(!pdocument->can_close_frame(this))
            {
               pobj->m_bRet = true;
               return;
            }
         }
      }


      //Application.m_pdocmanager->close_all_documents(true);

   }


   bool frame::pre_create_window(::user::create_struct& cs)
   {
      
      if( !simple_frame_window::pre_create_window(cs) )
         return FALSE;
      
      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;


      return TRUE;

   }

   /////////////////////////////////////////////////////////////////////////////
   // frame diagnostics

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




   void frame::OnTimer(uint32_t nIDEvent)
   {
      static float theta;
      if(nIDEvent == 3)
      {
    
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
   // trans   simple_frame_window::OnTimer(nIDEvent);
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


} // namespace biteditor



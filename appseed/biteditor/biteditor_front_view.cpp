#include "framework.h"


namespace biteditor
{


   front_view::front_view(::aura::application * papp) :
      object(papp),
      html_form(papp),
      html_view(papp)
   {

   }


   front_view::~front_view()
   {

   }


   void front_view::install_message_handling(::message::dispatch * pinterface)
   {

      html_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &front_view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &front_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &front_view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &front_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &front_view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &front_view::_001OnSetCursor);
      //IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &front_view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_USER + 101     , pinterface, this, &front_view::_001OnPost);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &front_view::_001OnTabClick);
      IGUI_WIN_MSG_LINK(WM_APP + 119      , pinterface, this, &front_view::_001OnWavePlayerEvent);
      //  IGUI_WIN_MSG_LINK(WM_CHAR, pinterface, this, &front_view::_001OnChar);
      //IGUI_WIN_MSG_LINK(WM_SYSCHAR, pinterface, this, &front_view::_001OnSysChar);
      //connect_command(ID_FILE_PRINT, html_view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, html_view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, html_view::OnFilePrintPreview)

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,
         pinterface,
         this,
         &front_view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,
         pinterface,
         this,
         &front_view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,
         pinterface,
         this,
         &front_view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,
         pinterface,
         this,
         &front_view::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP,
         pinterface,
         this,
         &front_view::_001OnKeyUp);

   }

#ifdef DEBUG
   void front_view::assert_valid() const
   {
      html_view::assert_valid();
   }

   void front_view::dump(dump_context & dumpcontext) const
   {
      html_view::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // front_view message handlers

   // vmpLightView.cpp : implementation of the front_view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // front_view


   bool front_view::pre_create_window(::user::create_struct& cs)
   {

      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
      cs.style &= ~WS_BORDER;

      return html_view::pre_create_window(cs);

   }


   void front_view::_001OnInitialUpdate()
   {
      html_view::_001OnInitialUpdate();



   }

   void front_view::on_update(::user::impact * pSender, LPARAM lHint, ::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 1001)
      {
         _001RedrawWindow();
      }


   }

   void front_view::_001OnDestroy(::signal_details * pobj)
   {
      html_view::_001OnDestroy(pobj);

   }



   void front_view::_001OnSize(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::size, psize, pobj);
      //sp(::user::document) pdoc = get_document();
   }

   void front_view::_001OnPaint(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void front_view:: _001OnDraw(::draw2d::dib * pdib)
   {

      pdc->OffsetViewportOrg(-2, -2);
      //CFileSpec fsDest(szDestFilename);
      //CBitmapDC destDC(srcSize.cx, srcSize.cy);

   }

   void front_view::_001OnCreate(::signal_details * pobj)
   {
      if(pobj->previous())
         return;

      SetTimer(100, 100, NULL);

      post_message(WM_USER + 101, 101, 1);



      /*sp(::user::document) pdoc = get_document();
      for(int32_t i = 0; i < pdoc->m_elementptraVisible.get_size(); i++)
      {
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,
      this,
      pdoc->m_elementptraVisible[i],
      &biteditor::Element2D::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,
      this,
      pdoc->m_elementptraVisible[i],
      &biteditor::Element2D::_001OnLButtonUp);
      }*/

   }
   void front_view::_001OnContextMenu(::signal_details * pobj)
   {
      SCAST_PTR(::message::context_menu, pcontextmenu, pobj);
         point point = pcontextmenu->GetPoint();

   }



   void front_view::_001OnWavePlayerEvent(::signal_details * pobj)
   {
      //   SCAST_PTR(::message::base, pbase, pobj);
      UNREFERENCED_PARAMETER(pobj);
   }

   void front_view::_001OnUpdateViewEncoding(::signal_details * pobj)
   {
      //SCAST_PTR(::message::update_cmd_ui, pupdatecmdui, pobj);
      UNREFERENCED_PARAMETER(pobj);
   }
   void front_view::_001OnViewEncoding(::signal_details * pobj)
   {
      //SCAST_PTR(::message::command, pcommand, pobj);
      UNREFERENCED_PARAMETER(pobj);
   }

   void front_view::_001OnSetCursor(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();
   }

   void front_view::_001OnLButtonDown(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
         point pt = pmouse->m_pt;
   }

   void front_view::_001OnLButtonUp(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
         point pt = pmouse->m_pt;
   }

   void front_view::_001OnMouseMove(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
         point pt = pmouse->m_pt;
   }


   ::user::document * front_view::get_document() const
   {

      return ::user::impact::get_document();

   }


   ::user::elemental * front_view::hit_test(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      //sp(::user::document) pdoc = get_document();
      return NULL;
   }

   void front_view::_001OnTimer(::timer * ptimer) 
   {
      html_view::_001OnTimer(ptimer);
         if(ptimer->m_nIDEvent >= 100
            && ptimer->m_nIDEvent <= 200)
         {
         }
         else if(ptimer->m_nIDEvent == 500 || ptimer->m_nIDEvent == 501 )
         {
            if(ptimer->m_nIDEvent == 500)
            {
               KillTimer(500);
               SetTimer(501, 300, NULL);
            }
            key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
         }

   }

   void front_view::_001OnKeyDown(::signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
         m_dwLastKeyWparam = (uint32_t) pkey->m_wparam;
      m_dwLastKeyLparam = (uint32_t) pkey->m_lparam;
      key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
      SetTimer(500, 500, NULL);
   }

   void front_view::_001OnKeyUp(::signal_details * pobj)
   {
      //   SCAST_PTR(::message::key, pkey, pobj);
      UNREFERENCED_PARAMETER(pobj);
      KillTimer(500);
      KillTimer(501);
   }


   void front_view::_001OnChar(::signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
         if(pkey->m_ekey == ::user::key_s)
         {
            if(Session.is_key_pressed(::user::key_control))
            {
               return;
            }
         }
   }


   void front_view::_001OnSysChar(::signal_details * pobj)
   {
      //   SCAST_PTR(::message::key, pkey, pobj);
      UNREFERENCED_PARAMETER(pobj);
   }


   /*
   bool front_view::pre_translate_message(::signal_details * pobj)
   {
   if(pMsg->oswindow == GetSafeoswindow_())
   {
   if(pMsg->message == WM_KEYDOWN)
   {
   ::message::key key;
   LRESULT lresult;
   key.set(pMsg->message, pMsg->wParam, pMsg->lParam, lresult);
   _001OnKeyDown(&key);
   return TRUE;
   }
   else if(pMsg->message == WM_KEYUP)
   {
   ::message::key key;
   LRESULT lresult;
   key.set(pMsg->message, pMsg->wParam, pMsg->lParam, lresult);
   _001OnKeyUp(&key);
   return TRUE;
   }
   }
   return html_view::pre_translate_message(pMsg);
   }
   */

   void front_view::key_to_char(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(lparam);

      ::message::key key(get_app());

      if(wparam == VK_LSHIFT || wparam == VK_RSHIFT
         || wparam == VK_LCONTROL || wparam == VK_RCONTROL
         || wparam == VK_LMENU || wparam == VK_RMENU)
      {
         return;
      }

      //   LRESULT lresult;
      key.m_nChar = wparam;
      bool bShift = Session.is_key_pressed(::user::key_shift);
      if(bShift && isalpha((int32_t) key.m_nChar))
      {
         key.m_nChar = toupper((int32_t) key.m_nChar);
      }
      else
      {
         key.m_nChar = tolower((int32_t) key.m_nChar);
      }
      _001OnChar(&key);
   }

   void front_view::_001OnPost(::signal_details * pobj)
   {

      SCAST_PTR(::message::base, pbase, pobj);

      if(pbase->m_wparam == 100)
      {

         post_message(WM_USER + 101, 101);

      }
      else if (pbase->m_wparam == 101)
      {

      }

   }


   void front_view::OnDocumentComplete(const char * lpszURL)
   {

      UNREFERENCED_PARAMETER(lpszURL);

      post_message(WM_USER + 101, 101);

   }


} // namespace biteditor






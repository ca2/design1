#include "framework.h"


namespace netnodeds
{


   html_stage_view::html_stage_view(::aura::application * papp) :
      ::object(papp),
      html_form(papp),
      html_view(papp)
   {

   }


   html_stage_view::~html_stage_view()
   {

   }


   void html_stage_view::install_message_handling(::message::dispatch * pinterface)
   {

      html_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &html_stage_view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &html_stage_view::_001OnSize);
      //IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &html_stage_view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &html_stage_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &html_stage_view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &html_stage_view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &html_stage_view::_001OnEraseBkgnd);
      //IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &html_stage_view::_001OnTimer);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &html_stage_view::_001OnTabClick);
      IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &html_stage_view::_001OnWavePlayerEvent);
      //  IGUI_WIN_MSG_LINK(WM_CHAR, pinterface, this, &html_stage_view::_001OnChar);
      //IGUI_WIN_MSG_LINK(WM_SYSCHAR, pinterface, this, &html_stage_view::_001OnSysChar);
      //connect_command(ID_FILE_PRINT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::user::impact::OnFilePrintPreview)

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
         this,
         this,
         &html_stage_view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
         this,
         this,
         &html_stage_view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, 
         this,
         this,
         &html_stage_view::_001OnMouseMove);

   }

#ifdef DEBUG
   void html_stage_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void html_stage_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // html_stage_view message handlers

   // vmpLightView.cpp : implementation of the html_stage_view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // html_stage_view


   bool html_stage_view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);

   }


   void html_stage_view::_001OnInitialUpdate() 
   {
      ::user::impact::_001OnInitialUpdate();



   }

   sp(::user::interaction) html_stage_view::get_guie()
   {
      return this;
   }

   void html_stage_view::on_update(::user::impact * pSender, LPARAM lHint, ::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 1001)
      {
         _001RedrawWindow();
      }
      else if(lHint == 123)
      {
         ::draw2d::dib_sp g(allocer());
         g->create(100, 100);
         get_document()->get_html_data()->layout(g);
         
      }
      /*xxx   if(phint != NULL)
      {
      if(base < main_document >::bases(phint))
      {
     sp(main_document) puh = (sp( main_document) ) phint;
      if(puh->is_type_of(main_document::TypeOnShowKaraoke))
      {
      ( (GetTopLevelFrame()))->SetActiveView(this);
      }
      else if(puh->is_type_of(main_document::TypeOnShowView))
      {
      netnodedsApp * papp = dynamic_cast < netnodedsApp * > (( (GetParentFrame()))->m_papp);
      POSITION posDoc = papp->m_ptemplate_netnodeds->get_document_count();
      sp(::user::document) pdoc = (sp(::user::document)) papp->m_ptemplate_netnodeds->get_document(posDoc);

      string str = pdoc->get_file_path();
      if(str.get_length() > 4)
      {
      if(str.Right(3).CompareNoCase(".ds") == 0)
      {
      int32_t iPos = str.reverse_find('\\');
      str = str.Mid(iPos + 1);
      str = str.Mid(0, str.get_length() - 3);
      str = "http://localhost:80/" + str;
      }
      }
      //          if(m_str == str)
      //               Refresh();
      //        else
      {
      m_str = str;
      Navigate(str);
      }
      }
      }
      }

      */

   }

   sp(::user::box) html_stage_view::BackViewGetWnd()
   {
      return this;
   }

   void html_stage_view::_001OnDestroy(::signal_details * pobj) 
   {
      ::user::impact::_001OnDestroy(pobj);

   }



   void html_stage_view::_001OnSize(::signal_details * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      // SCAST_PTR(::message::size, psize, pobj);
      //   sp(html_stage_document) pdoc = get_document();
   }

   void html_stage_view::_001OnPaint(::signal_details * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void html_stage_view:: _001OnDraw(::draw2d::graphics * pgraphics)
   {

      html_view::_001OnDraw(pdib);

   }


   void html_stage_view::_001OnCreate(::signal_details * pobj) 
   {
      if(pobj->previous())
         return;

      //   sp(html_stage_document) pdoc = get_document();

      SetTimer(100, 100, NULL);




      /*sp(html_stage_document) pdoc = get_document();
      for(int32_t i = 0; i < pdoc->m_elementptraVisible.get_size(); i++)
      {
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
      this,
      pdoc->m_elementptraVisible[i],
      &::netnodeds::Element2D::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
      this,
      pdoc->m_elementptraVisible[i],
      &::netnodeds::Element2D::_001OnLButtonUp);
      }*/

   }
   void html_stage_view::_001OnContextMenu(::signal_details * pobj) 
   {
      SCAST_PTR(::message::context_menu, pcontextmenu, pobj);
         point point = pcontextmenu->GetPoint();

   }



   void html_stage_view::_001OnWavePlayerEvent(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::base, pbase, pobj);
   }

   void html_stage_view::_001OnUpdateViewEncoding(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::update_cmd_ui, pupdatecmdui, pobj);
   }

   void html_stage_view::_001OnViewEncoding(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::command, pcommand, pobj);
   }


   void html_stage_view::_001OnSetCursor(::signal_details * pobj) 
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();

   }


   void html_stage_view::_001OnEraseBkgnd(::signal_details * pobj) 
   {
      SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pobj);
         perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void html_stage_view::_001OnLButtonDown(::signal_details * pobj) 
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
         point pt = pmouse->m_pt;
   }

   void html_stage_view::_001OnLButtonUp(::signal_details * pobj) 
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
         point pt = pmouse->m_pt;
   }

   void html_stage_view::_001OnMouseMove(::signal_details * pobj) 
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
         point pt = pmouse->m_pt;
   }

   sp(html_stage_document) html_stage_view::get_document() const
   {
      return  (::user::impact::get_document());
   }

   ::user::elemental * html_stage_view::hit_test(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      //sp(html_stage_document) pdoc = get_document();
      return NULL;
   }

   void html_stage_view::_001OnTimer(::timer * ptimer) 
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
         }

   }

   void html_stage_view::_001OnKeyDown(::signal_details * pobj) 
   {
      //   SCAST_PTR(::message::key, pkey, pobj);
      UNREFERENCED_PARAMETER(pobj);
      SetTimer(500, 500, NULL);
   }

   void html_stage_view::_001OnKeyUp(::signal_details * pobj) 
   {
      // SCAST_PTR(::message::key, pkey, pobj);
      UNREFERENCED_PARAMETER(pobj);
      KillTimer(500);
      KillTimer(501);
   }


   void html_stage_view::_001OnChar(::signal_details * pobj) 
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


   void html_stage_view::_001OnSysChar(::signal_details * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::key, pkey, pobj);
   }

   void html_stage_view::pre_translate_message(::signal_details * pobj)
   {
      ::user::impact::pre_translate_message(pobj);
   }

   void html_stage_view::key_to_char(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(lparam);
      ::message::key key(get_app());

      if(wparam == VK_LSHIFT || wparam == VK_RSHIFT
         || wparam == VK_LCONTROL || wparam == VK_RCONTROL
         || wparam == VK_LMENU || wparam == VK_RMENU)
      {
         return;
      }


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


} // namespace netnodeds



#include "framework.h"


namespace devedge
{


   html_edit_view::html_edit_view(::aura::application * papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::user::form_interface(papp),
      ::user::form(papp),
      html_form(papp),
      html_view(papp)
   {
   }

   html_edit_view::~html_edit_view()
   {
   }

   void html_edit_view::install_message_handling(::message::dispatch * pinterface)
   {
      html_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &html_edit_view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &html_edit_view::_001OnSize);
      //IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &html_edit_view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &html_edit_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &html_edit_view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &html_edit_view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &html_edit_view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_USER + 101     , this, this, &html_edit_view::_001OnPost);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &html_edit_view::_001OnTabClick);
      IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &html_edit_view::_001OnWavePlayerEvent);
      IGUI_WIN_MSG_LINK(WM_USER, pinterface, this, &html_edit_view::_001OnUser);
      //  IGUI_WIN_MSG_LINK(WM_CHAR, pinterface, this, &html_edit_view::_001OnChar);
      //IGUI_WIN_MSG_LINK(WM_SYSCHAR, pinterface, this, &html_edit_view::_001OnSysChar);
      //connect_command(ID_FILE_PRINT, html_view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, html_view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, html_view::OnFilePrintPreview)

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,
         this,
         this,
         &html_edit_view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,
         this,
         this,
         &html_edit_view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,
         this,
         this,
         &html_edit_view::_001OnMouseMove);

   }

#ifdef DEBUG
   void html_edit_view::assert_valid() const
   {
      html_view::assert_valid();
   }

   void html_edit_view::dump(dump_context & dumpcontext) const
   {
      html_view::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // html_edit_view message handlers

   // vmpLightView.cpp : implementation of the html_edit_view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // html_edit_view


   bool html_edit_view::pre_create_window(::user::create_struct& cs)
   {

      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      cs.style &= ~WS_BORDER;

      return html_view::pre_create_window(cs);

   }


   void html_edit_view::_001OnInitialUpdate(::signal_details * pobj)
   {
      html_view::_001OnInitialUpdate(pobj);



   }

   sp(::user::interaction) html_edit_view::get_guie()
   {
      return this;
   }

   void html_edit_view::on_update(::aura::impact * pSender, LPARAM lHint, ::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 1001)
      {
         _001RedrawWindow();
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
      else if(puh->is_type_of(main_document::TypeOnBeforeShowView))
      {
      ::devedge::application_interface * papp = dynamic_cast < ::devedge::application_interface * > (get_app());
      POSITION posDoc = papp->m_ptemplate_devedge->get_document_count();
      sp(::aura::document) pdoc = (sp(::aura::document)) papp->m_ptemplate_devedge->get_document(posDoc);
      if(m_str == pdoc->get_path_name())
      {
      //               transform_back();
      }
      else
      {
      m_str = pdoc->get_path_name();
      }
      }
      else if(puh->is_type_of(main_document::TypeOnShowView))
      {
      transform();
      Navigate(System.dir().time("html.html"));
      }
      }
      }
      */


   }

   sp(::database::user::interaction) html_edit_view::BackViewGetWnd()
   {
      return this;
   }

   void html_edit_view::_001OnDestroy(::signal_details * pobj)
   {
      html_view::_001OnDestroy(pobj);

   }



   void html_edit_view::_001OnSize(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // SCAST_PTR(::message::size, psize, pobj)
      //   sp(::aura::document) pdoc = get_document();
   }

   void html_edit_view::_001OnPaint(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void html_edit_view:: _001OnDraw(::draw2d::graphics * pdc)
   {
      html_view::_001OnDraw(pdc);
   }

   void html_edit_view::_001OnCreate(::signal_details * pobj)
   {
      if(pobj->previous())
         return;

      SetTimer(100, 100, NULL);

      post_message(WM_USER + 101, 100, 1);



      /*sp(::aura::document) pdoc = get_document();
      for(int32_t i = 0; i < pdoc->m_elementptraVisible.get_size(); i++)
      {
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,
      this,
      pdoc->m_elementptraVisible[i],
      &::devedge::Element2D::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,
      this,
      pdoc->m_elementptraVisible[i],
      &::devedge::Element2D::_001OnLButtonUp);
      }*/

   }
   void html_edit_view::_001OnContextMenu(::signal_details * pobj)
   {
      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
         point point = pcontextmenu->GetPoint();

   }



   void html_edit_view::_001OnWavePlayerEvent(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::base, pbase, pobj)
   }

   void html_edit_view::_001OnUpdateViewEncoding(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // SCAST_PTR(::message::update_cmd_ui, pupdatecmdui, pobj)
   }

   void html_edit_view::_001OnViewEncoding(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::command, pcommand, pobj)
   }

   void html_edit_view::_001OnSetCursor(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)

      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();
   }

   void html_edit_view::_001OnLButtonDown(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         point pt = pmouse->m_pt;
   }

   void html_edit_view::_001OnLButtonUp(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         point pt = pmouse->m_pt;
   }

   void html_edit_view::_001OnMouseMove(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         point pt = pmouse->m_pt;
   }

   sp(::aura::document) html_edit_view::get_document() const
   {
      return  (::aura::impact::get_document());
   }

   ::user::elemental * html_edit_view::hit_test(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      //   sp(::aura::document) pdoc = get_document();
      return NULL;
   }

   void html_edit_view::_001OnTimer(::signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj)
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

   void html_edit_view::_001OnKeyDown(::signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj)
         m_dwLastKeyWparam = (uint32_t) pkey->m_wparam;
      m_dwLastKeyLparam = (uint32_t) pkey->m_lparam;
      key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
      SetTimer(500, 500, NULL);
   }

   void html_edit_view::_001OnKeyUp(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::key, pkey, pobj)
      KillTimer(500);
      KillTimer(501);
   }


   void html_edit_view::_001OnChar(::signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj)
         if(pkey->m_ekey == ::user::key_s)
         {
            if(Session.is_key_pressed(::user::key_control))
            {
               return;
            }
         }
   }


   void html_edit_view::_001OnSysChar(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::key, pkey, pobj)
   }

   void html_edit_view::pre_translate_message(::signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_KEYUP)
      {
         post_message(WM_USER, MessageUserCheckChange);
         return;
      }
      return html_view::pre_translate_message(pobj);
   }

   void html_edit_view::key_to_char(WPARAM wparam, LPARAM lparam)
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

   void html_edit_view::_001OnPost(::signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
         if(pbase->m_wparam == 100)
         {
            post_message(WM_APP + 80, 101);
         }
         else if (pbase->m_wparam == 101)
         {
         }
   }

   void html_edit_view::transform()
   {
      /* xxx
      devedgeApp * papp = dynamic_cast < devedgeApp * > (( (GetParentFrame()))->m_papp);
      POSITION posDoc = papp->m_ptemplate_devedge->get_document_count();
      sp(::aura::document) pdoc = (sp(::aura::document)) papp->m_ptemplate_devedge->get_document(posDoc);

      string strSourcePath = pdoc->get_path_name();
      string strDestPath = System.dir().time("html.html");
      string strSource = Application.file().as_string(strSourcePath);

      string strImgNns = Application.dir().matter("html_edit_nns.png");


      string strDest;
      int32_t iStart = 0;
      int32_t iPos = 0;
      int32_t iLastEnd = 0;
      if(strSource.Mid(0, 4) == "<?ss")
      {
      iLastEnd = strSource.find("?>", iPos);
      if(iLastEnd > 0)
      {
      iLastEnd += 2;
      strDest += strSource.Mid(iPos + 4, iLastEnd - iPos - 6);
      iStart = iLastEnd;
      }
      }
      while((iPos = strSource.find("<?ds", iStart)) >= 0)
      {
      if(iPos > iLastEnd)
      {
      strDest += strSource.Mid(iLastEnd, iPos - iLastEnd);
      }
      iLastEnd = strSource.find("?>", iPos);
      if(iLastEnd < 0)
      break;
      iLastEnd += 2;
      m_straScript.add(strSource.Mid(iPos + 4, iLastEnd - iPos - 6));
      string strFormat;
      strFormat.Format("<visual id=\"netnodescript.%d src=\"%s\" />", m_straScript.get_upper_bound(), strImgNns);
      strDest += strFormat;
      iStart = iLastEnd;
      }
      strDest += strSource.Mid(iStart);

      Application.file().put_contents(strDestPath, strDest);
      */

   }

   void html_edit_view::_001OnUser(::signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
         if(pbase->m_wparam == MessageUserCheckChange)
         {
         }
   }


   void html_edit_view::transform_back()
   {

      //   string strSourcePath = System.dir().time("html.html");
      //   SaveAs(strSourcePath);

      string strImgNns = Application.dir().matter("html_edit_nns.png");

      /* xxx
      devedgeApp * papp = dynamic_cast < devedgeApp * > (( (GetParentFrame()))->m_papp);
      POSITION posDoc = papp->m_ptemplate_devedge->get_document_count();
      sp(::aura::document) pdoc = (sp(::aura::document)) papp->m_ptemplate_devedge->get_document(posDoc);
      string strDestPath = pdoc->get_path_name();

      string str;
      GetDocumentHTML(str);

      for(int32_t i = 0; i < m_straScript.get_size(); i++)
      {
      string strFormat;
      strFormat.Format("<visual id=\"netnodescript.%d src=\"%s\" />", m_straScript.get_upper_bound(), strImgNns);
      str.replace(
      strFormat,
      m_straScript[i]);
      }

      Application.file().put_contents(strDestPath, str);

      */
   }



} // namespace devedge



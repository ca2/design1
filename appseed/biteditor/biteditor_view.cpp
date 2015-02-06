#include "framework.h"


namespace biteditor
{


   view::view(::aura::application * papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      m_mutexData(papp)
   {

      m_iSelStart       = 0;
      m_iSelEnd         = 0;
      m_iLineSize       = 16;
      m_iViewOffset     = 0;
      m_iViewSize       = 1000;


      m_pasciibox = new biteditor::ascii_box(papp);
      m_phexbox = new biteditor::hex_box(papp);
      m_pasciibox->m_pview = this;
      m_phexbox->m_pview = this;

   }

   view::~view()
   {
   }

   void view::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::scroll_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &view::_001OnHScroll);

      IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,
         this,
         this,
         &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,
         this,
         this,
         &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,
         this,
         this,
         &view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP,
         this,
         this,
         &view::_001OnRButtonUp);

   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::scroll_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::scroll_view::dump(dumpcontext);
   }
#endif //DEBUG



   bool view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::scroll_view::pre_create_window(cs);

   }


   void view::_001OnInitialUpdate(::signal_details * pobj)
   {
      ::user::scroll_view::_001OnInitialUpdate(pobj);

      m_pasciibox->on_update();
      m_phexbox->on_update();

      if(m_iLineHeight <= 0)
         return;


      ::draw2d::memory_graphics pdc(allocer());
      m_pasciibox->_001OnCalcLayout(this, pdc);
      m_phexbox->_001OnCalcLayout(this, pdc);

      size64 sizeTotal;
      sizeTotal.cx = m_pasciibox->m_size.cx + m_phexbox->m_size.cx + 200;
      sizeTotal.cy = m_iLineHeight * get_document()->m_pfile->get_length() / m_iLineSize + 200;
      size64 sizePage;
      rect rect;
      GetClientRect(rect);
      sizePage.cx = rect.width();
      sizePage.cy = rect.height() - rect.height() % m_iLineHeight - m_iLineHeight;
      size64 sizeLine;
      sizeLine.cx = sizeTotal.cx;
      sizeLine.cy = m_iLineHeight;
      m_scrollinfo.m_sizeTotal = sizeTotal;
      m_scrollinfo.m_sizePage = sizePage;
      m_scrollinfo. m_sizeLine = sizeLine;
      //SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

   }

   void view::on_update(::aura::impact * pSender, LPARAM lHint, ::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      if(lHint == 1001)
      {
         _001RedrawWindow();
      }
      else if(lHint == 789231)
      {
         m_pasciibox->m_bGetTextNeedUpdate = true;
         m_phexbox->m_bGetTextNeedUpdate = true;
      }
      else if(lHint == 789231)
      {
         m_iSelStart = get_document()->m_iSelStart;
         m_iSelEnd = get_document()->m_iSelEnd;
         _001RedrawWindow();
      }
      if(phint != NULL)
      {
         if(base_class <biteditor::pane_view_update_hint> ::bases(phint))
         {
            biteditor::pane_view_update_hint * puh = (biteditor::pane_view_update_hint * ) phint;
            if(puh->is_type_of(biteditor::pane_view_update_hint::TypeOnBeforeShowView))
            {
               //get_document()->on_save_document(get_document()->get_path_name());
            }
            else if(puh->is_type_of(biteditor::pane_view_update_hint::TypeOnShowView))
            {
               get_document()->reload();
            }
         }
      }

   }

   void view::_001OnDestroy(::signal_details * pobj)
   {
      ::user::scroll_view::_001OnDestroy(pobj);

   }



   void view::_001OnSize(::signal_details * pobj)
   {

      single_lock sl(&m_mutexData, true);

      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::size, psize, pobj)

      m_pasciibox->on_update();
      m_phexbox->on_update();



      //   sp(::aura::document) pdoc = get_document();
      ::draw2d::memory_graphics pdc(allocer());

      pdc->SelectObject(m_phexbox->m_spfont);
      size size1 = pdc->GetTextExtent("gqYALH");

      pdc->SelectObject(m_pasciibox->m_spfont);
      size size2 = pdc->GetTextExtent("gqYALH");




      m_iLineHeight = MAX(size1.cy, size2.cy);

      file_position iLineCount = MIN(m_iViewSize, get_document()->m_peditfile->get_length()) / m_iLineSize;

      iLineCount += 4;

      int32_t iHeight = (int32_t) (m_iLineHeight * iLineCount);

      class size sizeHex;
      class size sizeAsc;

      sizeHex.cx = (LONG) (m_iLineSize * 3 * size1.cx / 6 + 20);
      sizeAsc.cx = (LONG) (m_iLineSize * size2.cx / 6 + 20);
      sizeHex.cy = sizeAsc.cy = iHeight;

      m_phexbox->SetWindowPos(ZORDER_TOP, 10, 10, sizeHex.cx, sizeHex.cy, SWP_SHOWWINDOW);
      m_pasciibox->SetWindowPos(ZORDER_TOP, sizeHex.cx + 10 + 10, 10, sizeAsc.cx, sizeAsc.cy, SWP_SHOWWINDOW);



      /*   pobj->previous();

      double d = psize->m_size.cy;
      d /= GetSystemMetrics(SM_CYSCREEN);
      SetScale(d);

      GetClientRect(m_rectKaraokeView);


      rect rectClient;
      GetClientRect(rectClient);
      rect rect = rectClient;

      rect.top = rect.bottom - 24;
      m_viewlineStatus.SetPlacement(rect);


      m_rectKaraokeView.bottom -= 16;

      LayoutTitleLines();
      LayoutLyricTemplateLines();
      LayoutLyricLines();
      LayoutKaraokeBouncingBall();*/
   }

   void view::_001OnPaint(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   /*
   void view:: _001OnDraw(::draw2d::graphics * pdc)
   {
   // sp(::aura::document) pdoc = get_document();
   //   pdc->OffsetViewportOrg(-m_ptScroll.x, -(m_ptScroll.y % m_iLineHeight));

   ::draw2d::region rgn;

   rect rectClient;
   GetClientRect(rectClient);
   ClientToScreen(rectClient);
   rgn.create_rect(rectClient);

   pdc->SelectClipRgn(&rgn);

   m_pasciibox->_001OnDraw(this, pdc);
   m_phexbox->_001OnDraw(this, pdc);

   }
   */

   void view::_001OnCreate(::signal_details * pobj)
   {
      if(pobj->previous())
         return;



      m_pasciibox->create_window(null_rect(), this, "ascii_box");
      m_phexbox->create_window(null_rect(), this, "hex_box");


      SetTimer(100, 100, NULL);


      /*sp(::aura::document) pdoc = get_document();
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
   void view::_001OnContextMenu(::signal_details * pobj)
   {
      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
         point point = pcontextmenu->GetPoint();

   }


   void view::_001OnRButtonUp(::signal_details * pobj)
   {

      track_popup_xml_matter_menu("devedge_contextmenu.xml", 0, pobj);

   }




   void view::_001OnWavePlayerEvent(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::base, pbase, pobj)
   }

   void view::_001OnUpdateViewEncoding(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::update_cmd_ui, pupdatecmdui, pobj)
   }
   void view::_001OnViewEncoding(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::command, pcommand, pobj)
   }

   void view::_001OnSetCursor(::signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj)

      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();

   }

   void view::_001OnLButtonDown(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         point pt = pmouse->m_pt;
      //ScreenToClient(&pt);
   }

   void view::_001OnLButtonUp(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         point pt = pmouse->m_pt;
      //ScreenToClient(&pt);
      if(Session.user()->get_mouse_focus_LButtonDown() != NULL)
      {
         Session.user()->get_mouse_focus_LButtonDown()->mouse_focus_OnLButtonUp(pobj);
         Session.user()->set_mouse_focus_LButtonDown(NULL);
      }

      /*biteditor::Element2D * pelement = hit_test(pt.x, pt.y);
      if(pelement != NULL)
      {
      pelement->_001OnLButtonUp(this, pobj);
      }*/
   }

   void view::_001OnMouseMove(::signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         point pt = pmouse->m_pt;
      //ScreenToClient(&pt);

   }

   sp(::biteditor::document) view::get_document() const
   {
      return  (::user::scroll_view::get_document());
   }


   void view::_001OnTimer(::signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj)
         if(ptimer->m_nIDEvent >= 100
            && ptimer->m_nIDEvent <= 200)
         {
            if(Session.user()->get_keyboard_focus() == m_pasciibox)
            {
               m_pasciibox->_001OnKeyboardFocusTimer(this, ptimer->m_nIDEvent - 100);
            }
            else if(Session.user()->get_keyboard_focus() == m_phexbox)
            {
               m_phexbox->_001OnKeyboardFocusTimer(this, ptimer->m_nIDEvent - 100);
            }
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

   void view::_001OnKeyDown(::signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj)

         if(pkey->m_ekey == ::user::key_return)
         {
            if(Session.is_key_pressed(::user::key_control)
               && Session.is_key_pressed(::user::key_alt))
            {
               pkey->m_bRet = false;
               return;
            }
         }
         else if(pkey->m_nChar == ::user::key_alt)
         {
            pkey->m_bRet = false;
            return;
         }

         m_dwLastKeyWparam = (uint32_t) pkey->m_wparam;
         m_dwLastKeyLparam = (uint32_t) pkey->m_lparam;
         key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
         SetTimer(500, 500, NULL);
   }

   void view::_001OnKeyUp(::signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj)
         if(pkey->m_ekey == ::user::key_return)
         {
            if(Session.is_key_pressed(::user::key_control)
               && Session.is_key_pressed(::user::key_alt))
            {
               pkey->m_bRet = false;
               return;
            }
         }
         else if(pkey->m_ekey == ::user::key_return)
         {
            pkey->m_bRet = false;
         }
         KillTimer(500);
         KillTimer(501);
   }


   void view::_001OnChar(::signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj)
         if(pkey->m_ekey == ::user::key_s)
         {
            if(Session.is_key_pressed(::user::key_control))
            {
               return;
            }
         }
         if(Session.user()->get_keyboard_focus() == m_pasciibox)
         {
            //m_pasciibox->_001OnChar(this, pobj);
         }
         else if(Session.user()->get_keyboard_focus() == m_phexbox)
         {
            //m_phexbox->_001OnChar(this, pobj);
         }
   }


   void view::_001OnSysChar(::signal_details * pobj)
   {
      //   SCAST_PTR(::message::key, pkey, pobj)
      if(Session.user()->get_keyboard_focus() == m_pasciibox)
      {
         //m_pasciibox->_001OnSysChar(this, pobj);
      }
      else if(Session.user()->get_keyboard_focus() == m_phexbox)
      {
         //m_phexbox->_001OnSysChar(this, pobj);
      }
   }

   void view::_001OnHScroll(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_pasciibox->m_bGetTextNeedUpdate = true;
      m_phexbox->m_bGetTextNeedUpdate = true;
   }

   void view::pre_translate_message(::signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_KEYDOWN)
      {
         SCAST_PTR(::message::key, pkey, pobj);
         _001OnKeyDown(pkey);
         if(pkey->m_bRet)
            return;
      }
      else if(pbase->m_uiMessage == WM_KEYUP)
      {
         SCAST_PTR(::message::key, pkey, pobj);
         _001OnKeyUp(pkey);
         if(pkey->m_bRet)
            return;
      }
      ::user::scroll_view::pre_translate_message(pobj);
   }
   void view::key_to_char(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(lparam);
      ::message::key key(get_app());
      key.m_nChar = wparam;
      if(wparam == VK_LSHIFT || wparam == VK_RSHIFT
         || wparam == VK_LCONTROL || wparam == VK_RCONTROL
         || wparam == VK_LMENU || wparam == VK_RMENU
         || wparam == VK_SHIFT || wparam == VK_CONTROL
         || wparam == VK_MENU)
      {
         return;
      }

      if(wparam == VK_RIGHT || wparam == VK_UP
         || wparam == VK_LEFT || wparam == VK_DOWN)
      {
         _001OnChar(&key);
         return;
      }

      //   LRESULT lresult;
      bool bShift = Session.is_key_pressed(::user::key_shift);
      if(isalpha((int32_t) key.m_nChar))
      {
         if(bShift)
         {
            key.m_nChar = toupper((int32_t) key.m_nChar);
         }
         else
         {
            key.m_nChar = tolower((int32_t) key.m_nChar);
         }
      }
      _001OnChar(&key);
   }




   int64_t view::CalcLineCount()
   {
      file_position dwLength = get_document()->m_peditfile->get_length();
      int64_t iMod = dwLength % m_iLineSize;
      int64_t iLineCount = dwLength / m_iLineSize;
      if(iMod == 0)
         return iLineCount;
      else
         return iLineCount + 1;
   }


   int32_t view::UpdateScrollSizes()
   {
      m_scrollinfo.m_sizeTotal.cx = 1024;
      m_scrollinfo.m_sizeTotal.cy = m_pasciibox->m_size.cy;
      return 0;
   }

   void view::get_view_lines(stringa & straLines)
   {
      file_offset iOffset = (m_iViewOffset / m_iLineSize * m_iLineSize);

      get_document()->m_memfile.seek(iOffset, ::file::seek_begin);

      int64_t iLineCount = m_iViewSize / m_iLineSize;

      char sz[16];
      primitive::memory_size iRead;
      string strLine;
      for(int32_t i = 0; i < iLineCount; i++)
      {
         //      int32_t iCount;
         strLine.Empty();
         iRead = get_document()->m_memfile.read(sz, 16);
         for(primitive::memory_size i = 0; i < iRead; i++)
         {
            if(sz[i] == '\0')
            {
               strLine += '\xff';
            }
            else
            {
               strLine += sz[i];
            }
         }
         straLines.add(strLine);
         if(iRead <= 0)
            break;
      }

   }


   void view::_001GetSelText(string & str)
   {
      file_position iEnd;
      file_position iStart;
      if(m_iSelEnd < 0)
      {
         if(m_iSelStart < 0)
         {
            iEnd = (file_position) get_document()->m_peditfile->get_length();
            iStart = 0;
         }
         else
         {
            iStart = m_iSelStart;
            iEnd = (file_position) get_document()->m_peditfile->get_length();
         }
      }
      else
      {
         if(m_iSelStart < 0)
         {
            iEnd = m_iSelEnd;
            iStart = 0;
         }
         else
         {
            iEnd = m_iSelEnd;
            iStart = m_iSelStart;
         }
      }
      strsize iSize = (strsize) (iEnd - iStart);
      char * psz = str.GetBufferSetLength(iSize + 1);
      get_document()->m_peditfile->seek((file_offset) iStart, ::file::seek_begin);
      get_document()->m_peditfile->read(psz, iSize);
      psz[iSize] = '\0';
      str.ReleaseBuffer();
   }


   int32_t view::get_wheel_scroll_delta()
   {
      return m_iLineHeight;
   }

   index view::SelToLine(file_position iSel)
   {
      iSel -= m_iViewOffset;
      return (index) (iSel / m_iLineSize);
   }

   file_position view::LineColumnToSel(index iLine, index iColumn)
   {
//      int32_t i1;
//      int32_t i2 = 0;
      while(iLine < 0)
      {
         OneLineUp();
         if(m_iViewOffset == 0)
         {
            iLine = 0;
            break;
         }
         iLine++;
      }
      file_position iOffset = 0;
      for(int32_t i = 0; i < iLine; i++)
      {
         iOffset += m_iLineSize;
      }
            if(iColumn < 0)
         iColumn = (int32_t) (iColumn + 1 + m_iLineSize);
      if(iColumn > m_iLineSize)
         iColumn = (int32_t)m_iLineSize;
      return m_iViewOffset + iOffset + iColumn;
   }


   index view::SelToColumn(file_position iSel)
   {
      iSel -= m_iViewOffset;
      return (int32_t) (iSel % m_iLineSize);
   }


   void view::OneLineUp()
   {
      m_scrollinfo.m_ptScroll.y -= m_iLineHeight;
      if(m_scrollinfo.m_ptScroll.y < 0)
         m_scrollinfo.m_ptScroll.y = 0;
      int32_t iHeight = 0;
   //   char flag;
      m_iViewOffset = 0;
      int64_t iLineSize;
      int64_t i = 0;
      int64_t iLineCount = CalcLineCount();
      while(m_scrollinfo.m_ptScroll.y > iHeight && i < iLineCount)
      {
         iLineSize = m_iLineSize;
         iHeight += m_iLineHeight;
         m_iViewOffset += iLineSize;
         i++;
      }

   }

} // namespace biteditor



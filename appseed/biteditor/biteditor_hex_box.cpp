﻿#include "framework.h"


namespace biteditor
{


   hex_box::hex_box(::aura::application * papp) :
      ::object(papp),
      m_spfont(allocer())
   {

      m_spfont->create_point_font("Courier New", 10.0);

      m_bGetTextNeedUpdate = true;

      m_y = -1;
      m_bMouseDown = false;
      m_dwCaretTime = 500;
      m_dwLastCaret = GetTickCount();
   }

   hex_box::~hex_box()
   {
   }


   template <class T> void Sort( T & t1, T & t2)
   {
      if(t1 > t2)
      {
         T t = t2;
         t2 = t1;
         t1 = t;
      }
   }


   void hex_box::install_message_routing(::message::sender * psender)
   {

      ::user::interaction::install_message_routing(psender);

      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &hex_box::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &hex_box::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &hex_box::_001OnMouseMove);

   }


   void hex_box::_001OnDraw(::draw2d::graphics * pgraphics)
   {



      if(has_focus())
      {
         m_bFocus = true;
      }
      else
      {
         m_bFocus = false;
      }

      single_lock sl(&m_pview->m_mutexData, true);

      point ptOffset = get_viewport_offset();

      m_pview->m_iViewOffset = (ptOffset.y * m_pview->m_iLineSize / m_pview->m_iLineHeight);

      COLORREF crBk = ARGB(255, 120, 80, 110);
      COLORREF crBkSel = ARGB(255, 120, 240, 150);
      COLORREF crSel = ARGB(255, 10, 30, 20);
      COLORREF cr = ARGB(255, 255, 255, 255);

      rect rectClient;
      GetClientRect(rectClient);
      pgraphics->fill_solid_rect(rectClient, ARGB(255, 240, 255, 240));

      ::draw2d::region_sp rgn(allocer());

      rect rectClip(rectClient);

      //rect rectWindow;
      //GetWindowRect(rectWindow);
      //rectClip.offset(rectWindow.top_left());

      //rgn->create_rect(rectClip.left, rectClip.top, rectClip.width(), rectClip.height());



      //pgraphics->SelectClipRgn(rgn, RGN_COPY);


      file_position_t iSelStart;
      file_position_t iSelEnd;
      file_position_t lim = 0;


      cr = ARGB(255, 0, 0, 0);
      crBk = ARGB(255, 250, 248, 240);
      crBkSel = ARGB(255, 0, 0, 127);
      crSel = ARGB(255, 255, 255, 255);


      int32_t y = rectClient.top;
      _001GetViewSel(iSelStart, iSelEnd);
      file_position_t iCursor = iSelEnd;
      Sort(iSelStart, iSelEnd);
      pgraphics->SelectObject(m_spfont);
      size size3 = pgraphics->GetTextExtent("gqYALH");
      int32_t maxcy = size3.cy;
      file_position_t iLineStart = m_pview->m_iViewOffset / m_pview->m_iLineSize;
      file_position_t iLineEnd = (iLineStart * m_pview->m_iLineSize + m_pview->m_iViewSize) / m_pview->m_iLineSize + 1;

      iSelStart *= 3;
      iSelEnd *= 3;
      iSelEnd -= 1;


      string strLine;
      string str1;
      string str2;
      string str3;
      string strExtent1;
      string strExtent2;
      string strExtent3;



      pgraphics->OffsetViewportOrg(0, - ptOffset.y % m_pview->m_iLineHeight);


      for(file_position_t iLine = iLineStart; iLine <= iLineEnd; iLine++)
      {
         read_line(strLine, iLine);
         strLine.replace("\t", " ");
         stringa stra;
         strsize i1 = (int32_t) (iSelStart - lim);
         strsize i2 = (int32_t) (iSelEnd - lim);
         strsize i3 = (int32_t) (iCursor - lim);
         strsize iStart = MAX(0, i1);
         strsize iEnd = MAX(MIN(i2, strLine.get_length()), iStart);
         str1 = strLine.Mid(0, iStart);
         str2 = strLine.Mid(iStart, iEnd - iStart);
         str3 = strLine.Mid(iEnd);
         strExtent1 = str1;
         strExtent2 = str2;
         strExtent3 = str3;
//         pgraphics->SetBkMode(TRANSPARENT);
         pgraphics->set_text_color(cr);
//         pgraphics->SetBkColor(crBkSel);
         pgraphics->text_out(rectClient.left, y, strExtent1);
         size size1 = pgraphics->GetTextExtent(strExtent1);
//         pgraphics->SetBkMode(OPAQUE);
         size size2 = pgraphics->GetTextExtent(strExtent2);
         pgraphics->fill_solid_rect_dim(rectClient.left + size1.cx, y, size2.cx, size2.cy,crBkSel);
         pgraphics->set_text_color(crSel);
         pgraphics->text_out(rectClient.left + size1.cx, y, strExtent2);
         pgraphics->set_text_color(cr);
//         pgraphics->SetBkColor(ARGB(255, 120, 240, 180));
//         pgraphics->SetBkMode(TRANSPARENT);
         size sizeExt3 = pgraphics->GetTextExtent(strExtent1 + strExtent2);
         pgraphics->text_out(rectClient.left + sizeExt3.cx, y, strExtent3);
         maxcy = MAX(size1.cy, size2.cy);
         maxcy = MAX(maxcy, size3.cy);
         if(m_bFocus && m_bCaretOn && i3 == str1.get_length())
         {
            pgraphics->move_to(rectClient.left + size1.cx, y);
            pgraphics->line_to(rectClient.left + size1.cx, y + maxcy);
         }
         if(m_bFocus && m_bCaretOn && i3 == (str1.get_length() + str2.get_length()))
         {
            pgraphics->move_to(rectClient.left + size1.cx + size2.cx, y);
            pgraphics->line_to(rectClient.left + size1.cx + size2.cx, y + maxcy);
         }
         y += maxcy;
         lim += m_pview->m_iLineSize * 3;
      }
   }

   void hex_box::_001GetSelText(string & str)
   {
      file_position_t iEnd;
      file_position_t iStart;
      if(m_pview->m_iSelEnd < 0)
      {
         if(m_pview->m_iSelStart < 0)
         {
            iEnd = (file_position_t) m_pview->get_document()->m_peditfile->get_length();
            iStart = 0;
         }
         else
         {
            iStart = m_pview->m_iSelStart;
            iEnd = (file_position_t) m_pview->get_document()->m_peditfile->get_length();
         }
      }
      else
      {
         if(m_pview->m_iSelStart < 0)
         {
            iEnd = m_pview->m_iSelEnd;
            iStart = 0;
         }
         else
         {
            iEnd = m_pview->m_iSelEnd;
            iStart = m_pview->m_iSelStart;
         }
      }
      strsize iSize = (strsize) (iEnd - iStart);
      char * psz = str.GetBufferSetLength(iSize + 1);
      m_pview->get_document()->m_peditfile->seek((file_offset_t) iStart, ::file::seek_begin);
      m_pview->get_document()->m_peditfile->read(psz, iSize);
      psz[iSize] = '\0';
      str.ReleaseBuffer();
   }

   void hex_box::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      m_bMouseDown = true;

      ::draw2d::memory_graphics pgraphics(allocer());

      point pt = pmouse->m_pt;
      ScreenToClient(&pt);

      m_pview->m_iSelStart = char_hit_test(m_pview, pgraphics, pt.x, pt.y, true);
      m_pview->m_iSelEnd = m_pview->m_iSelStart;

      m_pview->set_need_redraw();
      Session.set_keyboard_focus(this);
      Session.user()->set_mouse_focus_LButtonDown(this);
      pobj->m_bRet = true;

   }
   void hex_box::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      ::draw2d::memory_graphics pgraphics(allocer());

      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      m_pview->m_iSelEnd = char_hit_test(m_pview, pgraphics, pt.x, pt.y, false);
      m_pview->m_iColumn = m_pview->SelToColumn(m_pview->m_iSelEnd);

      m_pview->set_need_redraw();
      m_bMouseDown = false;
      pobj->m_bRet = true;
      //System.simple_message_box(m_strText);
   }

   void hex_box::_001OnCalcLayoutProc(sp(view) pview, ::draw2d::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pview);
      pgraphics->SelectObject(m_spfont);
      int64_t y = 0;
      //int32_t i = 1;
//      char buf[4096 + 1];
//      uint32_t uiRead;
//      LPTSTR lpsz;
      m_pview->get_document()->m_peditfile->seek(0, ::file::seek_begin);
      if(m_size.cx <= 0)
         m_size.cx = 200;
      y = m_pview->m_iLineHeight * m_pview->CalcLineCount();
      if(y <= 0)
         y = 200;
      m_size.cy = (LONG) y;
      size size3 = pgraphics->GetTextExtent("gqYAL�pd");
      m_size.cx = (LONG) (size3.cx * m_pview->m_iLineSize * 3 / 8 );
      m_pview->UpdateScrollSizes();
   }

   void hex_box::_001OnCalcLayout(sp(view) pview, ::draw2d::graphics * pgraphics)
   {

      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pgraphics);


      /*pgraphics->SelectObject(m_spfont);
      string str;
      _001GetViewText(pview, str);
      stringa & straLines = m_straLines;
      file_position_t iSelStart;
      file_position_t iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
      //      int32_t lim = 0;
      int32_t maxcy;
      int32_t y = 0;
      //      bool bFound = false;
      string strLine;
      size size3 = pgraphics->GetTextExtent("gqYAL�WM");
      size size;
      m_size.cx = 0;
      for(int32_t i = 0; i < straLines.get_size(); i++)
      {
         strLine = straLines[i];
         strLine.replace("\t", "   ");
         size = strLine.get_length() * size3.cx / 8;
         maxcy = MAX(size.cy, size3.cy);
         y += maxcy;
         if(size.cx > m_size.cx)
            m_size.cx = size.cx;

      }
      m_size.cy = y;*/
   }


   file_position_t hex_box::char_hit_test(sp(view) pview, ::draw2d::graphics * pgraphics, int32_t px, int32_t py, bool bSelBeg)
   {

      pgraphics->SelectObject(m_spfont);

      point ptOffset = m_pview->get_viewport_offset();

      py += ptOffset.y % m_pview->m_iLineHeight;

      file_position_t iSelStart;
      file_position_t iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
      int32_t lim = 0;
      int32_t maxcy;
      rect rectClient;
      GetClientRect(rectClient);
      int32_t y = rectClient.top;
      bool bFound = false;
      string strLine;
      string strExtent;
      file_position_t iOffset = 0;
      file_position_t iLineStart = m_pview->m_iViewOffset / m_pview->m_iLineSize;
      file_position_t iLineEnd = (iLineStart * m_pview->m_iLineSize + m_pview->m_iViewSize) / m_pview->m_iLineSize + 1;

      string strExtent3;
      file_position_t iLine;
      for(iLine = iLineStart; iLine <= iLineEnd; iLine++)
      {
         maxcy = m_pview->m_iLineHeight;
         if(py >= y && py < y + maxcy)
         {
            bFound = true;
            break;
         }
         y += m_pview->m_iLineHeight;
         iOffset += m_pview->m_iLineSize;
      }
      int32_t lim2 = 0;
      int32_t lim1 = 0;
      int32_t j = 0;
      read_line(strLine, iLine);
      for(int32_t i = 0; i < strLine.get_length(); i+=3)
      {
         lim = lim1;
         lim1 = pgraphics->GetTextExtent(strLine.Mid(0, i)).cx;
         lim2 = pgraphics->GetTextExtent(strLine.Mid(0, i + 2)).cx;
         if(px >= lim && px <= lim1)
         {
            return iOffset+ j + m_pview->m_iViewOffset;
         }
         else if(px >= lim1 && px <= lim2)
         {
            if(m_pview->m_iSelStart > (iOffset+ j - 1 + m_pview->m_iViewOffset))
            {
               return iOffset+ j + m_pview->m_iViewOffset;
            }
            else
            {
               return iOffset+ j + 1 + m_pview->m_iViewOffset;
            }
         }
         /*else if(px >= lim && px <= lim2)
         {
            return iOffset + j + 1 + m_pview->m_iViewOffset;
         }*/
         j++;
      }
      return iOffset + strLine.get_length() + m_pview->m_iViewOffset;
   }

   void hex_box::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      //pmouse->m_ecursor = ::visual::cursor_text_select;


      if(m_bMouseDown)
      {

         single_lock sl(&m_pview->m_mutexData, true);

         ::draw2d::memory_graphics pgraphics(allocer());

         point pt = pmouse->m_pt;
         ScreenToClient(&pt);

         m_pview->m_iSelEnd = char_hit_test(m_pview, pgraphics, pt.x, pt.y, false);

         m_pview->set_need_redraw();
      }

      pmouse->m_ecursor = ::visual::cursor_text_select;

   }


   void hex_box::read_line(string & str, file_position_t iLine)
   {

      str.Empty();

      m_pview->get_document()->m_peditfile->seek(iLine * m_pview->m_iLineSize, ::file::seek_begin);

      memory_size_t iRead = m_pview->get_document()->m_peditfile->read(m_pchLineBuffer, (memory_size_t) m_pview->m_iLineSize);

      if(iRead <= 0)
         return;

      string strHex;

      uint32_t dw = m_pchLineBuffer[0] & 0x000000ff;

      str.Format("%02x", dw);

      for(memory_size_t i = 1; i < iRead; i++)
      {

         dw = m_pchLineBuffer[i] & 0x000000ff;

         strHex.Format(" %02x", dw);

         str += strHex;

      }

   }


   void hex_box::_001GetViewSel(file_position_t &iSelStart, file_position_t &iSelEnd)
   {
      iSelStart = m_pview->m_iSelStart - m_pview->m_iViewOffset;
      iSelEnd = m_pview->m_iSelEnd - m_pview->m_iViewOffset;
   }

   void hex_box::SetFile(sp(::file::file) pfile)
   {
      m_pview->get_document()->m_peditfile->SetFile(pfile);
      OnFileUpdate();
   }

   void hex_box::OnFileUpdate()
   {
      m_bGetTextNeedUpdate = true;
      m_y = -1;
   }


   void hex_box::_001OnChar(::message::message * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
      bool bShift = Session.is_key_pressed(::user::key_shift);

      if(pkey->m_ekey == ::user::key_back)
      {
         file_position_t i1 = m_pview->m_iSelStart;
         file_position_t i2 = m_pview->m_iSelEnd;
         if(i1 != i2)
         {

            sp(::biteditor::document) pdoc = m_pview->get_document();

            document::SetSelCommand * psetsel = new document::SetSelCommand;

            psetsel->m_iPreviousSelStart = m_pview->m_iSelStart;

            psetsel->m_iPreviousSelEnd = m_pview->m_iSelEnd;

            Sort(i1, i2);

            m_pview->get_document()->m_peditfile->seek((file_offset_t) i1, ::file::seek_begin);

            m_pview->get_document()->m_peditfile->Delete((memory_size_t) (i2 - i1));

            IndexRegisterDelete(i1, i2 - i1);

            m_pview->m_iSelEnd = i1;
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
            psetsel->m_iSelStart = m_pview->m_iSelStart;
            psetsel->m_iSelEnd = m_pview->m_iSelEnd;
            pdoc->MacroBegin();
            pdoc->MacroRecord(psetsel);
            pdoc->MacroRecord(new document::FileCommand());
            pdoc->MacroEnd();
            on_update();
         }
         else if(m_pview->m_iSelEnd >= 0 && m_pview->get_document()->m_peditfile->get_length() > 0)
         {
            sp(::biteditor::document) pdoc = m_pview->get_document();
            document::SetSelCommand * psetsel = new document::SetSelCommand;
            psetsel->m_iPreviousSelStart = m_pview->m_iSelStart;
            psetsel->m_iPreviousSelEnd = m_pview->m_iSelEnd;
            m_pview->m_iSelEnd--;
            m_pview->get_document()->m_peditfile->seek((file_offset_t) m_pview->m_iSelEnd, ::file::seek_begin);
            m_pview->get_document()->m_peditfile->Delete((memory_size_t) 1);
            IndexRegisterDelete(m_pview->m_iSelEnd, 1);
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
            psetsel->m_iSelStart = m_pview->m_iSelStart;
            psetsel->m_iSelEnd = m_pview->m_iSelEnd;
            pdoc->MacroBegin();
            pdoc->MacroRecord(psetsel);
            pdoc->MacroRecord(new document::FileCommand());
            pdoc->MacroEnd();
            on_update();
         }
      }
      else if(pkey->m_ekey == ::user::key_up)
      {
         index iLine = m_pview->SelToLine(m_pview->m_iSelEnd);
         iLine--;
         m_pview->m_iSelEnd = m_pview->LineColumnToSel(iLine, m_pview->m_iColumn);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         m_pview->set_need_redraw();
      }
      else if(pkey->m_ekey == ::user::key_down)
      {
         index iLine = m_pview->SelToLine(m_pview->m_iSelEnd);
         iLine++;
         m_pview->m_iSelEnd = m_pview->LineColumnToSel(iLine, m_pview->m_iColumn);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         m_pview->set_need_redraw();
      }
      else if(pkey->m_ekey == ::user::key_right)
      {
         if(!bShift && m_pview->m_iSelStart > m_pview->m_iSelEnd)
         {
            m_pview->m_iSelEnd = m_pview->m_iSelStart;
         }
         else if(!bShift && m_pview->m_iSelEnd > m_pview->m_iSelStart)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         else if(natural(m_pview->m_iSelEnd) < m_pview->get_document()->m_peditfile->get_length())
         {

            char buf[2];

            m_pview->get_document()->m_peditfile->seek((file_offset_t) m_pview->m_iSelEnd, ::file::seek_begin);

            memory_size_t uiRead = m_pview->get_document()->m_peditfile->read(buf, 2);

            if(uiRead == 2 && buf[0] == '\r' && buf[1] == '\n')
            {
               m_pview->m_iSelEnd += 2;
            }
            else
            {
               m_pview->m_iSelEnd ++;
            }
            if(!bShift)
            {
               m_pview->m_iSelStart = m_pview->m_iSelEnd;
            }
         }
         m_pview->set_need_redraw();
      }
      else if(pkey->m_ekey == ::user::key_left)
      {
         if(!bShift && m_pview->m_iSelStart < m_pview->m_iSelEnd)
         {
            m_pview->m_iSelEnd = m_pview->m_iSelStart;
         }
         else if(!bShift && m_pview->m_iSelEnd < m_pview->m_iSelStart)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         else if(m_pview->m_iSelEnd > 0)
         {
            if(m_pview->m_iSelEnd > 2)
            {

               char buf[2];

               m_pview->get_document()->m_peditfile->seek(m_pview->m_iSelEnd - 2, ::file::seek_begin);

               memory_size_t uiRead = m_pview->get_document()->m_peditfile->read(buf, 2);

               if(uiRead == 2 && buf[0] == '\r' && buf[1] == '\n')
               {

                  m_pview->m_iSelEnd -= 2;

               }
               else
               {

                  m_pview->m_iSelEnd --;

               }

            }
            else
            {
               m_pview->m_iSelEnd--;
            }
            if(!bShift)
            {
               m_pview->m_iSelStart = m_pview->m_iSelEnd;
            }
         }
         m_pview->set_need_redraw();
      }
      else if(pkey->m_ekey == ::user::key_home)
      {
         index iLine = m_pview->SelToLine(m_pview->m_iSelEnd);
         m_pview->m_iSelEnd = m_pview->LineColumnToSel(iLine, 0);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         m_pview->set_need_redraw();
      }
      else if(pkey->m_ekey == ::user::key_end)
      {
         index iLine = m_pview->SelToLine(m_pview->m_iSelEnd);
         m_pview->m_iSelEnd = m_pview->LineColumnToSel(iLine, -1);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         m_pview->set_need_redraw();
      }
      else
      {
         if(pkey->m_ekey == ::user::key_return)
         {
            // Kill Focus => Kill Key Repeat Timer
            //System.simple_message_box("VK_RETURN reached hex_box");
         }
         sp(::biteditor::document) pdoc = m_pview->get_document();
         document::SetSelCommand * psetsel = new document::SetSelCommand;
         psetsel->m_iPreviousSelStart = m_pview->m_iSelStart;
         psetsel->m_iPreviousSelEnd = m_pview->m_iSelEnd;
         m_pview->get_document()->m_peditfile->MacroBegin();
         file_position_t i1 = m_pview->m_iSelStart;
         file_position_t i2 = m_pview->m_iSelEnd;
         Sort(i1, i2);
         m_pview->get_document()->m_peditfile->seek((file_offset_t) i1, ::file::seek_begin);
         m_pview->get_document()->m_peditfile->Delete((memory_size_t) (i2 - i1));
         IndexRegisterDelete(i1, i2 - i1);
         m_pview->m_iSelEnd = i1;
         m_pview->get_document()->m_peditfile->seek((file_offset_t) m_pview->m_iSelEnd, ::file::seek_begin);
         m_pview->m_iSelEnd++;
         m_pview->m_iSelStart = m_pview->m_iSelEnd;
         string str;
         char ch = (char) pkey->m_nChar;
         int32_t iChar =(int32_t) pkey->m_nChar;
         if(bShift)
         {
            iChar |= 0x80000000;
         }
//         int32_t i;
         str = ch;
         m_pview->get_document()->m_peditfile->Insert(&ch, 1);
         IndexRegisterInsert(m_pview->m_iSelEnd, str);
         m_pview->get_document()->m_peditfile->MacroEnd();
         psetsel->m_iSelStart = m_pview->m_iSelStart;
         psetsel->m_iSelEnd = m_pview->m_iSelEnd;
         pdoc->MacroBegin();
         pdoc->MacroRecord(psetsel);
         pdoc->MacroRecord(new document::FileCommand());
         pdoc->MacroEnd();
         on_update();
      }
      if(pkey->m_ekey != ::user::key_up
            && pkey->m_ekey != ::user::key_down)
      {
         m_pview->m_iColumn = m_pview->SelToColumn(m_pview->m_iSelEnd);
      }
      m_dwLastCaret = ::GetTickCount();
      m_bCaretOn = true;
      m_pview->set_need_redraw();
   }

   void hex_box::_001OnSysChar(::message::message * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
      if(pkey->m_ekey == ::user::key_delete)
      {
         file_position_t i1 = m_pview->m_iSelStart;
         file_position_t i2 = m_pview->m_iSelEnd;
         if(i1 != i2)
         {
            Sort(i1, i2);
            m_pview->get_document()->m_peditfile->seek((file_offset_t) i1, ::file::seek_begin);
            m_pview->get_document()->m_peditfile->Delete((memory_size_t) (i2 - i1));
            m_pview->m_iSelEnd = i1;
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         else if(natural(m_pview->m_iSelEnd) < m_pview->get_document()->m_peditfile->get_length())
         {
            m_pview->get_document()->m_peditfile->seek((file_offset_t) m_pview->m_iSelEnd, ::file::seek_begin);
            m_pview->get_document()->m_peditfile->Delete((memory_size_t) 1);
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
      }
   }


   void hex_box::_001OnKeyboardFocusTimer(sp(view) pview, int32_t iTimer)
   {
      if(iTimer == 0)
      {
         if(m_dwLastCaret + m_dwCaretTime < GetTickCount())
         {
            m_dwLastCaret = GetTickCount();
            m_bCaretOn = !m_bCaretOn;
            m_pview->set_need_redraw();
         }
      }
   }


   void hex_box::IndexRegisterDelete(file_position_t iSel, file_size_t iCount)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(iCount);
   }

   void hex_box::IndexRegisterInsert(file_position_t iSel, const char * lpcszWhat)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(lpcszWhat);
   }

   void hex_box::on_update()
   {
      m_bGetTextNeedUpdate = 1;
      m_y = -1;
      m_pchLineBuffer = new char[(int32_t) m_pview->m_iLineSize];
   }


} // namespace biteditor




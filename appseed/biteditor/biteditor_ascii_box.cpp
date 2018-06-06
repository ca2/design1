#include "framework.h"


namespace biteditor
{


   ascii_box::ascii_box(::aura::application * papp) :
      ::object(papp),
      m_spfont(allocer())
   {

      m_spfont->create_point_font("Lucida Console", 10);

      m_bGetTextNeedUpdate = true;


      m_y = -1;
      m_bMouseDown = false;
      m_dwCaretTime = 500;
      m_dwLastCaret = GetTickCount();
   }

   void ascii_box::install_message_routing(::message::sender * psender)
   {

      ::user::interaction::install_message_routing(psender);

      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &::biteditor::ascii_box::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &::biteditor::ascii_box::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &::biteditor::ascii_box::_001OnMouseMove);
      IGUI_MSG_LINK(WM_CHAR, psender, this, &::biteditor::ascii_box::_001OnChar);
      IGUI_MSG_LINK(WM_SYSCHAR, psender, this, &::biteditor::ascii_box::_001OnSysChar);

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


   void ascii_box::_001OnDraw(::draw2d::graphics * pgraphics)
   {



      if(m_pview == NULL || m_pview->get_document() == NULL)
         return;

      single_lock sl(&m_pview->m_mutexData, true);

      point ptOffset = get_viewport_offset();

      m_pview->m_iViewOffset = (ptOffset.y * m_pview->m_iLineSize / m_pview->m_iLineHeight);

      //if(m_pview->get_document()->get_data()->is_in_use())
      // return;

      rect rectClient;

      GetClientRect(rectClient);
      m_pt.x = 0;
      m_pt.y = 0;

      COLORREF crBk = ARGB(255, 120, 80, 110);
      COLORREF crBkSel = ARGB(255, 120, 240, 150);
      COLORREF crSel = ARGB(255, 10, 30, 20);
      COLORREF cr = ARGB(255, 0, 0, 0);

      pgraphics->fill_solid_rect(rectClient, ARGB(255, 240, 255, 240));

      ::draw2d::region_sp rgn(allocer());

      rect rectClip(rectClient);

      //rect rectWindow;
      //GetWindowRect(rectWindow);
      //rectClip.offset(rectWindow.top_left());

      //rgn->create_rect(rectClip.left, rectClip.top, rectClip.width(), rectClip.height());



      //pgraphics->SelectClipRgn(rgn, RGN_COPY);
      if(Session.get_keyboard_focus() == (elemental *) this)
      {
         m_bFocus = true;
      }
      else
      {
         m_bFocus = false;
      }
      string str;

      file_position_t iSelStart;
      file_position_t iSelEnd;
      file_position_t lim = 0;


      cr = ARGB(255, 0, 0, 0);
      crBk = ARGB(255, 250, 248, 240);
      crBkSel = ARGB(255, 0, 0, 127);
      crSel = ARGB(255, 255, 255, 255);


      /*rectClient.top = m_pt.y;
      rectClient.left = m_pt.x;
      rectClient.bottom = rectClient.top + m_size.cy;
      rectClient.right = rectClient.left + m_size.cx;*/
      ///pgraphics->FillSolidRect(rectClient, crBk);


      int32_t y = m_pt.y;
      _001GetViewSel(iSelStart, iSelEnd);
      file_position_t iCursor = iSelEnd;
      Sort(iSelStart, iSelEnd);
      pgraphics->SelectObject(m_spfont);
      int32_t maxcy = m_pview->m_iLineHeight;



      file_position_t iLineStart = m_pview->m_iViewOffset / m_pview->m_iLineSize;
      file_position_t iLineEnd = (iLineStart * m_pview->m_iLineSize + m_pview->m_iViewSize) / m_pview->m_iLineSize + 1;

//      point ptOffset = get_viewport_offset();

      pgraphics->OffsetViewportOrg(0, - ptOffset.y % m_pview->m_iLineHeight);

      string strLine;
      string str1;
      string str2;
      string str3;
      string strExtent1;
      string strExtent2;
      string strExtent3;
      for(file_position_t iLine = iLineStart; iLine <= iLineEnd; iLine++)
      {
         read_line(strLine, iLine);
         stringa stra;
         strsize i1 = (strsize) (iSelStart - lim);
         strsize i2 = (strsize) (iSelEnd - lim);
         strsize i3 = (strsize) (iCursor - lim);
         strsize iStart = MAX(0, i1);
         strsize iEnd = MAX(MIN(i2, strLine.get_length()), iStart);
         str1 = strLine.utf8_substr(0, iStart);
         str2 = strLine.utf8_substr(iStart, iEnd - iStart);
         str3 = strLine.utf8_substr(iEnd);
         strExtent1 = str1;
         strExtent2 = str2;
         strExtent3 = str3;
//         pgraphics->SetBkMode(TRANSPARENT);
         pgraphics->set_text_color(cr);
//         pgraphics->SetBkColor(crBkSel);
         pgraphics->text_out(m_pt.x, y, strExtent1);
         size size1 = pgraphics->GetTextExtent(strExtent1);
//         pgraphics->SetBkMode(OPAQUE);
         size size2 = pgraphics->GetTextExtent(strExtent2);
         pgraphics->fill_solid_rect_dim(rectClient.left + size1.cx, y, size2.cx, m_pview->m_iLineHeight,crBkSel);
         pgraphics->set_text_color(crSel);
         pgraphics->text_out(m_pt.x + size1.cx, y, strExtent2);
         pgraphics->set_text_color(cr);
//         pgraphics->SetBkColor(ARGB(255, 120, 240, 180));
//         pgraphics->SetBkMode(TRANSPARENT);
         pgraphics->text_out(m_pt.x + size1.cx + size2.cx, y, strExtent3);

         maxcy = m_pview->m_iLineHeight;
         if(m_bFocus && m_bCaretOn && i3 == str1.get_length())
         {
            pgraphics->move_to(m_pt.x + size1.cx, y);
            pgraphics->line_to(m_pt.x + size1.cx, y + maxcy);
         }
         if(m_bFocus && m_bCaretOn && i3 == (str1.get_length() + str2.get_length()))
         {
            pgraphics->move_to(m_pt.x + size1.cx + size2.cx, y);
            pgraphics->line_to(m_pt.x + size1.cx + size2.cx, y + maxcy);
         }

         y += m_pview->m_iLineHeight;

         lim += m_pview->m_iLineSize;

      }
   }


   void ascii_box::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      m_bMouseDown = true;

      ::draw2d::memory_graphics pgraphics(allocer());

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      m_pview->m_iSelStart = char_hit_test(m_pview, pgraphics, pt.x, pt.y);

      m_pview->m_iSelEnd = m_pview->m_iSelStart;

      m_pview->RedrawWindow();

      Session.user()->set_mouse_focus_LButtonDown(this);

      Session.set_keyboard_focus(this);

      if(m_pview->m_iSelStart >= 0)
      {

         pobj->m_bRet = true;

      }

   }


   void ascii_box::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      ::draw2d::memory_graphics pgraphics(allocer());

      point pt = pmouse->m_pt;
      ScreenToClient(&pt);


      m_pview->m_iSelEnd = char_hit_test(m_pview, pgraphics, pt.x, pt.y);
      m_pview->m_iColumn = m_pview->SelToColumn(m_pview->m_iSelEnd);
      m_pview->RedrawWindow();
      m_bMouseDown = false;
      if(m_pview->m_iSelEnd >= 0)
      {
         pobj->m_bRet = true;
      }
   }

   void ascii_box::_001OnCalcLayoutProc(sp(view) pview, ::draw2d::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pgraphics);
      /*UNREFERENCED_PARAMETER(pview);
      pgraphics->SelectObject(m_spfont);
      int64_t y = 0;
      //int32_t i = 1;
      //   char buf[4096 + 1];
      ///   uint32_t uiRead;
      //   LPTSTR lpsz;
      ::file::edit_file * peditfile = get_document()->m_peditfile;
      peditfile->seek(0, ::file::seek_begin);
      if(m_size.cx <= 0)
         m_size.cx = 200;
      y = m_pview->m_iLineHeight * peditfile->get_length() / m_pview->m_iLineSize;
      if(y <= 0)
         y = 200;
      m_size.cy = (long) y;
      size size3 = pgraphics->GetTextExtent("gqYAL�pd");
      m_size.cx = size3.cx * m_pview->m_iLineSize / 8;
      m_pview->UpdateScrollSizes();*/
   }

   void ascii_box::_001OnCalcLayout(sp(view) pview, ::draw2d::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pgraphics);
      /*
      pgraphics->SelectObject(m_spfont);
      string str;
      _001GetViewText(pview, str);
      stringa & straLines = m_straLines;
      file_position_t iSelStart;
      file_position_t iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
      //   int32_t lim = 0;
      int32_t maxcy;
      int32_t y = 0;
      //   bool bFound = false;
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



   file_position_t ascii_box::char_hit_test(sp(view) pview, ::draw2d::graphics * pgraphics, int32_t px, int32_t py)
   {
      single_lock sl(&m_pview->m_mutexData, true);
      pgraphics->SelectObject(m_spfont);
      point ptOffset = get_viewport_offset();
      py += ptOffset.y % m_pview->m_iLineHeight;
      file_position_t iSelStart;
      file_position_t iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
      int32_t lim = 0;
      int32_t maxcy;
      int32_t y = m_pt.y;
      bool bFound = false;
      string strLine;
      string strExtent;
      size size3 = pgraphics->GetTextExtent("gqYAL�");
      file_position_t iOffset = 0;
      file_position_t iLineStart = m_pview->m_iViewOffset / m_pview->m_iLineSize;
      file_position_t iLineEnd = (iLineStart * m_pview->m_iLineSize + m_pview->m_iViewSize) / m_pview->m_iLineSize + 1;

      string strExtent3;
      for(file_position_t iLine = iLineStart; iLine <= iLineEnd; iLine++)
      {
         read_line(strLine, iLine);
         strExtent = strLine;
         strExtent.replace("\t", " ");
         size size = pgraphics->GetTextExtent(strExtent);
         maxcy = m_pview->m_iLineHeight;
         if(py >= y && py < y + m_pview->m_iLineHeight)
         {
            bFound = true;
            break;
         }
         y += m_pview->m_iLineHeight;
         iOffset += m_pview->m_iLineSize;
      }
      int32_t lim2 = 0;
      int32_t lim1;
      for(int32_t i = 0; i < strLine.get_length(); i++)
      {
         lim1 = lim2;
         strExtent = strLine.Mid(0, i + 1);
         strExtent.replace("\t", " ");
         lim2 = pgraphics->GetTextExtent(strExtent).cx;
         lim = (lim2 + lim1) / 2;
         if(px >= lim1 && px <= lim)
         {
            return (int32_t) (iOffset+ i + m_pview->m_iViewOffset);
         }
         else if(px >= lim && px <= lim2)
         {
            return (int32_t) (iOffset + i + 1 + m_pview->m_iViewOffset);
         }
      }
      return (int32_t)(iOffset + strLine.get_length() + m_pview->m_iViewOffset);
   }

   void ascii_box::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_text_select;


      if(m_bMouseDown)
      {

         single_lock sl(&m_pview->m_mutexData, true);

         ::draw2d::memory_graphics pgraphics(allocer());

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         m_pview->m_iSelEnd = char_hit_test(m_pview, pgraphics, pt.x, pt.y);

         m_pview->RedrawWindow();

      }

   }


   void ascii_box::read_line(string & str, int64_t iLine)
   {

      str.Empty();

      m_pview->get_document()->m_peditfile->seek(iLine * m_pview->m_iLineSize, ::file::seek_begin);

      memory_size_t iRead = m_pview->get_document()->m_peditfile->read(m_pchLineBuffer, (memory_size_t) m_pview->m_iLineSize);

      string strChar;

      WCHAR sz[2];

      for(memory_size_t i = 0; i < iRead; i++)
      {

         char ch = m_pchLineBuffer[i];

         if(ch < 0)
         {
            WCHAR table[] =
            {
               0x20AC,0x0081,0x201A,0x0192,0x201E,0x2026,0x2020,0x2021, //128-135
               0x02C6,0x2030,0x0160,0x2039,0x0152,0x008D,0x017D,0x008F,//135-143
               0x0090,0x2018,0x2019,0x201C,0x201D,0x2022,0x2013,0x2014,//144-151
               0x02DC,0x2122,0x0161,0x203A,0x0153,0x009D,0x017E,0x0178,//152-159
               0x00A0,0x00A1,0x00A2,0x00A3,0x00A4,0x00A5,0x00A6,0x00A7,//160-167
               0x00A8,0x00A9,0x00AA,0x00AB,0x00AC,0x00AD,0x00AE,0x00AF,//168-175
               0x00B0,0x00B1,0x00B2,0x00B3,0x00B4,0x00B5,0x00B6,0x00B7,//176-183
               0x00B8,0x00B9,0x00BA,0x00BB,0x00BC,0x00BD,0x00BE,0x00BF,//184-191
               0x00C0,0x00C1,0x00C2,0x00C3,0x00C4,0x00C5,0x00C6,0x00C7,//192-199
               0x00C8,0x00C9,0x00CA,0x00CB,0x00CC,0x00CD,0x00CE,0x00CF,//200-207
               0x00D0,0x00D1,0x00D2,0x00D3,0x00D4,0x00D5,0x00D6,0x00D7,//208-215
               0x00D8,0x00D9,0x00DA,0x00DB,0x00DC,0x00DD,0x00DE,0x00DF,//216-223
               0x00E0,0x00E1,0x00E2,0x00E3,0x00E4,0x00E5,0x00E6,0x00E7,//224
               0x00E8,0x00E9,0x00EA,0x00EB,0x00EC,0x00ED,0x00EE,0x00EF,
               0x00F0,0x00F1,0x00F2,0x00F3,0x00F4,0x00F5,0x00F6,0x00F7,
               0x00F8,0x00F9,0x00FA,0x00FB,0x00FC,0x00FD,0x00FE,0x00FF
            };

            sz[0] = table[ch + 0x80];
            sz[1] = L'\0';
            ::str::international::unicode_to_utf8(strChar, sz);
            str += strChar;
         }
         else if(ch < 32 && ch >= 0)
         {
            WCHAR table[] =
            {
               0x263C, 0x263A, 0x263B, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022,
               0x25D8, 0x25CB, 0x25d9, 0x2642, 0x2640, 0x266A, 0x266B, 0x263C,
               0x25BA, 0x25C4, 0x2195, 0x203C, 0x00B6, 0x00A7, 0x25AC, 0x21A8,
               0x2191, 0x2193, 0x2192, 0x2190, 0x211F, 0x2194, 0x25B2, 0x25BC
            };
            sz[0] = table[ch];
            sz[1] = L'\0';
            ::str::international::unicode_to_utf8(strChar, sz);
            str += strChar;
         }
         else
         {
            str += m_pchLineBuffer[i];
         }
      }
   }


   void ascii_box::_001GetViewSel(file_position_t &iSelStart, file_position_t &iSelEnd)
   {
      iSelStart = m_pview->m_iSelStart - m_pview->m_iViewOffset;
      iSelEnd = m_pview->m_iSelEnd - m_pview->m_iViewOffset;
   }

   void ascii_box::SetFile(sp(::file::file) pfile)
   {
      m_pview->get_document()->m_peditfile->SetFile(pfile);
      OnFileUpdate();
   }

   void ascii_box::OnFileUpdate()
   {
      m_bGetTextNeedUpdate = true;
      m_y = -1;
   }


   void ascii_box::_001OnChar(::message::message * pobj)
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
         m_pview->RedrawWindow();
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
         m_pview->RedrawWindow();
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
         else if(m_pview->m_iSelEnd < m_pview->get_document()->m_peditfile->get_length())
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
         m_pview->RedrawWindow();
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
         m_pview->RedrawWindow();
      }
      else if(pkey->m_ekey == ::user::key_home)
      {
         index iLine = m_pview->SelToLine(m_pview->m_iSelEnd);
         m_pview->m_iSelEnd = m_pview->LineColumnToSel(iLine, 0);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         m_pview->RedrawWindow();
      }
      else if(pkey->m_ekey == ::user::key_end)
      {
         index iLine = m_pview->SelToLine(m_pview->m_iSelEnd);
         m_pview->m_iSelEnd = m_pview->LineColumnToSel(iLine, -1);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         m_pview->RedrawWindow();
      }
      else
      {
         if(pkey->m_ekey == ::user::key_return)
         {
            // Kill Focus => Kill Key Repeat Timer
            //System.simple_message_box("VK_RETURN reached ascii_box");
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
         int32_t iChar = (int32_t) pkey->m_nChar;
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
      m_pview->RedrawWindow();
   }

   void ascii_box::_001OnSysChar(::message::message * pobj)
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


   void ascii_box::_001OnKeyboardFocusTimer(sp(view) pview, uint_ptr iTimer)
   {
      if(iTimer == 0)
      {
         if(m_dwLastCaret + m_dwCaretTime < GetTickCount())
         {
            m_dwLastCaret = GetTickCount();
            m_bCaretOn = !m_bCaretOn;
            m_pview->RedrawWindow();
         }
      }
   }


   void ascii_box::IndexRegisterDelete(file_position_t iSel, file_size_t iCount)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(iCount);
   }

   void ascii_box::IndexRegisterInsert(file_position_t iSel, const char * lpcszWhat)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(lpcszWhat);
   }

   void ascii_box::on_update()
   {
      m_bGetTextNeedUpdate = 1;
      m_y = -1;
      m_pchLineBuffer = new char[(int32_t) m_pview->m_iLineSize];
   }




} // namespace biteditor



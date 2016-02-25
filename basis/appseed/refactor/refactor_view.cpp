#include "framework.h"
#include "aura/user/colorertake5/colorertake5.h"
#include <math.h>

   string str_block(char ch, int iSize)
   {
      string str;
      for(int i = 0; i < iSize; i++)
      {
         str += ch;
      }
      return str;
   }


   void str_fill(string & str, char ch)
   {
      str = str_block(ch, (int) str.get_length());
   }

namespace refactor
{


   view::view(::aura::application * papp) :
      ::object(papp),
      ::user::plain_edit(papp),
      ::user::plain_edit_view(papp),
      m_dib(allocer()),
      m_dibColor(allocer()),
      m_font(allocer())
   {



      m_strHelloMultiverse = "Hello Multiverse!!";




   }

   view::~view()
   {
   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif 


   void view::_001OnUserMessage(::signal_details * pobj)
   {
      
      SCAST_PTR(::message::base, pbase, pobj);

      if(pbase->m_wparam == 11)
      {

//         m_pdata->SetFile(get_document()->m_file);

         //_001OnUpdate();

      }

   }

   void view::on_update(::user::impact * pSender, LPARAM lHint, ::object * phint) 
   {
      
      ::user::plain_edit_view::on_update(pSender, lHint, phint);

      if(lHint == 1001)
      {
         _001RedrawWindow();
      }
      else if(lHint == 11)
      {
         //PostMessage(WM_USER, 11);
         // todo colorer_select_type();
      }
      else if(lHint == 123)
      {
         //m_pdata->SetFile(get_document()->m_file);
         //// todo colorer_select_type();
         //::ca::graphics * pdc = GetDC();
         //_001OnCalcLayout(pdc);
         //ReleaseDC(pdc);
         //_001LayoutScrollBars();
      }
      else if(lHint == 12345)
      {
         //m_pdata->m_editfile.Save(get_document()->m_fileSave);
         //m_pdata->m_editfile.Flush();
      }
      else if(lHint == 771984)
      {
         //ex1::byte_ostream & ostream = dynamic_cast < ex1::byte_ostream & > (*phint);
         //m_pdata->m_editfile.SaveTo(ostream);
      }
      else if(lHint == 1234508)
      {
         //CreateLineIndex();
         //m_bGetTextNeedUpdate = true;
         //RedrawWindow();
         //::ca::graphics * pdc = GetDC();
         //_001OnCalcLayout(pdc);
         //ReleaseDC(pdc);

         //__begin_thread(get_app(), ThreadProcScrollSize, dynamic_cast < ::user::plain_edit * > (this));

      }
      /*xxx if(phint != NULL)
      {
         if(base < main_document >::bases(phint))
         {
            main_document * puh = (main_document * ) phint;
            if(puh->is_type_of(main_document::TypeOnBeforeShowView))
            {
               get_document()->on_save_document(get_document()->get_file_path());
            }
            else if(puh->is_type_of(main_document::TypeOnShowView))
            {
               get_document()->reload();
            }
         }
      }*/
      
   }




   void view:: _001OnDraw(::draw2d::dib * pdib)
   {

      ::user::plain_edit_view::_001OnDraw(pdc);

//      if(m_iSelStart != m_iSelEnd)
//         return;
//
//      stringa straAutoComplete;
//
//      on_auto_complete(m_iSelStart, straAutoComplete);
//
//
//      pdc->set_text_rendering(::ca::text_rendering_anti_alias);
//
//      COLORREF crBk;
//      COLORREF crBkSel;
//      COLORREF crSel;
//      COLORREF cr;
//
//
//      cr          = ARGB(255, 23, 23, 23);
//      crBk        = ARGB(255, 255, 255, 255);
//      crBkSel     = ARGB(255, 0, 0, 127);
//      crSel       = ARGB(255, 255, 255, 255);
//
//      ::ca::job * pjob = pdc->m_pjob;
//
//      ::user::print_job * pprintjob = NULL;
//      if(pjob!= NULL)
//         pprintjob = dynamic_cast < ::user::print_job * > (pjob);
//      else
//         pprintjob = NULL;
//
//
//      rect rectClient;
//      GetClientRect(rectClient);
//
//      if(pprintjob != NULL)
//      {
//         TRACE("Print Job Is Printing page %d", pprintjob->m_iPrintingPage);
//      }
//
//
//
//      //rectClient.deflate(0, 0, 1, 1);
//
//
//
//      if(_001IsBackgroundBypass())
//      {
//      }
//      else if(_001IsTranslucent())
//      {
//      }
//      else
//      {
//      }
//      /*else if(!System.savings().is_trying_to_save(gen::resource_processing)
//      && !System.savings().is_trying_to_save(gen::resource_blur_background))
//      {
//
//         pdc->blur(true, 4, rectClient);
//         //class imaging & imaging = System.imaging();
//         //rect rectClient;
////         GetWindowRect(rectClient);
//  //       rectClient.offset(rectClient.top_left());
///*         if(rectClient.size() != m_dibBk->size())
//         {
//            m_dibBk->create(rectClient.size());
//            m_dibBk->Fill(184, 184, 170);
///*            HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
//            ::visual::fastblur *( *pfnNew )(sp(::aura::application)) = (::visual::fastblur *(*)(sp(::aura::application))) ::GetProcAddress(hmodule, "new_fastblur");*/
///*            m_fastblur.create(get_app());
//            m_fastblur.initialize(rectClient.size(), 2);
//         }
//         if(m_fastblur.is_set() && m_fastblur->get_graphics() != NULL)
//         {
//            m_fastblur->get_graphics()->BitBlt(0, 0, rectClient.width(), rectClient.height(), pdc, 0, 0, SRCCOPY);
//            m_fastblur.blur();
//            imaging.bitmap_blend(
//               m_fastblur->get_graphics(),
//               null_point(),
//               rectClient.size(),
//               m_dibBk->get_graphics(),
//               null_point(),
//               49);
//            pdc->from(rectClient.size(),
//               m_fastblur->get_graphics(),
//               null_point(),
//               SRCCOPY);
//         }*/
//      /*}
//      else
//      {
//         class imaging & imaging = System.imaging();
//         //_001DrawBackground(pdc, rectClipBox);
//         imaging.color_blend(
//            pdc,
//            rectClient,
//            RGB(200, 255, 255),
//            127);
//      }*/
//
//      color c;
//      c.set_rgb(RGB(227, 227, 210));
//      c.hls_rate(0.0, -0.33, -0.23);
//      COLORREF crBorder = c.get_rgb() | (0xff << 24);
//      pdc->Draw3dRect(rectClient, crBorder, crBorder);
//
//      if(m_pdata == NULL)
//         return;
//
//      if(m_pdata->is_in_use())
//      {
//         return;
//      }
//
//      if(m_iLineHeight == 0)
//      {
//         pdc->OffsetViewportOrg(-m_scrollinfo.m_ptScroll.x, m_scrollinfo.m_ptScroll.y);
//      }
//      else
//      {
//         pdc->OffsetViewportOrg(-m_scrollinfo.m_ptScroll.x, -(m_scrollinfo.m_ptScroll.y % m_iLineHeight));
//      }
//
//      ::ca::region_sp rgn(get_app());
//
//      rectClient.deflate(2, 2);
//
//      //ClientToScreen(rectClient);
//      rgn->CreateRectRgnIndirect(rectClient);
//
//      double left = rectClient.left;
//
//   //   pdc->SelectClipRgn(&rgn);
//
//      if(Application.get_keyboard_focus() == this)
//      {
//         m_bFocus = keyboard_focus_is_focusable();
//      }
//      else
//      {
//         m_bFocus = false;
//      }
//
//      strsize iSelStart;
//      strsize iSelEnd;
//      strsize lim = 0;
//
//
//
//
//
//      double y = rectClient.top;
//      _001GetViewSel(iSelStart, iSelEnd);
//      strsize iCursor = iSelEnd;
//      sort::sort(iSelStart, iSelEnd);
//      pdc->SelectObject(GetFont());
//      size size3;
//      visual::graphics_extension(get_app()).GetTextExtent(pdc, unitext("gGYIﾍ"), size3);
//      int iLineHeight = size3.cy;
//      stringa & straLines = m_lines.lines;
//      stringa straLineFeed;
//      string strLine;
//      string str1;
//      string str2;
//      string str3;
//      string strExtent1;
//      string strExtent2;
//      string strExtent3;
//      index iLineStart = should_load_full_file() ? m_iLineOffset : 0;
//      index iLineEnd = should_load_full_file() ? m_iLineCount - 1 : straLines.get_size() - 1;
//      iLineEnd = min(iLineEnd, straLines.get_upper_bound());
//      for(index i = iLineStart; i <= iLineEnd; i++)
//      {
//         straLineFeed.remove_all();
//         straLineFeed.add_smallest_tokens(straLines[i], m_straSep, FALSE, FALSE);
//         if(straLineFeed.get_size() > 0)
//         {
//            strLine = straLineFeed[0];
//         }
//         else
//         {
//            strLine.Empty();
//         }
//         colorertake5::LineRegion * pregion = NULL;
//         if(m_bColorerTake5)
//            pregion = getLineRegions(i);
//         if(pregion != NULL)
//         {
//            for(; pregion != NULL; pregion = pregion->next)
//            {
//               if(pregion->special || pregion->rdef == NULL)
//                  continue;
//               index end = pregion->end;
//               if(end == -1)
//                  end = strLine.get_length();
//               strsize x = pregion->start;
//               strsize len = end - pregion->start;
//               if(x < 0)
//               {
//                  len += x;
//                  x = 0;
//               }
//               if(len < 0)
//                  continue;
//               if(pregion->styled()->bfore)
//               {
//               }
//               else
//               {
//               }
//               if(pregion->styled()->bback)
//               {
//               }
//               else
//               {
//               }
//               string strExtent1;
//               strExtent1 = strLine.Left(x);
//               string strExtent2;
//               strExtent2 = strLine.Mid(x, len);
//               class size size1;
//               visual::graphics_extension(get_app()).GetTextExtent(pdc, strExtent1, size1);
//               pdc->TextOutA(left + size1.cx, y, strExtent2);
//
//            }
//         }
//         else
//         {
//            stringa stra;
//            strsize i1 = iSelStart - lim;
//            strsize i2 = iSelEnd - lim;
//            strsize i3 = iCursor - lim;
//
//            strsize iStart = max(0, i1);
//            strsize iEnd = min(i2, strLine.get_length());
//            if(m_bPassword)
//            {
//               str_fill(strLine, '*');
//            }
//            str1 = strLine.Mid(0, iStart);
//            str2 = strLine.Mid(iStart, iEnd - iStart);
//            str3 = strLine.Mid(iEnd);
//            strExtent1 = str1;
//            strExtent2 = str2;
//            strExtent3 = str3;
//            strExtent1.replace("\t", "   ");
//            strExtent2.replace("\t", "   ");
//            strExtent3.replace("\t", "   ");
//            if(m_bPassword)
//            {
//               str_fill(strExtent1, '*');
//               str_fill(strExtent2, '*');
//               str_fill(strExtent3, '*');
//            }
//            pdc->SetBkMode(TRANSPARENT);
//            pdc->set_color(cr);
//            pdc->SetBkColor(crBkSel);
//            sized size1(0.0, 0.0);
//            pdc->GetTextExtent(size1, strLine, strLine.length(), iStart);
//
//            if(i1 >= 0 && i1 <= iEnd)
//            {
//               
//               pdc->setColor(ARGB(255, 0, 255, 0));
//
//               for(int i = 0; i < straAutoComplete.get_size(); i++)
//               {
//
//                  pdc->TextOut(left + size1.cx, y + (iLineHeight * (i + 1)), straAutoComplete[i]);
//
//               }
//               
//               break;
//
//            }
//
//            sized sizeb(0.0, 0.0);
//            pdc->GetTextExtent(sizeb, strLine, iEnd);
//            sized size2(0.0, 0.0);
//            pdc->GetTextExtent(size2, strLine, strLine.length(), iEnd);
//            size2.cx -= size1.cx;
//            if(iEnd > iStart)
//            {
//      //         pdc->FillSolidRect((int) (left + size1.cx), y, size2.cx, size2.cy, ARGB(255, 120, 240, 180));
//               pdc->set_color(crSel);
//    //           pdc->TextOut(left + size1.cx, y, strExtent2);
//            }
//            pdc->set_color(cr);
//            
//            pdc->SetBkMode(TRANSPARENT);
//  //          pdc->TextOut(left + size1.cx + size2.cx, y, strExtent3);
//            //maxcy = max(size1.cy, size2.cy);
//            //maxcy = max(maxcy, size3.cy);
//            if(m_bFocus && m_bCaretOn && i3 == str1.get_length())
//            {
//            }
//            else if(m_bFocus && m_bCaretOn && i3 == (str1.get_length() + str2.get_length()))
//            {
////               pdc->MoveTo(left + size2.cx + size1.cx, y);
//            }
//         }
//         y += iLineHeight;
//         lim += straLines[i].get_length();
//      }
//
//
   }


   sp(document) view::get_document()
   {

      return ::user::plain_edit_view::get_document();

   }


   void view::on_auto_complete(index iSel, stringa & stra)
   {
      
      int iLine = SelToLine(iSel);
      
      int iCol = SelToColumn(iSel);

      if(iLine < 0 || iCol < 0)
         return;

      stringa straSource;

      straSource.add("replace");
      straSource.add("replace_regexp");

      straSource.get_begins_ci(stra, m_plines->getLine(iLine).substr(0, iCol));
      
   }


   void view::install_message_handling(::message::dispatch * pinterface)
   {


      ::user::plain_edit_view::install_message_handling(pinterface);

      //IGUI_WIN_MSG_LINK(WM_CONTEXTMENU    , pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_USER           , pinterface, this, &view::_001OnUserMessage);


   }


} // namespace refactor




#include "framework.h"
#include "user_rich_text_global.h"



namespace user
{


   namespace rich_text
   {


      ::count get_vars(strsize_array & ia1, strsize_array & ia2, string str)
      {

         strsize i1 = 0;

         strsize i2 = 0;

         while (true)
         {

            i1 = str.find('%', i1);

            if (i1 < 0)
            {

               break;

            }

            i2 = str.find('%', i1 + 1);

            if (i2 < 0)
            {

               break;

            }

            if (i2 == i1 + 1)
            {

               i1 = i2 + 1;

               continue;

            }

            ia1.add(i1);

            ia2.add(i2);

            i1 = i2 + 1;

         }

         ASSERT(ia1.get_size() == ia2.get_size());

         return ia1.get_size();

      }



      data::data(::aura::application * papp) :
         ::object(papp),
         ::data::data(papp)
      {

         m_dwCaretTime = 500;

         defer_create_mutex();

      }


      data::~data()
      {

      }


      strsize data::get_sel_beg()
      {

         return min_non_neg(m_iSelBeg3, m_iSelEnd3);

      }


      strsize data::get_sel_end()
      {

         return MAX(m_iSelBeg3, m_iSelEnd3);

      }


      void data::on_selection_change(format * pformat)
      {

         index iCharBeg = get_sel_beg();

         index iCharEnd = get_sel_end();

         update_box_cache(m_boxa, m_layouta);

         index iBeg = find_box(m_boxa, iCharBeg);

         index iEnd = find_box(m_boxa, iCharEnd);

         if (iBeg >= 0 && iEnd >= iBeg)
         {

            sp(box) pboxBeg = m_boxa[iBeg];

            *pformat = *m_formata[pboxBeg->m_iFormat];

            while (true)
            {

               iBeg++;

               if (iBeg > iEnd)
               {

                  break;

               }

               if (m_boxa[iBeg]->m_bParagraph)
               {

                  continue;

               }

               pformat->intersect(*m_formata[m_boxa[iBeg]->m_iFormat]);

            }

         }

      }


      strsize data::hit_test(pointd pt)
      {

         synch_lock sl(m_pmutex);

         for (auto & line : m_layouta)
         {

            for (auto & range : *line)
            {

               if (range->m_rectHitTest2.contains(pt))
               {

                  int iPos = 0;

                  double xLeft = range->m_rectDevice.left;

                  double xLast = range->m_rectHitTest2.left;

                  double xRight;

                  strsize iChar = range->m_iSelBeg;

                  for (; iChar < range->m_iSelEnd; iChar++, iPos++)
                  {

                     xRight = (range->m_xaDevice[iPos] - xLeft) / 2.0 + xLeft;

                     if (ceil(xLast) < pt.x && pt.x <= ceil(xRight))
                     {

                        return iChar;

                     }

                     xLeft = range->m_xaDevice[iPos];

                     xLast = xRight;

                  }

                  return iChar;

               }

            }

         }

         return -1;

      }


      strsize data::hit_test_line_x(index iLine, double x)
      {

         synch_lock sl(m_pmutex);

         if (iLine < 0 || iLine >= m_layouta.get_count())
         {

            return -1;

         }

         auto & line = m_layouta[iLine];

         for (auto & range : *line)
         {

            if (range->m_rectHitTest2.left <= x && x <= range->m_rectHitTest2.right)
            {

               int iPos = 0;

               double xLeft = range->m_rect22.left;

               double xLast = range->m_rectHitTest2.left;

               double xRight;

               strsize iChar = range->m_iSelBeg;

               for (; iChar < range->m_iSelEnd; iChar++, iPos++)
               {

                  xRight = (range->m_xa2[iPos] - xLeft) / 2.0 + xLeft;

                  if (ceil(xLast) < x && x <= ceil(xRight))
                  {

                     return iChar;

                  }

                  xLeft = range->m_xa2[iPos];

                  xLast = xRight;

               }

               return iChar;

            }

         }

         return -1;

      }

      void data::_001GetText(string & str) const
      {

         str = text(m_boxa);

      }


      void data::_001GetLayoutText(string & str) const
      {

         str = layout_text(m_layouta);

      }


      index data::SelToLine(strsize iSel)
      {

         return sel_line(m_layouta, iSel);

      }


      index data::LineColumnToSel(index iLine, strsize iColumn)
      {

         if (iLine < 0)
         {

            return -1;

         }

         int iMax = (int) _001GetLayoutTextLength();

         if (iLine >= m_layouta.get_count())
         {

            return iMax;

         }

         if (iColumn < 0)
         {

            int iChar = (int) ( iColumn + m_layouta[iLine]->last().m_iSelEnd + 2);

            if (iChar < 0)
            {

               return 0;

            }

            return iChar;

         }

         return MIN(m_layouta[iLine]->first().m_iSelBeg + iColumn, iMax);

      }


      void data::_001Delete(strsize i1, strsize i2)
      {

         strsize iSelBeg = min_non_neg(i1, i2);

         strsize iSelEnd = MAX(i1, i2);

         if (iSelBeg == iSelEnd)
         {

            return;

         }

         synch_lock sl(m_pmutex);

         update_box_cache(m_boxa, m_layouta);

         index iBeg = find_box(m_boxa, iSelBeg);

         index iEnd = find_box(m_boxa, iSelEnd - 1);

         index iCharBeg = 0;

         index iCharEnd = 0;

         while (i1 >= 0 && i2 >= 0 && i1 <= _001GetLayoutTextLength() && i2 <= _001GetLayoutTextLength())
         {

            iCharBeg = sel_char(m_layouta, iSelBeg);

            iCharEnd = sel_char(m_layouta, iSelEnd - 1);

            if (iCharBeg > iCharEnd)
            {

               return;

            }
            else  if (iCharBeg <= iCharEnd)
            {

               break;

            }

            //if (iBeg > 0 && iBeg == iEnd && m_boxa[iBeg]->m_bParagraph)
            //{

            //   break;

            //}

            //if (i2 < i1)
            //{

            //   i2--;

            //}
            //else
            //{

            //   i2++;

            //}

            iSelBeg = min_non_neg(i1, i2);

            iSelEnd = MAX(i1, i2);

         }

         if(iBeg > 0 && iBeg == iEnd && m_boxa[iBeg]->m_bParagraph)
         {

            m_boxa.remove_at(iBeg);

         }
         else if (iBeg >= 0 && iEnd >= iBeg)
         {

            sp(box) pboxBeg = m_boxa[iBeg];

            sp(box) pboxEnd = m_boxa[iEnd];

            if (iBeg == iEnd)
            {

               pboxBeg->m_str = pboxBeg->m_str.Left(iCharBeg - pboxBeg->m_iCharBeg) + pboxBeg->m_str.Mid(iCharEnd - pboxBeg->m_iCharBeg + 1);

               if (pboxBeg->m_str.is_empty())
               {

                  m_boxa.remove_at(iBeg);

               }

               return;

            }

            index iEndBeg = pboxEnd->m_iCharBeg;

            index iEndEnd = pboxEnd->m_iCharEnd;

            if (iCharBeg > pboxBeg->m_iCharBeg)
            {

               pboxBeg->m_str = pboxBeg->m_str.Left(iCharBeg - pboxBeg->m_iCharBeg);

               pboxBeg->m_iCharEnd = (int) (iCharBeg - 1);

               iBeg++;

            }

            if (iCharEnd <= iEndEnd)
            {

               pboxEnd->m_str = pboxEnd->m_str.Mid(iCharEnd - iEndBeg + 1);

               pboxEnd->m_iCharBeg = (int) iCharEnd;

               iEnd--;

            }

            int iCount = (int) (iEnd - iBeg + 1);

            if (iCount > 0)
            {

               m_boxa.remove_at(iBeg, iCount);

            }

         }

      }


      void data::_001InsertText(const char * psz)
      {

         synch_lock sl(m_pmutex);

         update_box_cache(m_boxa, m_layouta);

         string strText = text(m_boxa);

         index iSelBeg = get_sel_beg();

         index iSelEnd = get_sel_end();

         index iCharBeg = sel_char(m_layouta, iSelBeg);

         //index iCharEnd = sel_char(m_layouta, iSelEnd);

         index iSelBox = iSelBeg - 1;

         index iBox = find_box(m_boxa, iSelBox);

         if (iBox >= 0 && m_boxa[iBox]->m_bParagraph)
         {

            iSelBox = iSelBeg;

            iBox = find_box(m_boxa, iSelBox);

         }

         index iFormat;

         sp(box) pbox;

         if (iBox >= 0)
         {

            pbox = m_boxa[iBox];

            iFormat = pbox->m_iFormat;

         }
         else
         {

            iFormat = 0;

         }

         _001Delete(iSelBeg, iSelEnd);

         update_box_cache(m_boxa, m_layouta);

         if (m_boxa.get_count() <= 1)
         {

            sp(box) pbox = canew(box(get_app()));

            pbox->m_str = psz;

            pbox->m_iFormat = iFormat;

            m_boxa.add(pbox);

            m_iSelBeg3 = m_iSelEnd3 = iSelBeg + strlen(psz);

            m_iSelCharBeg = m_iSelCharEnd = iCharBeg + strlen(psz);

         }
         else
         {

            index iSelBox = iSelBeg - 1;

            index iBox = find_box(m_boxa, iSelBox);

            if (iBox >= 0 && m_boxa[iBox]->m_bParagraph)
            {

               iSelBox = iSelBeg;

               iBox = find_box(m_boxa, iSelBox);

            }

            sp(box) pbox = m_boxa[iBox];

            if (string(psz) == "\r" || string(psz) == "\n")
            {

               string str = pbox->m_str;

               sp(box) pbox2 = canew(box(get_app()));

               pbox2->m_bParagraph = true;

               pbox2->m_str = "";

               pbox2->m_iFormat = pbox->m_iFormat;

               pbox2->m_ealign = box_align(m_boxa, iBox);

               if (iCharBeg <= pbox->m_iCharBeg)
               {

                  m_boxa.insert_at(iBox, pbox2);

               }
               else
               {

                  pbox->m_str = str.Left(iCharBeg - pbox->m_iCharBeg);

                  m_boxa.insert_at(iBox + 1, pbox2);

                  if (iCharBeg <= pbox->m_iCharEnd)
                  {

                     sp(box) pbox3 = canew(box(get_app()));

                     pbox3->m_str = str.Mid(iCharBeg - pbox->m_iCharBeg);

                     m_boxa.insert_at(iBox + 2, pbox2);

                  }

               }

               m_iSelBeg3 = m_iSelEnd3 = iSelBeg + 1;

               m_iSelCharBeg = m_iSelCharEnd = iCharBeg;

            }
            else if (iBox >= 0)
            {

               if (pbox->m_bParagraph)
               {

                  sp(box) pboxNew = canew(box(get_app()));

                  if (iSelBeg < pbox->m_iSelBeg)
                  {

                     m_boxa.insert_at(iBox, pboxNew);

                     m_iSelBeg3 = m_iSelEnd3 = iSelBeg + strlen(psz);

                     m_iSelCharBeg = m_iSelCharEnd = -1;


                  }
                  else
                  {

                     m_boxa.insert_at(iBox + 1, pboxNew);

                     m_iSelBeg3 = m_iSelEnd3 = iSelBeg + strlen(psz);

                     m_iSelCharBeg = m_iSelCharEnd = iCharBeg + strlen(psz);


                  }

                  pboxNew->m_str = psz;

               }
               else
               {

                  pbox->m_str =
                  pbox->m_str.Left(iCharBeg - pbox->m_iCharBeg) +
                  string(psz) +
                  pbox->m_str.Mid(iCharBeg - pbox->m_iCharBeg);

                  m_iSelBeg3 = m_iSelEnd3 = iSelBeg + strlen(psz);

                  if (iBox + 1 < m_boxa.get_count() && m_boxa[iBox + 1]->m_bParagraph)
                  {

                     m_iSelCharBeg = m_iSelCharEnd = -1;

                  }
                  else
                  {

                     m_iSelCharBeg = m_iSelCharEnd = iCharBeg + strlen(psz);

                  }


               }


            }

         }

      }


      void data::_001SetSelFontFormat(format * pformat, attribute_flags & eattributea)
      {

         synch_lock sl(m_pmutex);

         update_box_cache(m_boxa, m_layouta);

         string strText = text(m_boxa);

         index iSelBeg = get_sel_beg();

         index iSelEnd = get_sel_end() - 1;

         index iCharBeg = sel_char(m_layouta, iSelBeg);

         index iCharEnd = sel_char(m_layouta, iSelEnd);

         index iBeg = find_box(m_boxa, iSelBeg);

         index iEnd = find_box(m_boxa, iSelEnd);

         if (iBeg >= 0 && iEnd >= iBeg)
         {

            sp(box) pboxBeg = m_boxa[iBeg];

            sp(box) pboxEnd = m_boxa[iEnd];

            index iEndBeg = pboxEnd->m_iCharBeg;

            index iEndEnd = pboxEnd->m_iCharEnd;

            string str;

            if (iBeg == iEnd)
            {

               if (iCharBeg > pboxBeg->m_iCharBeg)
               {

                  str = pboxBeg->m_str;

                  pboxBeg->m_str = str.Left(iCharBeg - pboxBeg->m_iCharBeg);

                  sp(box) pbox2 = canew(box(get_app()));
                  pbox2->m_str = str.Mid(iCharBeg - pboxBeg->m_iCharBeg, iCharEnd - iCharBeg + 1);
                  pbox2->m_iFormat = get_format(m_formata, pboxBeg->m_iFormat, pformat, eattributea);
                  m_boxa.insert_at(iBeg + 1, pbox2);

                  if (iCharEnd < pboxBeg->m_iCharEnd)
                  {

                     sp(box) pbox3 = canew(box(get_app()));
                     pbox3->m_str = str.Mid(iCharEnd - pboxBeg->m_iCharBeg + 1);
                     pbox3->m_iFormat = pboxBeg->m_iFormat;
                     m_boxa.insert_at(iBeg + 2, pbox3);

                  }

               }
               else
               {

                  if (iCharEnd < pboxBeg->m_iCharEnd)
                  {

                     str = pboxBeg->m_str;

                     sp(box) pbox2 = canew(box(get_app()));
                     pbox2->m_str = str.Mid(iCharEnd - pboxBeg->m_iCharBeg + 1);
                     pbox2->m_iFormat = pboxBeg->m_iFormat;
                     m_boxa.insert_at(iBeg + 1, pbox2);

                     pboxBeg->m_str = str.Left(iCharEnd - pboxBeg->m_iCharBeg + 1);

                  }

                  pboxBeg->m_iFormat = get_format(m_formata, pboxBeg->m_iFormat, pformat, eattributea);

               }

            }
            else
            {

               if (iCharBeg > pboxBeg->m_iCharBeg)
               {

                  iEnd++;

                  str = pboxBeg->m_str;

                  pboxBeg->m_str = str.Left(iCharBeg - pboxBeg->m_iCharBeg);

                  sp(box) pbox2 = canew(box(get_app()));
                  pbox2->m_str = str.Mid(iCharBeg - pboxBeg->m_iCharBeg);
                  pbox2->m_iFormat = get_format(m_formata, pboxBeg->m_iFormat, pformat, eattributea);
                  m_boxa.insert_at(iBeg + 1, pbox2);

               }
               else
               {

                  pboxBeg->m_iFormat = get_format(m_formata, pboxBeg->m_iFormat, pformat, eattributea);

               }


               if (iCharEnd < iEndEnd)
               {

                  str = pboxEnd->m_str;

                  sp(box) pbox3 = canew(box(get_app()));
                  pbox3->m_str = str.Left(iCharEnd - iEndBeg + 1);
                  pbox3->m_iFormat = get_format(m_formata, pboxEnd->m_iFormat, pformat, eattributea);

                  m_boxa.insert_at(iEnd, pbox3);

                  pboxEnd->m_str = str.Mid(iCharEnd - iEndBeg + 1);

               }
               else
               {

                  pboxEnd->m_iFormat = get_format(m_formata, pboxEnd->m_iFormat, pformat, eattributea);

               }

               for (index i = iBeg + 1; i < iEnd; i++)
               {

                  if (m_boxa[i].is_set())
                  {

                     m_boxa[i]->m_iFormat = get_format(m_formata, m_boxa[i]->m_iFormat, pformat, eattributea);

                  }

               }

            }

         }

         optimize_data();

         m_pedit->on_after_change(::user::event_after_change_text_format);

      }


      void data::_001OnDraw(::draw2d::graphics * pgraphics, LPCRECTD lpcrect)
      {

         synch_lock sl(m_pmutex);

         update_box_cache(m_boxa);

         pgraphics->set_text_rendering_hint_hint(::draw2d::text_rendering_hint_anti_alias);

         rectd rectClient(lpcrect);

         int x = lpcrect->left;

         //int iLine = 0;

         m_layouta.remove_all();

         bool bNewLine = false;

         ::count c;

         bool bHasFocus = false;

         if (m_pedit->has_focus())
         {

            bHasFocus = true;

         }

         bool bCaretOn = false;

         if (bHasFocus && m_pedit->is_text_editable())
         {

            bCaretOn = ((get_tick_count() - m_pedit->m_dwFocusStartTick) % (m_dwCaretTime * 2)) < m_dwCaretTime;

         }

         // TODO: Should determine visible portion and layout it

         sp(spa(layout)) pline;

         strsize iCharBeg2 = 0;

         strsize iCharEnd2 = 0;

         strsize iCharBegLayout = 0;

         strsize iCharEndLayout = 0;

         if (m_boxa.get_count() <= 0 || !m_boxa[0]->m_bParagraph)
         {

            m_boxa.insert_at(0, canew(box(get_app(), align_left)));

         }

         // horizontal layout

         e_align ealign = align_center;

         int xLast = x;

         //bool bFirstParagraph = true;

         spa(box) boxa;

         for (index iBox = 0; iBox < m_boxa.get_size(); iBox++)
         {

            sp(box) pbox = m_boxa[iBox];

            if (pbox->m_bParagraph)
            {

               if (pline.is_set() && pline->has_elements())
               {


                  pline->last().m_iSelEnd++;

                  iCharBegLayout++;

                  pline->last().m_str += " ";

                  align(*pline, rectClient, ealign);

                  m_layouta.add(pline);

               }

               pline = canew(spa(layout));

               x = lpcrect->left;

               xLast = x;

               bNewLine = false;

               ealign = pbox->m_ealign;

               x = lpcrect->left;

               bNewLine = false;

               sp(layout) playout = canew(layout);

               playout->m_bParagraph = true;

               index iBox = find_char_box(m_boxa, iCharBeg2);

               playout->m_iFormat = iBox >= 0 ? m_boxa[iBox]->m_iFormat : 0;

               sp(format) & pformat = m_formata.element_at_grow(playout->m_iFormat);

               if (pformat.is_null())
               {

                  pformat = canew(format(get_app()));

               }

               pgraphics->set_font(pformat->get_font(pgraphics));

               sized s = pgraphics->GetTextExtent("A"); // sample

               s.cx = 0;

               playout->m_ealign = ealign;

               playout->m_str = "";

               playout->m_rect22.set(x, 0, x, 0);

               playout->m_rectHitTest2.set(x, 0, x, 0);

               playout->m_size.set_size(s);

               playout->m_iCharBeg = iCharBeg2;

               playout->m_iCharEnd = iCharBeg2 - 1;

               iCharBeg2 = playout->m_iCharEnd + 1;

               playout->m_xa2.add(x);

               playout->m_xa2.add(x);

               playout->m_iSelBeg = iCharBegLayout;

               playout->m_iSelEnd = iCharBegLayout - 1;

               iCharBegLayout = playout->m_iSelEnd + 1;

               pbox->m_iSelBeg = playout->m_iSelBeg;

               pbox->m_iSelEnd = playout->m_iSelEnd;

               pline->add(playout);

               continue;

            }

            pbox->m_iSelBeg = iCharBegLayout;

            pbox->m_str.replace("\n", "");

            pbox->m_str.replace("\r", "");

            sp(format) & pformat = m_formata.element_at_grow(pbox->m_iFormat);

            if (pformat.is_null())
            {

               pformat = canew(format(get_app()));

            }

            pgraphics->set_font(pformat->get_font(pgraphics));

            stringa straWords;

            words(straWords, pbox->m_str);

            sized s;

restart1:

            while (straWords.get_count() > 0)
            {

               ::count iCount = straWords.get_count();

               for (c = iCount; c >= 1; c--)
               {

                  string str = straWords.implode("", 0, c);

                  s = pgraphics->GetTextExtent(str);

                  if (c == iCount && !isspace_dup(str[str.get_length()-1])
                        && iBox < m_boxa.get_upper_bound()
                        && !m_boxa[iBox+1]->m_bParagraph
                        && m_boxa[iBox+1]->m_str.has_char())
                  {

                     stringa straWords2;

                     words(straWords2, m_boxa[iBox+1]->m_str);

                     sized s2;

                     {

                        sp(format) & pformat = m_formata.element_at_grow(m_boxa[iBox + 1]->m_iFormat);

                        if (pformat.is_null())
                        {

                           pformat = canew(format(get_app()));

                        }

                        pgraphics->set_font(pformat->get_font(pgraphics));

                     }

                     s2 = pgraphics->GetTextExtent(straWords2[0]);

                     if (ceil(x + s.cx + s2.cx) >= lpcrect->right)
                     {

                        // gonna overflow: cannot consider c count words anymore.

                        c--;

                        if (c <= 0)
                        {

                           break;

                        }

                        str = straWords.implode("", 0, c);

                        s = pgraphics->GetTextExtent(str);

                        bNewLine = true;

                     }

                     {

                        sp(format) & pformat = m_formata.element_at_grow(pbox->m_iFormat);

                        pgraphics->set_font(pformat->get_font(pgraphics));

                     }

                  }

                  if (x + s.cx < lpcrect->right)
                  {

                     sp(layout) playout = canew(layout);
                     playout->m_ealign = ealign;
                     playout->m_rect22.left = x;
                     playout->m_rect22.right = x + ceil(s.cx);
                     playout->m_size = s;
                     playout->m_iFormat = pbox->m_iFormat;
                     playout->m_str = straWords.implode("", 0, c);
                     array < sized > sizea;
                     pgraphics->GetEachCharTextExtent(sizea, playout->m_str);

                     double pos = x;
                     for (auto & size : sizea)
                     {
                        pos = x + size.cx;
                        playout->m_xa2.add(pos);

                     }
                     playout->m_rectHitTest2.left = xLast;
                     int iLastCharW = 0;
                     if (playout->m_xa2.get_count() > 0)
                     {
                        if (playout->m_xa2.get_count() > 1)
                        {
                           iLastCharW = playout->m_xa2.last() - playout->m_xa2.last(-2);
                        }
                        else
                        {
                           iLastCharW = playout->m_xa2.last() - x;
                        }
                     }
                     playout->m_rectHitTest2.right = x + ceil(s.cx) - iLastCharW / 2;
                     xLast = playout->m_rectHitTest2.right;

                     iCharEnd2 = iCharBeg2 + playout->m_str.get_length() - 1;
                     playout->m_iCharBeg = iCharBeg2;
                     playout->m_iCharEnd = iCharEnd2;
                     iCharBeg2 = iCharEnd2 + 1;

                     iCharEndLayout = iCharBegLayout + playout->m_str.get_length() - 1;
                     playout->m_iSelBeg = iCharBegLayout;
                     playout->m_iSelEnd = iCharEndLayout;
                     iCharBegLayout = iCharEndLayout + 1;


                     pline->add(playout);

                     straWords.remove_at(0, c);

                     x += ceil(s.cx);

                     if (bNewLine)
                     {

                        pline->last().m_iSelEnd++;

                        iCharBegLayout++;

                        pline->last().m_str += " ";

                        align(*pline, rectClient, ealign);

                        m_layouta.add(pline);

                        pline = canew(spa(layout));

                        x = lpcrect->left;

                        xLast = x;

                        bNewLine = false;

                        goto restart1;

                     }

                     break;

                  }
                  else
                  {

                     bNewLine = true;

                  }

               }

               //if (c == 0)
               //{

               //   align(*pline, rectClient, ealign);

               //   m_layouta.add(pline);

               //   pline = canew(spa(layout));

               //   x = lpcrect->left;

               //   xLast = x;

               //   bNewLine = false;

               //   continue;

               //}


               if (straWords.has_elements())
               {

                  string strWord = straWords[0];

                  straWords.remove_at(0);

restart2:

                  while (strWord.length() > 0)
                  {

                     ::count iCount = strWord.length();

                     for (c = iCount; c >= 1; c--)
                     {

                        sized s = pgraphics->GetTextExtent(strWord.Left(c));

                        sized s2 = pgraphics->GetTextExtent(strWord.Left(c - 1));

                        if (x + s.cx < lpcrect->right || c== 1)
                        {

                           sp(layout) playout = canew(layout);
                           playout->m_ealign = ealign;
                           playout->m_rect22.left = x;
                           playout->m_rect22.right = x + ceil(s.cx);
                           playout->m_size = s;
                           playout->m_iFormat = pbox->m_iFormat;
                           playout->m_str = strWord.Left(c);


                           array < sized > sizea;
                           pgraphics->GetEachCharTextExtent(sizea, playout->m_str);

                           double pos = x;
                           for (auto & size : sizea)
                           {
                              pos = x + size.cx;
                              playout->m_xa2.add(pos);

                           }
                           playout->m_rectHitTest2.left = xLast;
                           int iLastCharW = 0;
                           if (playout->m_xa2.get_count() > 0)
                           {
                              if (playout->m_xa2.get_count() > 1)
                              {
                                 iLastCharW = playout->m_xa2.last() - playout->m_xa2.last(-2);
                              }
                              else
                              {
                                 iLastCharW = playout->m_xa2.last() - x;
                              }
                           }


                           iCharEnd2 = iCharBeg2 + playout->m_str.get_length() - 1;
                           playout->m_iCharBeg = iCharBeg2;
                           playout->m_iCharEnd = iCharEnd2;
                           iCharBeg2 = iCharEnd2 + 1;

                           iCharEndLayout = iCharBegLayout + playout->m_str.get_length() - 1;
                           playout->m_iSelBeg = iCharBegLayout;
                           playout->m_iSelEnd = iCharEndLayout;
                           iCharBegLayout = iCharEndLayout + 1;

                           playout->m_rectHitTest2.left = xLast;
                           iLastCharW = s.cx - s2.cx;
                           playout->m_rectHitTest2.right = x + ceil(s.cx) - iLastCharW / 2;
                           xLast = playout->m_rectHitTest2.right;

                           pline->add(playout);

                           strWord = strWord.Mid(c);

                           x += ceil(s.cx);

                           if (bNewLine)
                           {

                              pline->last().m_iSelEnd++;

                              iCharBegLayout++;

                              pline->last().m_str += " ";

                              align(*pline, rectClient, ealign);

                              m_layouta.add(pline);

                              pline = canew(spa(layout));

                              x = lpcrect->left;
                              xLast = x;

                              if (strWord.trimmed().get_length() == 0)
                              {

                                 strWord.Empty();

                              }

                              bNewLine = false;

                              goto restart2;

                           }

                           break;

                        }
                        else
                        {

                           bNewLine = true;

                        }

                     }

                  }


               }

            }

            pbox->m_iSelEnd = iCharBegLayout - 1;

         }

         if (pline->has_elements())
         {

            pline->last().m_iSelEnd++;

            iCharBegLayout++;

            pline->last().m_str += " ";

            align(*pline, rectClient, ealign);

            m_layouta.add(pline);

         }

         for (auto & line : m_layouta)
         {

            if (line->has_elements())
            {

               line->first().m_rectHitTest2.left = lpcrect->left;

               line->last().m_rectHitTest2.right = lpcrect->right;

            }

         }

         update_box_cache(m_boxa, m_layouta);

         if (m_iSelCharBeg >= 0)
         {

            m_iSelBeg3 = char_sel(m_layouta, m_iSelCharBeg, bias_none);

         }

         if (m_iSelCharEnd >= 0)
         {

            m_iSelEnd3 = char_sel(m_layouta, m_iSelCharEnd, bias_none);

         }

         //m_iSelBeg3 = char_sel(m_layouta, m_iSelCharBeg, m_ebiasBeg);

         //m_iSelEnd3 = char_sel(m_layouta, m_iSelCharEnd, m_ebiasEnd);

         if (m_iSelBeg3 > _001GetLayoutTextLength())
         {

            m_iSelBeg3 = _001GetLayoutTextLength();

         }

         if (m_iSelEnd3 > _001GetLayoutTextLength())
         {

            m_iSelEnd3 = _001GetLayoutTextLength();

         }

         //if (m_layouta.has_elements() && m_layouta.last().has_elements())
         //{

         //   m_layouta.last().last().m_iSelEnd--;

         //   m_layouta.last().last().m_str.Truncate(m_layouta.last().last().m_str.length()-1);

         //}

         int y = lpcrect->top;

         int nexty;

         // vertical layout

         for (auto & line : m_layouta)
         {

            int iMaxCy = 0;

            for (auto & range : *line)
            {

               iMaxCy = MAX(iMaxCy, range->m_size.cy);

               range->m_rect22.top = y;
               range->m_rectHitTest2.top = y;

            }

            nexty = y + iMaxCy;

            for (auto & range : *line)
            {

               range->m_rect22.bottom = nexty;

               range->m_rectHitTest2.bottom = nexty;

               range->m_rect22.right += 2;

            }

            y = nexty;

         }

         // Draw Select Rectangle

         if (bHasFocus && m_pedit->is_text_editable())
         {

            for (auto & line : m_layouta)
            {

               if (line->get_count() > 0)
               {

                  sp(layout) playoutBeg = line->first_sp();

                  sp(layout) playoutEnd = line->last_sp();

                  strsize iCharBeg = playoutBeg->m_iSelBeg;

                  strsize iCharEnd = playoutEnd->m_iSelEnd;

                  if (iCharBeg <= get_sel_end() && get_sel_beg() <= iCharEnd)
                  {

                     iCharBeg = MAX(iCharBeg, get_sel_beg());

                     iCharEnd = MIN(iCharEnd, get_sel_end());

                     index iBeg = line->pred_find_first([&](auto & range)
                     {

                        return range->m_iSelBeg <= iCharBeg && iCharBeg <= range->m_iSelEnd;

                     });

                     if (iBeg >= 0)
                     {

                        playoutBeg = line->element_at(iBeg);

                        index iEnd = line->pred_find_first([&](auto & range)
                        {

                           return range->m_iSelBeg <= iCharEnd && iCharEnd <= range->m_iSelEnd;

                        });

                        if (iEnd >= 0)
                        {

                           playoutEnd = line->element_at(iEnd);

                           double l;

                           if (iCharBeg == playoutBeg->m_iSelBeg)
                           {

                              l = playoutBeg->m_rect22.left;

                           }
                           else
                           {

                              l = playoutBeg->m_xa2[iCharBeg - playoutBeg->m_iSelBeg - 1];

                           }

                           double r;

                           if (iCharEnd == playoutEnd->m_iSelBeg)
                           {

                              r = playoutEnd->m_rect22.left;

                           }
                           else
                           {

                              r = (int)ceil(playoutEnd->m_xa2[iCharEnd - playoutEnd->m_iSelBeg - 1]);
                           }

                           pgraphics->fill_solid_rect_coord(l,
                                                            playoutBeg->m_rect22.top,
                                                            r,
                                                            playoutEnd->m_rect22.bottom,
                                                            ARGB(127, 128, 128, 128));


                        }

                     }

                  }

               }

            }

         }

         ::visual::fastblur dibDropShadow;

         ::rect rDropShadow(m_pedit->m_ppic->m_rectDrawing);

         rDropShadow.offset(-rDropShadow.center());

         ::draw2d::dib_sp dib;

         if (m_pedit->m_ppic != NULL && m_pedit->m_ppic->m_bGlowDropShadow)
         {

            dib.alloc(allocer());

            dib->create(m_pedit->m_ppic->m_rectDrawing.get_size());

            ::size sz = m_pedit->m_ppic->m_rectDrawing.get_size();

            dib->g()->SetViewportOrg(sz.cx/2, sz.cy /2);

            draw_text(dib->g());

            dib->g()->SetViewportOrg(0, 0);

            m_pedit->defer_draw_drop_shadow_phase1(rDropShadow, dibDropShadow, dib);

            m_pedit->defer_draw_drop_shadow_phase2(pgraphics, rDropShadow, dibDropShadow);

         }

         draw_text(pgraphics);

         // Draw Caret

         if(bCaretOn &&  m_pedit->is_text_editable())
         {

            sp(layout) playout = find_range(m_layouta, m_iSelEnd3);

            if (playout.is_set())
            {

               double r;

               if (m_iSelEnd3 == playout->m_iSelBeg)
               {

                  r = playout->m_rect22.left;

               }
               else
               {

                  r = (int)ceil(playout->m_xa2[m_iSelEnd3 - playout->m_iSelBeg - 1]);

               }

               pgraphics->fill_solid_rect_coord(r,
                                                playout->m_rect22.top,
                                                r+1.0,
                                                playout->m_rect22.bottom,
                                                ARGB(255, 0, 0, 0));

            }

         }

         ::draw2d::matrix m;

         pgraphics->get_viewport_scale(m);

         //m.invert();

         for (auto & line : m_layouta)
         {

            for (auto & range : *line)
            {

               range->m_rectDevice = range->m_rect22;

               m.transform(range->m_rectHitTest2.top_left());
               m.transform(range->m_rectHitTest2.bottom_right());

               m.transform(range->m_rectDevice.top_left());
               m.transform(range->m_rectDevice.bottom_right());

               range->m_xaDevice.remove_all();

               for (auto & x : range->m_xa2)
               {

                  range->m_xaDevice.add(x * m.a1);

               }

            }

         }


      }


      void data::optimize_data()
      {

         synch_lock sl(m_pmutex);

         {

            index_array iaFormatUsed;

            for (index i = 0; i < m_boxa.get_count(); i++)
            {

               if (m_boxa[i]->m_bParagraph)
               {

                  continue;

               }

               iaFormatUsed.add_unique(m_boxa[i]->m_iFormat);

               m_boxa[i]->m_iFormat = iaFormatUsed.find_first(m_boxa[i]->m_iFormat);

            }

            {

               spa(format) formata;

               for (index i = 0; i < iaFormatUsed.get_count(); i++)
               {

                  formata.add(m_formata[iaFormatUsed[i]]);

               }

               ::lemon::array::copy(m_formata, formata);

            }

         }



         for (index i = 0; i < m_boxa.get_count(); i++)
         {

            if (m_boxa[i]->m_bParagraph)
            {

               continue;

            }

            index iFormat = m_boxa[i]->m_iFormat;

            i++;

            while (i < m_boxa.get_count() && !m_boxa[i]->m_bParagraph)
            {

               if (m_boxa[i]->m_iFormat == iFormat)
               {

                  m_boxa[i - 1]->m_str += m_boxa[i]->m_str;

                  m_boxa.remove_at(i);

               }
               else
               {

                  iFormat = m_boxa[i]->m_iFormat;

                  i++;

               }

            }

         }

      }


      strsize data::_001GetTextLength() const
      {

         synch_lock sl(m_pmutex);

         if (m_layouta.is_empty())
         {

            return 0;

         }

         return m_layouta.last().last().m_iCharEnd + 1;

      }

      strsize data::_001GetLayoutTextLength() const
      {

         synch_lock sl(m_pmutex);

         if (m_layouta.is_empty())
         {

            return 0;

         }

         return m_layouta.last().last().m_iSelEnd;

      }


      void data::internal_update_sel_char()
      {

         //m_iSelCharBeg = sel_char(m_layouta, m_iSelBeg3, m_ebiasBeg);

         //m_iSelCharEnd = sel_char(m_layouta, m_iSelEnd3, m_ebiasEnd);

         bool bNeedRedraw = false;

         strsize iCharBeg = sel_char2(m_layouta, m_iSelBeg3);

         strsize iCharEnd = sel_char2(m_layouta, m_iSelEnd3);

         string str;

         _001GetText(str);

         strsize_array ia1;

         strsize_array ia2;

         get_vars(ia1, ia2, str);

         bool bCharEndMoved = false;

         for (index i = 0; i < ia1.get_count(); i++)
         {

            if (iCharBeg >= ia1[i] && iCharBeg <= ia2[i])
            {

               iCharBeg = ia1[i];

            }
            if (iCharEnd >= ia1[i] && iCharEnd <= ia2[i])
            {
               if (m_iSelBeg3 > iCharEnd)
               {
                  iCharEnd = ia1[i]-1;
               }
               else
               {
                  iCharEnd = ia2[i];

               }

               bCharEndMoved = true;

            }

         }

         if (bCharEndMoved)
         {

            iCharEnd++;

         }

         if (iCharBeg != m_iSelCharBeg)
         {

            m_iSelCharBeg = iCharBeg;

            bNeedRedraw = true;

         }

         if (iCharEnd != m_iSelCharEnd)
         {

            m_iSelCharEnd = iCharEnd;

            bNeedRedraw = true;

         }

         m_pedit->set_need_redraw();

      }


      void data::io(stream & serialize)
      {

         serialize.stream_array(m_boxa);

         serialize.stream_array(m_formata);


      }

      void data::draw_text(::draw2d::graphics * pgraphics)
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         for (auto & line : m_layouta)
         {

            for (auto & range : *line)
            {

               if (range->m_iFormat < 0)
               {

                  continue;

               }

               sp(format) & pformat = m_formata.element_at_grow(range->m_iFormat);

               if (pformat.is_null())
               {

                  pformat = canew(format(get_app()));

               }

               rect r = range->m_rect22;

               if (pformat->m_escript == script_subscript)
               {

                  r.offset(0, r.height() / 6);

               }
               else if (pformat->m_escript == script_superscript)
               {

                  r.offset(0, -r.height() / 3);

               }

               if (m_pedit->m_ppic->m_bOutline)
               {

                  ::draw2d::path_sp path(allocer());

                  path->add_string(range->m_str, r, DT_LEFT | DT_BOTTOM | DT_SINGLELINE, pformat->get_font(pgraphics), pformat->m_crForeground);

                  ::draw2d::pen_sp pen(allocer());

                  ::draw2d::brush_sp brush(allocer());

                  pen->create_solid(m_pedit->m_ppic->m_iOutlineWidth, color(m_pedit->m_ppic->m_hlsOutline));

                  brush->create_solid(pformat->m_crForeground);

                  pgraphics->SelectObject(pen);

                  pgraphics->SelectObject(brush);

                  pgraphics->path(path);

               }
               else
               {

                  pgraphics->set_font(pformat->get_font(pgraphics));

                  pgraphics->set_text_color(pformat->m_crForeground);

                  pgraphics->draw_text(range->m_str, r, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);

               }

            }

         }

      }


   } // namespace rich_text


} // namespace user



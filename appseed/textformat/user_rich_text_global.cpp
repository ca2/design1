#include "framework.h"
#include "user_rich_text_global.h"


namespace user
{


   namespace rich_text
   {


      bool is_equal_bool(bool b1, bool b2)
      {

         return (b1 && b2) || (!b1 && !b2);

      }

      bool is_similar_font_size(double d1, double d2)
      {

         return fabs(d2 - d1) < 0.25;

      }


      void words(stringa & stra, string str)
      {

         strsize iFind = 0;

         strsize iFind2;

         strsize iFind3;

         while (true)
         {


            iFind2 = str.find_first_in(" \t\r\n", iFind);

            if (iFind2 < 0)
            {

               stra.add(str.Mid(iFind));

               return;

            }

            iFind3 = str.find_first_not_in(" \t\r\n", iFind2);

            if (iFind3 < 0)
            {

               stra.add(str.Mid(iFind));

               return;

            }

            stra.add(str.Mid(iFind, iFind3 - iFind));

            iFind = iFind3;

         }

      }


      index sel_line(spa(spa(layout)) & layouta, index iSel)
      {

         if (iSel < 0)
         {

            return -1;

         }

         layout * rangeLast = NULL;

         index iLine = 0;

         for (; iLine < layouta.get_count(); iLine++)
         {

            auto & line = layouta[iLine];

            for (auto & range : *line)
            {

               rangeLast = range;

               if (range->m_iSelBeg <= iSel && iSel <= range->m_iSelEnd)
               {

                  return iLine;

               }

            }

         }

         return layouta.get_upper_bound();

      }

      index sel_line_x(spa(spa(layout)) & layouta, index iSel, double & x)
      {

         if (iSel < 0)
         {

            return -1;

         }

         layout * rangeLast = NULL;

         index iLine = 0;

         for (; iLine < layouta.get_count(); iLine++)
         {

            auto & line = layouta[iLine];

            for (auto & range : *line)
            {

               rangeLast = range;

               if (range->m_iSelBeg <= iSel && iSel <= range->m_iSelEnd)
               {
                  strsize iChar = iSel - range->m_iSelBeg;

                  int xLeft;
                  int xRight;

                  if (iChar <= 0)
                  {

                     xLeft = range->m_rect22.left;

                  }
                  else if((iChar - 1) >= range->m_xa2.get_count())
                  {

                     xLeft = range->m_xa2[iChar-1];

                  }
                  else
                  {

                     xLeft = range->m_rect22.left;

                  }

                  if (iChar >= 0 && iChar < range->m_xa2.get_count())
                  {

                     xRight = range->m_xa2[iChar];

                  }
                  else
                  {

                     xRight = xLeft;

                  }

                  x = (xRight + xLeft) / 2;

                  return iLine;

               }

            }

         }

         return layouta.get_upper_bound();

      }


      index sel_char(spa(spa(layout)) & layouta, index iSel)
      {

         if (iSel < 0 || layouta.isEmpty() || layouta.first().isEmpty())
         {

            return -1;

         }

         for (auto & line : layouta)
         {

            for (auto & range : *line)
            {

               if (range->m_iSelBeg <= iSel && iSel <= range->m_iSelEnd)
               {

                  return MIN(range->m_iCharEnd + 1, iSel - range->m_iSelBeg + range->m_iCharBeg);

               }

            }

         }

         return layouta.last().last().m_iCharEnd + 1;

      }


      strsize sel_char(spa(spa(layout)) & layouta, index iSel, e_bias & ebias)
      {

         ebias = bias_none;

         if (iSel < 0 || layouta.isEmpty() || layouta.first().isEmpty())
         {

            return -1;

         }

         for (auto & line : layouta)
         {

            for (auto & range : *line)
            {

               if (range->m_iSelBeg <= iSel && iSel <= range->m_iSelEnd)
               {

                  if (range == line->last_ptr() && iSel == range->m_iSelEnd &&
                        !range->m_bParagraph)
                  {

                     ebias = bias_right;

                  }

                  return MIN(range->m_iCharEnd + 1, iSel - range->m_iSelBeg + range->m_iCharBeg);

               }

            }

         }

         return layouta.last().last().m_iCharEnd + 1;

      }

      strsize sel_char2(spa(spa(layout)) & layouta, index iSel)
      {

         if (iSel < 0 || layouta.isEmpty() || layouta.first().isEmpty())
         {

            return -1;

         }

         for (auto & line : layouta)
         {

            for (auto & range : *line)
            {

               if (range->m_iSelBeg <= iSel && iSel <= range->m_iSelEnd)
               {

                  strsize iChar = iSel - range->m_iSelBeg + range->m_iCharBeg;

                  if (iChar <= range->m_iCharEnd)
                  {

                     return iChar;

                  }

               }

            }

         }

         return -1;

      }

      strsize char_sel(spa(spa(layout)) & layouta, strsize iChar, e_bias ebias)
      {


         if (iChar < 0 || layouta.isEmpty() || layouta.first().isEmpty())
         {

            return -1;

         }

         for (auto & line : layouta)
         {

            for (auto & range : *line)
            {

               if ((ebias == bias_left && range->m_iCharBeg <= iChar-1 && iChar-1 <= range->m_iCharEnd))
               {
                  int i = (line == layouta.last_ptr()
                           && range == line->last_ptr() ? 0 : 1);
                  return MIN(range->m_iSelEnd + i,
                             iChar - range->m_iCharBeg + range->m_iSelBeg);

               }
               else if ((ebias == bias_none && range->m_iCharBeg <= iChar && iChar <= range->m_iCharEnd)
                        ||
                        (ebias == bias_right &&
                         range->m_bParagraph &&
                         range->m_iCharBeg <= iChar && iChar <= range->m_iCharEnd + 1))
               {

                  if (range == line->last_ptr() && ebias == bias_right)
                  {

                     return MIN(range->m_iSelEnd + (line == layouta.last_ptr() ? 0 : 1)
                                , iChar - range->m_iCharBeg + range->m_iSelBeg + 1);

                  }

                  return MIN(range->m_iSelEnd +
                             (line == layouta.last_ptr()
                              && range == line->last_ptr() ? 0 : 1),
                             iChar - range->m_iCharBeg + range->m_iSelBeg);

               }

            }

         }

         return layouta.last().last().m_iSelEnd;

      }




      string line_text(spa(layout) & line)
      {

         string str;

         for (auto & range : line)
         {

            str += range->m_str;

         }

         return str;

      }

      string text(const spa(box) & boxa)
      {

         string str;

         for (auto & box : boxa)
         {

            if (box->m_bParagraph)
            {

               continue;

            }

            str += box->m_str;

         }

         return str;

      }


      void update_box_cache(spa(box) & boxa)
      {

         int iPos = 0;

         int iNextPos;

         for (index i = 0; i < boxa.get_count(); i++)
         {

            sp(box) & box = boxa[i];

            if (box->m_bParagraph && i == 0)
            {

               continue;

            }

            iNextPos = (int) (iPos + box->m_str.length() - 1);

            box->m_iCharBeg = iPos;

            box->m_iCharEnd = iNextPos;

            iPos = iNextPos + 1;

         }

      }


      void update_box_cache(spa(box) & boxa, spa(spa(layout)) & layouta)
      {

         update_box_cache(boxa);

         //for (index l = 0; l < layouta.get_count(); l++)
         //{

         //   auto & line = layouta.element_at(l);

         //   for (index j = 0; j < line->get_count(); j++)
         //   {

         //      auto & range = line->element_at(j);

         //      if (range->m_bParagraph && j == 0 && l == 0)
         //      {

         //         continue;

         //      }

         //      for (index i = 0; i < boxa.get_count(); i++)
         //      {

         //         sp(box) & box = boxa[i];

         //         if (box->m_bParagraph && i == 0)
         //         {

         //            continue;

         //         }

         //         if (box->m_iCharBeg == range->m_iCharBeg)
         //         {

         //            box->m_iSelBeg = range->m_iSelBeg;

         //         }

         //         if (box->m_iCharEnd == range->m_iCharEnd)
         //         {

         //            box->m_iSelEnd = range->m_iSelEnd;

         //         }

         //      }

         //   }

         //}

      }


      e_align box_align(spa(box) & boxa, index iBox)
      {

         while (true)
         {

            if (iBox > boxa.get_count())
            {

               iBox = boxa.get_upper_bound();

            }

            if (iBox < 0)
            {

               return align_left;

            }

            if (boxa[iBox]->m_bParagraph)
            {

               return boxa[iBox]->m_ealign;

            }

            iBox--;

         }


      }


      bool box_align(spa(box) & boxa, index iBox, e_align ealign)
      {

         while (true)
         {

            if (iBox > boxa.get_count())
            {

               iBox = boxa.get_upper_bound();

            }

            if (iBox < 0)
            {

               return false;

            }

            if (boxa[iBox]->m_bParagraph)
            {

               boxa[iBox]->m_ealign = ealign;

               return true;

            }

            iBox--;

         }


      }

      index find_box(spa(box) & boxa, index iSel, bool bParagraph)
      {

         string str;

         for (index i = 0; i < boxa.get_count(); i++)
         {

            sp(box) & box = boxa[i];

            if (box->m_bParagraph && (i == 0 || !bParagraph))
            {

               continue;

            }

            if (iSel <= box->m_iSelEnd)
            {

               return i;

            }

         }

         return boxa.get_upper_bound();

      }


      index find_char_box(spa(box) & boxa, strsize iChar)
      {

         if (iChar < 0)
         {

            return -1;

         }

         string str;

         for (index i = 0; i < boxa.get_count(); i++)
         {

            sp(box) & box = boxa[i];

            if (box->m_bParagraph)
            {

               continue;

            }

            if (iChar >= box->m_iCharBeg && iChar <= box->m_iCharEnd)
            {

               return i;

            }

         }

         return boxa.get_upper_bound();

      }


      void align(spa(layout) & line, LPCRECTD lpcrect, e_align ealign)
      {

         if (line.is_empty())
         {

            return;

         }

         // line.last().m_str += "\n";

         if (ealign == align_left)
         {

            // Nothing to do:
            // "line" is already left aligned;

         }
         else
         {

            int iWidth = line.last().m_rect22.right;

            int iOffset = lpcrect->right - iWidth;

            if (ealign == align_center)
            {

               iOffset /= 2;

            }

            for (auto & range : line)
            {

               range->m_rect22.offset(iOffset, 0);
               range->m_rectHitTest2.offset(iOffset, 0);

               for (auto & d : range->m_xa2)
               {

                  d += (double)iOffset;

               }

            }


         }


      }


      layout * find_range(spa(spa(layout)) & layouta, index iSel)
      {

         if (iSel < 0 || layouta.isEmpty() || layouta.first().isEmpty())
         {

            return NULL;

         }

         layout * rangeLast = NULL;

         for (auto & line : layouta)
         {

            for (auto & range : *line)
            {

               rangeLast = range;

               if (range->m_iSelBeg <= iSel && iSel <= range->m_iSelEnd)
               {

                  return range;

               }

            }

         }

         return rangeLast;

      }


      string layout_text(const spa(spa(layout)) & layout)
      {

         string str;

         index iLine = 0;

         for (; iLine < layout.get_count(); iLine++)
         {

            auto & line = layout[iLine];

            for (auto & range : *line)
            {

               str += range->m_str;

            }

         }

         return str;

      }



      index find_format(spa(format) & formata, format * pformat)
      {

         return formata.pred_find_first([&](auto & pitem)
         {

            return *pitem == *pformat;

         });

      }


      index get_format(spa(format) & formata, format * pformat)
      {

         index iFind = find_format(formata, pformat);

         if (iFind >= 0)
         {

            return iFind;

         }

         formata.add(canew(format(*pformat)));

         return formata.get_upper_bound();

      }


      index get_format(spa(format) & formata, index i, format * pformat, attribute_flags  & eattributea)
      {

         sp(format) pformatSynth = canew(format(*formata[i]));

         pformatSynth->apply(pformat, eattributea);

         index iFind = find_format(formata, pformatSynth);

         if (iFind >= 0)
         {

            return iFind;

         }

         formata.add(pformatSynth);

         return formata.get_upper_bound();

      }


   } // namespace rich_text


} // namespace user




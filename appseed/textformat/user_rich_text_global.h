#pragma once


namespace user
{


   namespace rich_text
   {


      bool is_equal_bool(bool b1, bool b2);
      bool is_similar_font_size(double d1, double d2);
      void update_box_cache(spa(box) & boxa);
      void update_box_cache(spa(box) & boxa, spa(spa(layout)) & layouta);
      index find_box(spa(box) & boxa, index iSel);
      e_align box_align(spa(box) & boxa, index iBox);
      bool box_align(spa(box) & boxa, index iBox, e_align ealign);
      index find_char_box(spa(box) & boxa, strsize iChar);
      layout * find_range(spa(spa(layout)) & layout, index iSel);
      string layout_text(const spa(spa(layout)) & layout);
      void align(spa(layout) & boxa, LPCRECTD lpcrect, e_align ealign);
      string line_text(spa(layout) & line);
      index sel_line(spa(spa(layout)) & layout, index iSel);
      index sel_line_x(spa(spa(layout)) & layout, index iSel, double & x);
      strsize sel_char(spa(spa(layout)) & layout, index iSel);
      strsize sel_char(spa(spa(layout)) & layout, index iSel, e_bias & ebias);
      strsize sel_char2(spa(spa(layout)) & layout, index iSel);
      strsize char_sel(spa(spa(layout)) & layout, strsize iChar, e_bias ebias);
      string text(const spa(box) & boxa);
      index get_format(spa(format) & formata, format * pformat);
      index get_format(spa(format) & formata, index i, format * pformat, attribute_flags & eattributea);
      void words(stringa & stra, string str);


   } // namespace rich_text


} // namespace user




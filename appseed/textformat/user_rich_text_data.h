#pragma once


namespace user
{


   namespace rich_text
   {


      class edit;


      class CLASS_DECL_DESIGN_TEXTFORMAT data :
         virtual public ::data::data
      {
      public:


         spa(box)                      m_boxa;
         spa(format)                   m_formata;

         spa(spa(layout))              m_layouta;

         strsize                       m_iSelBeg3;
         strsize                       m_iSelEnd3;
         strsize                       m_iSelCharBeg;
         e_bias                        m_ebiasBeg;
         strsize                       m_iSelCharEnd;
         e_bias                        m_ebiasEnd;
         rich_text::edit *             m_pedit;
         DWORD                         m_dwCaretTime;


         data(::aura::application * papp);
         virtual ~data();

         virtual void _001OnDraw(::draw2d::graphics * pgraphics, LPCRECTD lpcrect);


         virtual strsize hit_test(pointd pt);
         virtual strsize hit_test_line_x(index iLine, double x);

         virtual strsize get_sel_beg();
         virtual strsize get_sel_end();

         virtual void internal_update_sel_char();

         virtual void on_selection_change(format * pformat);

         virtual void _001SetSelFontFormat(format * pformat, attribute_flags & eattributea);

         virtual void _001Delete(strsize i1, strsize i2);
         virtual void _001InsertText(const char * psz);

         virtual void _001GetText(string & str) const;
         virtual void _001GetLayoutText(string & str) const;

         virtual void draw_text(::draw2d::graphics * pgraphics);

         virtual void optimize_data();

         virtual index SelToLine(strsize i);
         virtual strsize LineColumnToSel(index iLine, strsize iColumn);

         virtual strsize _001GetTextLength() const;
         virtual strsize _001GetLayoutTextLength() const;

         virtual void io(stream & stream) override;

      };


   } // namespace rich_text


} // namespace user




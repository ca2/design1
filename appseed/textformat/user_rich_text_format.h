#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_DESIGN_TEXTFORMAT format :
         virtual public object
      {
      public:



         bool                 m_bBold;
         bool                 m_bItalic;
         bool                 m_bUnderline;
         string               m_strFontFamily;
         double               m_dFontSize;
         COLORREF             m_crForeground;
         COLORREF             m_crBackground;
         e_script             m_escript;
         e_line_height        m_elineheight;


         // cache or transport (not serialized)
         bool                 m_bUpdated;
         ::draw2d::font_sp    m_font;
         e_align              m_ealign;


         format(::aura::application * papp);
         format(const format & format);
         virtual ~format();


         virtual void stream(serialize & serialize) override;


         void apply(format * pformat, attribute_flags & eattributea);

         ::draw2d::font * get_font(::draw2d::graphics * pgraphics);

         bool operator == (const format & format) const;
         format & operator = (const format & format);

         void intersect(const format & format);


      };


   } // namespace rich_text


} // namespace user





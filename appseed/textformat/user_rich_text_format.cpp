#include "framework.h"
#include "user_rich_text_global.h"





namespace user
{


   namespace rich_text
   {


      format::format(::aura::application * papp) :
         object(papp)
      {

         m_bBold = false;
         m_bItalic = false;
         m_bUnderline = false;
         m_strFontFamily = FONT_SANS;
         m_dFontSize = 12.0;
         m_crForeground = ARGB(255, 0, 0, 0);
         m_crBackground = 0;
         m_escript = script_normal;
         m_elineheight = line_height_single;
         m_bUpdated = false;

      }

      format::format(const format & format) :
         ::object(format.get_app())
      {

         operator = (format);


      }



      format::~format()
      {


      }

      bool format::operator==(const format & format) const
      {

         return m_strFontFamily.compare_ci(format.m_strFontFamily) == 0
                && is_equal_bool(m_bBold, format.m_bBold)
                && is_equal_bool(m_bItalic, format.m_bItalic)
                && is_equal_bool(m_bUnderline, format.m_bUnderline)
                && is_similar_font_size(m_dFontSize, format.m_dFontSize)
                && m_crForeground == format.m_crForeground
                && m_crBackground == format.m_crBackground
                && m_escript == format.m_escript
                && m_elineheight == format.m_elineheight;

      }


      void format::apply(format * pformat, comparable_array < e_attribute > & eattributea)
      {

         if (eattributea.contains(attribute_bold))
         {

            m_bBold = pformat->m_bBold;

         }

         if (eattributea.contains(attribute_italic))
         {

            m_bItalic = pformat->m_bItalic;

         }

         if (eattributea.contains(attribute_underline))
         {

            m_bUnderline = pformat->m_bUnderline;

         }

         if (eattributea.contains(attribute_family))
         {

            m_strFontFamily = pformat->m_strFontFamily;

         }

         if (eattributea.contains(attribute_size))
         {

            m_dFontSize = pformat->m_dFontSize;

         }

         if (eattributea.contains(attribute_script))
         {

            m_escript = pformat->m_escript;

         }

         if (eattributea.contains(attribute_foreground))
         {

            m_crForeground = pformat->m_crForeground;

         }

      }

      void format::intersect(const format & format)
      {

         if (!is_equal_bool(m_bBold, format.m_bBold))
         {

            m_bBold = false;

         }

         if (!is_equal_bool(m_bItalic, format.m_bItalic))
         {

            m_bItalic = false;

         }

         if (!is_equal_bool(m_bUnderline, format.m_bUnderline))
         {

            m_bItalic = false;

         }

         if (m_strFontFamily.compare_ci(format.m_strFontFamily) != 0)
         {

            m_strFontFamily.Empty();

         }

         if (!is_similar_font_size(m_dFontSize, format.m_dFontSize))
         {

            m_dFontSize = -1.0;

         }

         if (m_ealign != format.m_ealign)
         {

            m_ealign = align_left;

         }

      }

      ::draw2d::font * format::get_font(::draw2d::graphics * pgraphics)
      {

         if (!m_bUpdated || m_font.is_null())
         {

            m_font.alloc(allocer());

            double dFontSize = m_dFontSize;

            if (m_escript == script_subscript || m_escript == script_superscript)
            {

               dFontSize /= 1.333;

            }

            m_font->create_point_font(m_strFontFamily, dFontSize,
                                      m_bBold ? FW_BOLD : FW_NORMAL,
                                      m_bItalic,
                                      m_bUnderline);

            m_bUpdated = true;

         }

         return m_font;

      }


      format & format::operator =(const format & format)
      {

         if (this != &format)
         {

            m_bBold = format.m_bBold;
            m_bItalic = format.m_bItalic;
            m_bUnderline = format.m_bUnderline;
            m_strFontFamily = format.m_strFontFamily;
            m_dFontSize = format.m_dFontSize;
            m_crForeground = format.m_crForeground;
            m_crBackground = format.m_crBackground;
            m_escript = format.m_escript;
            m_elineheight = format.m_elineheight;
            m_bUpdated = false;

         }

         return *this;

      }


      void format::io(stream & serialize)
      {

         property_set set;

         serialize.prop_start(set);

         serialize.prop_serial("bold", m_bBold);
         serialize.prop_serial("italic", m_bItalic);
         serialize.prop_serial("underline", m_bUnderline);
         serialize.prop_serial("family", m_strFontFamily);
         serialize.prop_serial("size", m_dFontSize);
         serialize.prop_serial("foreground", (u32&) m_crForeground);
         serialize.prop_serial("background", (u32&)m_crBackground);
         serialize.prop_serial("script", (i32&)m_escript);
         serialize.prop_serial("lineheight", (i32&)m_elineheight);

         serialize.prop_end();

         if (!serialize.is_storing())
         {

            m_bUpdated = false;

         }

      }


   } // namespace rich_text


} // namespace user



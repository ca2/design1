#include "framework.h"
#include "user_rich_text_global.h"


namespace user
{


   namespace rich_text
   {


      box::box(::aura::application * papp)
      {

         m_iFormat = 0;
         m_bParagraph = false;

      }


      box::box(::aura::application * papp, e_align ealign)
      {

         m_iFormat = 0;
         m_bParagraph = true;
         m_ealign = ealign;

      }


      box::~box()
      {


      }


      void box::xml_export(::xml::output_tree & xmlo)
      {

         if (m_bParagraph)
         {

            xmlo.set_attr("type", "paragraph");
            xmlo.set_attr("align", (i32)m_ealign);

         }
         else
         {

            xmlo.set_value(m_str);
            xmlo.set_attr("type", "text");
            xmlo.set_attr("format", m_iFormat);

         }

      }


      void box::xml_import(::xml::input_tree & xmli)
      {

         string str;

         xmli.get_attr("type", str);

         if (str.contains_ci("paragraph"))
         {

            m_bParagraph = true;
            xmli.get_attr("align", (i32 &)m_ealign);

         }
         else
         {

            m_bParagraph = false;

            xmli.get_value(m_str);
            xmli.get_attr("format", m_iFormat);

         }

      }


   } // namespace rich_text


} // namespace user




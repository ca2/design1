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


      void box::io(stream & serialize)
      {

         property_set set;

         if (serialize.is_storing())
         {

            if(m_bParagraph)
            {

               set["type"] = "paragraph";
               set["align"] = (i32)m_ealign;

            }
            else
            {

               set["type"] = "text";
               set["value"] = m_str;
               set["align"] = (i32)m_iFormat;

            }

            serialize(set);

         }
         else
         {

            serialize(set);

            string strType = set["type"];

            if (strType.contains_ci("paragraph"))
            {

               m_bParagraph = true;
               m_ealign = (e_align) set["align"].i32();

            }
            else
            {

               m_bParagraph = false;

               m_str = set["value"];
               m_iFormat = set["format"];

            }

         }

      }



   } // namespace rich_text


} // namespace user




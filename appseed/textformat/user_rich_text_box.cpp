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


      box::box(const box & box)
      {

         operator = (box);
      }

      box::~box()
      {


      }


      box & box::operator=(const box & box)
      {

         m_bParagraph = box.m_bParagraph;
         m_ealign = box.m_ealign;

         m_str = box.m_str;
         m_iFormat = box.m_iFormat;

         /// temporary/cache/calculated values, not persisted
         m_iCharBeg = box.m_iCharBeg;
         /// temporary/cache/calculated values, not persisted
         m_iCharEnd = box.m_iCharEnd;
         m_iSelBeg = box.m_iSelEnd;
         m_iSelEnd = box.m_iSelEnd;

         return *this;

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




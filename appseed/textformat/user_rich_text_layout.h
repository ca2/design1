#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_DESIGN_TEXTFORMAT layout :
         virtual public simple_object
      {
      public:

         bool           m_bParagraph = false;
         e_align        m_ealign;
         rectd          m_rect2;
         rectd          m_rectHitTest;
         string         m_str;
         int            m_iFormat;
         sized          m_size;
         int            m_iCharBeg;
         int            m_iCharEnd;
         int            m_iSelBeg;
         int            m_iSelEnd;
         double_array   m_xa;

      };


   } // namespace rich_text


} // namespace user





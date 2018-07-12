#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_DESIGN_TEXTFORMAT box :
         virtual public ::object
      {
      public:





         bool              m_bParagraph;
         e_align           m_ealign;

         string            m_str;
         int               m_iFormat;

         /// temporary/cache/calculated values, not persisted
         int               m_iCharBeg;
         /// temporary/cache/calculated values, not persisted
         int               m_iCharEnd;
         int               m_iSelBeg;
         int               m_iSelEnd;

         box(::aura::application * papp);
         box(::aura::application * papp, e_align ealign);
         virtual ~box();


         virtual void io(stream & stream) override;


      };


   } // namespace rich_text


} // namespace user




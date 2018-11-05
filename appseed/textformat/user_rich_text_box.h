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
         index             m_iFormat;

         /// temporary/cache/calculated values, not persisted
         strsize           m_iCharBeg;
         /// temporary/cache/calculated values, not persisted
         strsize           m_iCharEnd;
         strsize           m_iSelBeg;
         strsize           m_iSelEnd;

         box(::aura::application * papp);
         box(::aura::application * papp, e_align ealign);
         box(const box & box);
         virtual ~box();


         virtual void io(stream & stream) override;

         box & operator=(const box & box);

      };


   } // namespace rich_text


} // namespace user




#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_APP_CORE_TEXTFORMAT box :
         virtual public ::xml::exportable,
         virtual public ::xml::importable
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

         virtual void xml_export(::xml::output_tree & xmlo) override;
         virtual void xml_import(::xml::input_tree & xmli) override;

      };


   } // namespace rich_text


} // namespace user




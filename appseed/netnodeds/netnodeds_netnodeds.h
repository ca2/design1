#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS netnodeds :
      virtual public ::aura::departament
   {
   public:
      
      
      sp(::user::single_document_template)    m_ptemplateEdge;
      sp(::aura::impact_system)           m_ptemplate_netnodeds;
      sp(::aura::impact_system)           m_ptemplate_solution;
      sp(::aura::impact_system)           m_ptemplateHtmlEdit;
      sp(::aura::impact_system)           m_ptemplateHtmlStage;
      sp(::aura::impact_system)           m_ptemplateFront;


      netnodeds(::aura::application * papp);
      virtual ~netnodeds();


      virtual bool initialize1();
      virtual bool initialize3();


   };


} // netnodeds
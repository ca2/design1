#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS netnodeds :
      virtual public ::aura::department
   {
   public:
      
      
      sp(::user::single_document_template)    m_ptemplateEdge;
      sp(::user::impact_system)           m_ptemplate_netnodeds;
      sp(::user::impact_system)           m_ptemplate_solution;
      sp(::user::impact_system)           m_ptemplateHtmlEdit;
      sp(::user::impact_system)           m_ptemplateHtmlStage;
      sp(::user::impact_system)           m_ptemplateFront;


      netnodeds(::aura::application * papp);
      virtual ~netnodeds();


      virtual bool initialize1();
      virtual bool initialize3();


   };


} // netnodeds
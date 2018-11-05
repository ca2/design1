#pragma once


namespace devedge
{


   class CLASS_DECL_DEVEDGE devedge :
      virtual public ::aura::department
   {
   public:
      
      
      sp(::user::single_document_template)    m_ptemplateEdge;
      sp(::user::impact_system)           m_ptemplate_devedge;
      sp(::user::impact_system)           m_ptemplate_solution;
      sp(::user::impact_system)           m_ptemplateHtmlEdit;
      sp(::user::impact_system)           m_ptemplateHtmlStage;
      sp(::user::impact_system)           m_ptemplateFront;


      devedge(::aura::application * papp);
      virtual ~devedge();


      virtual bool initialize1();
      virtual bool initialize3();


   };


} // devedge
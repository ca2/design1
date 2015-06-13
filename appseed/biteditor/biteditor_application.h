#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR application:
      virtual public ::tesseract::application
   {
   public:


      sp(::user::impact_system) m_ptemplateEdge;
      sp(::user::impact_system) m_ptemplate_devedge;
      sp(::user::impact_system) m_ptemplateFront;


      application();
      virtual ~application();

      virtual void construct();

      virtual void on_request(sp(::create) pcreatecontext);

      bool initialize_instance();


   };



} // namespace biteditor




#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA application :
      virtual public ::tesseract::application
   {
   public:


      sp(::xml::tree_schema) m_pxmlschemaDrawing;

      sp(::user::single_document_template)   m_pdoctemplateMain;
      sp(::user::multiple_document_template)    m_pdoctemplate;

      pane_view *    m_ppaneview;


      application();
      virtual ~application();


      virtual bool initialize_instance();
      virtual int32_t exit_instance();


      void on_request(sp(::create) pcreatecontext);

      virtual bool on_install();

   };


} // namespace tarsila



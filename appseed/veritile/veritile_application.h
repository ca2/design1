#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE application :
      virtual public ::tesseract::application
   {
   public:


      sp(::xml::tree_schema) m_pxmlschemaDrawing;

      sp(::user::single_document_template)   m_pdoctemplateMain;
      sp(::user::multiple_document_template)    m_pdoctemplate;

      pane_view *    m_ppaneview;


      application();
      virtual ~application();

      virtual void ensure_tileset_dock(id id);


      virtual bool initialize_instance();
      virtual int32_t exit_instance();


      void on_request(sp(::create) pcreatecontext);

      virtual bool on_install();



      virtual void on_create_split_view(::user::split_view * psplit);

   };


} // namespace veritile



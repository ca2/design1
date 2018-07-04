#pragma once



namespace textformat
{


   class CLASS_DECL_APP_CORE_TEXTFORMAT application :
      virtual public ::core::application
   {
   public:



      string                                 m_strTextFormat;
      string                                 m_strTextFormatDefault;
      string                                 m_strAlternateTextFormat;
      string                                 m_strAlternateTextFormatDefault;

      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_view *              m_prollfps;
      ::user::single_document_template *     m_ptemplateTextFormatMain;
      ::user::single_document_template *     m_ptemplateTextFormatView;
      pane_view *                            m_ppaneview;


      application();
      virtual ~application();

      virtual string preferred_userschema() override;
      virtual bool init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual int64_t add_ref() override;
      virtual int64_t dec_ref() override;

   };


} // namespace textformat




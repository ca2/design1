﻿#pragma once


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


      virtual bool init_instance() override;
      virtual void term_instance() override;


      void on_request(::create * pcreate);


      virtual bool on_install();


   };


} // namespace tarsila



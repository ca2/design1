﻿#pragma once

namespace refactor
{

   class CLASS_DECL_CA2_REFACTOR application :
      public ::core::application
   {
   public:


      ::user::single_document_template *  m_ptemplateRefactorMain;
      ::user::single_document_template *  m_ptemplateRefactor;


      application();
      virtual ~application();


      virtual bool init_instance() override;
      virtual void term_instance() override;

      virtual void on_request(::create * pcreate);


   };


} // namespace refactor




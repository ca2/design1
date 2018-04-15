﻿#include "framework.h"


namespace netnodeds
{


   main_document::main_document(::aura::application * papp) :
      ::object(papp),
      ::user::controller(papp),
      ::data::data_container_base(papp),
      ::user::document(papp)
   {

   }


   main_document::~main_document()
   {

   }


   bool main_document::on_new_document()
   {
      if (!::user::document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
   }



   void main_document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void main_document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }



   bool main_document::on_open_document(var varFile)
   {

      ::netnodeds::netnodeds & netnodeds = Application.netnodeds();

      sp(::create) cc(get_app());

      cc->m_spCommandLine->m_varFile = varFile;

      netnodeds.m_ptemplate_netnodeds->request_create(cc);

      return ::user::get_document(cc) != NULL;

   }


   bool main_document::on_save_document(const char * lpszPathName)
   {

      UNREFERENCED_PARAMETER(lpszPathName);

      return true;

   }


} // namespace netnodeds



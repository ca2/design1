#include "framework.h"


namespace devedge
{


   main_document::main_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::controller(papp),
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


#ifdef DEBUG
   void main_document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void main_document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }
#endif //DEBUG


   bool main_document::on_open_document(var varFile)
   {

      ::devedge::devedge & devedge = Application.devedge();
      sp(::create) cc(get_app());
      cc->m_spCommandLine->m_varFile = varFile;
      
      devedge.m_ptemplate_devedge->request_create(cc);

      return ::user::get_document(cc) != NULL;

   }


   bool main_document::on_save_document(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
      return TRUE;
   }




} // namespace devedge



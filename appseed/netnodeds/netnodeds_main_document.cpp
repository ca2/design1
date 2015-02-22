#include "framework.h"


namespace netnodeds
{


   main_document::main_document(::aura::application * papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {
   }

   main_document::~main_document()
   {
   }


   bool main_document::on_new_document()
   {
      if (!::aura::document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
   }


#ifdef DEBUG
   void main_document::assert_valid() const
   {
      ::aura::document::assert_valid();
   }

   void main_document::dump(dump_context & dumpcontext) const
   {
      ::aura::document::dump(dumpcontext);
   }
#endif //DEBUG


   bool main_document::on_open_document(var varFile)
   {

      ::netnodeds::netnodeds & netnodeds = Application.netnodeds();
      sp(::create) cc(get_app());
      cc->m_spCommandLine->m_varFile = varFile;
      return netnodeds.m_ptemplate_netnodeds->open_document_file(cc) != NULL;

   }


   bool main_document::on_save_document(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
      return TRUE;
   }




} // namespace netnodeds



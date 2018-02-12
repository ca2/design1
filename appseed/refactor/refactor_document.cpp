#include "framework.h"


namespace refactor
{


   document::document(::aura::application * papp) :
      ::object(papp),
      ::user::controller(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_file(papp)
   {
   }

   document::~document()
   {
   }


#ifdef DEBUG
   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }
#endif //DEBUG


   bool document::on_open_document(var varFile)
   {

      //::data::writing writing(get_data());

      if(m_file->IsOpened())
         m_file->close();


      try
      {

         m_file = Application.file().get_file(varFile,::file::type_binary | ::file::mode_read_write | ::file::share_deny_none);

      }
      catch(::exception::base & e)
      {

         string strMessage;

         string strError;

         strError = e.m_pszMessage;

         strMessage.Format("Failed to open file. Error: %s", strError);

         System.simple_message_box(NULL, strMessage);

         return false;

      }

      /*::ex1::file_exception_sp fe(get_app());
      if(!m_file->open(varFile, ::file::type_binary | ::file::mode_read_write | ::file::shareDenyNone, &fe))
      {
         string strMessage;
         string strError;
         fe->GetErrorMessage(strError);
         strMessage.Format("Failed to open file. Error: %s", strError);
         System.simple_message_box(NULL, strMessage);
         return FALSE;
      }*/

      set_path_name(varFile);

      update_all_views(NULL, 11);

      return true;

   }


} // namespace refactor



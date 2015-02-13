#include "framework.h"


namespace biteditor
{


   main_document::main_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp),
      m_memfile(papp),
      m_file(papp)
   {

      string str = "\
                   Curitiba, 24 de fevereiro de 2008.\n\
                   \n\
                   The LoadCursor function loads the cursor resource only\n\
                   if it has not been loaded; otherwise, it retrieves the\n\
                   handle to the existing resource. This function returns\n\
                   a valid cursor handle only if the lpCursorName parameter\n\
                   is a pointer to a cursor resource. If lpCursorName is\n\
                   a pointer to any type of resource other than a cursor\n\
                   (such as an icon), the return value is not NULL, even\n\
                   though it is not a valid cursor handle.\n\
                   ";

   }

   bool main_document::on_new_document()
   {
      if (!::aura::document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
   }

   main_document::~main_document()
   {
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



   void main_document::data_on_after_change(::signal_details * pobj)
   {


      UNREFERENCED_PARAMETER(pobj);


   }

   bool main_document::on_open_document(var varFile)
   {


      if(m_file->IsOpened())
         m_file->close();


      if(!m_file->open(varFile, ::file::type_binary | ::file::mode_read_write))
         return FALSE;

      return TRUE;

   }


   bool main_document::on_save_document(const char * lpszPathName)
   {

      UNREFERENCED_PARAMETER(lpszPathName);

      return TRUE;


   }



} // namespace biteditor




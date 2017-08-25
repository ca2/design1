#include "framework.h"


namespace netnodeds
{


   front_document::front_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_memfile(papp), 
      m_file(papp),
      m_memfileBody(papp),
      html_document(papp)
   {


   }

   front_document::~front_document()
   {
   }

   bool front_document::_001OnUpdateCmdUi(::user::command * pcommand)
   {
      string strId(pcommand->m_id);
      if(strId == "start")
      {
         OnUpdateStart(pcommand);
         return TRUE;
      }
      else if(strId == "edit::undo")
      {
         OnUpdateEditUndo(pcommand);
         return TRUE;
      }
      else if(strId == "edit::redo")
      {
         OnUpdateEditRedo(pcommand);
         return TRUE;
      }
      // xyzxyz
      //return html_document::_001OnCmdMsg(pcommand);
      return false;
   }

   bool front_document::_001OnCommand(id id)
   {
      if(id == "start")
      {
         OnStart();
         return true;
      }
      else if(id == "edit::undo")
      {
         OnEditUndo();
         return true;
      }
      else if(id == "edit::redo")
      {
         OnEditRedo();
         return true;
      }
//      return html_document::_001OnCommand(id);
      // xyzxyz
      return false;
   }


   bool front_document::on_new_document()
   {
      if (!html_document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
   }



#ifdef DEBUG
   void front_document::assert_valid() const
   {
      html_document::assert_valid();
   }

   void front_document::dump(dump_context & dumpcontext) const
   {
      html_document::dump(dumpcontext);
   }
#endif //DEBUG


   bool front_document::on_open_document(var varFile)
   {
      UNREFERENCED_PARAMETER(varFile);
      //if(m_file.IsOpened())
      // m_file.close();
      //if(!m_file.open(lpszPathName, ::file::type_binary | ::file::mode_read_write))
      // return FALSE;
      return TRUE;
   }


   bool front_document::on_save_document(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
      return TRUE;
   }

   void front_document::OnUpdateStart(::user::command *pcommand)
   {
      pcommand->Enable(TRUE);
   }

   void front_document::OnUpdateEditUndo(::user::command *pcommand)
   {
      UNREFERENCED_PARAMETER(pcommand);
   }

   void front_document::OnUpdateEditRedo(::user::command *pcommand)
   {
      UNREFERENCED_PARAMETER(pcommand);
   }

   void front_document::OnStart()
   {
      open_document("http://localhost:10011/");
   }

   void front_document::OnEditUndo()
   {
   }

   void front_document::OnEditRedo()
   {
   }



   void front_document::get_output(const char * lpcsz, string & strHead, ::memory_file & file)
   {

      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(strHead);

      file = m_memfileBody;


   }



} // namespace netnodeds




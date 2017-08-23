#include "framework.h"


namespace biteditor
{


   front_document::front_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_memfile(papp),
      m_file(papp),
      html_document(papp)
   {
   }

   bool front_document::on_simple_action(::user::command * pcommand)
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
      return html_document::on_simple_action(id);
   }

   bool front_document::on_simple_update(command_ui * pcommandui)
   {
      if(pcommandui->m_id == "start")
      {
         OnUpdateStart(pcommandui);
         return TRUE;
      }
      else if(pcommandui->m_id == "edit::undo")
      {
         OnUpdateEditUndo(pcommandui);
         return TRUE;
      }
      else if(pcommandui->m_id == "edit::redor")
      {
         OnUpdateEditRedo(pcommandui);
         return TRUE;
      }
      return html_document::on_simple_update(pcommandui);
   }

   bool front_document::on_new_document()
   {
      if (!html_document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
   }

   front_document::~front_document()
   {
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

   void front_document::OnUpdateStart(command_ui *pcommandui)
   {
      pcommandui->Enable(TRUE);
   }

   void front_document::OnUpdateEditUndo(command_ui *pcommandui)
   {
      UNREFERENCED_PARAMETER(pcommandui);
   }

   void front_document::OnUpdateEditRedo(command_ui *pcommandui)
   {
      UNREFERENCED_PARAMETER(pcommandui);
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


} // namespace biteditor




#include "framework.h"


namespace netnodeds
{


   html_stage_document::html_stage_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_memfile(papp),
      m_file(papp), 
      html_document(papp)
   {

      m_iBranch = 0;

   }



   html_stage_document::~html_stage_document()
   {
   }



   bool html_stage_document::_001OnUpdateCmdUi(::user::command * pcommand)
   {

      string strId(pcommand->m_id);
      if(strId == "file::save")
      {
         OnUpdateFileSave(pcommand);
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
//      return html_document::_001OnUpdateCmdUi(pcommand);
      return false;
   }

   bool html_stage_document::_001OnCommand(id id)
   {
      if(id == "file::save")
      {
         on_file_save();
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
         return TRUE;
      }
      // xyzxyz
      // return html_document::_001OnCommand(id);
      return false;
   }


   bool html_stage_document::on_new_document()
   {
      if (!html_document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
   }

#ifdef DEBUG
   void html_stage_document::assert_valid() const
   {
      html_document::assert_valid();
   }

   void html_stage_document::dump(dump_context & dumpcontext) const
   {
      html_document::dump(dumpcontext);
   }
#endif //DEBUG


   bool html_stage_document::on_open_document(var varFile)
   {
      return html_document::on_open_document(varFile);
   }


   bool html_stage_document::on_save_document(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
      return TRUE;
   }

   void html_stage_document::OnUpdateFileSave(::user::command *pcommand)
   {
      pcommand->Enable(TRUE);
   }

   void html_stage_document::OnUpdateEditUndo(::user::command *pcommand)
   {
      UNREFERENCED_PARAMETER(pcommand);
   }

   void html_stage_document::OnUpdateEditRedo(::user::command *pcommand)
   {
      UNREFERENCED_PARAMETER(pcommand);
   }

   void html_stage_document::on_file_save()
   {
      html_document::on_file_save();
   }

   void html_stage_document::OnEditUndo()
   {
   }

   void html_stage_document::OnEditRedo()
   {
   }





} // namespace netnodeds




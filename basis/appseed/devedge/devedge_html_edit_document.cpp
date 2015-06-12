#include "framework.h"


namespace devedge
{


   html_edit_document::html_edit_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_memfile(papp), 
      m_file(papp),
      html_document(papp)
   {
   }

   html_edit_document::~html_edit_document()
   {
   }

   bool html_edit_document::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      string strId(pcmdui->m_id);
      if(strId == "file::save")
      {
         OnUpdateFileSave(pcmdui);
         return TRUE;
      }
      else if(strId == "edit::undo")
      {
         OnUpdateEditUndo(pcmdui);
         return TRUE;
      }
      else if(strId == "edit::redo")
      {
         OnUpdateEditRedo(pcmdui);
         return TRUE;
      }
      // xyzxyz
//      return html_document::_001OnUpdateCmdUi(pcmdui);
      return false;
   }

   bool html_edit_document::_001OnCommand(id id)
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
         return true;
      }
      // xyzxyz
      //return html_document::_001OnCommand(id);
      return false;
   }


   bool html_edit_document::on_new_document()
   {
      if (!html_document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
   }




#ifdef DEBUG
   void html_edit_document::assert_valid() const
   {
      html_document::assert_valid();
   }

   void html_edit_document::dump(dump_context & dumpcontext) const
   {
      html_document::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // html_edit_document serialization

   /*
   void html_edit_document::Serialize(CArchive& ar)
   {
   if (ar.IsStoring())
   {
   // TODO: add storing code here
   }
   else
   {
   // TODO: add loading code here
   }
   }
   */

   bool html_edit_document::on_open_document(var varFile)
   {
      UNREFERENCED_PARAMETER(varFile);
      //if(m_file.IsOpened())
      // m_file.close();
      //if(!m_file.open(lpszPathName, ::file::type_binary | ::file::mode_read_write))
      //   return FALSE;
      return TRUE;
   }


   bool html_edit_document::on_save_document(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
      return TRUE;
   }

   void html_edit_document::OnUpdateFileSave(cmd_ui *pcmdui)
   {
      pcmdui->Enable(TRUE);
   }

   void html_edit_document::OnUpdateEditUndo(cmd_ui *pcmdui)
   {
      UNREFERENCED_PARAMETER(pcmdui);
   }

   void html_edit_document::OnUpdateEditRedo(cmd_ui *pcmdui)
   {
      UNREFERENCED_PARAMETER(pcmdui);
   }

   void html_edit_document::on_file_save()
   {
      html_document::on_file_save();
   }

   void html_edit_document::OnEditUndo()
   {
   }

   void html_edit_document::OnEditRedo()
   {
   }





} // namespace devedge




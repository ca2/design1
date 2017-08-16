#include "framework.h"


namespace biteditor
{


   document::document(::aura::application * papp) :
      ::object(papp),
      ::data::data(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_memfile(papp),
      ::data::tree(papp)
   {
      m_iBranch = 0;
      m_pgroupcommand = NULL;

      m_ptreeitem = get_base_item();

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
      m_memfile.write(str, str.get_length());
      m_pfile = &m_memfile;
      m_peditfile = new ::file::edit_file(get_app());
      m_peditfile->SetFile(m_pfile);


      connect_update_cmd_ui("edit_undo", &document::_001OnUpdateEditUndo);
      connect_command("edit_undo", &document::_001OnEditUndo);
      connect_update_cmd_ui("edit_redo", &document::_001OnUpdateEditRedo);
      connect_command("edit_redo", &document::_001OnEditRedo);
      connect_update_cmd_ui("file_save", &document::_001OnUpdateFileSave);
      connect_command("file_save", &document::_001OnFileSave);
      connect_update_cmd_ui("edit_cut", &document::_001OnUpdateEditCut);
      connect_command("edit_cut", &document::_001OnEditCut);
      connect_update_cmd_ui("edit_copy", &document::_001OnUpdateEditCopy);
      connect_command("edit_copy", &document::_001OnEditCopy);
      connect_update_cmd_ui("edit_paste", &document::_001OnUpdateEditPaste);
      connect_command("edit_paste", &document::_001OnEditPaste);

   }

   bool document::_001OnCmdMsg(::user::command * pcmdmsg)
   {
      /*   sp(::aura::application) papp = ::ca2::get_app();
      CommandIdSpace idspace;
      if (nCode == CN_UPDATE_COMMAND_UI)
      {
      command_ui * pcommandui = (command_ui *) pExtra;
      if(nID == papp->GetResourceId(idspace, "file_save"))
      {
      OnUpdateFileSave(pcommandui);
      return TRUE;
      }
      else if(nID == papp->GetResourceId(idspace, "edit_undo"))
      {
      OnUpdateEditUndo(pcommandui);
      return TRUE;
      }
      else if(nID == 1003)
      {
      OnUpdateEditRedo(pcommandui);
      return TRUE;
      }
      else if(nID == 1004)
      {
      OnUpdateFilePut(pcommandui);
      return TRUE;
      }
      }
      else
      {
      int32_t nMsg = HIWORD(nCode);
      nCode = LOWORD(nCode);

      // for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
      if (nMsg == 0)
      nMsg = WM_COMMAND;

      if(nMsg == WM_COMMAND)
      {
      if(nID == 1001)
      {
      on_file_save();
      return TRUE;
      }
      else if(nID == 1002)
      {
      OnEditUndo();
      return TRUE;
      }
      else if(nID == 1003)
      {
      OnEditRedo();
      return TRUE;
      }
      else if(nID == 1004)
      {
      OnFilePut();
      return TRUE;
      }
      }
      }*/
      return ::user::document::_001OnCmdMsg(pcmdmsg);
   }


   bool document::on_new_document()
   {
      if (!::user::document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      return TRUE;
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

   /////////////////////////////////////////////////////////////////////////////
   // document serialization

   /*
   void document::Serialize(CArchive& ar)
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


   void document::data_on_after_change(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool document::on_open_document(var varFile)
   {

      ::file::file_sp spfile;
      m_bReadOnly = false;
      spfile = Application.file().get_file(varFile, ::file::type_binary | ::file::mode_read_write | ::file::share_deny_none);
      if(spfile.is_null())
      {
         m_bReadOnly = true;
         spfile = Application.file().get_file(varFile, ::file::type_binary | ::file::mode_read | ::file::share_deny_none);
         if(spfile.is_null())
            return FALSE;
      }
      m_pfile = spfile;
      m_peditfile->SetFile(m_pfile);
      //update_all_views(NULL);
      return TRUE;

   }

   void document::reload()
   {
      if(m_pfile != &m_memfile)
      {
         if(m_pfile->IsOpened())
            m_pfile->close();
         if(!m_pfile->open(get_file_path(), ::file::type_binary | ::file::mode_read_write |
            ::file::share_deny_none))
            return;
      }
      m_peditfile->SetFile(m_pfile);
      update_all_views(NULL);
   }


   bool document::on_save_document(const char * lpszPathName)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
      m_peditfile->flush();
      return TRUE;
   }

   void document::_001OnUpdateFileSave(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
         pcommandui->Enable(TRUE);
   }

   void document::_001OnUpdateFilePut(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
         pcommandui->Enable(TRUE);
   }

   void document::_001OnUpdateEditUndo(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
         pcommandui->Enable(m_peditfile->CanUndo());
   }

   void document::_001OnUpdateEditRedo(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
         pcommandui->Enable(m_peditfile->GetRedoBranchCount() > 0);
   }

   void document::_001OnUpdateEditCut(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
         pcommandui->Enable(TRUE);
   }

   void document::_001OnUpdateEditCopy(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
         pcommandui->Enable(TRUE);
   }

   void document::_001OnUpdateEditPaste(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
         pcommandui->Enable(TRUE);
   }

   void document::_001OnFileSave(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::biteditor::document::on_file_save();
   }

   void document::_001OnEditCut(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void document::_001OnEditCopy(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void document::_001OnEditPaste(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void document::_001OnFilePut(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::biteditor::document::on_file_save();
      Put();
   }

   void document::_001OnEditUndo(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Undo();
   }

   void document::_001OnEditRedo(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Redo();
   }

   void document::MacroRecord(sp(Command) pcommand)
   {

      if(m_pgroupcommand != NULL && m_pgroupcommand != pcommand)
      {

         m_pgroupcommand->add(pcommand);

         return;

      }

      if(m_ptreeitem->get_expandable_children_count() > 0 && m_iBranch < m_ptreeitem->get_expandable_children_count())
      {

         m_ptreeitem = m_ptreeitem->get_expandable_child(m_iBranch);

      }

      sp(::data::tree_item) pitem = insert_item(pcommand, ::data::RelativeLastSibling, m_ptreeitem);

      if(pitem != NULL)
      {

         m_ptreeitem = pitem;

      }

   }


   bool document::CanUndo()
   {
      return m_ptreeitem != get_base_item();
   }


   int32_t document::GetRedoBranchCount()
   {
      return (int32_t) (m_ptreeitem->get_expandable_children_count()
         + (m_ptreeitem->get_next() != NULL ? 1 : 0)
         + (m_ptreeitem->first_child() != NULL ? 1 : 0));
   }

   bool document::Undo()
   {
      if(!CanUndo())
         return false;

      sp(Command) pcommand = (sp(Command)) m_ptreeitem->m_pitem;
      pcommand->Undo(this);
      m_ptreeitem = m_ptreeitem->get_previous_or_parent();
      update_all_views(NULL, 789231, NULL);
      return true;
   }
   bool document::Redo()
   {
      if(m_iBranch < 0
         || m_iBranch >= GetRedoBranchCount())
      {
         return false;
      }
      sp(Command) pcommand = NULL;
      sp(::data::tree_item) ptreeitem;
      if(m_iBranch < m_ptreeitem->get_expandable_children_count())
      {
         ptreeitem = m_ptreeitem->get_expandable_child(m_iBranch);
      }
      else if(m_ptreeitem->get_next() != NULL)
      {
         ptreeitem = m_ptreeitem->get_next();
      }
      else
      {
         ptreeitem = m_ptreeitem->first_child();
      }
      if(ptreeitem == NULL)
         return true;
      m_ptreeitem = ptreeitem;
      pcommand = (sp(Command)) ptreeitem->m_pitem;
      pcommand->Redo(this);
      update_all_views(NULL, 789231, NULL);
      return true;
   }

   void document::MacroBegin()
   {
      sp(GroupCommand) pgroupcommand = new GroupCommand;
      pgroupcommand->m_pparent = m_pgroupcommand;
      m_pgroupcommand = pgroupcommand;
   }

   void document::MacroEnd()
   {
      if(m_pgroupcommand == NULL)
      {
         ASSERT(FALSE);
         return;
      }
      if(m_pgroupcommand->m_pparent == NULL)
      {
         MacroRecord(m_pgroupcommand);
      }
      m_pgroupcommand = m_pgroupcommand->m_pparent;
   }


   void document::SetSelCommand::Undo(sp(::biteditor::document) pdoc)
   {
      pdoc->m_iSelStart = m_iPreviousSelStart;
      pdoc->m_iSelEnd = m_iPreviousSelEnd;
      pdoc->update_all_views(NULL, 789232, NULL);
   }
   void document::SetSelCommand::Redo(sp(::biteditor::document) pdoc)
   {
      pdoc->m_iSelStart = m_iSelStart;
      pdoc->m_iSelEnd = m_iSelEnd;
      pdoc->update_all_views(NULL, 789232, NULL);
   }

   void document::FileCommand::Undo(sp(::biteditor::document) pdoc)
   {
      pdoc->m_peditfile->Undo();
      pdoc->update_all_views(NULL, 1001, NULL);
   }

   void document::FileCommand::Redo(sp(::biteditor::document) pdoc)
   {
      pdoc->m_peditfile->Redo();
      pdoc->update_all_views(NULL, 1001, NULL);
   }


   void document::GroupCommand::Undo(sp(::biteditor::document) pdoc)
   {
      for(index i = get_upper_bound(); i >= 0; i--)
      {
         element_at(i)->Undo(pdoc);
      }
   }
   void document::GroupCommand::Redo(sp(::biteditor::document) pdoc)
   {
      for(index i = 0; i < get_size(); i++)
      {
         element_at(i)->Redo(pdoc);
      }
   }

   void document::Put()
   {

      ::file::path strFolder = System.dir().element();
      
      string strCommon;

      string strRemote;

      strCommon = strFolder / "cast\\seed\\ca2\\fontopus\\net\\ds\\common";

      if(strCommon.compare_ci(get_file_path().Mid(0, strCommon.get_length())) == 0)
      {
         strCommon = get_file_path().Mid(strCommon.get_length());
         strCommon.replace("\\", "/");
         strRemote = "cast/seed/ca2/fontopus/net/ds/common" + strCommon;
         FtpPut(get_file_path(), strRemote);
      }
   }

   void document::FtpPut(const char * lpcszLocal, const char * lpcszRemote)
   {
      UNREFERENCED_PARAMETER(lpcszLocal);
      UNREFERENCED_PARAMETER(lpcszRemote);
      throw not_implemented(get_app());

      //   CInternetSession Sess("MyProgram/1.0");

      /* CFtpConnection* pConnect = NULL;

      try
      {
      // Request a connection to ftp.microsoft.com. Default
      // parameters mean that we'll try with username = ANONYMOUS
      // and password set to the machine name @ domain name
      pConnect = sess.GetFtpConnection(file_contents_dup("C:\\archive\\root\\x\\sensitive\\sensitive\\seed\\netnodeds_host.txt"),file_contents_dup("C:\\archive\\root\\x\\sensitive\\sensitive\\seed\\netnodeds_user.txt"), file_contents_dup("C:\\archive\\root\\x\\sensitive\\sensitive\\seed\\netnodeds_pass.txt"));

      pConnect->PutFile(lpcszLocal, lpcszRemote);

      }
      catch (CInternetException* pEx)
      {
      string str;
      pEx->get_error_message(str);
      printf_s("ERROR!  %s\n", str);
      pEx->Delete();
      }

      // if the connection is open, close it
      if (pConnect != NULL)
      {
      pConnect->close();
      delete pConnect;
      }
      */
   }


   sp(::data::item) document::on_allocate_item()
   {
      return new Command;
   }



} // namespace biteditor



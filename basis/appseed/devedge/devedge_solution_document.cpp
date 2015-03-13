#include "framework.h"


namespace devedge
{


   solution_document::solution_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp),
      m_file(papp),
      m_fileSave(papp)
   {


      m_psolution = NULL;


      m_pview = NULL;
      m_iBranch = 0;

      //command_signalid id;
      //::ca::signalid * pid;


      /*id.m_id = System.id("edit_undo";
      pid = m_signalidaCommand.get(&id);
      id.m_id = "edit_redo";
      pid = m_signalidaCommand.get(&id);
      id.m_id = "file_save";
      pid = m_signalidaCommand.get(&id);*/
      connect_update_cmd_ui("file_save", &solution_document::_001OnUpdateFileSave);
      connect_command("file_save", &solution_document::_001OnFileSave);
      connect_update_cmd_ui("edit_cut", &solution_document::_001OnUpdateEditCut);
      connect_command("edit_cut", &solution_document::_001OnEditCut);
      connect_update_cmd_ui("edit_copy", &solution_document::_001OnUpdateEditCopy);
      connect_command("edit_copy", &solution_document::_001OnEditCopy);
      connect_update_cmd_ui("edit_paste", &solution_document::_001OnUpdateEditPaste);
      connect_command("edit_paste", &solution_document::_001OnEditPaste);
      connect_command("file_new", &solution_document::_001OnFileNew);
      connect_update_cmd_ui("file_new", &solution_document::_001OnUpdateFileNew);
   }


   solution_document::~solution_document()
   {
   }




   bool solution_document::on_new_document()
   {
      if (!::aura::document::on_new_document())
         return FALSE;

      set_path_name(Application.file().time_square());
      if(m_file->IsOpened())
         m_file->close();
      if(!m_file->open(get_file_path(), ::file::type_binary | ::file::mode_read_write |
         ::file::share_deny_none))
         return FALSE;

      update_all_views(NULL, 11);

      return TRUE;
   }

 
   #ifdef DEBUG
   void solution_document::assert_valid() const
   {
      ::aura::document::assert_valid();
   }

   void solution_document::dump(dump_context & dumpcontext) const
   {
      ::aura::document::dump(dumpcontext);
   }
   #endif //DEBUG


   bool solution_document::on_open_document(var varFile)
   {
      //if(!::aura::document::on_open_document(varFile))
        // return FALSE;

      m_psolution = new ::devedge::solution(this);

      if(m_psolution == NULL)
         return false;

      m_pview = get_typed_view < solution_view > ();

      set_path_name(varFile);

      if(!m_psolution->load(varFile, m_pview))
      {
         
         delete_contents();

         return false;

      }

      

      return true;

   }


   void solution_document::reload()
   {
      if(m_file->IsOpened())
         m_file->close();
      if(!m_file->open(get_file_path(), ::file::type_binary | ::file::mode_read_write |
         ::file::share_deny_none))
         return;
      update_all_views(NULL, 123);
   }


   bool solution_document::on_save_document(const char * lpszPathName)
   {
      if(!m_fileSave->open(lpszPathName, ::file::type_binary | ::file::mode_read_write | ::file::mode_create))
         return FALSE;
      update_all_views(NULL, 12345);
      return TRUE;
   }

   void solution_document::_001OnUpdateFileSave(::signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnUpdateFileNew(::signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnUpdateFilePut(::signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }


   void solution_document::_001OnUpdateEditCut(::signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnUpdateEditCopy(::signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnUpdateEditPaste(::signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void solution_document::_001OnFileSave(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::aura::document::on_file_save();
   }

   void solution_document::_001OnFileNew(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::aura::document::on_new_document();
   }

   void solution_document::_001OnEditCut(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void solution_document::_001OnEditCopy(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void solution_document::_001OnEditPaste(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void solution_document::_001OnFilePut(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::aura::document::on_file_save();
      Put();
   }




   void solution_document::Put()
   {
      ::file::path strFolder = System.dir().element();
      string strCommon;
      string strRemote;
      strCommon = strFolder / "seed\\ca\\fontopus\\net\\ds\\common";
      if(strCommon.CompareNoCase(get_file_path().Mid(0, strCommon.get_length())) == 0)
      {
         strCommon = get_file_path().Mid(strCommon.get_length());
         strCommon.replace("\\", "/");
         strRemote = "seed/ca/fontopus/net/ds/common" + strCommon;
         FtpPut(get_file_path(), strRemote);
      }
   }

   void solution_document::FtpPut(const char * lpcszLocal, const char * lpcszRemote)
   {
      UNREFERENCED_PARAMETER(lpcszLocal);
      UNREFERENCED_PARAMETER(lpcszRemote);
      throw not_implemented(get_app());
   /*   CInternetSession sess("MyProgram/1.0");

      CFtpConnection* pConnect = NULL;

       try
       {
           // Request a connection to ftp.microsoft.com. Default
           // parameters mean that we'll try with username = ANONYMOUS
           // and password set to the machine name @ domain name
           pConnect = sess.GetFtpConnection("ca2os.com", "ca2os", "1p.t5mL.1..");

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





} // namespace devedge




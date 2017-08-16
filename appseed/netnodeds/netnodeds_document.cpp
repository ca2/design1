#include "framework.h"


namespace netnodeds
{


   document::document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_file(papp)
   {

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
      connect_update_cmd_ui("file_save", &document::_001OnUpdateFileSave);
      connect_command("file_save", &document::_001OnFileSave);
      connect_update_cmd_ui("edit_cut", &document::_001OnUpdateEditCut);
      connect_command("edit_cut", &document::_001OnEditCut);
      connect_update_cmd_ui("edit_copy", &document::_001OnUpdateEditCopy);
      connect_command("edit_copy", &document::_001OnEditCopy);
      connect_update_cmd_ui("edit_paste", &document::_001OnUpdateEditPaste);
      connect_command("edit_paste", &document::_001OnEditPaste);
      connect_command("file_new", &document::_001OnFileNew);
      connect_update_cmd_ui("file_new", &document::_001OnUpdateFileNew);
   }



   bool document::on_new_document()
   {
      
      if (!::user::document::on_new_document())
         return FALSE;

      set_path_name(Application.file().time_square());
      
      if(m_file->IsOpened())
         m_file->close();

      if(!m_file->open(get_file_path(), ::file::type_binary | ::file::mode_read_write | ::file::share_deny_none))
         return FALSE;

      update_all_views(NULL, 11);

      return true;

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
      // xyzxyz
      //::data::lock writing(get_data());

      if(m_file->IsOpened())
         m_file->close();


      try
      {

         m_file = Application.file().get_file(varFile, ::file::type_binary | ::file::mode_read_write | ::file::share_deny_none);

      }
      catch(::exception::base & e)
      {
         
         string strMessage;
         
         string strError;

         e.get_error_message(strError);

         strMessage.Format("Failed to open file. Error: %s", strError);

         System.simple_message_box(NULL, strMessage);

         return false;

      }

      /*::ca::file_exception_sp fe(get_app());
      if(!m_file->open(varFile, ::file::type_binary | ::file::mode_read_write | ::file::share_deny_none, &fe))
      {
         string strMessage;
         string strError;
         fe->get_error_message(strError);
         strMessage.Format("Failed to open file. Error: %s", strError);
         System.simple_message_box(NULL, strMessage);
         return FALSE;
      }*/
      
      set_path_name(varFile);
      
      update_all_views(NULL, 11);

      return true;

   }

   void document::reload()
   {
      if(m_file->IsOpened())
         m_file->close();
      if(!m_file->open(get_file_path(), ::file::type_binary | ::file::mode_read_write |
         ::file::share_deny_none))
         return;
      update_all_views(NULL, 123);
   }



   void document::_001OnUpdateFileSave(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
      pcommandui->Enable(TRUE);
   }

   void document::_001OnUpdateFileNew(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
      pcommandui->Enable(TRUE);
   }

   void document::_001OnUpdateFilePut(::signal_details * pobj)
   {
      SCAST_PTR(::command_ui, pcommandui, pobj);
      pcommandui->Enable(TRUE);
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
      ::user::document::on_file_save();
   }

   void document::_001OnFileNew(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::user::document::on_new_document();
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
      ::user::document::on_file_save();
      Put();
   }


   void document::Put()
   {
      
      ::file::path strFolder = System.dir().element();

      string strCommon;

      string strRemote;

      strCommon = strFolder / "seed\\ca\\fontopus\\net\\ds\\common";

      if(strCommon.compare_ci(get_file_path().Mid(0, strCommon.get_length())) == 0)
      {
         
         strCommon = get_file_path().Mid(strCommon.get_length());

         strCommon.replace("\\", "/");

         strRemote = ::file::path("seed/ca/fontopus/net/ds/common") / strCommon;

         FtpPut(get_file_path(), strRemote);

      }

   }


   void document::FtpPut(const char * lpcszLocal, const char * lpcszRemote)
   {
      UNREFERENCED_PARAMETER(lpcszLocal);
      UNREFERENCED_PARAMETER(lpcszRemote);
      throw not_implemented(get_app());
/*      CInternetSession sess("MyProgram/1.0");

      CFtpConnection* pConnect = NULL;

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


   sp(view) document::get_edit_view()
   {


      return get_typed_view < view > ();


   }

   void document::write(::file::byte_ostream & ostream)
   {
      update_all_views(NULL, 771984, &ostream);
   }



} // namespace netnodeds



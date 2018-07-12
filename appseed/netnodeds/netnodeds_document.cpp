﻿#include "framework.h"


namespace netnodeds
{


   document::document(::aura::application * papp) :
      ::object(papp),
      ::user::controller(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      m_file(papp)
   {

      m_pview = NULL;
      m_iBranch = 0;


      //command_signalid id;
      //::ca::message::senderid * pid;


      /*id.m_id = System.id("edit_undo";
      pid = m_signalidaCommand.get(&id);
      id.m_id = "edit_redo";
      pid = m_signalidaCommand.get(&id);
      id.m_id = "file_save";
      pid = m_signalidaCommand.get(&id);*/
      connect_command_probe("file_save", &document::_001OnUpdateFileSave);
      connect_command("file_save", &document::_001OnFileSave);
      connect_command_probe("edit_cut", &document::_001OnUpdateEditCut);
      connect_command("edit_cut", &document::_001OnEditCut);
      connect_command_probe("edit_copy", &document::_001OnUpdateEditCopy);
      connect_command("edit_copy", &document::_001OnEditCopy);
      connect_command_probe("edit_paste", &document::_001OnUpdateEditPaste);
      connect_command("edit_paste", &document::_001OnEditPaste);
      connect_command("file_new", &document::_001OnFileNew);
      connect_command_probe("file_new", &document::_001OnUpdateFileNew);
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




   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }



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



   void document::_001OnUpdateFileSave(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      pcommand->Enable(TRUE);
   }

   void document::_001OnUpdateFileNew(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      pcommand->Enable(TRUE);
   }

   void document::_001OnUpdateFilePut(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      pcommand->Enable(TRUE);
   }


   void document::_001OnUpdateEditCut(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      pcommand->Enable(TRUE);
   }

   void document::_001OnUpdateEditCopy(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      pcommand->Enable(TRUE);
   }

   void document::_001OnUpdateEditPaste(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      pcommand->Enable(TRUE);
   }

   void document::_001OnFileSave(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::user::document::on_file_save();
   }

   void document::_001OnFileNew(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::user::document::on_new_document();
   }

   void document::_001OnEditCut(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void document::_001OnEditCopy(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void document::_001OnEditPaste(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void document::_001OnFilePut(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::user::document::on_file_save();
      Put();
   }


   void document::Put()
   {

      ::file::path strFolder = System.dir().install();

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
      _throw(not_implemented(get_app()));
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

   void document::write(serialize & ostream)
   {
      update_all_views(NULL, 772000, &ostream);
   }



} // namespace netnodeds



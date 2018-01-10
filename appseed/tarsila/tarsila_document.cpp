#include "framework.h"


namespace tarsila
{


   document::document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::controller(papp),
      ::user::document(papp)
   {

      connect_command("file_save",&document::_001OnFileSave);
      connect_command("file_save_as",&document::_001OnFileSaveAs);

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


   bool document::on_open_document(var varFile)
   {



      data * pdata = new data(get_app());


      add_data(pdata);


      ::xml::document document(get_app());

      if(!document.load(Application.file().as_string(varFile)))
      {
         do_save(varFile);
         return true;
      }

      ::xml::input_tree xmlif(get_app(),Application.m_pxmlschemaDrawing);

      xmlif.m_pdocument = &document;

      pdata->xml_import(xmlif);

      
      //::data::lock writing(get_typed_data < ::user::plain_text_tree >());

      //if(m_file.is_set() && m_file->IsOpened())
      //   m_file->close();

      //string strFile;

      //if(varFile.get_type() == ::var::type_string
      //   || varFile.get_type() == ::var::type_pstring)
      //{

      //   strFile = varFile;

      //}
      //else if(varFile.get_type() == var::type_propset)
      //{

      //   if(varFile.has_property("url"))
      //   {

      //      strFile = varFile["url"];

      //   }

      //}

      //try
      //{

      //   m_file = Application.file().get_file(varFile,::file::type_binary | ::file::mode_read_write | ::file::share_deny_none);

      //}
      //catch(::file::exception & e)
      //{

      //   if(e.m_cause == ::file::exception::badPath)
      //   {

      //      get_typed_view < view >()->GetTypedParent < pane_view >()->remove_tab_by_id("veriedit://" + e.m_strFileName);
      //      return false;

      //   }

      //   string strMessage;

      //   string strError;

      //   e.get_error_message(strError);

      //   strMessage.Format("Failed to open file. Error: %s",strError);

      //   System.simple_message_box(NULL,strMessage);

      //   return false;

      //}
      //catch(::exception::base & e)
      //{

      //   string strMessage;

      //   string strError;

      //   e.get_error_message(strError);

      //   strMessage.Format("Failed to open file. Error: %s",strError);

      //   System.simple_message_box(NULL,strMessage);

      //   return false;

      //}

      //if(m_file.is_null())
      //{

      //   string strMessage;

      //   strMessage = "";

      //   if(strFile.has_char())
      //   {
      //      if(!Application.file().exists(strFile))
      //      {
      //         strMessage = "Failed to open non existent file : \"" + strFile + "\"";
      //      }
      //      else
      //      {
      //         strMessage += "Failed to open file. Unknown error. File path : " + strFile;
      //      }
      //   }
      //   else
      //   {
      //      strMessage += "Failed to open file";
      //   }

      //   System.simple_message_box(NULL,strMessage,MB_ICONINFORMATION);

      //   return false;

      //}

      ///*::ca2::file_exception_sp fe(get_app());
      //if(!m_file->open(varFile, ::file::type_binary | ::file::mode_read_write | ::file::share_deny_none, &fe))
      //{
      //string strMessage;
      //string strError;
      //fe->get_error_message(strError);
      //strMessage.Format("Failed to open file. Error: %s", strError);
      //System.simple_message_box(NULL, strMessage);
      //return FALSE;
      //}*/

      //set_path_name(varFile);

      //update_all_views(NULL,::user::impact::hint_set_edit_file);


      return true;

   }

   void document::write(::file::ostream & ostream)
   {

      data * pdata = get_typed_data < data >();

      ::xml::document document(get_app());

      ::xml::output_tree xmlof(get_app(),Application.m_pxmlschemaDrawing);

      xmlof.m_pdocument = &document;

      pdata->xml_export(xmlof);

      ostream.write(document.get_xml());

   }



   void document::_001OnFileSave(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      pobj->m_bRet = true;

      do_save(m_filepath);

   }

   void document::_001OnFileSaveAs(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Application.m_ppaneview->set_cur_tab_by_id("file_manager");
      Application.m_ppaneview->FileManagerSaveAs(this);
   }

} // namespace tarsila




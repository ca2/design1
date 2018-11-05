#include "framework.h"


namespace veritile
{


   document::document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp)
   {
      connect_command("file_save",&document::_001OnFileSave);
      connect_command("file_save_as",&document::_001OnFileSaveAs);
   }


   bool document::on_new_document()
   {

      if (!::user::document::on_new_document())
         return FALSE;


      add_data(canew(data(get_app())));

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


   bool document::add_tileset(const string & strFile)
   {

      try
      {

         Application.ensure_tileset_dock(m_idVeritile);

      }
      catch(...)
      {

         return false;

      }


      sp(tileset) ptileset = canew(tileset(get_app()));

      if(!ptileset->load(strFile))
      {

         return false;

      }

      m_tileseta.add(ptileset);

      sp(tileset_pane_view) ptilesetview = get_typed_view < tileset_pane_view >();

      ptileset->m_strId = ptileset->m_strFile + ":" + get_tileset_count(ptileset->m_strFile);

      ptilesetview->add_tab(::file::path(ptileset->m_strFile).name(),ptileset->m_strId,true,true);

      ptilesetview->set_cur_tab_by_id(ptileset->m_strId);

      return true;

   }

   tileset * document::get_tileset(const string & strId)
   {

      return m_tileseta.pred_ptr_first([=](tileset * ptileset) { return ptileset->m_strId == strId; });

   }

   tileset * document::get_tileset(const string & strPath, index iIndex)
   {

      string strId;
      
      strId += strPath;
      strId += ":";
      strId += ::str::from(iIndex);

      return get_tileset(strId);

   }


   ::count document::get_tileset_count(const string & strPath)
   {

      return m_tileseta.pred_get_count([=](tileset * ptileset) { return ptileset->m_strFile == strPath; });

   }


   bool document::on_open_document(var varFile)
   {

      if(::str::ends_ci(varFile.get_string(),".png"))
      {

         return add_tileset(varFile);

      }


      data * pdata = new data(get_app());

      if (::str::ends_ci(varFile.get_string(), ".tmx"))
      {

         pdata->m_bTmx = true;

      }

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

   void document::write(serialize & ostream)
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

} // namespace veritile




#include "framework.h"


namespace netnodeds
{


   view::view(::aura::application * papp) :
      ::object(papp),
      ::data::listener(papp),
      ::user::interaction(papp), 
      ::user::scroll_view(papp),
      ::user::edit_plain_text(papp),
      ::user::edit_plain_text_view(papp)
   {


      m_bMultiLine = true;
      m_bColorerTake5 = true;

      connect_update_cmd_ui("edit_undo", &view::_001OnUpdateEditUndo);
      connect_command("edit_undo", &view::_001OnEditUndo);
      connect_update_cmd_ui("edit_redo", &view::_001OnUpdateEditRedo);
      connect_command("edit_redo", &view::_001OnEditRedo);



   }

   view::~view()
   {
   }



   #ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::edit_plain_text_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::edit_plain_text_view::dump(dumpcontext);
   }
   #endif //DEBUG

   void view::on_update(::aura::impact * pSender, LPARAM lHint, ::object * phint) 
   {
      ::user::edit_plain_text_view::on_update(pSender, lHint, phint);
      if(lHint == 1001)
      {
         _001RedrawWindow();
      }
      else if(lHint == 11)
      {
         post_message(WM_USER, 11);
      }
      else if(lHint == 123)
      {
         //m_pdata->SetFile(get_document()->m_file);
         //colorer_select_type();
         //::ca::client_graphics pdc(this);
         //_001OnCalcLayout(pdc);
         //
         //_001LayoutScrollBars();
      }
      else if(lHint == 12345)
      {
//         m_pdata->m_editfile.Save(get_document()->m_fileSave);
      }
      else if(lHint == 1234508)
      {
         //CreateLineIndex();
         //m_bGetTextNeedUpdate = true;
         //RedrawWindow();
         //::ca::client_graphics pdc(this);
         //_001OnCalcLayout(pdc);
         //

         //ThreadProcScrollSize(dynamic_cast < ::user::edit_plain_text * > (this));

      }
      /*xxx if(phint != NULL)
      {
         if(base < main_document >::bases(phint))
         {
           sp(main_document) puh = (sp( main_document) ) phint;
            if(puh->is_type_of(main_document::TypeOnBeforeShowView))
            {
               get_document()->on_save_document(get_document()->get_file_path());
            }
            else if(puh->is_type_of(main_document::TypeOnShowView))
            {
               get_document()->reload();
            }
         }
      }*/
      
   }

   void view::_001OnContextMenu(::signal_details * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
//      int32_t iItem;
//      HRESULT hr;
      //point point = pmouse->m_pt;
      point point;
      Session.get_cursor_pos(&point);
      class point ptClient = point;
      ClientToScreen(&point);
      //ScreenToClient(&ptClient);
      sp(::aura::menu_base) menu = new aura::menu(get_app());
      ::file::text_buffer_sp spfile(get_app());

      ::file::path strModuleFolder = System.get_module_folder();

      if(!spfile->open(strModuleFolder / "netnodeds_contextmenu.xml", ::file::type_text | ::file::mode_read))
         return;

      string str;
      spfile->read_full_string(str);

      xml::document doc(get_app());

      doc.load(str);

      if(menu->LoadMenu(&doc))
      {
         
         menu->TrackPopupMenu(0, point.x, point.y, GetParentFrame(), &menu);

      }

   }

   sp(::netnodeds::document) view::get_document() const
   {
      return  (::user::edit_plain_text_view::get_document());
   }

   void view::_001OnUpdateEditUndo(::signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
         // xyzxyz
      //pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.CanUndo());
   }

   void view::_001OnUpdateEditRedo(::signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
         // xyzxyz
      //pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.GetRedoBranchCount() > 0);
   }

   void view::_001OnEditUndo(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Undo();
   }

   void view::_001OnEditRedo(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Redo();
   }

   void view::_001OnAfterChangeText()
   {
      // xyzxyz
//      ::user::edit_plain_text_view::_001OnAfterChangeText();
      get_document()->set_modified_flag(TRUE);
   }

   void view::install_message_handling(::message::dispatch * pinterface)
   {
      
      ::user::edit_plain_text_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU    , pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_USER           , pinterface, this, &view::_001OnUserMessage);

   }


   void view::_001OnUserMessage(::signal_details * pobj)
   {
      
      SCAST_PTR(::message::base, pbase, pobj);

      if(pbase->m_wparam == 11)
         // xyzxyz
      {
//         m_pdata->SetFile(get_document()->m_file);
         // xyzxyz
//         _001OnUpdate();
//         ::ca::client_graphics pdc(this);
  //       _001OnCalcLayout(pdc);
    //     
      //   _001LayoutScrollBars();
         colorer_select_type();
      }

   }


} // namespace netnodeds



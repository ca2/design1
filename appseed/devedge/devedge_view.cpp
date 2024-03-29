﻿#include "framework.h"


namespace devedge
{


   view::view(::aura::application * papp) :
      ::object(papp),
      ::user::plain_edit(papp),
      ::user::plain_edit_view(papp)
   {

      m_bMultiLine = true;
      m_bColorerTake5 = true;

      connect_command_probe("edit_undo", &view::_001OnUpdateEditUndo);
      connect_command("edit_undo", &view::_001OnEditUndo);
      connect_command_probe("edit_redo", &view::_001OnUpdateEditRedo);
      connect_command("edit_redo", &view::_001OnEditRedo);

   }


   view::~view()
   {

   }





   void view::assert_valid() const
   {
      ::user::plain_edit_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::plain_edit_view::dump(dumpcontext);
   }

   void view::on_update(::user::impact * pSender, LPARAM lHint, ::object * phint)
   {
      ::user::plain_edit_view::on_update(pSender, lHint, phint);
      if(lHint == 1001)
      {
         set_need_redraw();
      }
      else if(lHint == 11)
      {
         post_message(WM_USER, 11);
      }
      else if(lHint == 123)
      {
         //m_pdata->SetFile(get_document()->m_file);
         //colorer_select_type();
         //::ca::client_graphics pgraphics(this);
         //_001OnCalcLayout(pgraphics);
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
         //set_need_redraw();
         //::ca::client_graphics pgraphics(this);
         //_001OnCalcLayout(pgraphics);
         //

         //ThreadProcScrollSize(dynamic_cast < ::user::plain_edit * > (this));

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

   void view::_001OnContextMenu(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj);
//      int32_t iItem;
//      HRESULT hr;
      //point point = pmouse->m_pt;
      point point;
      Session.get_cursor_pos(&point);
      class point ptClient = point;
      ClientToScreen(&point);
      //ScreenToClient(&ptClient);

      sp(::user::menu) menu = new user::menu(get_app());

      ::file::text_buffer_sp spfile(get_app());

      string strModuleFolder;
      strModuleFolder = System.dir().module();

      if(!spfile->open(strModuleFolder /  "devedge_contextmenu.xml", ::file::type_text | ::file::mode_read))
         return;

      string str;
      spfile->read_full_string(str);

      xml::document doc(get_app());

      doc.load(str);

      if(menu->load_menu(&doc))
      {

         menu->track_popup_menu(GetParentFrame());

      }

   }

   sp(::devedge::document) view::get_document() const
   {
      return  (::user::plain_edit_view::get_document());
   }

   void view::_001OnUpdateEditUndo(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      // xyzxyz
      //pcommand->Enable(m_pdata->m_editfile.CanUndo());
   }

   void view::_001OnUpdateEditRedo(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      // xyzxyz
      //pcommand->Enable(m_pdata->m_editfile.GetRedoBranchCount() > 0);
   }

   void view::_001OnEditUndo(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Undo();
   }

   void view::_001OnEditRedo(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Redo();
   }

   void view::_001OnAfterChangeText()
   {
      // xyzxyz
//      ::user::plain_edit_view::_001OnAfterChangeText();
      get_document()->set_modified_flag(TRUE);
   }

   void view::install_message_routing(::message::sender * pinterface)
   {

      ::user::plain_edit_view::install_message_routing(pinterface);
      IGUI_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_MSG_LINK(WM_USER, pinterface, this, &view::_001OnUserMessage);

   }


   void view::_001OnUserMessage(::message::message * pobj)
   {

      SCAST_PTR(::message::base, pbase, pobj);

      if(pbase->m_wparam == 11)
         // xyzxyz
      {
//         m_pdata->SetFile(get_document()->m_file);
         // xyzxyz
//         _001OnUpdate();
//         ::ca::client_graphics pgraphics(this);
         //       _001OnCalcLayout(pgraphics);
         //
         //   _001LayoutScrollBars();
         colorer_select_type();
      }

   }


} // namespace devedge



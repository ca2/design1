#include "framework.h"

namespace abc
{
   string upper(int i)
   {
      string str;
      while(i >= 0)
      {
         int iDigit = i % 26;
         char ch = iDigit + 'A';
         str = ch + str;

         i /= 26;
         i--;
      }
      return str;
   }
}

namespace veritile
{

   
   void property_sheet::callback::on_property_change(property & property)
   {

   }


   property_sheet::property_sheet(::aura::application * papp):
      ::object(papp),
      base_form_list_view(papp),
      m_font(allocer())
   {


      m_pdata = NULL;

      m_iItemHeight  = 24;
      m_iLeftMargin  = 49;
      m_iTopMargin   = 33;

      connect_update_cmd_ui("edit_undo",&property_sheet::_001OnUpdateEditUndo);
      connect_command("edit_undo",&property_sheet::_001OnEditUndo);
      connect_update_cmd_ui("edit_redo",&property_sheet::_001OnUpdateEditRedo);
      connect_command("edit_redo",&property_sheet::_001OnEditRedo);
      connect_update_cmd_ui("media_transfer",&property_sheet::_001OnUpdateMediaTransfer);
      connect_command("media_transfer",&property_sheet::_001OnMediaTransfer);



   }

   property_sheet::~property_sheet()
   {
   }



#ifdef DEBUG


   void property_sheet::assert_valid() const
   {

      base_form_list_view::assert_valid();

   }


   void property_sheet::dump(dump_context & dumpcontext) const
   {

      base_form_list_view::dump(dumpcontext);

   }


#endif //DEBUG


   bool property_sheet::on_simple_command(e_simple_command ecommand,lparam lparam,LRESULT & lresult)
   {

      if(base_form_list_view::on_simple_command(ecommand,lparam,lresult))
         return true;

      switch(ecommand)
      {
      case simple_command_set_edit_file:
      {

      }
      break;
      default:
         break;
      }

      return false;

   }

   void property_sheet::on_update(::user::impact * pSender,LPARAM lHint,::object * phint)
   {

      base_form_list_view::on_update(pSender,lHint,phint);

      if(lHint == 1001)
      {
         _001RedrawWindow();
      }
      else if(lHint == 123)
      {

         //         ::data::lock writing(m_ptree);
         //         
         //         m_ptree->SetFile(get_document()->m_file);
         //         
         //         // todo colorer_select_type();
         //         
         //         _001OnCalcLayout();
         //
         ////         _001LayoutScrollBars();

      }
      else if(lHint == 12345)
      {
         ////m_ptree->m_editfile.Save(get_document()->m_fileSave);
         //m_ptree->m_editfile.flush();
      }
      else if(lHint == ::user::impact::hint_save_to_ostream)
      {

         //::file::ostream & ostream = dynamic_cast < ::file::ostream & > (*phint);

         //m_ptree->m_editfile.SaveTo(ostream);

      }
      else if(lHint == 1234508)
      {
         /*CreateLineIndex();
         m_bGetTextNeedUpdate = true;
         RedrawWindow();

         _001OnCalcLayout();
         */

         //ThreadProcScrollSize(dynamic_cast < ::user::edit_plain_text * > (this));

      }
      /*xxx if(phint != NULL)
      {
      if(base_class <main_document >::bases(phint))
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


   void property_sheet::_001InsertColumns()
   {

      class user::control::descriptor control;

      m_eview = view_report;

      ::user::list_column column;


      //index i;
      //for(i = 0; i < iCount; i++)
      //{
      //   control.m_bTransparent = true;
      //   control.set_type(user::control_type_button);
      //   control.m_typeinfo = System.type_info < ::user::button >();
      //   control.m_id = 1000 + i;
      //   control.add_function(user::control::function_action);
      //   index iControl = _001AddControl(control);

      //   column.m_iWidth = 18;
      //   column.m_iSubItem = i;
      //   column.m_iControl = iControl;
      //   column.m_bCustomDraw = true;
      //   column.m_bEditOnSecondClick = true;
      //   column.m_pil = pcallback->GetActionButtonImageList(i);
      //   _001AddColumn(column);
      //}


      column.m_iWidth = 50;
      column.m_iSubItem = 0;
      column.m_iControl = -1;
      _001AddColumn(column);


      control.set_type(user::control_type_edit_plain_text);
      control.m_typeinfo = System.type_info < ::user::plain_edit >();
      control.m_iSubItem = 1;
      control.m_id = "edit";
      index iControl = _001AddControl(control);


      column.m_iWidth = 300;
      column.m_iSubItem = 1;
      column.m_iControl = iControl;
      column.m_bEditOnSecondClick = true;
      column.m_bCustomDraw = true;
      _001AddColumn(column);


   }


   void property_sheet::_001OnContextMenu(::signal_details * pobj)
   {

      track_popup_xml_matter_menu("devedge_contextmenu.xml",0,pobj);

   }


   void property_sheet::_001OnUpdateEditUndo(::signal_details * pobj)
   {

      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);

      //pcmdui->m_pcmdui->Enable(m_ptree->m_editfile.CanUndo());

   }


   void property_sheet::_001OnUpdateEditRedo(::signal_details * pobj)
   {

      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);

      //pcmdui->m_pcmdui->Enable(m_ptree->m_editfile.GetRedoBranchCount() > 0);

   }


   void property_sheet::_001OnEditUndo(::signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      //Undo();

   }


   void property_sheet::_001OnEditRedo(::signal_details * pobj)
   {


      UNREFERENCED_PARAMETER(pobj);

      //Redo();


   }


   void property_sheet::_001GetItemText(::user::mesh_item * pitem)
   {

      if(m_pdata == NULL)
      {

         pitem->m_strText = "-";

         pitem->m_bOk = true;

         return;

      }

      if(pitem->m_iSubItem == 0)
      {

         pitem->m_strText = m_pdata->m_set.at(pitem->m_iItem).m_element1;

         pitem->m_bOk = true;

         return;

      }
      else if(pitem->m_iSubItem == 1)
      {

         pitem->m_strText = m_pdata->m_set.at(pitem->m_iItem).m_element2;

         pitem->m_bOk = true;

         return;

      }

   }


   void property_sheet::_001OnAfterChangeText(::action::context actioncontext)
   {


      //::user::scroll_view::_001OnAfterChangeText(actioncontext);

      if(get_document() != NULL)
      {

         get_document()->set_modified_flag(TRUE);

      }


   }


   void property_sheet::install_message_handling(::message::dispatch * pinterface)
   {


      base_form_list_view::install_message_handling(pinterface);


      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&property_sheet::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU,pinterface,this,&property_sheet::_001OnContextMenu);


   }


   void property_sheet::_001OnCreate(::signal_details * pobj)
   {


      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      m_font->create_point_font("Lucida Console",12.0);

      _001UpdateColumns();

   }


   void property_sheet::_001OnUpdateMediaTransfer(::signal_details * pobj)
   {


      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);

      pcmdui->m_pcmdui->Enable(TRUE);


   }


   void property_sheet::_001OnMediaTransfer(::signal_details * pobj)
   {


      UNREFERENCED_PARAMETER(pobj);


   }


   bool property_sheet::keyboard_focus_OnSetFocus()
   {

      return true;

   }


   ::count property_sheet::_001GetItemCount()
   {

      if(m_pdata == NULL)
         return 1;

      return m_pdata->m_set.get_count();

   }


   ::count property_sheet::_001GetColumnCount()
   {

      return base_form_list_view::_001GetColumnCount();

   }


   bool property_sheet::get_font(::draw2d::font_sp & spfont)
   {

      spfont = m_font;

      return true;

   }

   void property_sheet::draw_item(::draw2d::graphics * pgraphics,int x,int y,general_data::item * pitem)
   {

      int iGridW = 200;
      int iGridH = m_iItemHeight;


      //pgraphics->TextOut(m_iLeftMargin + (iGridW * x),iGridH * (y + 1),pitem->m_strName);


   }

   void property_sheet::draw_framing(::draw2d::dib * pdib)
   {

      ::draw2d::graphics * pgraphics = pdib->get_graphics();

      int iGridW = 200;
      int iGridH = m_iItemHeight;

      point ptScroll = get_viewport_offset();

      int x;
      int y;
      int xStart;
      int yStart;
      int xOffset;
      int yOffset;


      if(m_eview == view_grid)
      {
         xStart = ptScroll.x;
         yStart = ptScroll.y;
         xOffset = 0;
         yOffset = 0;
      }
      else
      {
         xStart = ptScroll.x / iGridW;
         yStart = ptScroll.y / iGridH;
         xOffset = ptScroll.x % iGridW;
         yOffset = ptScroll.y % iGridH;
      }

      rect rectClient;

      GetClientRect(rectClient);

      rectClient.top += iGridH;
      rectClient.left += iGridW;

      ::draw2d::pen_sp pen2(allocer());

      pen2->create_solid(1.0,ARGB(255,0,0,0));

      pgraphics->SelectObject(pen2);

      pgraphics->FillSolidRect(rect(0,0,m_iLeftMargin,m_iTopMargin),ARGB(228,184,184,184));

      for(index j = 0;;j++)
      {

         if(j <= 0)
         {

            y = 0;

         }
         else
         {

            y = (j - 1)* iGridH + yOffset + m_iTopMargin;

         }

         if(y > rectClient.bottom)
         {

            break;

         }

         pgraphics->DrawLine(0,y,m_iLeftMargin,y);

         if(j > 0)
         {

            pgraphics->FillSolidRect(rect(0,y,m_iLeftMargin,y + iGridH),ARGB(228,184,184,184));

            pgraphics->DrawLine(0,y,m_iLeftMargin,y);

            pgraphics->draw_text(::str::from(yStart + j),rect(0,y,m_iLeftMargin,y + iGridH),DT_CENTER | DT_VCENTER);

         }

      }

      for(index i = 0;;i++)
      {

         x = m_iLeftMargin + i * iGridW + xOffset;

         if(x > rectClient.right)
         {
            break;
         }

         pgraphics->FillSolidRect(rect(x,0,x + iGridW,m_iTopMargin),ARGB(228,184,184,184));

         pgraphics->DrawLine(x,0,x,m_iTopMargin);

         pgraphics->draw_text(::abc::upper(xStart + i),rect(x,0,x + iGridW,m_iTopMargin),DT_CENTER | DT_VCENTER);

      }

      pgraphics->DrawLine(m_iLeftMargin,0,rectClient.right,0);
      pgraphics->DrawLine(m_iLeftMargin,m_iTopMargin,rectClient.right,m_iTopMargin);
      pgraphics->DrawLine(0,0,0,rectClient.bottom);
      pgraphics->DrawLine(m_iLeftMargin,0,m_iLeftMargin,rectClient.bottom);

      ::draw2d::pen_sp pen1(allocer());

      pen1->create_solid(1.0,ARGB(84,184,184,184));

      pgraphics->SelectObject(pen1);

      for(index j = 1;;j++)
      {

         if(j <= 0)
         {

            y = 0;

         }
         else
         {

            y = j * iGridH + yOffset + m_iTopMargin;

         }

         if(y > rectClient.bottom)
         {

            break;

         }

         pgraphics->DrawLine(m_iLeftMargin,y,rectClient.right,y);

      }

      for(index i = 1;;i++)
      {

         if(i <= 0)
         {

            x = 0;

         }
         else
         {

            x = m_iLeftMargin + i * iGridW + xOffset;

         }

         if(x > rectClient.right)
         {
            break;
         }

         pgraphics->DrawLine(x,m_iTopMargin,x,rectClient.bottom);

      }

   }

   //void property_sheet::_001OnDraw(::draw2d::dib * pdib)
   //{

   //   ::user::scroll_view::draw_control_background(pgraphics);

   //   int x;
   //   int y;


   //   draw_framing(pgraphics);

   //   int_map < int_map < cell > >::assoc * passoc = m_map.PGetFirstAssoc();

   //   while(passoc != NULL)
   //   {
   //      
   //      x = passoc->m_element1;

   //      int_map < cell >::assoc * passoc2 = passoc->m_element2.PGetFirstAssoc();

   //      while(passoc2 != NULL)
   //      {

   //         y = passoc2->m_element1;

   //         draw_item(pgraphics,x,y,&passoc2->m_element2);

   //         passoc2 = passoc->m_element2.PGetNextAssoc(passoc2);
   //      }


   //      passoc = m_map.PGetNextAssoc(passoc);
   //   }

   //}

   void property_sheet::load_plain_text(const string & str)
   {

      stringa stra;

      stra.add_lines(str);

      int y = 0;

      int x;

      stringa stra2;

      //for(string strLine : stra)
      //{

      //   stra2.remove_all();

      //   stra2.explode(";",strLine);

      //   x = 0;

      //   for(string strToken : stra2)
      //   {

      //      m_pmeshcache->m_map[y][x].m_strText = strToken;

      //      x++;

      //   }


      //   y++;

      //}

      _001OnUpdateColumnCount();
      _001OnUpdateItemCount();

   }


   bool property_sheet::get_color(COLORREF & cr,::user::e_color ecolor)
   {

      if(ecolor == ::user::color_background)
      {

         cr = ARGB(230,255,255,255);

         return true;

      }

      return ::user::form_mesh::get_color(cr,ecolor);

   }


   void property_sheet::set_data(general_data * pdata, callback * pcallback)
   {

      m_pcallback = pcallback;

      if(m_pdata != NULL)
      {

         synch_lock sl(m_pdata->m_pmutex);

         m_pdata = NULL;

      }

      {

         synch_lock sl(pdata->m_pmutex);

         m_pdata = pdata;

      }


      _001OnUpdateItemCount();

   }

   bool property_sheet::_001OnControlSetFocus(::user::interaction * pui)
   {

      base_form_list_view::_001OnControlSetFocus(pui);

      index iItem;

      index iSubItem;

      if(m_controldescriptorset.find_control(pui,iItem,iSubItem))
      {

         if(iSubItem == 1)
         {

            validate(pui, iItem, true);

         }

      }

      return true;

   }



   bool property_sheet::_001OnSetItemText(::user::interaction * pui,index iItem,index iSubItem)
   {

      if(iSubItem == 1)
      {

         if(!validate(pui, iItem, true))
         {

            return false;

         }

      }

      return true;

   }


   bool property_sheet::validate(::user::interaction * pui, index iItem, bool bInteract)
   {

      string strText;

      sp(::user::plain_edit) pedit = pui;

      if(pedit.is_set())
      {

         pedit->_001GetText(strText);

         id id = m_pdata->m_set.at(iItem).m_element1;

         general_data::item & item = m_pdata->m_map[id];

         var val;

         val = strText;

         stringa stra = item.m_validate.nok(val);

         if(stra.get_count() > 0)
         {

            if(bInteract)
            { 
            
               pedit->show_tooltip(stra.implode("\r\n"),true);

            }

            return false;

         }

         if(m_pdata->m_set.at(iItem).m_element2 != strText)
         {

            m_pdata->m_set.at(iItem).m_element2 = strText;
         
            if(m_pcallback != NULL)
            {

               m_pcallback->on_property_change(m_pdata->m_set.at(iItem));

            }

         }

      }

      return true;

   }


   bool property_sheet::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_after_change_text)
      {

         if(pevent->m_actioncontext.is_user_source())
         {

            pevent->m_puie->hide_tooltip();

         }

         index iItem;

         index iSubItem;

         if(m_controldescriptorset.find_control(pevent->m_puie,iItem,iSubItem))
         {

            if(iSubItem == 1)
            {

               validate(pevent->m_puie,iItem, false);

            }

         }


      }

      return base_form_list_view::BaseOnControlEvent(pevent);

   }

} // namespace veritile








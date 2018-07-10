#include "framework.h"


namespace userex
{


   group_image_list_view::group_image_list_view(::aura::application * papp) :
      object(papp),
      m_buttonMenu(papp),
      m_dib(allocer())
   {

      m_size.cx = 7;
      m_size.cy = 5;

      m_idaHandledCommands.add("menu");

      m_dib.load_from_matter("project.jpg", false);



   }


   group_image_list_view::~group_image_list_view()
   {

   }


   void group_image_list_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void group_image_list_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void group_image_list_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      ::user::impact::on_update(pSender, lHint, phint);

   }

   void group_image_list_view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &group_image_list_view::_001OnCreate);


   }


   bool group_image_list_view::add_group(string strGroup, string strIcon, string strTitle, ::file::path pathFolder)
   {

      sp(group) pgroup = canew(group);

      pgroup->m_strGroup = strGroup;

      pgroup->m_strIcon = strIcon;

      pgroup->m_strTitle = strTitle;

      m_idaHandledCommands.add("menu_item_" + strGroup);

      m_groupa.add(pgroup);

      if (pathFolder.has_char())
      {

         auto * plist = get_group_list(strGroup);

         plist->m_pathFolder = pathFolder;

         plist->update_data(false);

      }

      return true;

   }


   void group_image_list_view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      m_buttonMenu.create_window(null_rect(), this, "menu");

      m_buttonMenu.set_button_style(::user::button::style_image_and_text);

      m_buttonMenu.create_color(::user::color_button_text, ARGB(255, 80, 80, 80));
      m_buttonMenu.create_color(::user::color_button_background, ARGB(255, 255, 255, 255));
      m_buttonMenu.create_int(::user::int_button_draw_text_and_image_flags, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

      m_buttonMenu.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);

   }


   group_image_list_view::group * group_image_list_view::get_group(string strGroup)
   {

      index iFind = m_groupa.pred_find_first([=](auto & item)
      {

         return item->m_strGroup.compare_ci(strGroup) == 0;


      });

      if (iFind < 0)
      {

         return NULL;

      }

      return m_groupa[iFind];

   }


   string group_image_list_view::get_group_title(group * pgroup)
   {

      ASSERT(pgroup != NULL);

      if (pgroup->m_strTitle.has_char())
      {

         return pgroup->m_strTitle;

      }

      return pgroup->m_strGroup;


   }


   ::file::path group_image_list_view::get_link_path(string strLink)
   {

      ::file::path path;

      for (auto & group : m_groupa)
      {

         path = group->m_plist->get_link_path(strLink);

         if (path.has_char())
         {

            break;

         }

      }

      return path;

   }


   ::userex::image_list_view * group_image_list_view::get_group_list(string strGroup)
   {

      sp(group) pgroup = get_group(strGroup);

      if (pgroup.is_null())
      {

         return NULL;

      }

      auto & plist = pgroup->m_plist;

      if (plist.is_null())
      {

         plist = create_view < ::userex::image_list_view >(NULL, null_rect(), NULL, m_id + "_image_list_" + strGroup);

         plist->m_ealign = align_top_center;

         plist->m_bMultiSel = false;

      }

      return plist;

   }


   bool group_image_list_view::show_group(string strGroup, ::file::path pathFolder)
   {

      sp(group) pgroup = get_group(strGroup);

      if (pgroup.is_null())
      {

         return false;

      }

      auto * plist = get_group_list(strGroup);

      ::draw2d::dib_sp dib = Application.get_matter_dib(pgroup->m_strIcon);

      m_buttonMenu.set_window_text(get_group_title(pgroup));

      m_buttonMenu.LoadBitmaps(dib);

      if (pathFolder.has_char())
      {

         plist->m_pathFolder = pathFolder;

         plist->update_data(false);

      }

      m_strGroup = strGroup;

      set_need_layout();

      set_need_redraw();

      return true;

   }


   void group_image_list_view::_001OnNcDraw(::draw2d::graphics * pgraphics)
   {

      ::user::impact::_001OnNcDraw(pgraphics);

   }


   void group_image_list_view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::user::impact::_001OnDraw(pgraphics);

   }


   void group_image_list_view::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::event_item_clicked)
      {


      }
      else if (pevent->m_eevent == ::user::event_button_clicked)
      {

         if (pevent->m_puie->m_id == "menu")
         {

            if (get_wnd()->m_pthread == NULL)
            {

               fork([&]()
               {

                  show_menu();

               });

            }
            else
            {

               get_wnd()->m_pthread->post_pred([&]()
               {

                  show_menu();

               });

            }

         }

      }

      return ::user::impact::on_control_event(pevent);

   }


   string group_image_list_view::get_menu_xml()
   {

      string str;

      str = "<menubar title = \"menu\" close_button=\"false\">";

      for (auto & pgroup : m_groupa)
      {

         str += "<item id=\"menu_item_";
         str += pgroup->m_strGroup;
         str += "\" image=\"";
         str += pgroup->m_strIcon;
         str += "\">";
         str += get_group_title(pgroup);
         str += "</item>";

      }

      str += "</menubar>";

      return str;

   }


   void group_image_list_view::show_menu()
   {

      string strXml(get_menu_xml());

      ::user::interaction * pui = &m_buttonMenu;

      rect rectWindow;

      pui->GetWindowRect(rectWindow);

      m_pmenu = track_popup_xml_string_menu(strXml, 0, rectWindow.bottom_left(), size(width(), 0));
      m_pmenu->create_color(::user::color_button_background, ARGB(255, 255, 255, 255));
      m_pmenu->create_color(::user::color_button_text, ARGB(255, 80, 80, 80));

      for (auto & item : *m_pmenu->m_pitem->m_spitema)
      {

         sp(::user::menu_button) pbutton = item->m_pui;

         ::draw2d::dib_sp dib = pbutton->m_pbitmap->m_dib->clone();

         dib->saturation(0.0);

         pbutton->m_pbitmap->m_dib.::draw2d::dib_sp::operator=(dib);

      }


   }


   void group_image_list_view::on_command(::user::command * pcommand)
   {

      string str = pcommand->m_id;

      if (::str::begins_eat_ci(str, "menu_item_"))
      {

         show_group(str);



      }

   }

   ::userex::image_list_view * group_image_list_view::get_current_list()
   {

      auto * pgroup = get_group(m_strGroup);

      if (pgroup == NULL)
      {

         return NULL;

      }

      return pgroup->m_plist;

   }


   void group_image_list_view::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.is_empty())
      {

         return;

      }

      ::rect rectMenu(rectClient);

      rectMenu.bottom = rectClient.top + 32;

      m_buttonMenu.SetWindowPos(ZORDER_TOP, rectMenu, SWP_SHOWWINDOW);

      ::rect rectList(rectClient);

      rectList.top = rectClient.top + 32;

      auto * plist = get_current_list();

      if (plist != NULL)
      {

         plist->SetWindowPos(ZORDER_TOP, rectList, SWP_SHOWWINDOW);

      }

      for (auto & pgroup : m_groupa)
      {

         if (pgroup->m_plist.is_set() && pgroup->m_plist != plist)
         {

            pgroup->m_plist->ShowWindow(SW_HIDE);

         }

      }

   }


} // namespace userex




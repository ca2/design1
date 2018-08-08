#include "framework.h"


namespace user
{


   menu_view::menu_view(::aura::application * papp) :
      object(papp),
      m_xmldoc(papp),
      m_brBkSel(allocer()),
      m_brBkHoverSel(allocer()),
      m_penBkSel(allocer()),
      m_pen(allocer())
   {

      m_iHover = -1;

      m_iMenuHover = -1;

      m_iCommandHover = -1;

      m_iMenuSel = -1;

      m_iCommandSel = -1;

      oprop("font_sel") = true;

      m_flagNonClient.unsignalize(non_client_background);

      m_flagNonClient.unsignalize(non_client_focus_rect);

      m_brBkHoverSel->create_solid(ARGB(255, 230, 230, 230));

      m_brBkSel->create_solid(ARGB(255, 240, 240, 240));

      m_penBkSel->create_solid(3.0, ARGB(255, 0, 148, 202));

      m_pen->create_solid(1.0, ARGB(255, 210, 210, 210));

   }


   menu_view::~menu_view()
   {

   }


   void menu_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void menu_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void menu_view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(message_view_update, psender, this, &menu_view::_001OnLayout);
      IGUI_MSG_LINK(WM_CREATE, psender, this, &menu_view::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &menu_view::_001OnDestroy);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &menu_view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &menu_view::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, psender, this, &menu_view::_001OnMouseLeave);

   }


   void menu_view::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      if (is_window_enabled())
      {

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         int iMenuSel;

         int iCommandSel;

         int iHover = hit_test(pt, iMenuSel, iCommandSel);

         UNUSED(iHover);

         ::id idCommand;

         if (iCommandSel >= 0)
         {

            xml::node * pnodeMain = m_xmldoc.get_child_at("menubar", 0, 1);

            if (pnodeMain->get_children_count("menubar") <= 0)
            {

               pnodeMain = &m_xmldoc;

            }
            xml::node * pnode = pnodeMain->get_child_at("menubar", iMenuSel, 1);

            if (pnode != NULL)
            {

               xml::node * pnodeItem = pnode->child_at(iCommandSel);

               if (pnodeItem != NULL)
               {

                  idCommand = pnodeItem->attr("id").get_id();

               }

            }

         }
         else
         {

            idCommand = "home";

         }

         pobj->m_bRet = true;

         pmouse->set_lresult(0);

         m_iMenuSel = iMenuSel;

         m_iCommandSel = iCommandSel;

         set_need_redraw();

         if (!idCommand.is_empty())
         {

            ::user::command command;

            command.m_id = idCommand;

            route_command_message(&command);

         }

      }

   }


   void menu_view::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      if (is_window_enabled())
      {

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         int iMenuHover;

         int iCommandHover;

         int iHover = hit_test(pt, iMenuHover, iCommandHover);

         if (iHover >= 0 && m_iHover < 0)
         {

            track_mouse_hover();

         }

         if (m_iMenuHover != iMenuHover
               || m_iCommandHover != iCommandHover
               || m_iHover != iHover)
         {

            m_iMenuHover = iMenuHover;

            m_iCommandHover = iCommandHover;

            m_iHover = iHover;

            set_need_redraw();

         }

      }

   }


   void menu_view::_001OnMouseLeave(::message::message * pobj)
   {

      m_iMenuHover = -1;

      m_iCommandHover = -1;

      m_iHover = -1;

      set_need_redraw();

   }


   void menu_view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      string strText;

      data_get("cur_text", strText);

      ::visual::dib_sp dibLogo(allocer());

      dibLogo.load_from_file("matter://main/logo.png", false);

      m_dibLogo = dibLogo;

      m_fontTitle.alloc(allocer());

      m_fontTitle->create_point_font("Segoe UI", 14, 800);

      m_font.alloc(allocer());

      m_font->create_point_font("Segoe UI", 14, 400);

      if (GetTypedParent<::user::split_view>() != NULL)
      {

         if (GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != NULL)
         {

            sp(::user::edit_text) pedit = GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view");

            pedit->_001SetText(strText, ::action::source_initialize);

         }

      }

   }


   void menu_view::_001OnDestroy(::message::message * pobj)
   {

   }


   void menu_view::_001OnLayout(::message::message * pobj)
   {

      synch_lock sl(m_pmutex);

      on_layout();


   }


   void menu_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      ::user::impact::on_update(pSender, lHint, phint);

      ::user::view_update_hint * puh = dynamic_cast < ::user::view_update_hint *> (phint);

      if (puh != NULL)
      {

         if (puh->m_ehint == ::user::view_update_hint::hint_after_change_text)
         {

            auto * peditview = _001TypedWindow < ::userex::top_edit_view >();

            if (peditview != NULL && puh->m_pui == peditview)
            {

               string strText;

               peditview->_001GetText(strText);

            }

         }

      }

   }


   bool menu_view::get_item_rect(int i, LPRECT lprect)
   {

      int iHeight = m_fontTitle->m_dFontSize * 1.25 + 20;

      int x = 10;

      int y = 10;

      y += m_dibLogo->m_size.cy;

      y += 10;

      rect rectClient;

      GetClientRect(rectClient);

      int w = rectClient.width() - x * 2;

      int k = 0;

      int iSep = 0;

      for (int j = 0; j < m_iaPopup.get_count(); j++)
      {

         if (i < k + m_iaPopup[j])
         {

            break;

         }

         k += m_iaPopup[j];

         iSep++;
      }

      lprect->top = y + (i + iSep) * iHeight;
      lprect->bottom = lprect->top + iHeight;
      lprect->left = x;
      lprect->right = x + w;

      return true;

   }


   int menu_view::hit_test(point pt, int & iMenu, int & iCommand)
   {

      int iPos = 0;

      rect r;

      xml::node * pnodeMain = m_xmldoc.get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = &m_xmldoc;

      }

      for (iMenu = 0; iMenu < pnodeMain->get_children_count("menubar"); iMenu++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", iMenu, 1);

         iCommand = -1;

         get_item_rect(iPos, r);

         if (r.contains(pt))
         {

            return iPos;

         }

         iPos++;

         for (iCommand = 0; iCommand < pnode->get_children_count(); iCommand++)
         {

            get_item_rect(iPos, r);

            if (r.contains(pt))
            {

               return iPos;

            }

            iPos++;

         }

      }

      iMenu = -1;

      iCommand = -1;

      return -1;

   }



   void menu_view::_001OnDraw(::draw2d::graphics * pgraphicsParam)
   {
      ::draw2d::dib_sp dib;

      if (m_dibMem.is_null())
      {
         m_dibMem.alloc(allocer());
      }

      dib = m_dibMem;

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;
      }
      dib->create(rectClient.get_size());
      ::draw2d::graphics * pgraphics = dib->get_graphics();

      if (is_window_enabled())
      {
         dib->FillByte(255);
      }
      else
      {
         dib->Fill(255, 200, 200, 200);
      }
      //int iMenu = 0;

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_antialias);

      pgraphics->draw(point(10, 10), m_dibLogo->m_size, m_dibLogo->get_graphics());

      rect r;

      rect_array raMenu;

      int iPos = 0;

      xml::node * pnodeMain = m_xmldoc.get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = &m_xmldoc;

      }

      for (int i = 0; i < pnodeMain->get_children_count("menubar"); i++)
      {

         rect rMenu(0, 0, 0, 0);

         xml::node * pnode = pnodeMain->get_child_at("menubar", i, 1);

         string strTitle = pnode->attr("title");

         pgraphics->select_font(m_fontTitle);

         get_item_rect(iPos, r);

         rMenu.unite(rMenu, r);

         pgraphics->SelectObject(m_pen);

         draw_header_rectangle(pgraphics, r);

         pgraphics->set_text_color(ARGB(255, 0, 0, 0));

         pgraphics->text_out(r.left + 10, r.top + 5, strTitle);

         iPos++;

         for (int j = 0; j < pnode->get_children_count(); j++)
         {

            xml::node * pnodeItem = pnode->child_at(j);

            if (pnodeItem->get_name() == "item")
            {

               string strItem;

               strItem = pnodeItem->get_value();

               get_item_rect(iPos, r);

               rMenu.unite(rMenu, r);

               pgraphics->SelectObject(m_pen);

               if (m_iMenuHover == i && m_iCommandHover == j)
               {

                  if (m_iMenuSel == i && m_iCommandSel == j)
                  {

                     pgraphics->SelectObject(m_brBkHoverSel);

                     draw_item_rectangle_hover_sel001(pgraphics, r);

                  }
                  else
                  {

                     pgraphics->SelectObject(m_brBkSel);

                     draw_item_rectangle_hover001(pgraphics, r);

                  }
               }
               else if (m_iMenuSel == i && m_iCommandSel == j)
               {

                  pgraphics->SelectObject(m_brBkSel);

                  draw_item_rectangle_sel001(pgraphics, r);

               }
               else
               {

                  draw_item_rectangle(pgraphics, r);

               }

               pgraphics->select_font(m_font);

               if (m_iMenuSel == i && m_iCommandSel == j)
               {

                  pgraphics->set_text_color(ARGB(255, 0, 148, 202));

               }
               else
               {

                  pgraphics->set_text_color(ARGB(255, 60, 60, 60));

               }

               pgraphics->text_out(r.left + 10, r.top + 5, strItem);

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               ::draw2d::dib * pdib = NULL;

               if (m_iMenuSel == i && m_iCommandSel == j)
               {

                  pgraphics->SelectObject(m_penBkSel);

                  pgraphics->move_to(r.left + 1, r.top);
                  pgraphics->line_to(r.left + 1, r.bottom - 1);

                  pdib = m_dibMap[pnodeItem->attr("id")];

               }
               else
               {

                  pdib = m_dibMapGray[pnodeItem->attr("id")];

               }

               if (pdib != NULL)
               {

                  rect rectDib;

                  rectDib.left = r.right - pdib->m_size.cx - 10;
                  rectDib.top = r.top + (r.height() - pdib->m_size.cy) / 2;
                  rectDib.set_size(pdib->m_size.cx, pdib->m_size.cy);

                  pgraphics->draw(rectDib, pdib->get_graphics());

               }

               iPos++;

            }

         }

         raMenu.add(rMenu);

      }

      iPos = 0;

      for (int i = 0; i < pnodeMain->get_children_count("menubar"); i++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", i, 1);

         get_item_rect(iPos, r);

         pgraphics->SelectObject(m_pen);

         draw_header_separator(pgraphics, r.bottom_left(), r.bottom_right());

         iPos++;

         for (int j = 0; j < pnode->get_children_count() - 1; j++)
         {

            xml::node * pnodeItem = pnode->child_at(j);

            if (pnodeItem->get_name() == "item")
            {

               string strItem;

               strItem = pnodeItem->get_value();

               get_item_rect(iPos, r);

               draw_item_separator(pgraphics, r.bottom_left(), r.bottom_right());

               iPos++;

            }

         }

         iPos++;

      }



      for (int i = 0; i < pnodeMain->get_children_count("menubar"); i++)
      {

         //xml::node * pnode = pnodeMain->get_child_at("menubar", i, 1);

         draw_border_rectangle(pgraphics, raMenu[i]);

      }

      if (!is_window_enabled())
      {

         dib->saturation(0.0);

      }

      pgraphicsParam->draw(rectClient, dib->get_graphics());

   }


   ::user::document * menu_view::get_document()
   {

      return  (::user::impact::get_document());

   }


   void menu_view::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

   }
   bool menu_view::load_xml(var varFile)
   {

      string str = Application.file().as_string(varFile);

      if (!m_xmldoc.load(str))
      {

         return false;

      }


      int iPos = 0;

      rect r;

      int iMenu;

      int iCommand;

      xml::node * pnodeMain = m_xmldoc.get_child_at("menubar", 0, 1);

      if (pnodeMain->get_children_count("menubar") <= 0)
      {

         pnodeMain = &m_xmldoc;

      }

      m_iaPopup.remove_all();

      for (iMenu = 0; iMenu < pnodeMain->get_children_count("menubar"); iMenu++)
      {

         xml::node * pnode = pnodeMain->get_child_at("menubar", iMenu, 1);

         m_iaPopup.add((const int)pnode->get_children_count() + 1);

         iPos++;

         for (iCommand = 0; iCommand < pnode->get_children_count(); iCommand++)
         {

            get_item_rect(iPos, r);

            ::visual::dib_sp dib(allocer());

            if (dib.load_from_file(pnode->child_at(iCommand)->attr("image"), false))
            {

               m_dibMap[pnode->child_at(iCommand)->attr("id")] = dib;

               ::draw2d::dib * pdibGray;

               m_dibMapGray[pnode->child_at(iCommand)->attr("id")].alloc(allocer());

               pdibGray = m_dibMapGray[pnode->child_at(iCommand)->attr("id")];

               pdibGray->from(dib);

               pdibGray->saturation(0.0);

            }



            iPos++;

         }

      }

      return true;

   }


   void menu_view::draw_border_rectangle(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {

      pgraphics->move_to(lpcrect->left, lpcrect->top);
      pgraphics->line_to(lpcrect->right, lpcrect->top);
      pgraphics->move_to(lpcrect->left, lpcrect->bottom);
      pgraphics->line_to(lpcrect->right, lpcrect->bottom);

   }

   void menu_view::draw_header_separator(::draw2d::graphics * pgraphics, LPPOINT ppt1, LPPOINT ppt2)
   {

      pgraphics->move_to(ppt1);
      pgraphics->line_to(ppt2);

   }

   void menu_view::draw_header_rectangle(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {

      pgraphics->fill_solid_rect(lpcrect, ARGB(255, 240, 240, 240));
      pgraphics->move_to(lpcrect->left, lpcrect->top);
      pgraphics->line_to(lpcrect->left, lpcrect->bottom);
      pgraphics->move_to(lpcrect->right, lpcrect->top);
      pgraphics->line_to(lpcrect->right, lpcrect->bottom);



   }


   void menu_view::draw_item_rectangle(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {

      pgraphics->move_to(lpcrect->left, lpcrect->top);
      pgraphics->line_to(lpcrect->left, lpcrect->bottom);
      pgraphics->move_to(lpcrect->right, lpcrect->top);
      pgraphics->line_to(lpcrect->right, lpcrect->bottom);

   }


   void menu_view::draw_item_rectangle_hover001(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {

      pgraphics->fill_rect(lpcrect);

      pgraphics->move_to(lpcrect->left, lpcrect->top);
      pgraphics->line_to(lpcrect->left, lpcrect->bottom);


      pgraphics->move_to(lpcrect->right, lpcrect->top);
      pgraphics->line_to(lpcrect->right, lpcrect->bottom);

   }


   void menu_view::draw_item_rectangle_sel001(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {

      pgraphics->fill_rect(lpcrect);
      pgraphics->move_to(lpcrect->left, lpcrect->top);
      pgraphics->line_to(lpcrect->left, lpcrect->bottom);
      pgraphics->move_to(lpcrect->right, lpcrect->bottom - 1);
      int h = ::height(lpcrect);
      point_array pta;
      pta.add(lpcrect->right, lpcrect->bottom - h / 3 - 2);
      pta.add(lpcrect->right + h * 3 / 16, lpcrect->bottom - h / 2 - 2);
      pta.add(lpcrect->right, lpcrect->bottom - h * 2 / 3 - 2);
      pgraphics->fill_polygon(pta);
      pgraphics->line_to(lpcrect->right, lpcrect->bottom - h / 3 - 2);
      pgraphics->line_to(lpcrect->right + h * 3 / 16, lpcrect->bottom - h / 2 - 2);
      pgraphics->line_to(lpcrect->right, lpcrect->bottom - h * 2 / 3 - 2);
      pgraphics->line_to(lpcrect->right, lpcrect->top);
   }

   void menu_view::draw_item_rectangle_hover_sel001(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {

      pgraphics->fill_rect(lpcrect);
      pgraphics->move_to(lpcrect->left, lpcrect->top);
      pgraphics->line_to(lpcrect->left, lpcrect->bottom);
      pgraphics->move_to(lpcrect->right, lpcrect->bottom - 1);
      int h = ::height(lpcrect);
      point_array pta;
      pta.add(lpcrect->right, lpcrect->bottom - h / 3 - 2);
      pta.add(lpcrect->right + h * 3 / 16, lpcrect->bottom - h / 2 - 2);
      pta.add(lpcrect->right, lpcrect->bottom - h * 2 / 3 - 2);
      pgraphics->fill_polygon(pta);
      pgraphics->line_to(lpcrect->right, lpcrect->bottom - h / 3 - 2);
      pgraphics->line_to(lpcrect->right + h * 3 / 16, lpcrect->bottom - h / 2 - 2);
      pgraphics->line_to(lpcrect->right, lpcrect->bottom - h * 2 / 3 - 2);

      pgraphics->line_to(lpcrect->right, lpcrect->top);

   }


   void menu_view::draw_item_separator(::draw2d::graphics * pgraphics, LPPOINT ppt1, LPPOINT ppt2)
   {

      pgraphics->move_to(ppt1);
      pgraphics->line_to(ppt2);
   }


} // namespace user



#include "framework.h"
#include "user_rich_text_global.h"


namespace user
{


   namespace rich_text
   {


      edit::edit() :
         edit(get_app())
      {

         m_bEditable = true;

      }


      edit::edit(::aura::application * papp) :
         ::object(papp),
         ::user::pic(papp),
         m_data(papp),
         m_keymessageLast(papp)
      {

         m_bEditable = true;

         m_data.m_pui = this;

         m_bKeyPressed = false;

         m_bSelDrag = false;


      }


      edit::~edit()
      {

      }


      bool edit::update_data(bool bSaveAndValidate)
      {

         if (bSaveAndValidate)
         {

         }
         else
         {

            set_need_layout();

            set_need_redraw();

         }

         return true;

      }


      void edit::assert_valid() const
      {

         ::user::box::assert_valid();

      }


      void edit::dump(dump_context & dumpcontext) const
      {

         ::user::box::dump(dumpcontext);

      }


      void edit::install_message_routing(::message::sender * psender)
      {

         ::user::box::install_message_routing(psender);

         IGUI_MSG_LINK(WM_CREATE, psender, this, &edit::_001OnCreate);
         IGUI_MSG_LINK(WM_DESTROY, psender, this, &edit::_001OnDestroy);
         IGUI_MSG_LINK(WM_SHOWWINDOW, psender, this, &edit::_001OnShowWindow);
         IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &edit::_001OnLButtonDown);
         IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &edit::_001OnLButtonUp);
         IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &edit::_001OnMouseMove);
         IGUI_MSG_LINK(WM_MOUSELEAVE, psender, this, &edit::_001OnMouseLeave);
         IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &edit::_001OnKeyDown);
         IGUI_MSG_LINK(WM_KEYUP, psender, this, &edit::_001OnKeyUp);

      }


      void edit::_001OnCreate(::message::message * pobj)
      {

         SCAST_PTR(::message::create, pcreate, pobj);

         pcreate->previous();

         if (pcreate->m_bRet)
            return;

#if !defined(APPLE_IOS) && !defined(VSNORD)
         Session.keyboard(); // trigger keyboard creationg
#endif


         SetTimer(100, 100, NULL);

         SetTimer(250, 500, NULL); // Caret

      }


      void edit::_001OnDestroy(::message::message * pobj)
      {

      }


      void edit::_001OnShowWindow(::message::message * pobj)
      {

         SCAST_PTR(::message::show_window, pshowwindow, pobj);

         if (pshowwindow->m_bShow)
         {


         }
         else
         {

            if (get_sys_format_tool() != NULL)
            {

               get_sys_format_tool()->ShowWindow(SW_HIDE);

            }

         }

      }


      void edit::on_selection_change()
      {

         m_data.on_selection_change(&get_sys_format_tool()->m_format);

         get_sys_format_tool()->update_data(false);

      }


      void edit::_001OnLButtonDown(::message::message * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);

         if (!m_bEditable)
         {

            return;

         }

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         pt += m_ptScrollPassword1;

         e_element eelement;

         int iHit = (int)hit_test(pt, eelement);

         if (iHit >= 0)
         {

            get_sys_format_tool()->show_for_ui(this);

            m_bSelDrag = true;

            m_data.m_iSelBeg3 = iHit;

            m_data.internal_update_sel_char();

            SetCapture();

            Session.set_keyboard_focus(this);

            Session.user()->set_mouse_focus_LButtonDown(this);

            pmouse->m_bRet = true;

         }
         else
         {

            if (get_sys_format_tool()->IsWindowVisible())
            {

               get_sys_format_tool()->ShowWindow(SW_HIDE);

            }

         }

      }


      ::sized edit::get_size()
      {

         ::rect r;

         GetWindowRect(r);

         return r.get_size();

      }


      void edit::_001OnLButtonUp(::message::message * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);

         if (!m_bEditable)
         {

            return;

         }

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         pt += m_ptScrollPassword1;

         ReleaseCapture();

         m_bSelDrag = false;

         e_element eelement;

         int iHit = hit_test(pt, eelement);

         if (iHit >= 0)
         {

            m_data.m_iSelEnd3 = iHit;

            m_data.internal_update_sel_char();

            on_selection_change();

            pmouse->m_bRet = true;

         }


      }


      void edit::_001OnMouseMove(::message::message * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);

         if (!m_bEditable)
         {

            return;

         }

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         pt += m_ptScrollPassword1;

         e_element eelement;

         int iHover = hit_test(pt, eelement);

         if (iHover >= 0)
         {

            pmouse->m_ecursor = ::visual::cursor_text_select;

            pmouse->m_bRet = true;

         }

         if (m_bSelDrag)
         {

            if (iHover >= 0)
            {

               m_data.m_iSelEnd3 = iHover;

               m_data.internal_update_sel_char();

               pmouse->m_bRet = true;

            }

         }


      }


      void edit::_001OnMouseLeave(::message::message * pobj)
      {

         ReleaseCapture();

         set_need_redraw();

      }


      bool edit::get_element_rect(LPRECT lprect, index i, e_element eelement)
      {

         if (eelement == ::user::element_icon)
         {

            if (!get_item_rect(lprect, i))
            {

               return false;

            }

            return true;

         }
         else if (eelement == ::user::element_text)
         {

            if (!get_item_rect(lprect, i))
            {

               return false;

            }

            return true;


         }

         return false;

      }

      bool edit::get_item_rect(LPRECT lprect, index i)
      {

         return true;

      }

      double edit::get_rotate()
      {

         if (is_pic_enabled())
         {

            return m_ppic->m_dRotate;

         }

         return 0.0;

      }

      index edit::hit_test(point p, ::user::e_element & eelement)
      {

         pointd pt(p);

         if (is_pic_enabled())
         {

            rectd rectWindow;

            {

               rect rWindow;

               GetWindowRect(rWindow);

               GetParent()->ScreenToClient(rWindow);

               copy(rectWindow, rWindow);

            }

            pt += rectWindow.top_left();

            _rtransform_point(pt);

            pt -= m_ppic->m_rect.center();

         }
         else
         {

            ScreenToClient(pt);

         }

         return m_data.hit_test(pt);

      }


      void edit::_001GetText(string & str) const
      {

         m_data._001GetText(str);

      }

      void edit::_001GetLayoutText(string & str) const
      {

         m_data._001GetLayoutText(str);

      }


      void edit::_001OnDraw(::draw2d::graphics * pgraphics)
      {

         if (!is_pic_enabled())
         {

            draw(pgraphics);

         }

      }


      void edit::draw_impl(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
      {

         //::draw2d::savedc savedc(pgraphics);

         //rect rClient;

         //GetClientRect(rClient);

         //rectd rectClient(rClient);

         //if (is_pic_enabled())
         //{

         //   //::draw2d::matrix mRot;

         //   //mRot.append(::draw2d::matrix::rotation(m_ppic->m_dRotate));

         //   //pgraphics->prepend(mRot);

         //   //::draw2d::matrix mTrans;

         //   //rect rectWindow;

         //   //GetWindowRect(rectWindow);

         //   //GetParent()->ScreenToClient(rectWindow);

         //   //mTrans.append(::draw2d::matrix::translation(get_size() / 2));

         //   //pgraphics->append(mTrans);

         //   //::draw2d::savedc savedc(pgraphics);

         //   pgraphics->IntersectClipRect(rClient);

         //   ::draw2d::matrix mRot;

         //   pgraphics->prepend(::draw2d::matrix::scaling(m_ppic->m_dZoom, m_ppic->m_dZoom));

         //   mRot.append(::draw2d::matrix::rotation(m_ppic->m_dRotate));

         //   pgraphics->prepend(mRot);

         //   ::draw2d::matrix mTrans;

         //   mTrans.append(::draw2d::matrix::translation(get_size() / 2));

         //   mTrans.append(::draw2d::matrix::translation((m_ppic->m_ptDrag.x) * m_ppic->m_rect.width(), (m_ppic->m_ptDrag.y)  * m_ppic->m_rect.height()));

         //   pgraphics->append(mTrans);
         //   rect r;

         //   rectClient.offset(-m_ppic->m_rect.get_size() / 2.0);

         //}

         rectd rectClient(lpcrect);

         //pgraphics->selectFont(_001GetFont(::user::font_default));

         rectClient.offset(sized(m_ptScrollPassword1));

         //pgraphics->fill_solid_rect(rectClient, ARGB(40, 255, 255, 255));

         //pgraphics->draw3d_rect(rectClient, ARGB(255, 192, 192, 192));

         //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         //pgraphics->set_text_color(ARGB(255, 255, 255, 180));

         //pgraphics->SelectClipRgn(NULL);

         m_data._001OnDraw(pgraphics, rectClient);

      }



      bool edit::_001IsPointInside(point64 p)
      {

         if (is_pic_enabled())
         {

            pointd pt(p);

            ScreenToClient(pt);

            rectd rectWindow;

            rect rWindow;

            GetWindowRect(rWindow);

            GetParent()->ScreenToClient(rWindow);

            copy(rectWindow, rWindow);

            pt += rectWindow.top_left();

            _rtransform_point(pt);

            pt -= rectWindow.top_left();

            rect rectClient;

            GetClientRect(rectClient);

            return rectClient.contains(point(pt));

         }

         return ::user::interaction::_001IsPointInside(p);

      }


      bool edit::_001GetItemText(string & str, index iItem)
      {

         return false;

      }


      void edit::on_layout()
      {


         rect rClient;

         rect rTotal(0, 0, 0, 0);

         ::user::box::on_layout();

      }


      void edit::on_control_event(::user::control_event * pevent)
      {

         if (pevent->m_eevent == ::user::event_after_change_cur_sel)
         {

            if (pevent->m_puie == get_sys_format_tool())
            {

               m_data._001SetSelFontFormat(&get_sys_format_tool()->m_format, get_sys_format_tool()->m_eattributea);

               if (get_sys_format_tool()->m_eattributea.contains(attribute_align))
               {

                  box_align(m_data.m_boxa, find_box(m_data.m_boxa, m_data.m_iSelEnd3), get_sys_format_tool()->m_format.m_ealign);

               }

               get_sys_format_tool()->m_eattributea.remove_all();

               //pevent->Ret();

               //return;

            }

         }

         return ::user::control::on_control_event(pevent);

      }


      ::userex::font_format_tool * edit::get_sys_format_tool()
      {

         sp(::userex::font_format_tool) ptool = System.oprop("textformat_sys_format_tool").cast < ::userex::font_format_tool > ();

         if (ptool.is_null())
         {

            ptool = canew(::userex::font_format_tool(get_app()));

            System.oprop("textformat_sys_format_tool") = ptool;

            //ptool->create_window(null_rect(), NULL, "textformat_sys_format_tool");

            ui_post([this, ptool]()
            {

               ::user::create_struct cs(WS_EX_TOOLWINDOW);

               ptool->create_window_ex(cs, NULL, "textformat_sys_format_tool");

            });

         }

         return ptool;

      }


      bool edit::keyboard_focus_is_focusable()
      {

         return IsWindowVisible() && m_bEditable;

      }


      void edit::keyboard_focus_OnChar(::message::message * pobj)
      {

         if (!m_bEditable)
         {

            return;

         }

         _001OnChar(pobj);

      }


      void edit::_001OnKeyDown(::message::message * pmessage)
      {

         //synch_lock sl(m_pmutex);

         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::event_key_down;

            ev.m_pmessage = pmessage;

            ev.m_actioncontext = ::action::source_user;

            on_control_event(&ev);

            if (ev.m_bRet)
            {

               return;

            }

         }

         SCAST_PTR(::message::key, pkey, pmessage);

         if (pkey->m_ekey == ::user::key_return)
         {

            if (Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

            //if ((!m_bMultiLine || m_bSendEnterKey) && GetParent() != NULL)
            //{

            //   ::user::control_event ev;

            //   ev.m_puie = this;

            //   ev.m_eevent = ::user::event_enter_key;

            //   ev.m_actioncontext = ::action::source_user;

            //   on_control_event(&ev);

            //   if (!ev.m_bRet && ev.m_bOk)
            //   {

            //      on_action("submit");

            //   }

            //   pmessage->m_bRet = true;

            //   return;

            //}

         }
         else if (pkey->m_ekey == ::user::key_tab)
         {

            if (Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
            {

               pkey->m_bRet = false;

               return;

            }

            //if (!m_bMultiLine)
            //{

            //   pkey->previous();

            //   ::user::control_event ev;

            //   ev.m_puie = this;

            //   ev.m_eevent = ::user::event_tab_key;

            //   ev.m_actioncontext = ::action::source_user;

            //   on_control_event(&ev);

            //   if (!ev.m_bRet && ev.m_bOk)
            //   {

            //      sp(::user::interaction) pui = keyboard_get_next_focusable();

            //      if (pui != NULL)
            //         pui->keyboard_set_focus();

            //   }

            //   pkey->m_bRet = true;

            //   return;

            //}

         }
         else if (pkey->m_ekey == ::user::key_alt)
         {

            pkey->m_bRet = false;

            return;

         }
         else if (pkey->m_ekey == ::user::key_escape)
         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::event_escape;

            ev.m_actioncontext = ::action::source_user;

            on_control_event(&ev);

            if (!ev.m_bRet && ev.m_bOk)
            {

               on_action("escape");

            }

            pmessage->m_bRet = true;

            return;

         }
         else if (pkey->m_ekey == ::user::key_c)
         {

            if (Session.is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

//            clipboard_copy();

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_v)
         {

            if (Session.is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

               if (is_window_enabled())
               {

//               clipboard_paste();

               }

               return;

            }

         }
         else if (pkey->m_ekey == ::user::key_x)
         {

            if (Session.is_key_pressed(::user::key_control))
            {

               pkey->m_bRet = true;

               //clipboard_copy();

               if (is_window_enabled())
               {

                  //_001EditDelete();

               }

               return;

            }

         }


         m_keymessageLast = *pkey;

         m_bKeyPressed = true;

         key_to_char(&m_keymessageLast);

         pkey->m_bRet = true;

      }


      void edit::_001OnKeyUp(::message::message * pobj)
      {
         SCAST_PTR(::message::key, pkey, pobj);
         if (pkey->m_ekey == ::user::key_return)
         {
            if (Session.is_key_pressed(::user::key_control)
                  && Session.is_key_pressed(::user::key_alt))
            {
               pkey->m_bRet = false;
               return;
            }
         }
         else if (pkey->m_ekey == ::user::key_alt)
         {
            pkey->m_bRet = false;
         }
         m_bKeyPressed = false;
      }

      void edit::_001OnTimer(::timer * ptimer)
      {

         control::_001OnTimer(ptimer);

         if (ptimer->m_nIDEvent >= 100
               && ptimer->m_nIDEvent <= 200)
         {
            if (this == Session.get_keyboard_focus())
            {

               //_001OnKeyboardFocusTimer(ptimer->m_nIDEvent - 100);

            }
         }
         else if (ptimer->m_nIDEvent == 500 || ptimer->m_nIDEvent == 501)
         {
            if (ptimer->m_nIDEvent == 500)
            {
               KillTimer(500);
               SetTimer(501, 300, NULL);
            }
            key_to_char(&m_keymessageLast);
         }
         else if (ptimer->m_nIDEvent == 250)
         {

            set_need_redraw();

         }

      }


      void edit::key_to_char(::message::key * pkey)
      {

         ::message::key & key = *pkey;

         if (key.m_ekey == ::user::key_shift || key.m_ekey == ::user::key_lshift || key.m_ekey == ::user::key_rshift
               || key.m_ekey == ::user::key_control || key.m_ekey == ::user::key_lcontrol || key.m_ekey == ::user::key_rcontrol
               || key.m_ekey == ::user::key_alt || key.m_ekey == ::user::key_lalt || key.m_ekey == ::user::key_ralt
            )
         {

            return;

         }

         if (key.m_ekey == ::user::key_right || key.m_ekey == ::user::key_up
               || key.m_ekey == ::user::key_left || key.m_ekey == ::user::key_down)
         {

            _001OnChar(&key);

            return;

         }

         bool bShift = Session.is_key_pressed(::user::key_shift);

         if (key.m_nChar < 256 && isalpha((int32_t)key.m_nChar))
         {

            if (bShift)
            {

               key.m_nChar = toupper((int32_t)key.m_nChar);

            }
            else
            {

               key.m_nChar = tolower((int32_t)key.m_nChar);

            }

         }

         _001OnChar(&key);

      }


      void edit::_001OnChar(::message::message * pobj)
      {

         bool bUpdate = true;

         //bool bFullUpdate = false;

         //index iLineUpdate = -1;

         {

//         _009OnChar(pobj);

//         if (pobj->m_bRet)
//            return;

            SCAST_PTR(::message::key, pkey, pobj);

            string strChar;

            if (pkey->m_ekey == ::user::key_s)
            {
               if (Session.is_key_pressed(::user::key_control))
               {
                  return;
               }
            }
            else if (pkey->m_ekey == ::user::key_a)
            {
               if (Session.is_key_pressed(::user::key_control))
               {
                  _001SetSel(0, _001GetTextLength());
                  return;
               }
            }
            else if (pkey->m_ekey == ::user::key_z)
            {
               if (Session.is_key_pressed(::user::key_control))
               {
                  if (is_window_enabled())
                  {
                     //Undo();
                  }
                  return;
               }
            }
            else if (pkey->m_ekey == ::user::key_y)
            {
               if (Session.is_key_pressed(::user::key_control))
               {
                  if (is_window_enabled())
                  {
                     //Redo();
                  }
                  return;
               }
            }
            else if (Session.is_key_pressed(::user::key_control))
            {
               if (pkey->m_ekey == ::user::key_home)
               {
               }
               else if (pkey->m_ekey == ::user::key_end)
               {
               }
               else
               {
                  return;
               }

            }


            {

               synch_lock sl(m_pmutex);

               bool bControl = Session.is_key_pressed(::user::key_control);

               bool bShift = Session.is_key_pressed(::user::key_shift);

               if (pkey->m_ekey == ::user::key_prior)
               {

                  //on_reset_focus_start_tick();

                  //int32_t x;
                  //index iLine = SelToLineX(m_data.m_iSelEnd, x);

                  //rect rectClient;

                  //GetFocusRect(rectClient);

                  //iLine -= rectClient.height() / m_iLineHeight;

                  //if (iLine < 0)
                  //{

                  //   iLine = 0;

                  //}

                  //m_data.m_iSelEnd = LineXToSel(iLine, m_iColumnX);

                  //if (!bShift)
                  //{

                  //   m_data.m_iSelBeg = m_data.m_iSelEnd;

                  //}

                  //_001EnsureVisibleLine(iLine);

               }
               else if (pkey->m_ekey == ::user::key_next)
               {

                  //on_reset_focus_start_tick();

                  //int32_t x;

                  //index iLine = SelToLineX(m_data.m_iSelEnd, x);

                  //rect rectClient;

                  //GetFocusRect(rectClient);

                  //iLine += rectClient.height() / m_iLineHeight;

                  //if (iLine >= m_iaLineBeg.get_size())
                  //{

                  //   iLine = m_iaLineBeg.get_upper_bound();

                  //}

                  //m_data.m_iSelEnd = LineXToSel(iLine, m_iColumnX);

                  //if (!bShift)
                  //{

                  //   m_data.m_iSelBeg = m_data.m_iSelEnd;

                  //}

                  //_001EnsureVisibleLine(iLine);

               }
               else if (pkey->m_ekey == ::user::key_back)
               {

                  if (is_window_enabled())
                  {

                     on_reset_focus_start_tick();

                     {

                        synch_lock sl(m_data.m_pmutex);

                        strsize i1 = m_data.get_sel_beg();

                        strsize i2 = m_data.get_sel_end();

                        if (i1 > 0)
                        {

                           if (i1 != i2)
                           {

                              m_data._001Delete(i1, i2);

                              m_data.m_iSelBeg3 = m_data.m_iSelEnd3 = i1;

                              m_data.m_iSelCharBeg = m_data.m_iSelCharEnd =
                                                     min_non_neg(m_data.m_iSelCharBeg, m_data.m_iSelCharEnd);


                              on_after_change(::user::event_after_change_text);

                              set_need_redraw();

                           }
                           else
                           {

                              string str;

                              _001GetLayoutText(str);

                              int iDecLen = ::str::utf8_dec_len(str, &str[i1]);

                              m_data._001Delete(i1, i1 - iDecLen);

                              m_data.m_iSelBeg3 = m_data.m_iSelEnd3 = i1 - iDecLen;

                              m_data.m_iSelCharBeg = m_data.m_iSelCharEnd =
                                                     min_non_neg(m_data.m_iSelCharBeg, m_data.m_iSelCharEnd)
                                                     - iDecLen;

                              on_after_change(::user::event_after_change_text);

                              set_need_redraw();

                           }

                        }

                     }

                  }

               }
               else if (pkey->m_ekey == ::user::key_delete)
               {

                  if (is_window_enabled())
                  {

                     on_reset_focus_start_tick();

                     {

                        synch_lock sl(m_data.m_pmutex);

                        strsize i1 = m_data.get_sel_beg();

                        strsize i2 = m_data.get_sel_end();

                        if (i1 != i2)
                        {

                           m_data._001Delete(i1, i2);

                           m_data.m_iSelBeg3 = m_data.m_iSelEnd3 = i1;

                           index i = find_box(m_data.m_boxa, i1);

                           if (i >= 0 && m_data.m_boxa[i]->m_bParagraph)
                           {

                              m_data.m_iSelCharBeg = m_data.m_iSelCharEnd = -1;

                           }
                           else
                           {

                              m_data.m_iSelCharBeg = m_data.m_iSelCharEnd =
                                                     min_non_neg(m_data.m_iSelCharBeg, m_data.m_iSelCharEnd);

                           }

                           on_after_change(::user::event_after_change_text);

                           set_need_redraw();

                        }
                        else if (i1 >= 0 && i1 < m_data._001GetLayoutTextLength())
                        {

                           string str;

                           _001GetLayoutText(str);

                           int iIncLen = ::str::utf8_inc_len(&str[i1]);

                           m_data._001Delete(i1, i1 + iIncLen);

                           m_data.m_iSelBeg3 = m_data.m_iSelEnd3 = i1;

                           index i = find_box(m_data.m_boxa, i1);

                           if (i >= 0 && m_data.m_boxa[i]->m_bParagraph)
                           {

                              m_data.m_iSelCharBeg = m_data.m_iSelCharEnd = -1;

                           }
                           else
                           {

                              m_data.m_iSelCharBeg = m_data.m_iSelCharEnd =
                                                     min_non_neg(m_data.m_iSelCharBeg, m_data.m_iSelCharEnd);

                           }

                           on_after_change(::user::event_after_change_text);

                           set_need_redraw();

                        }

                     }

                  }

                  return;

               }
               else if (pkey->m_ekey == ::user::key_up)
               {

                  on_reset_focus_start_tick();

                  synch_lock sl(m_data.m_pmutex);

                  double x;

                  index iLine = sel_line_x(m_data.m_layouta, m_data.m_iSelEnd3, x);

                  iLine--;

                  if (iLine >= 0)
                  {

                     m_data.m_iSelEnd3 = m_data.hit_test_line_x(iLine, x);

                     if (!bShift)
                     {

                        m_data.m_iSelBeg3 = m_data.m_iSelEnd3;

                     }

                     //_001EnsureVisibleLine(iLine);

                     m_data.internal_update_sel_char();

                  }

               }
               else if (pkey->m_ekey == ::user::key_down)
               {

                  on_reset_focus_start_tick();

                  synch_lock sl(m_data.m_pmutex);

                  double x;

                  index iLine = sel_line_x(m_data.m_layouta, m_data.m_iSelEnd3, x);

                  iLine++;

                  if (iLine < m_data.m_layouta.get_count())
                  {

                     m_data.m_iSelEnd3 = m_data.hit_test_line_x(iLine, x);

                     if (!bShift)
                     {

                        m_data.m_iSelBeg3 = m_data.m_iSelEnd3;

                     }


                     //_001EnsureVisibleLine(iLine);

                     m_data.internal_update_sel_char();

                  }

               }
               else if (pkey->m_ekey == ::user::key_right)
               {

                  on_reset_focus_start_tick();

                  if (!bShift && m_data.m_iSelBeg3 > m_data.m_iSelEnd3)
                  {

                     synch_lock sl(m_data.m_pmutex);

                     m_data.m_iSelEnd3 = m_data.m_iSelBeg3;

                     m_data.internal_update_sel_char();

                  }
                  else if (!bShift && m_data.m_iSelEnd3 > m_data.m_iSelBeg3)
                  {

                     synch_lock sl(m_data.m_pmutex);

                     m_data.m_iSelBeg3 = m_data.m_iSelEnd3;

                     m_data.internal_update_sel_char();

                  }
                  else
                  {

                     synch_lock sl(m_data.m_pmutex);

                     if (m_data.m_iSelEnd3 < m_data._001GetLayoutTextLength())
                     {

                        string strText;

                        _001GetLayoutText(strText);

                        const char * psz = strText;

                        const char * end = &psz[m_data.m_iSelEnd3];

                        const char * inc = ::str::utf8_inc(end);

                        m_data.m_iSelEnd3 += inc - end;

                        if (!bShift)
                        {

                           m_data.m_iSelBeg3 = m_data.m_iSelEnd3;

                        }

                        m_data.internal_update_sel_char();

                     }

                  }

               }
               else if (pkey->m_ekey == ::user::key_left)
               {

                  on_reset_focus_start_tick();

                  if (!bShift && m_data.m_iSelBeg3 < m_data.m_iSelEnd3)
                  {

                     synch_lock sl(m_data.m_pmutex);

                     m_data.m_iSelEnd3 = m_data.m_iSelBeg3;

                     m_data.internal_update_sel_char();

                  }
                  else if (!bShift && m_data.m_iSelEnd3 < m_data.m_iSelBeg3)
                  {

                     synch_lock sl(m_data.m_pmutex);

                     m_data.m_iSelBeg3 = m_data.m_iSelEnd3;

                     m_data.internal_update_sel_char();

                  }
                  else if (m_data.m_iSelEnd3 > 0)
                  {

                     synch_lock sl(m_data.m_pmutex);

                     string strText;

                     _001GetLayoutText(strText);

                     const char * psz = strText;

                     const char * end = &psz[m_data.m_iSelEnd3];

                     const char * dec = ::str::utf8_dec(psz, end);

                     m_data.m_iSelEnd3 -= end - dec;

                     if (!bShift)
                     {

                        m_data.m_iSelBeg3 = m_data.m_iSelEnd3;

                     }

                     m_data.internal_update_sel_char();

                  }

               }
               else if (pkey->m_ekey == ::user::key_home)
               {

                  on_reset_focus_start_tick();

                  synch_lock sl(m_data.m_pmutex);

                  if (bControl)
                  {

                     m_data.m_iSelEnd3 = 0;

                     //   _001EnsureVisibleLine(0);

                  }
                  else
                  {

                     index iLine = m_data.SelToLine(m_data.m_iSelEnd3);

                     m_data.m_iSelEnd3 = m_data.LineColumnToSel(iLine, 0);

                  }

                  if (!bShift)
                  {

                     m_data.m_iSelBeg3 = m_data.m_iSelEnd3;

                  }

                  m_data.internal_update_sel_char();

               }
               else if (pkey->m_ekey == ::user::key_end)
               {

                  on_reset_focus_start_tick();

                  synch_lock sl(m_data.m_pmutex);

                  if (bControl)
                  {

                     m_data.m_iSelEnd3 = _001GetTextLength();

                     //   _001EnsureVisibleLine(iLine);

                  }
                  else
                  {

                     index iLine = m_data.SelToLine(m_data.m_iSelEnd3);

                     m_data.m_iSelEnd3 = m_data.LineColumnToSel(iLine, -1);

                  }

                  if (!bShift)
                  {

                     m_data.m_iSelBeg3 = m_data.m_iSelEnd3;

                  }

                  m_data.internal_update_sel_char();

               }
               else if (pkey->m_ekey == ::user::key_escape)
               {
               }
               else if (is_window_enabled())
               {

                  on_reset_focus_start_tick();
                  //if (!m_bReadOnly)
                  {
                     if (pkey->m_ekey == ::user::key_return)
                     {
                        // Kill Focus => Kill Key Repeat timer
                        //System.simple_message_box("VK_RETURN reached plain_edit");
                     }

                     string str;
                     char ch = 0;
                     if (pkey->m_ekey == ::user::key_tab)
                     {

                        //if (m_bTabInsertSpaces)
                        //{

                        //   auto iColumn = SelToColumn(m_data.m_iSelEnd);

                        //   str = string(m_iTabWidth - (iColumn % m_iTabWidth), ' ');

                        //}
                        //else
                        //{

                        //   str = '\t';

                        //}

                        str = "   ";

                     }
                     else if (pkey->m_ekey == ::user::key_refer_to_text_member)
                     {
                        str = pkey->m_strText;
                        //                     if(bShift)
                        //                     {
                        //                        str.make_upper();
                        //                     }
                     }
                     else
                     {
                        ch = (char)pkey->m_nChar;
                        if (ch == '\r')
                           ch = '\n';
                        int32_t iChar = (int32_t)pkey->m_nChar;
                        if (iChar == '\r')
                           iChar = '\n';
                        if (bShift)
                        {
                           iChar |= 0x80000000;
                        }
                        int32_t iCode = pkey->m_nFlags & 0xff;
                        if (bShift)
                        {
                           iCode |= 0x80000000;
                        }
                        str = Session.keyboard().process_key(pkey);
                     }

                     m_data._001InsertText(str);

                     on_after_change(::user::event_after_change_text);

                     set_need_redraw();

                     bUpdate = false;

                  }

               }

               //int iColumnX;

               //auto iColumn = SelToColumnX(m_data.m_iSelEnd, iColumnX);

               //if ((pkey->m_ekey != ::user::key_up && pkey->m_ekey == ::user::key_down
               //      && pkey->m_ekey != ::user::key_prior && pkey->m_ekey != ::user::key_next) &&
               //      iColumn != m_iColumn)
               //{

               //   m_iColumn = iColumn;
               //   m_iColumnX = iColumnX;

               //}

            }

         }

         //if (bUpdate)
         //{

         //   internal_edit_update(bFullUpdate, iLineUpdate);

         //}

      }

      void edit::on_after_change(::user::e_event eevent)
      {


         ::user::control_event ev;

         ev.m_eevent = eevent;

         ev.m_id = m_id;

         ev.m_puie = this;

         on_control_event(&ev);

      }

      strsize edit::_001GetTextLength() const
      {

         return m_data._001GetTextLength();

      }


      void edit::update_placement()
      {

         if (m_ppic == NULL)
         {

            return;

         }

         SetWindowPos(0, rect(m_ppic->m_rect), SWP_NOZORDER);

      }


      void edit::io(stream & stream)
      {

         ::user::pic::io(stream);

         m_data.io(stream);

         rect rectWindow;

         if (stream.is_storing())
         {

            GetWindowRect(rectWindow);

            if (GetParent() != NULL)
            {

               GetParent()->ScreenToClient(rectWindow);

            }

            stream(rectWindow);

         }
         else
         {

            stream(rectWindow);

            SetWindowPos(0, rectWindow, SWP_NOZORDER | SWP_SHOWWINDOW);

            set_need_layout();

         }

      }


   } // namespace rich_text


} // namespace user



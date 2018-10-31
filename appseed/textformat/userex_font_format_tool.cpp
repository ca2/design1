#include "framework.h"

#ifdef WINDOWSEX
#include <Commdlg.h>
#endif

namespace userex
{


   font_format_tool::font_format_tool(::aura::application * papp) :
      ::object(papp),
      m_buttonBold(papp),
      m_buttonItalic(papp),
      m_buttonUnderline(papp),
      m_comboFamily(papp),
      m_comboSize(papp),
      m_buttonForeground(papp),
      m_buttonBackground(papp),
      m_buttonSubscript(papp),
      m_buttonSuperscript(papp),
      m_buttonLineHeight(papp),
      m_buttonAlignLeft(papp),
      m_buttonAlignCenter(papp),
      m_buttonAlignRight(papp),
      m_format(papp)
   {



      set_translucent();

   }


   font_format_tool::~font_format_tool()
   {

   }


   void font_format_tool::install_message_routing(::message::sender * psender)
   {

      ::user::tool_window::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &::userex::font_format_tool::_001OnCreate);

   }


   void font_format_tool::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
      {

         return;

      }


      m_buttonBold.create_window(null_rect(), this, "font_bold");
      m_buttonBold.LoadBitmaps("matter://fontformat/bold-text-option12.png");
      m_buttonBold.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonBold.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_buttonItalic.create_window(null_rect(), this, "font_italic");
      m_buttonItalic.LoadBitmaps("matter://fontformat/italicize-text12.png");
      m_buttonItalic.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonItalic.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_buttonUnderline.create_window(null_rect(), this, "font_underline");
      m_buttonUnderline.LoadBitmaps("matter://fontformat/underline-text-option12.png");
      m_buttonUnderline.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonUnderline.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_comboFamily.create_window(null_rect(), this, "combo_family");
      auto pfont = m_comboFamily.create_point_font(::user::font_plain_edit, "Segoe UI", 9.0);
      pfont->m_etextrenderinghint = ::draw2d::text_rendering_hint_clear_type_grid_fit;
      m_comboFamily.create_color(::user::color_text, ARGB(255, 80, 80, 80));
      m_comboFamily.create_color(::user::color_background, ARGB(255, 255, 255, 255));

      m_comboSize.create_window(null_rect(), this, "combo_size");
      pfont = m_comboSize.create_point_font(::user::font_plain_edit, "Segoe UI", 9.0);
      pfont->m_etextrenderinghint = ::draw2d::text_rendering_hint_clear_type_grid_fit;
      m_comboSize.create_color(::user::color_text, ARGB(255, 80, 80, 80));
      m_comboSize.create_color(::user::color_background, ARGB(255, 255, 255, 255));
      ::rectd r(2, 2, 2, 2);
      create_rect(::user::rect_edit_padding, r, ::draw2d::unit_pixel);


      m_comboSize.m_edatamode = ::user::combo_box::data_mode_string;

      m_comboSize.m_bEdit = true;

      m_comboSize.AddString("6", "6");
      m_comboSize.AddString("6.5", "6.5");
      m_comboSize.AddString("7", "7");
      m_comboSize.AddString("7.5", "7.5");
      m_comboSize.AddString("8", "8");
      m_comboSize.AddString("8.5", "8.5");
      m_comboSize.AddString("9", "9");
      m_comboSize.AddString("10", "10");
      m_comboSize.AddString("11", "11");
      m_comboSize.AddString("12", "12");
      m_comboSize.AddString("14", "14");
      m_comboSize.AddString("16", "16");
      m_comboSize.AddString("18", "18");
      m_comboSize.AddString("21", "21");
      m_comboSize.AddString("24", "24");
      m_comboSize.AddString("32", "32");
      m_comboSize.AddString("36", "36");
      m_comboSize.AddString("42", "42");
      m_comboSize.AddString("48", "48");
      m_comboSize.AddString("56", "56");
      m_comboSize.AddString("64", "64");
      m_comboSize.AddString("72", "72");
      m_comboSize.AddString("144", "144");

      m_buttonForeground.create_window(null_rect(), this, "font_foreground");
      m_buttonForeground.LoadBitmaps("matter://fontformat/font-foreground12.png");

      m_buttonForeground.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonForeground.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_buttonBackground.create_window(null_rect(), this, "font_background");
      m_buttonBackground.LoadBitmaps("matter://fontformat/text-background12.png");
      m_buttonBackground.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonBackground.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_buttonSubscript.create_window(null_rect(), this, "font_subscript");
      m_buttonSubscript.LoadBitmaps("matter://fontformat/x2-symbol-of-a-letter-and-a-number-subscript12.png");
      m_buttonSubscript.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonSubscript.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_buttonSuperscript.create_window(null_rect(), this, "font_superscript");
      m_buttonSuperscript.LoadBitmaps("matter://fontformat/superscript-text-formatting12.png");
      m_buttonSuperscript.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonSuperscript.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_buttonAlignLeft.create_window(null_rect(), this, "align_left");
      m_buttonAlignLeft.LoadBitmaps("matter://fontformat/align-to-left12.png");
      m_buttonAlignLeft.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonAlignLeft.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_buttonAlignCenter.create_window(null_rect(), this, "align_center");
      m_buttonAlignCenter.LoadBitmaps("matter://fontformat/center-text-alignment12.png");
      m_buttonAlignCenter.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonAlignCenter.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      m_buttonAlignRight.create_window(null_rect(), this, "align_right");
      m_buttonAlignRight.LoadBitmaps("matter://fontformat/align-to-right12.png");
      m_buttonAlignRight.m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);
      m_buttonAlignRight.m_flagNonClient.unsignalize(::user::interaction::non_client_background);

      create_color(::user::color_background, ARGB(255, 200, 200, 200));
      create_color(::user::color_button_background, ARGB(0, 0, 0, 0));
      create_color(::user::color_button_background_hover, ARGB(255, 180, 180, 180));
      create_color(::user::color_button_background_press, ARGB(255, 160, 160, 160));

   }


   void font_format_tool::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::draw2d::brush_sp brBk(allocer());

      rect rectClient;

      GetClientRect(rectClient);

      brBk->CreateLinearGradientBrush(rectClient.top_left(), rectClient.bottom_left(),
                                      ARGB(255, 230, 230, 230), ARGB(255, 200, 200, 200));

      pgraphics->fill_rect(rectClient, brBk);

   }


   void font_format_tool::on_layout()
   {

      m_buttonBold.SetWindowPos(ZORDER_TOP, 5, 5, 20, 20, SWP_SHOWWINDOW);
      m_buttonItalic.SetWindowPos(ZORDER_TOP, 25, 5, 20, 20, SWP_SHOWWINDOW);
      m_buttonUnderline.SetWindowPos(ZORDER_TOP, 45, 5, 20, 20, SWP_SHOWWINDOW);
      m_comboFamily.SetWindowPos(ZORDER_TOP, 70, 5, 120, 20, SWP_SHOWWINDOW);
      m_comboSize.SetWindowPos(ZORDER_TOP, 195, 5, 40, 20, SWP_SHOWWINDOW);

      int x = 245;

      m_buttonForeground.SetWindowPos(ZORDER_TOP, x, 5, 20, 20, SWP_SHOWWINDOW);
      x += 20;
      m_buttonBackground.SetWindowPos(ZORDER_TOP, x, 5, 20, 20, SWP_SHOWWINDOW);
      x += 20;
      m_buttonSubscript.SetWindowPos(ZORDER_TOP, x, 5, 20, 20, SWP_SHOWWINDOW);
      x += 20;
      m_buttonSuperscript.SetWindowPos(ZORDER_TOP, x, 5, 20, 20, SWP_SHOWWINDOW);
      x += 20;

      x += 10;

      m_buttonAlignLeft.SetWindowPos(ZORDER_TOP, x, 5, 20, 20, SWP_SHOWWINDOW);
      x += 20;
      m_buttonAlignCenter.SetWindowPos(ZORDER_TOP, x, 5, 20, 20, SWP_SHOWWINDOW);
      x += 20;
      m_buttonAlignRight.SetWindowPos(ZORDER_TOP, x, 5, 20, 20, SWP_SHOWWINDOW);
      x += 20;

      //m_buttonItalic;
      //m_buttonUnderline;
      //m_buttonFamily;
      //m_buttonForeground;
      //m_buttonBackground;
      //m_buttonSubscript;
      //m_buttonSuperscript;
      //m_buttonLineHeight


   }


   bool font_format_tool::is_showing_for_ui(::user::interaction * pui)
   {

      return GetOwner() == pui;

   }


   void font_format_tool::show_for_ui(::user::interaction * pui)
   {

      rect rW;

      pui->GetWindowRect(rW);

      SetOwner(pui);

      rect r(rW.top_left() - size(0, 48), ::size(100, 100));

      rect rectWindow;

      GetWindowRect(rectWindow);

      rect rWindow;

      rWindow.left = r.left - 32;
      rWindow.top = r.top - 32;
      rWindow.right = rWindow.left + 400;
      rWindow.bottom = rWindow.top + 32;

      fork([this, rWindow]()
      {

         enable_window();

         SetWindowPos(ZORDER_TOPMOST, rWindow, SWP_NOACTIVATE | SWP_SHOWWINDOW);

      });

   }


   void font_format_tool::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_actioncontext.is_user_source())
      {

         if (pevent->m_eevent == ::user::event_button_clicked)
         {

            if (pevent->m_puie->m_id == "font_bold")
            {

               m_buttonBold._001ToggleCheck(::action::source_user);

               m_eattributea.add(::user::rich_text::attribute_bold);

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_italic")
            {

               m_buttonItalic._001ToggleCheck(::action::source_user);

               m_eattributea.add(::user::rich_text::attribute_italic);

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_underline")
            {

               m_buttonUnderline._001ToggleCheck(::action::source_user);

               m_eattributea.add(::user::rich_text::attribute_underline);

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_subscript")
            {

               m_buttonSubscript._001ToggleCheck(::action::source_user);

               if (m_buttonSubscript._001GetCheck() == ::check::checked)
               {

                  m_buttonSuperscript._001SetCheck(::check::unchecked, ::action::source_sync);

               }

               m_eattributea.add(::user::rich_text::attribute_script);

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_superscript")
            {

               m_buttonSuperscript._001ToggleCheck(::action::source_user);

               if (m_buttonSuperscript._001GetCheck() == ::check::checked)
               {

                  m_buttonSubscript._001SetCheck(::check::unchecked, ::action::source_sync);

               }

               m_eattributea.add(::user::rich_text::attribute_script);

               update_data(true);

               pevent->Ret();

            }

            else if (pevent->m_puie->m_id == "align_left")
            {

               m_buttonAlignLeft._001SetCheck(::check::checked, ::action::source_user);

               if (m_buttonAlignCenter._001GetCheck() == ::check::checked)
               {

                  m_buttonAlignCenter._001SetCheck(::check::unchecked, ::action::source_sync);

               }

               if (m_buttonAlignRight._001GetCheck() == ::check::checked)
               {

                  m_buttonAlignRight._001SetCheck(::check::unchecked, ::action::source_sync);

               }

               m_eattributea.add(::user::rich_text::attribute_align);

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "align_center")
            {

               m_buttonAlignCenter._001SetCheck(::check::checked, ::action::source_user);

               if (m_buttonAlignLeft._001GetCheck() == ::check::checked)
               {

                  m_buttonAlignLeft._001SetCheck(::check::unchecked, ::action::source_sync);

               }

               if (m_buttonAlignRight._001GetCheck() == ::check::checked)
               {

                  m_buttonAlignRight._001SetCheck(::check::unchecked, ::action::source_sync);

               }

               m_eattributea.add(::user::rich_text::attribute_align);

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "align_right")
            {

               m_buttonAlignRight._001SetCheck(::check::checked, ::action::source_user);

               if (m_buttonAlignLeft._001GetCheck() == ::check::checked)
               {

                  m_buttonAlignLeft._001SetCheck(::check::unchecked, ::action::source_sync);

               }

               if (m_buttonAlignCenter._001GetCheck() == ::check::checked)
               {

                  m_buttonAlignCenter._001SetCheck(::check::unchecked, ::action::source_sync);

               }

               m_eattributea.add(::user::rich_text::attribute_align);

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_foreground")
            {

               fork([&]()
               {

#ifdef WINDOWSEX
                  CHOOSECOLOR cc;
                  COLORREF crCustColors[16];

                  // init-int this array did not affect the mouse problem
                  // uint idx ;
                  // for (idx=0; idx<16; idx++) {
                  // crCustColors[idx] = RGB(idx, idx, idx) ;
                  // }

                  ZeroMemory(&cc, sizeof(cc));
                  cc.lStructSize = sizeof(CHOOSECOLOR);
                  cc.rgbResult = RGB(0, 0, 0);
                  cc.lpCustColors = crCustColors;
                  cc.Flags = CC_RGBINIT | CC_FULLOPEN;
                  cc.hwndOwner = get_safe_handle() ; // this hangs parent, as well as me

                  if (::ChooseColor(&cc))
                  {

                     m_eattributea.add(::user::rich_text::attribute_foreground);

                     m_format.m_crForeground = cc.rgbResult | (255 << 24);

                     update_data(true);

                  }
#endif
               });

            }

         }
         else if (pevent->m_eevent == ::user::event_after_change_text)
         {

            if (pevent->m_puie->m_id == "combo_size")
            {

               m_eattributea.add(::user::rich_text::attribute_size);

               update_data(true);

               pevent->Ret();

            }

         }
         else if (pevent->m_eevent == ::user::event_enter_key)
         {

            if (pevent->m_puie->m_id == "combo_size")
            {

               m_eattributea.add(::user::rich_text::attribute_size);

               update_data(true);

               pevent->Ret();

            }

         }
         else if (pevent->m_eevent == ::user::event_after_change_cur_sel)
         {

            if (pevent->m_puie->m_id == "combo_family")
            {

               m_eattributea.add(::user::rich_text::attribute_family);

               update_data(true);

               pevent->Ret();


            }
            else if (pevent->m_puie->m_id == "combo_size")
            {

               m_eattributea.add(::user::rich_text::attribute_size);

               update_data(true);

               pevent->Ret();

            }

         }

      }

      if (pevent->m_bRet)
      {

         return;

      }

      return ::user::tool_window::on_control_event(pevent);

   }


   void font_format_tool::set_font_size(double dFontSize)
   {

      dFontSize = MAX(6.0, MIN(1440.0, dFontSize));

      double dRound = dFontSize - (double)(int)dFontSize;

      int iRound = -1;

      int iDouble = -1;

      string strEdit;

      if (dRound < 0.25)
      {

         iRound = dFontSize;

         m_format.m_dFontSize = (double)iRound;

         strEdit = ::str::from(iRound);

      }
      else if (dRound >= 0.75)
      {

         iRound = dFontSize;

         iRound++;

         m_format.m_dFontSize = (double)iRound;

         strEdit = ::str::from(iRound);

      }
      else
      {

         iDouble = (dFontSize + 0.25) * 2.0;

         m_format.m_dFontSize = ((double)iRound) / 2.0;

         strEdit = ::str::from(iDouble / 2) + ".5";

      }

      m_comboSize._001SetText(strEdit, ::action::source_sync);

   }


   bool font_format_tool::update_data(bool bSaveAndValidate)
   {

      if (bSaveAndValidate)
      {

         if (m_comboFamily.m_iSel >= 0)
         {

            m_format.m_strFontFamily = m_comboFamily.m_plist.cast <::user::font_list>()->m_pfontlist->m_itema[m_comboFamily.m_iSel]->m_strName;

         }

         string str;

         m_comboSize._001GetText(str);

         set_font_size(strtod(str, NULL));

         m_format.m_bUnderline = m_buttonUnderline._001GetCheck() == ::check::checked;
         m_format.m_bItalic = m_buttonItalic._001GetCheck() == ::check::checked;
         m_format.m_bBold = m_buttonBold._001GetCheck() == ::check::checked;
         if (m_buttonSuperscript._001GetCheck() == ::check::checked)
         {

            m_format.m_escript = ::user::rich_text::script_superscript;

         }
         else if (m_buttonSubscript._001GetCheck() == ::check::checked)
         {

            m_format.m_escript = ::user::rich_text::script_subscript;

         }
         else
         {

            m_format.m_escript = ::user::rich_text::script_normal;

         }
         if (m_buttonAlignRight._001GetCheck() == ::check::checked)
         {

            m_format.m_ealign = ::user::rich_text::align_right;

         }
         else if (m_buttonAlignCenter._001GetCheck() == ::check::checked)
         {

            m_format.m_ealign = ::user::rich_text::align_center;

         }
         else
         {

            m_format.m_ealign = ::user::rich_text::align_left;

         }

         m_format.m_bUpdated = false;

         ::user::control_event ev;

         ev.m_eevent = ::user::event_after_change_cur_sel;

         ev.m_puie = this;

         ev.m_id = m_id;

         on_control_event(&ev);

      }
      else
      {

         m_comboFamily._001SetCurSel(m_comboFamily.m_plist.cast <::user::font_list>()->m_pfontlist->find_name(m_format.m_strFontFamily), ::action::source_sync);

         set_font_size(m_format.m_dFontSize);

         m_buttonBold._001SetCheck(m_format.m_bBold ? ::check::checked : ::check::unchecked, ::action::source_sync);
         m_buttonItalic._001SetCheck(m_format.m_bItalic ? ::check::checked : ::check::unchecked, ::action::source_sync);
         m_buttonUnderline._001SetCheck(m_format.m_bUnderline ? ::check::checked : ::check::unchecked, ::action::source_sync);

         bool bLeft = m_format.m_ealign == ::user::rich_text::align_left;
         bool bCenter = m_format.m_ealign == ::user::rich_text::align_center;
         bool bRight = m_format.m_ealign == ::user::rich_text::align_right;

         m_buttonAlignLeft._001SetCheck(bLeft, ::action::source_sync);
         m_buttonAlignCenter._001SetCheck(bCenter, ::action::source_sync);
         m_buttonAlignRight._001SetCheck(bRight, ::action::source_sync);

      }

      return true;

   }


} // namespace user




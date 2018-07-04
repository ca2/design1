#include "framework.h"
#include <math.h>


namespace textformat
{


   view::view(::aura::application * papp):
      object(papp),
      m_dibColor(allocer()),
      m_dibAi1(allocer()),
      m_dibAi2(allocer())
   {

      m_iTurn = 0;
      oprop("font_sel") = true;


      m_flagNonClient.unsignalize(non_client_background);
      m_flagNonClient.unsignalize(non_client_focus_rect);

      m_bOkPending               = false;

      m_bOkPending = true;


   }


   view::~view()
   {

   }

   void view::assert_valid() const
   {
      user::box::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE,psender,this,&view::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &view::_001OnDestroy);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &view::_001OnLButtonDown);

   }


   void view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      string strText;

      data_get("cur_text",strText);

      if(GetTypedParent<::user::split_view>() != NULL)
      {

         if(GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != NULL)
         {

            sp(::user::edit_text) pedit = GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view");

            pedit->_001SetText(strText,::action::source_initialize);


         }

      }

   }


   void view::_001OnDestroy(::message::message * pobj)
   {

   }


   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
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


   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      GetClientRect(rectClient);

      pgraphics->fill_solid_rect(rectClient, ARGB(40, 255, 255, 255));

   }


   void view::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->previous();

      pobj->m_bRet = true;

      sp(::user::rich_text::edit) pedit = canew(::user::rich_text::edit(get_app()));

      fill(pedit);

      pedit->create_color(::user::color_background, ARGB(255, 255, 255, 255));

      m_edita.add(pedit);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      pedit->create_window(rect(pt, ::size(128, 384)), this, string("edit_") + ::str::from(m_edita.get_count()));

   }

   void view::fill(::user::rich_text::edit * pedit)
   {

      int iTurn = m_iTurn % 3;

      m_iTurn++;

      if (iTurn == 0)
      {

         sp(::user::rich_text::format) pformat = canew(::user::rich_text::format(get_app()));

         pedit->m_data.m_formata.add(pformat);

         sp(::user::rich_text::box) pbox = canew(::user::rich_text::box(get_app()));

         pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_center));

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app()));

         pbox->m_str = "Segoe UI Tex";

         pformat->m_crForeground = ARGB(255, 80, 80, 80);

         pbox->m_iFormat = 0;

         pedit->m_data.m_boxa.add(pbox);

         pformat = canew(::user::rich_text::format(get_app()));

         pformat->m_bBold = true;

         pformat->m_crForeground = ARGB(255, 255, 0, 0);

         pedit->m_data.m_formata.add(pformat);

         pbox = canew(::user::rich_text::box(get_app()));

         pbox->m_str = "t Segoe UI Bold Gold Text";

         pbox->m_iFormat = 1;

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_center));

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app()));

         pbox->m_str = "One Line";

         pbox->m_iFormat = 0;

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_center));

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_center));

         pbox->m_bParagraph = true;

         pbox->m_iFormat = 0;

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app()));

         pbox->m_str = "Two Lines";

         pbox->m_iFormat = 0;

         pedit->m_data.m_boxa.add(pbox);

      }
      else if (iTurn == 1)
      {

         sp(::user::rich_text::format) pformat = canew(::user::rich_text::format(get_app()));

         pedit->m_data.m_formata.add(pformat);

         sp(::user::rich_text::box) pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_left));

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app()));

         pbox->m_str = "10000";

         pformat->m_crForeground = ARGB(255, 80, 80, 80);

         pbox->m_iFormat = 0;

         pedit->m_data.m_boxa.add(pbox);

         pformat = canew(::user::rich_text::format(get_app()));

         pformat->m_bBold = true;

         pformat->m_crForeground = ARGB(255, 255, 0, 0);

         pedit->m_data.m_formata.add(pformat);

         pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_left));

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app()));

         pbox->m_str = "20000";

         pbox->m_iFormat = 1;

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_left));

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app()));

         pbox->m_str = "30000";

         pbox->m_iFormat = 0;

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_left));

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app(), ::user::rich_text::align_left));

         pedit->m_data.m_boxa.add(pbox);

         pbox = canew(::user::rich_text::box(get_app()));

         pbox->m_str = "40000";

         pbox->m_iFormat = 0;

         pedit->m_data.m_boxa.add(pbox);

      }

   }


   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }


   void view::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      m_bOkPending = true;

   }


} // namespace textformat



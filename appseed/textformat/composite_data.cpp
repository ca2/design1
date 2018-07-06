#include "framework.h"


namespace composite
{


   data::data(::aura::application * papp) :
      ::object(papp),
      ::data::data(papp),
      m_sizePagePrev(0, 0)
   {

      m_rectMargin.set(0);
      m_rectMaxMarginDrawing.set(0);
      m_rectMarginDrawing.set(0);

      m_pictool = canew(pic_tool(get_app()));

      m_pictool->m_map[pic_tool::tool_rotate].m_dib = Application.get_matter_dib("pictool/rotation24.png");
      m_pictool->m_map[pic_tool::tool_crop].m_dib = Application.get_matter_dib("pictool/crop-icon24.png");
      m_pictool->m_map[pic_tool::tool_close].m_dib = Application.get_matter_dib("pictool/close-button24.png");
      m_pictool->m_map[pic_tool::tool_stack_up].m_dib = Application.get_matter_dib("pictool/stackup24.png");
      m_pictool->m_map[pic_tool::tool_special_effect].m_dib = Application.get_matter_dib("pictool/fx24.png");
      m_pictool->m_map[pic_tool::tool_stack_down].m_dib = Application.get_matter_dib("pictool/stackdown24.png");
      m_pictool->m_map[pic_tool::tool_resize].m_dib = Application.get_matter_dib("pictool/resize20.png");

      m_pictool->m_map[pic_tool::tool_zoom_out].m_dib = Application.get_matter_dib("pictool/zoomout24.png");
      m_pictool->m_map[pic_tool::tool_zoom_in].m_dib = Application.get_matter_dib("pictool/zoomin24.png");
      m_pictool->m_map[pic_tool::tool_move].m_dib = Application.get_matter_dib("pictool/drag24.png");
      m_pictool->m_map[pic_tool::tool_apply].m_dib = Application.get_matter_dib("pictool/apply24.png");

      m_pictool->m_map[pic_tool::tool_resize].m_ecursor = visual::cursor_size_bottom_right;

      m_pictool->m_penBorder.alloc(allocer());
      m_pictool->m_penBorder->create_solid(1.0, ARGB(190, 80, 120, 200));
      m_pictool->m_penBorder->m_etype = ::draw2d::pen::type_dash;

   }


   data::~data()
   {



   }


   void data::stream(::serialize & serialize)
   {

      serialize.stream_array(m_pica);

   }

   pic::pic(::aura::application * papp) :
      ::object(papp),
      ::user::pic(papp)
   {

      m_pview = Application.m_pcompositeviewCurrent;

   }


   bool pic::pic::is_valid()
   {

      return m_dib.is_set() && m_dib->area() > 0;

   }


   ::sized pic::pic::get_size()
   {

      return m_dib->m_size;

   }


   void pic::stream(serialize & serialize)
   {

      if (serialize.is_storing())
      {

         string strLink = m_dib->oprop("read_only_link");

         serialize(strLink);

      }
      else
      {

         string strLink;

         serialize(strLink);

         if (strLink.is_empty())
         {

            return;

         }

         m_dib.alloc(allocer());

         System.imaging().load_from_file(m_dib, m_pview->get_link_path(strLink));

         m_dib->oprop("read_only_link") = strLink;

      }

      ::user::pic::stream(serialize);

   }


   void pic::pic::draw(::draw2d::graphics * pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      ::draw2d::matrix mRot;

      rectd rClip(m_ppic->m_rect);

      pointd_array pta;

      pta.set_size(4);

      pta[0] = _transform(rClip.top_left());
      pta[1] = _transform(rClip.top_right());
      pta[2] = _transform(rClip.bottom_right());
      pta[3] = _transform(rClip.bottom_left());

      ::draw2d::region_sp rgn(allocer());

      rgn->create_polygon(pta.get_data(), (int)pta.get_count(), ::draw2d::fill_mode_winding);

      pgraphics->SelectClipRgn(rgn, RGN_AND);

      mRot.append(::draw2d::matrix::rotation(m_ppic->m_dRotate));

      pgraphics->prepend(mRot);

      pgraphics->prepend(::draw2d::matrix::scaling(m_ppic->m_dZoom, m_ppic->m_dZoom));

      ::draw2d::matrix mTrans;

      mTrans.append(::draw2d::matrix::translation(m_ppic->m_rect.center().x, m_ppic->m_rect.center().y));

      pgraphics->append(mTrans);

      rect r(-point(m_ppic->m_rect.get_size() / 2.0) +
             point(m_ppic->m_ptDrag.x * m_ppic->m_rect.width(),
                   m_ppic->m_ptDrag.y * m_ppic->m_rect.height()), ::size(m_ppic->m_rect.get_size()));

      pgraphics->draw(r, m_dib->g(), rect(m_dib->m_size));

   }




} // namespace composite
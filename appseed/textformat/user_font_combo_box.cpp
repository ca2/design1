#include "framework.h"


namespace user
{


   font_combo_box::font_combo_box()
   {

      font_combo_box_common_construct();

   }


   font_combo_box::font_combo_box(::aura::application * papp) :
      ::object(papp),
      ::user::combo_box(papp)
   {

      font_combo_box_common_construct();

   }


   void font_combo_box::font_combo_box_common_construct()
   {
      
      m_typeComboList = System.type_info < ::user::font_list >();
      
      m_bEdit = false;

   }
   

   font_combo_box::~font_combo_box()
   {

   }


   void font_combo_box::install_message_routing(::message::sender * psender)
   {

      ::user::combo_box::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &::user::font_combo_box::_001OnCreate);

   }


   void font_combo_box::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);
      
      pcreate->previous();

      ::rectd r(2, 2, 2, 2);

      create_rect(::user::rect_edit_padding, r, ::draw2d::unit_pixel);

      defer_create_combo_list();

      sp(::user::font_list) plist = m_plist;

      m_edatamode = data_mode_string;

      plist->m_layout.m_elayout = ::visual::font_list::layout_single_column;

   }


   void font_combo_box::on_layout()
   {

      ::user::font_list & list = *m_plist.cast < ::user::font_list>();

      synch_lock sl(list.m_pmutex);

      for (auto & item : list.m_pfontlist->m_itema)
      {

         if (item.is_set())
         {

            AddString(item->m_strName, item->m_strName);

         }

      }

   }


} //  namespace user




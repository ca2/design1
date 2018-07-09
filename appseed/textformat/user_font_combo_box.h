#pragma once


namespace user
{


   class CLASS_DECL_DESIGN_TEXTFORMAT font_combo_box :
      virtual public ::user::combo_box
   {
   public:


      font_combo_box();
      font_combo_box(::aura::application * papp);
      virtual ~font_combo_box();


      virtual void install_message_routing(::message::sender * psender);


      DECL_GEN_SIGNAL(_001OnCreate);

      void on_layout();


   };


} //  namespace user




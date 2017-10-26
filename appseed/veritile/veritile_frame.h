#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE frame : 
      virtual public simple_frame_window
   {
   public:
   
      frame(::aura::application * papp);
      virtual ~frame();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      void install_message_routing(::message::sender * pinterface);


      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);;


      bool get_translucency(::user::e_translucency  & etranslucency);


   };


} // namespace veritile







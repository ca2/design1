#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE frame : 
      virtual public simple_frame_window
   {
   public:
   
      frame(::aura::application * papp);
      virtual ~frame();

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      void install_message_handling(::message::dispatch * pinterface);


      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);;


      bool get_translucency(::user::ETranslucency  & etranslucency);


   };


} // namespace veritile






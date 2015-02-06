#pragma once


namespace devedge
{


   class CLASS_DECL_DEVEDGE child_frame :
      public simple_child_frame
   {
   public:

      
      child_frame(::aura::application * papp);
      virtual ~child_frame();

      sp(::filemanager::manager) GetFileManager();

      virtual bool on_create_bars() override;
      

      

      virtual void install_message_handling(::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnAppLanguage);


   };


} // namespace devedge





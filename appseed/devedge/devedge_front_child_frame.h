#pragma once


namespace devedge
{


   class CLASS_DECL_DEVEDGE front_child_frame :
      public simple_child_frame
   {
   public:


      front_child_frame(::aura::application * papp);
      virtual ~front_child_frame();


      void OnChangeEditSearch();

      bool pre_create_window(::user::create_struct& cs);

      sp(::filemanager::manager) GetFileManager();

      virtual bool on_create_bars() override;
      

      virtual void _001OnCmdMsg(::user::command * pcommand) override; 


      DECL_GEN_SIGNAL(_001OnCreate);

         DECL_GEN_SIGNAL(_001OnAppLanguage);

         
   };



} // namespace devedge





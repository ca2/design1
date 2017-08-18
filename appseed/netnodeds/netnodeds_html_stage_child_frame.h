#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS html_stage_child_frame :
      public simple_child_frame
   {
   public:
      

      html_stage_child_frame(::aura::application * papp);
      virtual ~html_stage_child_frame();

      void OnChangeEditSearch();

      sp(::filemanager::manager) GetFileManager();

      virtual bool on_create_bars() override;
      
      
      bool pre_create_window(::user::create_struct& cs);

      virtual bool _001OnCmdMsg(::user::command * pcommand); 

      

      DECL_GEN_SIGNAL(_001OnCreate);

      DECL_GEN_SIGNAL(_001OnAppLanguage);

   };



} // namespace netnodeds



#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS front_child_frame :
      public simple_child_frame
   {
   public:


      front_child_frame(::aura::application * papp);
      virtual ~front_child_frame();


      void OnChangeEditSearch();

      bool pre_create_window(::user::create_struct& cs);

      sp(::filemanager::manager) GetFileManager();

      virtual bool on_create_bars() override;
      

      virtual bool _001OnCmdMsg(::user::command * pcommand); 


      DECL_GEN_SIGNAL(_001OnCreate);

         DECL_GEN_SIGNAL(_001OnAppLanguage);

         
   };



} // namespace netnodeds





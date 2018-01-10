#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR front_child_frame :
      public simple_child_frame
   {
   public:


      front_child_frame(::aura::application * papp);
      virtual ~front_child_frame();

      bool pre_create_window(::user::create_struct& cs);


      void OnChangeEditSearch();

      sp(::filemanager::manager) GetFileManager();

      virtual bool on_create_bars();

      virtual bool _001OnCmdMsg(::user::command * pcommand); 

      DECL_GEN_SIGNAL(_001OnCreate);

      DECL_GEN_SIGNAL(_001OnAppLanguage);

   };


} // namespace biteditor




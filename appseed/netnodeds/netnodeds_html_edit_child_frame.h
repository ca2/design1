#pragma once



namespace devedge
{



   class CLASS_DECL_DEVEDGE html_edit_child_frame :
      public simple_child_frame
   {
   public:


      html_edit_child_frame(::aura::application * papp);
      virtual ~html_edit_child_frame();

      void OnChangeEditSearch();

      sp(::filemanager::manager) GetFileManager();
      virtual bool on_create_bars() override;
      
      virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg); 

      bool pre_create_window(::user::create_struct& cs);

      DECL_GEN_SIGNAL(_001OnCreate);

      DECL_GEN_SIGNAL(_001OnAppLanguage);
         ;
   };



} // namespace devedge



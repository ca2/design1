#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE main_frame : public simple_frame_window
   {
   public:
      
      
      main_frame(::aura::application * papp);
      virtual ~main_frame();


      virtual bool get_translucency(::user::ETranslucency & etranslucency);


   };


} // namespace syllomatter




















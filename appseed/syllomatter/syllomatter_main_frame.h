#pragma once


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER main_frame : public simple_frame_window
   {
   public:


      main_frame(::aura::application * papp);
      virtual ~main_frame();


      virtual bool on_create_bars();

   };


} // namespace syllomatter






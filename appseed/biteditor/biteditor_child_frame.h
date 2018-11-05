#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR child_frame :
      public simple_child_frame
   {
   public:


      child_frame(::aura::application * papp);
      virtual ~child_frame();


      bool on_create_bars();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnAppLanguage);


   };



} // namespace biteditor





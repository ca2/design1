#pragma once


namespace refactor
{


   class pane_view;


   class CLASS_DECL_CA2_REFACTOR frame :
      public simple_frame_window
   {
   public:


      frame(::aura::application * papp);
      virtual ~frame();


      sp(::user::wndfrm::frame::frame) create_frame_schema();
	   
   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif


   };


} // namespace refactor





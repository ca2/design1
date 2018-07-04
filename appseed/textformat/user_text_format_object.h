#pragma once


namespace user
{


   class CLASS_DECL_APP_CORE_TEXTFORMAT text_format_object :
      virtual public object
   {
   public:


      string            m_str = "Night1";

      ::rect            m_rect;


      text_format_object();
      text_format_object(::aura::application * papp);
      virtual ~text_format_object();


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


   };


} // namespace user
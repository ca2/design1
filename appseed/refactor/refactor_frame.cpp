#include "framework.h"
#include <math.h>


namespace refactor
{


   frame::frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp)
   {
      m_dataid = "ca2::refactor::frame";

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.handler()->m_varTopicQuery["client_only"].is_set();

   }

   frame::~frame()
   {
   }

#ifdef DEBUG
   void frame::assert_valid() const
   {
	   simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
	   simple_frame_window::dump(dumpcontext);
   }
#endif //DEBUG



   sp(::user::wndfrm::frame::frame) frame::create_frame_schema()
   {

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema(NULL,"002");
      pschema->set_style("StyleLightBlue");
//      pschema->m_typeinfoControlBoxButton = System.template type_info < MetaButton > ();
      return pschema;

/*      frame::FrameSchemaHardCoded005 * pschema = new frame::FrameSchemaHardCoded005(get_app());
      pschema->m_typeinfoControlBoxButton = typeid(MetaButton);
      pschema->SetStyle(frame::FrameSchemaHardCoded005::StyleTranslucidWarmGray);
      return pschema;*/
   }


} // namespace refactor




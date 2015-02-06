#pragma once


#include "app-core/appseed/tesseract/tesseract/tesseract.h"
#include "core/user/userex/userex.h"



#ifdef _APP_CORE_TARSILA_LIBRARY
#define CLASS_DECL_APP_CORE_TARSILA  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_CORE_TARSILA  CLASS_DECL_IMPORT
#endif



namespace tarsila
{

   class application;
   class drawing;
   class element;

} // namespace tarsila




#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::tarsila::application > ())



#include "tarsila_enum.h"


#include "tarsila_area.h"

#include "tarsila_element.h"
#include "tarsila_element_array.h"

#include "tarsila_polygon.h"
#include "tarsila_polygon_array.h"
#include "tarsila_drawing.h"


#include "tarsila_document.h"
#include "tarsila_frame.h"
#include "tarsila_view.h"


#include "tarsila_application.h"


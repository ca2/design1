#pragma once

namespace tarsila
{

   class CLASS_DECL_APP_CORE_TARSILA main_document : public ::user::document
   {
   public:
      main_document(::aura::application * papp);
      virtual ~main_document();
   };

} // namespace syllomatter
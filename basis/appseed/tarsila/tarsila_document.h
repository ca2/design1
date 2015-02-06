#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA document:
      public ::aura::document
   {
   public:


      document(::aura::application * papp);
      virtual ~document();


   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual bool on_new_document();


   };

} // namespace tarsila 
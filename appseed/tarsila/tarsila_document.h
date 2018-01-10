#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA document:
      public ::user::document
   {
   public:


      


      document(::aura::application * papp);
      virtual ~document();



      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual bool on_new_document();
      virtual bool on_open_document(var varFile);

      DECL_GEN_SIGNAL(_001OnFileSaveAs);
      DECL_GEN_SIGNAL(_001OnFileSave);


      void write(::file::ostream & ostream);

   };

} // namespace tarsila 
#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE document:
      public ::user::document
   {
   public:


      


      document(::aura::application * papp);
      virtual ~document();


   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual bool on_new_document();
      virtual bool on_open_document(var varFile);

      DECL_GEN_SIGNAL(_001OnFileSaveAs);
      DECL_GEN_SIGNAL(_001OnFileSave);


      void write(::file::ostream & ostream);

   };

} // namespace veritile 
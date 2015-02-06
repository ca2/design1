#pragma once


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER document :
      public html_document
   {
   public:


      document(::aura::application * papp);



      bool open_commit_message();

      virtual bool on_new_document();
      virtual ~document();
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      bool on_open_document(var varFile);

      DECL_GEN_SIGNAL(data_on_after_change);

   };



} // namespace syllomatter



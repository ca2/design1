#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR front_document :
      public html_document
   {
   public:


      ::memory_file           m_memfile;
      ::file::file_sp                m_file;


      front_document(::aura::application * papp);   
      virtual ~front_document();

      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(const char * lpszPathName);


      void on_simple_command(::user::command * pcommand); 
      void on_simple_command_probe(::user::command * pcommand); 

      void OnUpdateStart(::user::command *pcommand);
      void OnUpdateEditUndo(::user::command *pcommand);
      void OnUpdateEditRedo(::user::command *pcommand);
      void OnStart();
      void OnEditUndo();
      void OnEditRedo();

      virtual bool on_new_document();

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };


} // namespace biteditor




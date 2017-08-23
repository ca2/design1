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


      bool on_simple_action(::user::command * pcommand); 
      bool on_simple_update(command_ui * pcommandui); 

      void OnUpdateStart(command_ui *pcommandui);
      void OnUpdateEditUndo(command_ui *pcommandui);
      void OnUpdateEditRedo(command_ui *pcommandui);
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




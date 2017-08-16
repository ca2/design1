#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS html_edit_document :
      public ::html_document
   {
   public:


      ::memory_file_sp              m_memfile;
      ::file::file_sp               m_file;


      html_edit_document(::aura::application * papp);
      virtual ~html_edit_document();

      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(const char * lpszPathName);


      bool _001OnCommand(id id);
      bool _001OnUpdateCmdUi(command_ui * pcommandui);

      void OnUpdateFileSave(command_ui *pcommandui);
      void OnUpdateEditUndo(command_ui *pcommandui);
      void OnUpdateEditRedo(command_ui *pcommandui);
      void on_file_save();
      void OnEditUndo();
      void OnEditRedo();
      virtual bool on_new_document();
      
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };


} // namespace netnodeds



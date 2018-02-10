#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR document :
      virtual public ::user::document,
      virtual public ::data::tree
   {
   public:

      enum ECommand
      {
         CommandUndefined,
         CommandSetSel,
         CommandFile,
         CommandGroup,
      };

      class Command : public ::data::item
      {
      public:
         virtual ECommand get_command() { return CommandUndefined; }
         virtual void Undo(sp(::biteditor::document) pdoc) {UNREFERENCED_PARAMETER(pdoc);}
         virtual void Redo(sp(::biteditor::document) pdoc) {UNREFERENCED_PARAMETER(pdoc);}

      };

      
      class SetSelCommand : public Command
      {
      public:
         
         
         file_position_t   m_iSelStart;
         file_position_t   m_iSelEnd;
         file_position_t   m_iPreviousSelStart;
         file_position_t   m_iPreviousSelEnd;


         virtual void Undo(sp(::biteditor::document) pdoc);
         virtual void Redo(sp(::biteditor::document) pdoc);
         virtual ECommand get_command(){ return CommandSetSel;};


      };


      class FileCommand : public Command
      {
      public:
         virtual void Undo(sp(::biteditor::document) pdoc);
         virtual void Redo(sp(::biteditor::document) pdoc);
         virtual ECommand get_command(){ return CommandFile;};
      };


      class GroupCommand : public Command,
         public spa(Command)
      {
      public:
         sp(GroupCommand) m_pparent;
         virtual ECommand get_command(){ return CommandGroup;};
         virtual void Undo(sp(::biteditor::document) pdoc);
         virtual void Redo(sp(::biteditor::document) pdoc);

      };

      sp(::data::tree_item)      m_ptreeitem;

      ::memory_file      m_memfile;
      ::file::file_sp          m_pfile;
      ::file::edit_file *      m_peditfile;
      file_position_t            m_iSelStart;
      file_position_t            m_iSelEnd;
      int32_t                    m_iBranch;

      sp(GroupCommand)           m_pgroupcommand;
      bool                       m_bReadOnly;


      document(::aura::application * papp);
      virtual ~document();


      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(const char * lpszPathName);

      bool CanUndo();
      int32_t GetRedoBranchCount();
      bool Undo();
      bool Redo();

      void reload();


      void MacroBegin();
      void MacroRecord(sp(Command) pcommand);
      void MacroEnd();
      DECL_GEN_SIGNAL(data_on_after_change);

      void _001OnCmdMsg(::user::command * pcommand);

      DECL_GEN_SIGNAL(_001OnUpdateFileSave);
      DECL_GEN_SIGNAL(_001OnUpdateFilePut);
      DECL_GEN_SIGNAL(_001OnUpdateEditUndo);
      DECL_GEN_SIGNAL(_001OnUpdateEditRedo);
      DECL_GEN_SIGNAL(_001OnUpdateEditCut);
      DECL_GEN_SIGNAL(_001OnUpdateEditCopy);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnFileSave);
      DECL_GEN_SIGNAL(_001OnFilePut);
      DECL_GEN_SIGNAL(_001OnEditUndo);
      DECL_GEN_SIGNAL(_001OnEditRedo);
      DECL_GEN_SIGNAL(_001OnEditCut);
      DECL_GEN_SIGNAL(_001OnEditCopy);
      DECL_GEN_SIGNAL(_001OnEditPaste);

      void Put();
      void FtpPut(const char * lpcszLocal, const char * lpcszRemote);

      virtual bool on_new_document();

   
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   


      virtual sp(::data::item) on_allocate_item();


   };


} // namespace biteditor



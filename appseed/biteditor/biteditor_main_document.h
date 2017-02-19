#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR main_document :
      public ::user::document
   {
   public:

      ::file::memory_buffer        m_memfile;
      ::file::file_sp             m_file;


      main_document(::aura::application * papp);

      virtual bool on_open_document(var varFile);
      virtual bool on_save_document(const char * lpszPathName);

   
   
      DECL_GEN_SIGNAL(data_on_after_change);

      virtual bool on_new_document();

      virtual ~main_document();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };


} // namespace biteditor




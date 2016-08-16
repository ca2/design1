#pragma once


namespace netnodeds
{


   class folder;


   class CLASS_DECL_DESIGN_NETNODEDS file :
      virtual public ::netnodeds::elemental,
      virtual public ::object
   {
   public:
      
      
      // initialize
      folder *          m_pfolder;
      ::file::path      m_strPath;
      //string          m_strName;

      // load
      sp(::user::document)        m_pdocument;


      file(::aura::application * papp);
      
      
      virtual e_solution_type get_solution_type();


      void initialize(folder * pfolder, const char * pszPath);

      void open(sp(::user::interaction) puieParent);

      void close();

   };

} // namespace netnodeds



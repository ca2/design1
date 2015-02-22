#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS elemental :
      virtual public ::data::tree_item,
      virtual public ::object
   {
   public:


      enum e_solution_type
      {
         solution_type_solution,
         solution_type_project,
         solution_type_headers,
         solution_type_source,
         solution_type_folder,
         solution_type_file,
      };


      index                      m_iImage;
      index                      m_iImageSelected;
      string                     m_strName;


      elemental();
      virtual ~elemental();

      virtual string get_text(::data::tree * ptree);
      virtual index get_image(::data::tree * ptree);



      virtual e_solution_type get_solution_type();

      /*#undef new
      void * operator new(size_t i, const char * lpszFileName, int32_t iLine);
      void * operator new(size_t i);
      #define new AURA_NEW
      void operator delete(void *);
      void operator delete(void *, const char * lpszFileName, int32_t iLine);*/


   };


} // namespace netnodeds



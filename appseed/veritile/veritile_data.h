#pragma once

namespace tmx
{
   class image :
      virtual public ::object,
      virtual public ::xml::exportable,
      virtual public ::xml::importable
   {
   public:

      string m_strSource;
      color   m_colorTrans;
      int m_iWidth;
      int m_iHeight;
      virtual void xml_import(::xml::input_tree & xmlif)
      {

         xmlif.get_attr("source", m_strSource);
         string strColor;
         xmlif.get_attr("trans", strColor);
         m_colorTrans.parse_color(strColor);
         xmlif.get_attr("tilewidth", m_iWidth);
         xmlif.get_attr("tileheight", m_iHeight);

      }
      virtual void xml_export(::xml::output_tree & xmlof)
      {
      }

   };

   // <tileset firstgid = "1" name = "archtest1_numbered" tilewidth = "16" tileheight = "16">
   class tileset :
      virtual public ::object,
      virtual public ::xml::exportable,
      virtual public ::xml::importable
   {
   public:

      
      int               m_iFirstGid;
      string            m_strName;
      int               m_iTileWidth;
      int               m_iTileHeight;
      sp(image)         m_pimage;


      virtual void xml_import(::xml::input_tree & xmlif)
      {

         xmlif.get_attr("firstgid", m_iFirstGid);
         xmlif.get_attr("name", m_strName);
         xmlif.get_attr("tilewidth", m_iTileWidth);
         xmlif.get_attr("tileheight", m_iTileHeight);
         m_pimage = canew(image);
         xmlif.import_node("image", *m_pimage);

      }
      virtual void xml_export(::xml::output_tree & xmlof)
      {
      }

   };

   class map :
      virtual public ::object,
      virtual public ::xml::exportable,
      virtual public ::xml::importable
   {
   public:

      int               m_iWidth;
      int               m_iHeight;
      int               m_iTileWidth;
      int               m_iTileHeight;
      sp(tileset)       m_ptileset;

      virtual void xml_import(::xml::input_tree & xmlif)
      {

         xmlif.get_attr("width", m_iWidth);
         xmlif.get_attr("height", m_iHeight);
         xmlif.get_attr("tilewidth", m_iTileWidth);
         xmlif.get_attr("tileheight", m_iTileHeight);
         m_ptileset = canew(tileset);
         xmlif.import_node("tileset", *m_ptileset);

      }

      virtual void xml_export(::xml::output_tree & xmlof)
      {
      }


   };

}

namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE data:
      virtual public ::data::data,
      virtual public ::xml::exportable,
      virtual public ::xml::importable
   {
   public:


      general_data                                    m_data;

      spa(layer)                                      m_spalayer;

      sp(tmx::map)                                    m_ptmxmap;

      bool                                            m_bTmx;


      data(::aura::application * papp);


      virtual void xml_import(::xml::input_tree & xmlif);
      virtual void xml_export(::xml::output_tree & xmlof);


   };


} // namespace veritile






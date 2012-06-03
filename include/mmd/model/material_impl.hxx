
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

//// ctor
inline
Material::Material()
  : toon_(NULL), texture_(NULL), sub_texture_(NULL),
    sub_texture_type_(MAT_SUB_TEX_OFF)
{}

//// vmember: name
inline const std::wstring&
Material::GetName() const {
    return name_;
}

inline void
Material::SetName(const std::wstring &name) {
    name_ = name;
}

//// vmember: name_en
inline const std::wstring&
Material::GetNameEn() const {
    return name_en_;
}

inline void
Material::SetNameEn(const std::wstring &name_en) {
    name_en_ = name_en;
}

//// vmember: diffuse_color
inline const Vector4f&
Material::GetDiffuseColor() const {
    return diffuse_color_;
}

inline void
Material::SetDiffuseColor(const Vector3f &diffuse) {
    diffuse_color_.c = diffuse.c;
}

inline void
Material::SetDiffuseColor(const Vector4f &diffuse) {
    diffuse_color_.c = diffuse.c;
}

//// vmember: specular_color
inline const Vector4f&
Material::GetSpecularColor() const {
    return specular_color_;
}
inline void
Material::SetSpecularColor(const Vector3f &specular) {
    specular_color_.c = specular.c;
}
inline void
Material::SetSpecularColor(const Vector4f &specular) {
    specular_color_.c = specular.c;
}

//// vmember: ambient_color
inline const Vector4f&
Material::GetAmbientColor() const {
    return ambient_color_;
}
inline void
Material::SetAmbientColor(const Vector3f &ambient) {
    ambient_color_.c = ambient.c;
}
inline void
Material::SetAmbientColor(const Vector4f &ambient) {
    ambient_color_.c = ambient.c;
}

//// vmember: shininess
inline float
Material::GetShininess() const {
    return shininess_;
}
inline void
Material::SetShininess(float shininess) {
    shininess_ = shininess;
}

//// vmember: draw_double_base
inline bool
Material::GetDrawDoubleFace() const {
    return draw_double_face_;
}
inline void
Material::SetDrawDoubleFace(bool draw_double_face) {
    draw_double_face_ = draw_double_face;
}

//// vmember: draw_ground_shadow
inline bool
Material::GetDrawGroundShadow() const {
    return draw_ground_shadow_;
}
inline void
Material::SetDrawGroundShadow(bool draw_ground_shadow) {
    draw_ground_shadow_ = draw_ground_shadow;
}

//// vmember: cast_self_shadow
inline bool
Material::GetCastSelfShadow() const {
    return cast_self_shadow_;
}
inline void
Material::SetCastSelfShadow(bool cast_self_shadow) {
    cast_self_shadow_ = cast_self_shadow;
}

//// vmember: draw_self_shadow
inline bool
Material::GetDrawSelfShadow() const {
    return draw_self_shadow_;
}
inline void
Material::SetDrawSelfShadow(bool draw_self_shadow) {
    draw_self_shadow_ = draw_self_shadow;
}

//// vmember: draw_edge
inline bool
Material::GetDrawEdge() const {
    return draw_edge_;
}
inline void
Material::SetDrawEdge(bool draw_edge) {
    draw_edge_ = draw_edge;
}

//// vmember: edge_color
inline const Vector4f&
Material::GetEdgeColor() const {
    return edge_color_;
}
inline void
Material::SetEdgeColor(const Vector3f &edge_color) {
    edge_color_.c = edge_color.c;
}
inline void
Material::SetEdgeColor(const Vector4f &edge_color) {
    edge_color_ = edge_color;
}

//// vmember: edge_size
inline float
Material::GetEdgeSize() const {
    return edge_size_;
}
inline void
Material::SetEdgeSize(float edge_size) {
    edge_size_ = edge_size;
}

//// pmember: toon
inline const Texture*
Material::GetToon() const {
    return toon_;
}
inline void
Material::SetToon(const Texture *toon) {
    toon_ = toon;
}

//// pmember: texture
inline const Texture*
Material::GetTexture() const {
    return texture_;
}
inline void
Material::SetTexture(const Texture *texture) {
    texture_ = texture;
}

//// pmember: sub_texture
inline const Texture*
Material::GetSubTexture() const {
    return sub_texture_;
}
inline void
Material::SetSubTexture(const Texture *sub_texture) {
    sub_texture_ = sub_texture;
}

//// vmember: sub_texture_type
inline Material::SubTextureTypeEnum
Material::GetSubTextureType() const {
    return sub_texture_type_;
}
inline void
Material::SetSubTextureType(Material::SubTextureTypeEnum type) {
    sub_texture_type_ = type;
}

//// vmember: meta_info
inline const std::wstring&
Material::GetMetaInfo() const {
    return meta_info_;
}
inline void
Material::SetMetaInfo(const std::wstring &meta_info) {
    meta_info_ = meta_info;
}

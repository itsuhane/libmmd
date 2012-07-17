
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __MATERIAL_HXX_8729491056BAD47471E94E86D155626F_INCLUDED__
#define __MATERIAL_HXX_8729491056BAD47471E94E86D155626F_INCLUDED__

namespace mmd {

    class Material {
    public:
        enum SubTextureTypeEnum {
            MAT_SUB_TEX_OFF = 0,
            MAT_SUB_TEX_SPH = 1,
            MAT_SUB_TEX_SPA = 2,
            MAT_SUB_TEX_SUB = 3
        };

        Material();

        const std::wstring &GetName() const;
        void SetName(const std::wstring &name);

        const std::wstring &GetNameEn() const;
        void SetNameEn(const std::wstring &name_en);

        const Vector4f &GetDiffuseColor() const;
        void SetDiffuseColor(const Vector3f &diffuse);
        void SetDiffuseColor(const Vector4f &diffuse);

        const Vector4f &GetSpecularColor() const;
        void SetSpecularColor(const Vector3f &specular);
        void SetSpecularColor(const Vector4f &specular);

        const Vector4f &GetAmbientColor() const;
        void SetAmbientColor(const Vector3f &ambient);
        void SetAmbientColor(const Vector4f &ambient);

        float GetShininess() const;
        void SetShininess(float shininess);

        bool GetDrawDoubleFace() const;
        void SetDrawDoubleFace(bool draw_double_face);

        bool GetDrawGroundShadow() const;
        void SetDrawGroundShadow(bool draw_ground_shadow);

        bool GetCastSelfShadow() const;
        void SetCastSelfShadow(bool cast_self_shadow);

        bool GetDrawSelfShadow() const;
        void SetDrawSelfShadow(bool draw_self_shadow);

        bool GetDrawEdge() const;
        void SetDrawEdge(bool draw_edge);

        const Vector4f &GetEdgeColor() const;
        void SetEdgeColor(const Vector3f &edge_color);
        void SetEdgeColor(const Vector4f &edge_color);

        float GetEdgeSize() const;
        void SetEdgeSize(float edge_size);

        const Texture *GetToon() const;
        void SetToon(const Texture *toon);

        const Texture *GetTexture() const;
        void SetTexture(const Texture *texture);

        const Texture *GetSubTexture() const;
        void SetSubTexture(const Texture *sub_texture);

        SubTextureTypeEnum GetSubTextureType() const;
        void SetSubTextureType(SubTextureTypeEnum type);

        const std::wstring &GetMetaInfo() const;
        void SetMetaInfo(const std::wstring &meta_info);

    private:
        std::wstring name_;
        std::wstring name_en_;

        Vector4f diffuse_color_;
        Vector4f specular_color_;
        Vector4f ambient_color_;

        float shininess_;

        bool draw_double_face_;
        bool draw_ground_shadow_;
        bool cast_self_shadow_;
        bool draw_self_shadow_;
        bool draw_edge_;

        Vector4f edge_color_;
        float edge_size_;

        const Texture *toon_;
        const Texture *texture_;
        const Texture *sub_texture_;
        SubTextureTypeEnum sub_texture_type_;

        std::wstring meta_info_;
    };

#include "material_impl.inl"

} /* End of namespace mmd */

#endif /* __MATERIAL_HXX_8729491056BAD47471E94E86D155626F_INCLUDED__ */

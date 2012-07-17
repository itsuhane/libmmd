
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __TEXTURE_HXX_B650DCFF820BBC57391916AB2D2825B2_INCLUDED__
#define __TEXTURE_HXX_B650DCFF820BBC57391916AB2D2825B2_INCLUDED__

namespace mmd {

    class Texture {
    public:
        Texture(const std::wstring &texture_path);
        const std::wstring& GetTexturePath() const;
        bool operator<(const Texture &texture) const;
    private:
        std::wstring texture_path_;
    };

    class TextureRegistry {
    public:
        const Texture& GetTexture(const std::wstring &texture_name, const std::wstring &model_location=L"");
        const Texture& GetGlobalToon(size_t toon_id);
        void SetGlobalToonRootPath(std::wstring root_path);
    private:
        std::set<Texture> registry_;
        std::wstring root_path_;
        const std::wstring CanonicalToonName(size_t id) const {
            const wchar_t *canonical_toon_names[] = {
                L"toon0.bmp",  // 0xFF
                L"toon01.bmp", // 0x00
                L"toon02.bmp", // 0x01
                L"toon03.bmp",
                L"toon04.bmp",
                L"toon05.bmp",
                L"toon06.bmp",
                L"toon07.bmp",
                L"toon08.bmp",
                L"toon09.bmp",
                L"toon10.bmp"  // 0x09
            };
            return canonical_toon_names[id];
        }
    };

#include "texture_impl.inl"

} /* End of namespace mmd */

#endif /* __TEXTURE_HXX_B650DCFF820BBC57391916AB2D2825B2_INCLUDED__ */

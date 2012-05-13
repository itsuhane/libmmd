
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __DWARF_HXX_5E76A470D59B9F42253757ECA0701149_INCLUDED__
#define __DWARF_HXX_5E76A470D59B9F42253757ECA0701149_INCLUDED__

namespace std {
    typedef std::basic_string<wchar_t> wstring;

#ifdef _MSC_VER
#if _MSC_VER<1600
    typedef unsigned __int8 uint8_t;
    typedef unsigned __int16 uint16_t;
    typedef unsigned __int32 uint32_t;
    typedef __int8 int8_t;
    typedef __int16 int16_t;
    typedef __int32 int32_t;
#endif
#endif

} /* End of namespace std */

namespace mmd {

    template<typename T>
    struct ref {
        typedef T& type;
    };

    template<typename T>
    struct val {
        typedef T type;
    };

    class exception : public std::exception
    {
    public:
        exception();
        exception(const std::string& message);
        exception(const std::exception& e);
        exception(const std::string& message, const std::exception& e);

        void PrependMessage(const std::string& message);

        /*virtual*/ const char* what() const;
    private:
        std::string msg_;
    };

    typedef std::vector<std::uint8_t> buffer_type;
#include "pack.hxx"
    template<size_t length>
    struct PACKED mmd_string
    {
        std::uint8_t content_[length];
        operator std::string () const;
    };
#include "unpack.hxx"

    class FileReader
    {
    public:
        FileReader(const std::string &filename);
        template<typename T> T Read();
        size_t ReadIndex(size_t byte_size);
        std::string ReadAnsiString();
        std::wstring ReadString(bool utf8 = false);

        const buffer_type& GetBuffer() const;
        void Reset();

        const std::string& GetPath() const;
        std::string GetFilename() const;
        std::string GetLocation() const;

        size_t GetLength() const;
        size_t GetPosition() const;
        ptrdiff_t GetRemainedLength() const;
    private:
        std::string path_;
        buffer_type buffer_;
        size_t cursor_;
    };

    std::string UTF16ToNativeString(const std::wstring &ws);
    std::wstring NativeToUTF16String(const std::string &s);
    std::wstring UTF8ToUTF16String(const std::string &s);
    std::wstring ShiftJISToUTF16String(const std::string &s);

#include "dwarf_impl.hxx"

} /* End of namespace mmd */

#endif /* __DWARF_HXX_5E76A470D59B9F42253757ECA0701149_INCLUDED__ */

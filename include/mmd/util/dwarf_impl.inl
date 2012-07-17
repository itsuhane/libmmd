
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

template<typename T>
inline T& make_null_ref() { return *reinterpret_cast<T*>(NULL); }

inline exception::exception() {}
inline exception::exception(const std::string& message) : msg_(message) {}
inline exception::exception(const std::exception& e) : msg_(e.what()) {}
inline exception::exception(const std::string& message, const std::exception& e) : msg_(message+'\n'+e.what()) {}

inline void exception::PrependMessage(const std::string& message) {
    msg_ = message+'\n'+msg_;
}
inline const char* exception::what() const throw() { return msg_.c_str(); }

template<size_t length> inline mmd_string<length>::operator std::string () const {
    char buffer[length+1];
    strncpy(buffer, (const char*)content_, length);
    buffer[length] = 0;
    return std::string(buffer);
}

inline void FileReader::Initialize() {
#ifdef MMD_WINDOWS
    FILE *f = _wfopen(path_.c_str(), L"rb");
#else
    FILE *f = fopen(UTF16ToNativeString(path_).c_str(), "rb");
#endif
    if(f==NULL) {
        throw exception(std::string("FileReader: Cannot open file."));
    }
    fseek(f, 0, SEEK_END);
    size_t file_length = (size_t)ftell(f);
    if(file_length==0) {
        fclose(f);
        throw exception(std::string("FileReader: File is empty."));
    }
    fseek(f, 0, SEEK_SET);
    buffer_.assign(file_length, 0);
    fread(&buffer_[0], 1, file_length, f);
    fclose(f);
}

inline FileReader::FileReader() : cursor_(0) {}

inline FileReader::FileReader(const std::string &filename) : path_(NativeToUTF16String(filename)), cursor_(0)
{
    Initialize();
}

inline FileReader::FileReader(const std::wstring &filename) : path_(filename), cursor_(0)
{
    Initialize();
}

inline bool FileReader::FileExists(const std::wstring &filename) {
#ifdef MMD_WINDOWS
    FILE *f = _wfopen(filename.c_str(), L"rb");
#else
    FILE *f = fopen(UTF16ToNativeString(filename).c_str(), "rb");
#endif
    bool result = (f!=NULL);
    if(result) {
        fclose(f);
    }
    return result;
}

template<typename T> inline T FileReader::Read() {
    if(cursor_+sizeof(T)>buffer_.size()) {
        throw exception(std::string("FileReader: Buffer length exceeded"));
    }
    T t = *reinterpret_cast<T*>(&buffer_[cursor_]);
    cursor_ += sizeof(T);
    return t;
}

inline size_t FileReader::ReadIndex(size_t byte_size) {
    if(cursor_+byte_size>buffer_.size()) {
        throw exception(std::string("FileReader: Buffer length exceeded"));
    }
    size_t result;
    switch(byte_size) {
    case 1:
        result = (size_t)(*reinterpret_cast<std::uint8_t*>(&buffer_[cursor_]));
        break;
    case 2:
        result = (size_t)(*reinterpret_cast<std::uint16_t*>(&buffer_[cursor_]));
        break;
    case 4:
        result = (size_t)(*reinterpret_cast<std::int32_t*>(&buffer_[cursor_]));
        break;
    default:
        throw exception(std::string("FileReader: Invalid byte size"));
    }
    cursor_ += byte_size;
    return result;
}

inline std::string FileReader::ReadAnsiString() {
    size_t length = (size_t)Read<std::int32_t>();
    if(cursor_+length>buffer_.size()) {
        throw exception(std::string("FileReader: Buffer length exceeded"));
    }
    cursor_ += length;
    return std::string((char*)&buffer_[cursor_-length], length);
}

inline std::wstring FileReader::ReadString(bool utf8) {
    size_t length = (size_t)Read<std::int32_t>();
    if(cursor_+length>buffer_.size()) {
        throw exception(std::string("FileReader: Buffer length exceeded"));
    }
    cursor_ += length;
    if(!utf8) {
#ifdef MMD_WINDOWS
        return std::wstring((wchar_t*)&buffer_[cursor_-length], length/sizeof(wchar_t));
#else
        return std::wstring((std::uint16_t*)&buffer_[cursor_-length], (std::uint16_t*)&buffer_[cursor_]);
#endif
    } else {
        return UTF8ToUTF16String(std::string((char*)&buffer_[cursor_-length], length));
    }
}

inline buffer_type& FileReader::GetBuffer() { return buffer_; }
inline const buffer_type& FileReader::GetBuffer() const { return buffer_; }
inline void FileReader::Reset() { cursor_ = 0; }

inline const std::wstring& FileReader::GetPath() const {
    return path_;
}
inline std::wstring FileReader::GetFilename() const {
    std::wstring::size_type pos = path_.find_last_of(L"/\\");
    if(pos!=std::wstring::npos) {
        return path_.substr(pos+1);
    } else {
        return path_;
    }
}
inline std::wstring FileReader::GetLocation() const {
    std::wstring::size_type pos = path_.find_last_of(L"/\\");
    if(pos!=std::wstring::npos) {
        return path_.substr(0,pos+1);
    } else {
        return L"";
    }
}

inline void FileReader::Seek(size_t position) {
    if(position<=buffer_.size()) {
        cursor_ = position;
    }
}

inline size_t FileReader::GetLength() const {
    return buffer_.size();
}

inline size_t FileReader::GetPosition() const {
    return cursor_;
}

inline ptrdiff_t FileReader::GetRemainedLength() const {
    return buffer_.size()-cursor_;
}


inline std::wstring s2ws(const std::string &s) {
    size_t wl = s.size()+1;
    std::wstring tws(wl, 0);
    mbstowcs(&tws[0], s.c_str(), wl);
    return std::wstring(tws.c_str());
}

inline std::string ws2s(const std::wstring &ws) {
    size_t l = 4*ws.size()+1;
    std::string ts(l, 0);
    wcstombs(&ts[0], ws.c_str(), l);
    return std::string(ts.c_str());
}

inline std::string UTF16ToNativeString(const std::wstring &ws) {
    std::string c_locale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "");
    std::string s = ws2s(ws);
    setlocale(LC_ALL, c_locale.c_str());
    return s;
}

inline std::wstring NativeToUTF16String(const std::string &s) {
    std::string c_locale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "");
    std::wstring ws = s2ws(s);
    setlocale(LC_ALL, c_locale.c_str());
    return ws;
}

inline std::wstring UTF8ToUTF16String(const std::string &s) {
    std::string c_locale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "C");
    std::wstring ws = s2ws(s);
    setlocale(LC_ALL, c_locale.c_str());
    return ws;
}

inline std::wstring ShiftJISToUTF16String(const std::string &s) {
#ifdef MMD_WINDOWS
    std::string c_locale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "Japanese_Japan.932");
    std::wstring ws = s2ws(s);
    setlocale(LC_ALL, c_locale.c_str());
    return ws;
#else
    iconv_t cd = iconv_open("UTF-16", "SHIFT-JIS");
    std::vector<char> from_buffer(s.begin(), s.end());
    std::vector<char> to_buffer(s.size()*4+1, '\0');
    char* from_ptr = &from_buffer[0];
    char* to_ptr = &to_buffer[0];
    size_t from_length = s.size();
    size_t to_length = s.size()*4+1;
    iconv(cd, &from_ptr, &from_length, &to_ptr, &to_length);
    iconv_close(cd);
    return std::wstring((std::uint16_t*)&to_buffer[0], (std::uint16_t*)&to_buffer[s.size()*4-to_length+1]);
#endif
}

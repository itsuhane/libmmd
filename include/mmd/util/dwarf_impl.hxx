
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

inline exception::exception() {}
inline exception::exception(const std::string& message) : msg_(message) {}
inline exception::exception(const std::exception& e) : msg_(e.what()) {}
inline exception::exception(const std::string& message, const std::exception& e) : msg_(message+'\n'+e.what()) {}

inline void exception::PrependMessage(const std::string& message) {
    msg_ = message+'\n'+msg_;
}
inline const char* exception::what() const { return msg_.c_str(); }

template<size_t length> inline mmd_string<length>::operator std::string () const {
    char buffer[length+1];
    strncpy(buffer, (const char*)content_, length);
    buffer[length] = 0;
    return std::string(buffer);
}

inline FileReader::FileReader(const std::string &filename)
    : cursor_(0), path_(filename)
{
    FILE *f = fopen(filename.c_str(), "rb");
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
        return std::wstring((wchar_t*)&buffer_[cursor_-length], length/sizeof(wchar_t));
    } else {
        return UTF8ToUTF16String(std::string((char*)&buffer_[cursor_-length], length));
    }
}

inline const buffer_type& FileReader::GetBuffer() const { return buffer_; }
inline void FileReader::Reset() { cursor_ = 0; }

inline const std::string& FileReader::GetPath() const {
    return path_;
}
inline std::string FileReader::GetFilename() const {
    std::string::size_type pos = path_.find_last_of("/\\");
    if(pos!=std::string::npos) {
        return path_.substr(pos+1);
    } else {
        return path_;
    }
}
inline std::string FileReader::GetLocation() const {
    std::string::size_type pos = path_.find_last_of("/\\");
    if(pos!=std::string::npos) {
        return path_.substr(0,pos+1);
    } else {
        return "";
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
    size_t l = 2*ws.size()+1;
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
    std::string c_locale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "Japanese_Japan.932");
    std::wstring ws = s2ws(s);
    setlocale(LC_ALL, c_locale.c_str());
    return ws;
}

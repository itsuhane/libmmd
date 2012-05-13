
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

inline MMDNG::MMDNG() {
}

inline MMDNG& MMDNG::GetMMDNG() {
    static MMDNG mmdng;
    return mmdng;
}

inline TextureRegistry& MMDNG::GetTextureRegistry() {
    return texture_registry_;
}

inline NullPhysicsReactor& MMDNG::GetNullReactor() {
    return null_reactor_;
}

inline Model* ReadModel(const std::string &filename) {
    Model *model = NULL;
    try {
        FileReader file(filename);
        exception ex;
        try {
            model = PmdReader().Read(file);
        } catch (std::exception& e) {
            ex.PrependMessage(e.what());
        }

        try {
            model = PmxReader().Read(file);
        } catch (std::exception& e) {
            ex.PrependMessage(e.what());
            throw ex;
        }
    } catch (std::exception& e) {
        throw exception(std::string("ReadModel: Exception caught."), e);
    } catch (...) {
        throw exception(std::string("ReadModel: Non-standard exception caught."));
    }

    return model;
}
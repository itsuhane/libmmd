
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

inline MMD::MMD() {
}

inline MMD &MMD::GetMMD() {
    static MMD mmd;
    return mmd;
}

inline TextureRegistry &MMD::GetTextureRegistry() {
    return texture_registry_;
}

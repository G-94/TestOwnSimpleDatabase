Package: zlib:x64-windows@1.3.1

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.42.34435.0
-    vcpkg-tool version: 2024-09-30-ab8988503c7cffabfd440b243a383c0a352a023d
    vcpkg-readonly: true
    vcpkg-scripts version: 2960d7d80e8d09c84ae8abf15c12196c2ca7d39a

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Using cached madler-zlib-v1.3.1.tar.gz.
-- Cleaning sources at D:/Programming/C++/BoostTest/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean. Use --editable to skip cleaning for the packages you specify.
-- Extracting source C:/Users/PC/AppData/Local/vcpkg/downloads/madler-zlib-v1.3.1.tar.gz
-- Applying patch 0001-Prevent-invalid-inclusions-when-HAVE_-is-set-to-0.patch
-- Applying patch 0002-build-static-or-shared-not-both.patch
-- Applying patch 0003-android-and-mingw-fixes.patch
-- Using source at D:/Programming/C++/BoostTest/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean
CMake Warning (dev) at scripts/cmake/vcpkg_find_acquire_program.cmake:70 (cmake_parse_arguments):
  The INTERPRETER keyword was followed by an empty string or no value at all.
  Policy CMP0174 is not set, so cmake_parse_arguments() will unset the
  arg_INTERPRETER variable rather than setting it to an empty string.
Call Stack (most recent call first):
  scripts/cmake/vcpkg_find_acquire_program.cmake:143 (z_vcpkg_find_acquire_program_find_internal)
  D:/Programming/C++/BoostTest/vcpkg_installed/x64-windows/share/vcpkg-cmake/vcpkg_cmake_configure.cmake:116 (vcpkg_find_acquire_program)
  C:/Users/PC/AppData/Local/vcpkg/registries/git-trees/3f05e04b9aededb96786a911a16193cdb711f0c9/portfile.cmake:17 (vcpkg_cmake_configure)
  scripts/ports.cmake:192 (include)
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) at scripts/cmake/vcpkg_find_acquire_program.cmake:30 (cmake_parse_arguments):
  The INTERPRETER keyword was followed by an empty string or no value at all.
  Policy CMP0174 is not set, so cmake_parse_arguments() will unset the
  arg_INTERPRETER variable rather than setting it to an empty string.
Call Stack (most recent call first):
  scripts/cmake/vcpkg_find_acquire_program.cmake:149 (z_vcpkg_find_acquire_program_find_external)
  D:/Programming/C++/BoostTest/vcpkg_installed/x64-windows/share/vcpkg-cmake/vcpkg_cmake_configure.cmake:116 (vcpkg_find_acquire_program)
  C:/Users/PC/AppData/Local/vcpkg/registries/git-trees/3f05e04b9aededb96786a911a16193cdb711f0c9/portfile.cmake:17 (vcpkg_cmake_configure)
  scripts/ports.cmake:192 (include)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Found external ninja('1.12.1').
-- Configuring x64-windows
-- Building x64-windows-dbg
-- Building x64-windows-rel
-- Installing: D:/Programming/C++/BoostTest/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows/share/zlib/vcpkg-cmake-wrapper.cmake
-- Fixing pkgconfig file: D:/Programming/C++/BoostTest/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows/lib/pkgconfig/zlib.pc
-- Downloading https://mirror.msys2.org/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst;https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst;https://mirror.yandex.ru/mirrors/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst;https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst;https://mirrors.ustc.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst;https://mirror.selfnet.de/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst -> msys2-mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst...
[DEBUG] To include the environment variables in debug output, pass --debug-env
[DEBUG] Trying to load bundleconfig from D:\Files\Visual studio\VC\vcpkg\vcpkg-bundle.json
[DEBUG] Bundle config: readonly=true, usegitregistry=true, embeddedsha=2960d7d80e8d09c84ae8abf15c12196c2ca7d39a, deployment=VisualStudio, vsversion=17.0
[DEBUG] VS telemetry opted in at SOFTWARE\WOW6432Node\Microsoft\VSCommon\17.0\SQM\\OptIn
[DEBUG] Metrics enabled.
[DEBUG] Feature flag 'binarycaching' unset
[DEBUG] Feature flag 'compilertracking' unset
[DEBUG] Feature flag 'registries' unset
[DEBUG] Feature flag 'versions' unset
[DEBUG] Feature flag 'dependencygraph' unset
warning: Download failed -- retrying after 1000ms
warning: Download failed -- retrying after 2000ms
warning: Download failed -- retrying after 4000ms
warning: Download failed -- retrying after 1000ms
warning: Download failed -- retrying after 2000ms
warning: Download failed -- retrying after 4000ms
error: Missing msys2-mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst and downloads are blocked by x-block-origin.
error: https://mirror.msys2.org/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: failed: status code 404
error: https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: failed: status code 404
error: https://mirror.yandex.ru/mirrors/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: failed: status code 404
error: https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: WinHttpSendRequest failed with exit code 12029
error: https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: WinHttpSendRequest failed with exit code 12029
error: https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: WinHttpSendRequest failed with exit code 12029
error: https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: WinHttpSendRequest failed with exit code 12029
error: https://mirrors.ustc.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: WinHttpSendRequest failed with exit code 12029
error: https://mirrors.ustc.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: WinHttpSendRequest failed with exit code 12029
error: https://mirrors.ustc.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: WinHttpSendRequest failed with exit code 12029
error: https://mirrors.ustc.edu.cn/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: WinHttpSendRequest failed with exit code 12029
error: https://mirror.selfnet.de/msys2/mingw/mingw64/mingw-w64-x86_64-pkgconf-1~2.2.0-1-any.pkg.tar.zst: failed: status code 404
[DEBUG] D:\a\_work\1\s\src\vcpkg\base\downloads.cpp(1030): 
[DEBUG] Time in subprocesses: 0us
[DEBUG] Time in parsing JSON: 12us
[DEBUG] Time in JSON reader: 0us
[DEBUG] Time in filesystem: 7080us
[DEBUG] Time in loading ports: 0us
[DEBUG] Exiting after 2.8 min (166444759us)

CMake Error at scripts/cmake/vcpkg_download_distfile.cmake:32 (message):
      
      Failed to download file with error: 1
      If you are using a proxy, please check your proxy setting. Possible causes are:
      
      1. You are actually using an HTTP proxy, but setting HTTPS_PROXY variable
         to `https://address:port`. This is not correct, because `https://` prefix
         claims the proxy is an HTTPS proxy, while your proxy (v2ray, shadowsocksr
         , etc..) is an HTTP proxy. Try setting `http://address:port` to both
         HTTP_PROXY and HTTPS_PROXY instead.
      
      2. If you are using Windows, vcpkg will automatically use your Windows IE Proxy Settings
         set by your proxy software. See https://github.com/microsoft/vcpkg-tool/pull/77
         The value set by your proxy might be wrong, or have same `https://` prefix issue.
      
      3. Your proxy's remote server is out of service.
      
      If you've tried directly download the link, and believe this is not a temporary
      download server failure, please submit an issue at https://github.com/Microsoft/vcpkg/issues
      to report this upstream download server failure.
      

Call Stack (most recent call first):
  scripts/cmake/vcpkg_download_distfile.cmake:270 (z_vcpkg_download_distfile_show_proxy_and_fail)
  scripts/cmake/vcpkg_acquire_msys.cmake:25 (vcpkg_download_distfile)
  scripts/cmake/vcpkg_acquire_msys.cmake:124 (z_vcpkg_acquire_msys_download_package)
  scripts/cmake/vcpkg_acquire_msys.cmake:212 (z_vcpkg_acquire_msys_download_packages)
  scripts/cmake/vcpkg_find_acquire_program(PKGCONFIG).cmake:52 (vcpkg_acquire_msys)
  scripts/cmake/vcpkg_find_acquire_program.cmake:121 (include)
  scripts/cmake/vcpkg_fixup_pkgconfig.cmake:193 (vcpkg_find_acquire_program)
  C:/Users/PC/AppData/Local/vcpkg/registries/git-trees/3f05e04b9aededb96786a911a16193cdb711f0c9/portfile.cmake:43 (vcpkg_fixup_pkgconfig)
  scripts/ports.cmake:192 (include)



```

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
  "name": "my-application",
  "version": "0.15.2",
  "dependencies": [
    "boost"
  ]
}

```
</details>

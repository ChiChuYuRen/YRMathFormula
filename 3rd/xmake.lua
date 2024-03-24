add_rules("mode.debug", "mode.release")

package("ads")
    set_description("Advanced Docking System for Qt")
    set_license("LGPL-2.1")
    set_urls("https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System/archive/refs/tags/$(version).zip")

    add_versions("4.2.1","0deb3a9f8cb5b2d3c9eac53911fcc230da3cc233dee78a524499720d1950fc83")

    add_deps("cmake")
    -- set_sourcedir(path.join(os.scriptdir(), "ads"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {
        "-DADS_VERSION=" .. package:version(),
        "-DBUILD_EXAMPLES=OFF",
        -- "-DBUILD_STATIC=ON",
        "-DCMAKE_PREFIX_PATH=" .. qt.sdkdir}
        if is_plat("windows") then
            table.insert(configs, "-DCMAKE_CXX_FLAGS=\"/MP\"")
        end
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))
        import("package.tools.cmake").install(package, configs)
    end)
    on_load(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local qt_ver = qt.sdkver
        if string.find(qt_ver, "6.",1) then 
        package:add("includedirs", "include/qt6advanceddocking")
        end 
        if string.find(qt_ver, "5.",1) then 
        package:add("includedirs", "include/qt5advanceddocking")
        end 
    end)
    
package_end()

package("MicroTex")
    set_description("A dynamic, cross-platform, and embeddable LaTeX rendering library")
    set_license("MIT")
    set_urls("https://github.com/ChiChuYuRen/MicroTeX.git")
    add_deps("cmake")
    -- set_sourcedir(path.join(os.scriptdir(), "MicroTex"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {"-DHAVE_AUTO_FONT_FIND=ON","-DQT=ON","-DCMAKE_PREFIX_PATH=" .. qt.sdkdir}
        if is_plat("windows") then
            table.insert(configs, "-DCMAKE_CXX_FLAGS=\"/MP\"")
        end
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))
        import("package.tools.cmake").install(package, configs)
    end)
    on_load(function (package)
        package:add("includedirs","include/microtex")
        package:add("includedirs","include/microtex-qt")
    end)
package_end()

package("CTK")
    set_description("A set of common support code for medical imaging, surgical navigation, and related purposes.")
    set_urls("https://github.com/ChiChuYuRen/CTK.git")
    set_license("Apache-2.0")
    add_deps("cmake")
    -- set_sourcedir(path.join(os.scriptdir(), "CTK"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {
            "-DBUILD_TESTING=OFF",
            "-DCTK_ENABLE_PluginFramework=ON",
            "-DCTK_ENABLE_Python_Wrapping=ON",
            "-DCTK_ENABLE_Widgets=ON",
            "-DCTK_LIB_Testing=OFF",
            -- "-DCTK_BUILD_ALL_PLUGINS=ON",
            "-DCMAKE_PREFIX_PATH=" .. qt.sdkdir}
        if is_plat("windows") then
            table.insert(configs, "-DCMAKE_CXX_FLAGS=\"/MP\"")
        end
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))
        import("package.tools.cmake").install(package, configs)
    end)
    on_load(function (package)
        package:add("includedirs","include/ctk-0.1")
        package:add("linkdir","lib/ctk-0.1")
        local lib={"CTKCore","CTKPluginFramework","CTKScriptingPythonCore","CTKWidgets"}
        package:add("links",lib)
    end)

    on_fetch(function (package)
        local result = {}
        result.links = {"CTKCore","CTKPluginFramework","CTKScriptingPythonCore","CTKWidgets"}
        result.linkdirs = package:installdir("lib/ctk-0.1")
        result.includedirs = package:installdir("include/ctk-0.1")
        return result
    end)
package_end()

target("qtadvancedcss")
    add_rules("qt.static")
    add_files("qtadvancedcss/src/QtAdvancedStylesheet.cpp")
    add_files("qtadvancedcss/src/QtAdvancedStylesheet.h","qtadvancedcss/src/acss_globals.h")
    add_includedirs("qtadvancedcss/src")
    add_defines("ACSS_STATIC")
    add_frameworks("QtCore","QtGui","QtWidgets","QtSvg")
target_end()

target("singleapplication")
    add_rules("qt.static")
    add_files("$(projectdir)/3rd/singleapplication/*.cpp")
    add_files("$(projectdir)/3rd/singleapplication/*.h")
    add_includedirs("$(projectdir)/3rd/singleapplication")
    add_defines("QAPPLICATION_CLASS=QApplication")
    add_frameworks("QtCore","QtNetwork","QtGui","QtWidgets")
target_end()

package("ECM")
    set_description("Extra modules and scripts for CMake.")
    set_license("MIT")
    set_urls("https://github.com/KDE/extra-cmake-modules/archive/refs/tags/$(version).zip")

    add_versions("v5.115.0","2866d67b6bd5719a582dc1f1cd55dcc16695bf56610974c82d7310fa2b4146a2")
    add_deps("cmake")
    -- set_sourcedir(path.join(os.scriptdir(), "ECM"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {"-DBUILD_TESTING=OFF","-DCMAKE_PREFIX_PATH=" .. qt.sdkdir}
        if is_plat("windows") then
            table.insert(configs, "-DCMAKE_CXX_FLAGS=\"/MP\"")
        end
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))
        import("package.tools.cmake").install(package, configs)
    end)
package_end()

package("KSyntaxHighlighting")
    set_description("Syntax highlighting Engine for Structured Text and Code.")
    set_urls("https://github.com/KDE/syntax-highlighting/archive/refs/tags/$(version).zip")
    add_versions("v5.115.0","60b9d933282055cf56ca50069c82359ff09e8912fe9eddbb03a6c643ed296626")
    add_deps("cmake","ECM")
    -- set_sourcedir(path.join(os.scriptdir(), "KSyntaxHighlighting"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {"-DBUILD_TESTING=OFF","-DCMAKE_PREFIX_PATH=" .. qt.sdkdir}
        -- local configs={}
        if is_plat("windows") then
            table.insert(configs, "-DCMAKE_CXX_FLAGS=\"/MP\"")
        end
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))
        import("package.tools.cmake").install(package, configs)
    end)
    on_load(function (package)
        package:add("includedirs","include/KF5/KSyntaxHighlighting")
    end)
package_end()

target("QSimpleUpdater")
    add_rules("qt.static")
    add_files("$(projectdir)/3rd/QSimpleUpdater/src/*.cpp")
    add_files("$(projectdir)/3rd/QSimpleUpdater/src/*.h")
    add_files("$(projectdir)/3rd/QSimpleUpdater/src/*.ui")
    add_includedirs("$(projectdir)/3rd/QSimpleUpdater/src")
    add_includedirs("$(projectdir)/3rd/QSimpleUpdater/include")
    add_frameworks("QtGui","QtWidgets","QtCore","QtNetwork")
target_end()




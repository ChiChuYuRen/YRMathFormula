add_rules("mode.debug", "mode.release")

package("ads")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "ads"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {
        "-DBUILD_EXAMPLES=OFF",
        "-DBUILD_STATIC=ON",
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
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "MicroTex"))
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
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "CTK"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {"-DBUILD_TESTING=OFF","-DCTK_ENABLE_PluginFramework=ON","-DCTK_ENABLE_Python_Wrapping=ON","-DCTK_ENABLE_Widgets=ON","-DCTK_LIB_Testing=OFF","-DCMAKE_PREFIX_PATH=" .. qt.sdkdir}
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
    add_files("singleapplication/*.cpp")
    add_files("singleapplication/*.h")
    add_includedirs("singleapplication")
    add_frameworks("QtCore","QtNetwork","QtGui","QtWidgets")
target_end()



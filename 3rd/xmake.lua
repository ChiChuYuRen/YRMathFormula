add_rules("mode.debug", "mode.release")

package("qtadvanceddocking")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "qtadvanceddocking"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {
        "-DADS_VERSION=4.2.1",
        "-DBUILD_EXAMPLES=OFF",
        "-DCMAKE_PREFIX_PATH=" .. qt.sdkdir}
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

package("MircoTex")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "MircoTex"))
    on_install(function (package)
        import("detect.sdks.find_qt")
        local qt = find_qt(nil,{verbose = true})
        local configs = {"-DHAVE_AUTO_FONT_FIND=ON","-DQT=ON","-DCMAKE_PREFIX_PATH=" .. qt.sdkdir}
    table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:is_debug() and "Debug" or "Release"))
        import("package.tools.cmake").install(package, configs)
    end)
    on_load(function (package)
        package:add("includedirs","include/microtex")
        package:add("includedirs","include/microtex-qt")
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




add_rules("mode.debug", "mode.release")

package("ads")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "notepadnext/src/ads"))
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
    add_files("$(projectdir)/3rd/singleapplication/*.cpp")
    add_files("$(projectdir)/3rd/singleapplication/*.h")
    add_includedirs("$(projectdir)/3rd/singleapplication")
    add_defines("QAPPLICATION_CLASS=QApplication")
    add_frameworks("QtCore","QtNetwork","QtGui","QtWidgets")
target_end()

target("scintlla")
    add_rules("qt.static")
    add_files("$(projectdir)/3rd/scintilla/src/*.cxx","$(projectdir)/3rd/scintilla/qt/ScintillaEdit/*.cpp","$(projectdir)/3rd/scintilla/qt/ScintillaEditBase/*.cpp")
    add_files("$(projectdir)/3rd/scintilla/src/*.h","$(projectdir)/3rd/scintilla/qt/ScintillaEdit/*.h","$(projectdir)/3rd/scintilla/qt/ScintillaEditBase/*.h")
    add_includedirs("$(projectdir)/3rd/scintilla/include","$(projectdir)/3rd/scintilla/qt/ScintillaEdit","$(projectdir)/3rd/scintilla/qt/ScintillaEditBase","$(projectdir)/3rd/scintilla/src")
    add_frameworks("QtCore","QtGui","QtWidgets")
    add_defines("SCINTILLA_QT=1 MAKING_LIBRARY=1 SCI_LEXER=1 _CRT_SECURE_NO_DEPRECATE=1")
    if is_mode("release") then 
        add_defines("EXPORT_IMPORT_API=NDEBUG=1")
    end 
target_end()

target("lexilla")
    set_kind("static")
    add_files("$(projectdir)/3rd/lexilla/lexers/LexLaTex.cxx","$(projectdir)/3rd/lexilla/lexers/LexTex.cxx")
    add_files("$(projectdir)/3rd/lexilla/src/*.cxx","$(projectdir)/3rd/lexilla/lexlib/*.cxx","$(projectdir)/3rd/lexilla/access/*.cxx")
    -- add_files("$(projectdir)/lexilla/lexlib/*.h")
    add_includedirs("$(projectdir)/3rd/lexilla/include","$(projectdir)/3rd/scintilla/include","$(projectdir)/3rd/lexilla/lexlib","$(projectdir)/3rd/lexilla/access")
target_end()

-- target("uchardet")
--     set_kind("static")
--     add_files("$(projectdir)/3rd/uchardet/src/*.cpp","$(projectdir)/3rd/uchardet/src/LangModels/*.cpp")
--     add_includedirs("$(projectdir)/3rd/uchardet/src")
-- target_end()

target("lua")
    set_kind("static")
    add_files("$(projectdir)/3rd/lua/src/*.c")
    add_includedirs("$(projectdir)/3rd/lua/src")
target_end()

target("QSimpleUpdater")
    add_rules("qt.static")
    add_files("$(projectdir)/3rd/QSimpleUpdater/src/*.cpp")
    add_files("$(projectdir)/3rd/QSimpleUpdater/src/*.h")
    add_files("$(projectdir)/3rd/QSimpleUpdater/src/*.ui")
    add_includedirs("$(projectdir)/3rd/QSimpleUpdater/src")
    add_includedirs("$(projectdir)/3rd/QSimpleUpdater/include")
    add_frameworks("QtGui","QtWidgets","QtCore","QtNetwork")
target_end()
if is_plat("windows") then
    if is_mode("debug") then
        set_runtimes("MDd")
        add_requires("ads", { debug = is_mode("debug") })
    else
        set_runtimes("MD")        
        add_requires("ads")
    end
else 
    if is_mode("debug") then
        add_requires("ads",{ debug = is_mode("debug") })
    else 
        add_requires("ads")
    end 
end



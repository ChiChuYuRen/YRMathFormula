
target("YRMathFormula")
    add_rules("qt.widgetapp")
    add_files("$(projectdir)/src/*.cpp","$(projectdir)/src/ui/*.cpp","$(projectdir)/src/manager/*.cpp","$(projectdir)/src/utils/*.cpp","$(projectdir)/src/edit/*.cpp")
    add_files("$(projectdir)/src/*.h","$(projectdir)/src/ui/*.h","$(projectdir)/src/manager/*.h","$(projectdir)/src/edit/*.h")
    add_headerfiles("$(projectdir)/src/*.h","$(projectdir)/src/ui/*.h","$(projectdir)/src/manager/*.h","$(projectdir)/src/edit/*.h")
    -- add_files("$(projectdir)/src/*.qrc")
    add_extrafiles("./*.qrc")
    add_includedirs("$(projectdir)/src","$(projectdir)/3rd/qtadvancedcss/src","$(projectdir)/src/utils","$(projectdir)/3rd/singleapplication")
    -- lexilla头文件
    add_includedirs("$(projectdir)/3rd/lexilla/include")
    -- scintilla头文件
    add_includedirs("$(projectdir)/3rd/scintilla/qt/ScintillaEdit","$(projectdir)/3rd/scintilla/qt/ScintillaEditBase","$(projectdir)/3rd/scintilla/include","$(projectdir)/3rd/scintilla/src")
    add_deps("qtadvancedcss","singleapplication","scintilla","lexilla")
    add_packages("ads","MicroTex")
    add_frameworks("QtGui","QtWidgets","QtCore","QtSvg","QtConcurrent")
    

    -- after_build(function (target)
    --     import("core.project.config")
    --     os.cp("$(projectdir)/src/resources/styles/*","$(buildir)/$(os)/$(arch)/$(mode)/resources/styles/",{rootdir = "src/resources/styles"})
    -- end)
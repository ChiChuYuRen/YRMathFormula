
target("YRMathFormula")
    add_rules("qt.widgetapp")
    add_files("$(projectdir)/src/*.cpp","$(projectdir)/src/ui/*.cpp","$(projectdir)/src/manager/*.cpp","$(projectdir)/src/utils/*.cpp","$(projectdir)/src/edit/*.cpp")
    add_files("$(projectdir)/src/*.h","$(projectdir)/src/ui/*.h","$(projectdir)/src/manager/*.h","$(projectdir)/src/edit/*.h")
    add_headerfiles("$(projectdir)/src/*.h","$(projectdir)/src/ui/*.h","$(projectdir)/src/manager/*.h","$(projectdir)/src/edit/*.h")
    -- add_files("$(projectdir)/src/*.qrc")

    --qrc
    --add_files("$(projectdir)/src/style/ads/ads.qrc","$(projectdir)/src/style/dark/darkstyle.qrc","$(projectdir)/src/style/light/lightstyle.qrc")
    add_extrafiles("./*.qrc")
    add_includedirs("$(projectdir)/src","$(projectdir)/3rd/qtadvancedcss/src","$(projectdir)/src/utils","$(projectdir)/3rd/singleapplication")
        add_deps("qtadvancedcss","singleapplication")
    add_packages("ads","MicroTex","KSyntaxHighlighting")
    add_defines("QAPPLICATION_CLASS=QApplication")
    add_frameworks("QtGui","QtWidgets","QtCore","QtSvg","QtConcurrent")
    

    -- after_build(function (target)
    --     import("core.project.config")
    --     os.cp("$(projectdir)/src/resources/styles/*","$(buildir)/$(os)/$(arch)/$(mode)/resources/styles/",{rootdir = "src/resources/styles"})
    -- end)
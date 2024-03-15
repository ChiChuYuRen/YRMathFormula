
target("YRMathFormula")
    add_rules("qt.widgetapp")
    add_files("$(projectdir)/src/*.cpp","$(projectdir)/src/ui/*.cpp","$(projectdir)/src/manager/*.cpp")
    add_files("$(projectdir)/src/*.h","$(projectdir)/src/ui/*.h","$(projectdir)/src/manager/*.h")
    add_headerfiles("$(projectdir)/src/*.h","$(projectdir)/src/ui/*.h","$(projectdir)/src/manager/*.h")
    add_files("$(projectdir)/src/*.qrc")
    add_extrafiles("./*.qrc")
    add_includedirs("$(projectdir)/src","$(projectdir)/3rd/qtadvancedcss/src")
    add_deps("qtadvancedcss")
    add_packages("ads","MicroTex","CTK")
    add_frameworks("QtGui","QtWidgets","QtCore","QtSvg","QtConcurrent")
    

    -- after_build(function (target)
    --     import("core.project.config")
    --     os.cp("$(projectdir)/src/resources/styles/*","$(buildir)/$(os)/$(arch)/$(mode)/resources/styles/",{rootdir = "src/resources/styles"})
    -- end)
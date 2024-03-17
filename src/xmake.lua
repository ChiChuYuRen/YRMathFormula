﻿
target("YRMathFormula")
    add_rules("qt.widgetapp")
    add_files("$(projectdir)/src/*.cpp","$(projectdir)/src/ui/*.cpp","$(projectdir)/src/manager/*.cpp","$(projectdir)/src/utils/*.cpp")
    add_files("$(projectdir)/src/*.h","$(projectdir)/src/ui/*.h","$(projectdir)/src/manager/*.h")
    add_headerfiles("$(projectdir)/src/*.h","$(projectdir)/src/ui/*.h","$(projectdir)/src/manager/*.h")
    -- add_files("$(projectdir)/src/*.qrc")
    add_extrafiles("./*.qrc")
    add_includedirs("$(projectdir)/src","$(projectdir)/3rd/qtadvancedcss/src","$(projectdir)/src/utils","$(projectdir)/3rd/singleapplication")
    add_deps("qtadvancedcss","singleapplication")
    add_packages("ads","MicroTex")
    add_frameworks("QtGui","QtWidgets","QtCore","QtSvg","QtConcurrent")
    

    -- after_build(function (target)
    --     import("core.project.config")
    --     os.cp("$(projectdir)/src/resources/styles/*","$(buildir)/$(os)/$(arch)/$(mode)/resources/styles/",{rootdir = "src/resources/styles"})
    -- end)
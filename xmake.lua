set_project("YRMathFormula")

add_rules("mode.debug", "mode.release")

set_languages("c++20")
if is_plat("windows") then
    if is_mode("debug") then
        set_runtimes("MDd")
        add_requires("ads","MicroTex", "CTK", { debug = is_mode("debug") })
    else
        set_runtimes("MD")        
        add_requires("ads","MicroTex","CTK")
    end
else 
    if is_mode("debug") then
        add_requires("ads","MicroTex","CTK",{ debug = is_mode("debug") })
    else 
        add_requires("ads","MicroTex","CTK")
    end 
end

if is_plat("windows") then
    -- set_optimize("fastest")  -- faster: -O2  fastest: -Ox  none: -O0
    add_cxflags("/EHsc")
    add_ldflags("/SAFESEH:NO")
elseif is_plat("mingw") then
    add_ldflags("-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lwinpthread -Wl,-Bdynamic", {force = true})
    set_optimize("faster")
else
    --set_optimize("none")   -- faster: -O2  fastest: -O3  none: -O0
    set_optimize("faster")   -- faster: -O2  fastest: -O3  none: -O0
    --add_cxflags("-Wno-narrowing", "-Wno-sign-compare", "-Wno-strict-aliasing")
    if is_plat("macosx", "iphoneos") then
        add_cxflags("-fno-pie")
    end
end

includes("3rd","src")


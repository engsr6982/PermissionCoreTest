add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")

add_requires("levilamina 0.10.5")
add_requires("PermissionCore") -- 添加 PermissionCore 包依赖


if not has_config("vs_runtime") then
    set_runtimes("MD")
end


-- 描述 PermissionCore 包
package("PermissionCore")
    set_urls("https://github.com/engsr6982/PermissionCore/releases/download/$(version)/SDK-PermissionCore.zip")
    add_versions("v0.5.0", "ae6a8a8bd173b370db2a77bdbc0a2860105f90e1afcebef3f19f6fcb7006c175")
    add_includedirs("include/")
    on_install(function (package)
        os.cp("*", package:installdir())
    end)


target("PermissionCoreTest")
    add_cxflags("/EHa", "/utf-8")
    add_defines("NOMINMAX", "UNICODE")
    add_files("src/**.cpp")
    add_includedirs("src")
    add_packages(
        "levilamina",
        "PermissionCore" -- 添加 PermissionCore 包
    )
    add_shflags("/DELAYLOAD:bedrock_server.dll")
    set_exceptions("none")
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")

    after_build(function (target)
        local plugin_packer = import("scripts.after_build")

        local plugin_define = {
            pluginName = target:name(),
            pluginFile = path.filename(target:targetfile()),
        }
        
        plugin_packer.pack_plugin(target,plugin_define)
    end)

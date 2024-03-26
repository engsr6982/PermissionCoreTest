add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")

-- add_requires("levilamina x.x.x") for a specific version
add_requires(
    "levilamina 0.9.4",
    "PermissionCore 0.2.0" -- 添加 PermissionCore 包
)

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

-- 描述 PermissionCore 包
package("PermissionCore")
    set_urls("https://github.com/engsr6982/PermissionCore/releases/download/v0.2.0/SDK-PermissionCore.zip")
    add_includedirs("include/")
    add_links("lib/*.lib")
    -- on_load(function (package)
    --     package:add("links", "PermissionCore")
    -- end)
    on_install(function (package)
        os.cp("*", package:installdir())
    end)

target("PermissionCoreTest") -- Change this to your plugin name.
    add_cxflags("/EHa", "/utf-8")
    add_defines("NOMINMAX", "UNICODE")
    add_files("src/**.cpp")
    add_includedirs("src")
    add_packages(
        "levilamina", 
        "PermissionCore" -- 添加 PermissionCore 包
    )
    add_shflags("/DELAYLOAD:bedrock_server.dll") -- To use symbols provided by SymbolProvider.
    set_exceptions("none") -- To avoid conflicts with /EHa.
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

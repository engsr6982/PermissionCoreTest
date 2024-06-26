#include "entry.h"

#include "Test/Global.h"
#include <ll/api/plugin/NativePlugin.h>
#include <memory>


namespace entry {

entry::entry() = default;

entry& entry::getInstance() {
    static entry instance;
    return instance;
}

ll::plugin::NativePlugin& entry::getSelf() const { return *mSelf; }

extern "C" {
_declspec(dllexport) bool ll_plugin_load(ll::plugin::NativePlugin& self) { return entry::getInstance().load(self); }

_declspec(dllexport) bool ll_plugin_enable(ll::plugin::NativePlugin&) { return entry::getInstance().enable(); }

_declspec(dllexport) bool ll_plugin_disable(ll::plugin::NativePlugin&) { return entry::getInstance().disable(); }

/// @warning Unloading the plugin may cause a crash if the plugin has not released all of its
/// resources. If you are unsure, keep this function commented out.
// _declspec(dllexport) bool ll_plugin_unload(ll::plugin::NativePlugin&) { return entry::getInstance().unload(); }
}


bool entry::load(ll::plugin::NativePlugin& self) {
    mSelf = std::addressof(self);
    getSelf().getLogger().info("loading...");

    // Code for loading the plugin goes here.

    return true;
}

bool entry::enable() {
    getSelf().getLogger().info("enabling...");

    // Code for enabling the plugin goes here.
    test::testManager();
    test::testCore();
    test::testRegister();

    return true;
}

bool entry::disable() {
    getSelf().getLogger().info("disabling...");

    // Code for disabling the plugin goes here.

    return false;
}

} // namespace entry

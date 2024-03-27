#include "Global.h"
#include <PermissionCore/Registers.h>
#include <cassert>
#include <entry/Entry.h>

namespace test {

void testRegisterPermission() {

    // registerperm
    {
        bool result1 = perm::registers::registerPermission("plugin1", "permission1", "value1");
        bool result2 = perm::registers::registerPermission("plugin1", "permission2", "value2");
        bool result3 = perm::registers::registerPermission("plugin1", "permission3", "value3");
        assert(result1 == true);
        assert(result2 == true);
        assert(result3 == true);
    }

    // test isReg
    {
        bool result1 = perm::registers::isPermissionRegistration("plugin1", "value1");
        bool result2 = perm::registers::isPermissionRegistration("plugin1", "value2");
        bool result3 = perm::registers::isPermissionRegistration("plugin1", "value3");
        assert(result1 == true);
        assert(result2 == true);
        assert(result3 == true);
    }

    // test getAllPerm
    {
        const std::vector<perm::registers::Authority>& result = perm::registers::getPluginAllPermissions("plugin1");
        assert(result.size() == 3);
    }

    // test getPerm
    {
        const std::optional<perm::registers::Authority>& result1 =
            perm::registers::getPluginPermission("plugin1", "value1");
        assert(result1.has_value());
        entry::entry::getInstance().getSelf().getLogger().info(
            "PermissionName: {}  |  PermissionValue: {}",
            result1->permissionName,
            result1->permissionValue
        );
        assert(result1->permissionName == "permission1");
        assert(result1->permissionValue == "value1");

        const std::optional<perm::registers::Authority>& result2 =
            perm::registers::getPluginPermission("plugin1", "value2");
        assert(result2.has_value());
        assert(result2->permissionName == "permission2");
        assert(result2->permissionValue == "value2");

        const std::optional<perm::registers::Authority>& result3 =
            perm::registers::getPluginPermission("plugin1", "value3");
        assert(result3.has_value());
        assert(result3->permissionName == "permission3");
        assert(result3->permissionValue == "value3");
    }


    // test unregisterPerm
    {
        bool result = perm::registers::unregisterPermission("plugin1", "value1");
        assert(result == true);
        // assert(perm::registers::registerPerm["plugin1"].empty());
    }
}

} // namespace test
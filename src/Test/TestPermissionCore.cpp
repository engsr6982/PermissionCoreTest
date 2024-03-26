#include "Global.h"
#include <PermissionCore/PermissionCore.h>
#include <PermissionCore/PermissionManager.h>
#include <cassert>
#include <iostream>
#include <memory>

void testRegisterPermissionCoreToManager() {
    using namespace perm;

    auto& manager = PermissionManager::getInstance();

    auto permCore = std::make_shared<PermissionCore>("test", true);

    manager.registerPermissionCore("test", permCore);

    std::cout << "PermissionCore registered" << std::endl;
}

void testManagerGetPermissionCore() {
    using namespace perm;

    auto& manager = PermissionManager::getInstance();

    auto permCore = manager.getPermissionCore("test");

    // permCore is nullptr if the permission core is not registered
    std::cout << "getPermissionCore test value: " << (permCore == nullptr) << std::endl;
}

void testPermissionCore() {
    using namespace perm;

    auto& manager = PermissionManager::getInstance();

    auto core = manager.getPermissionCore("test");

    if (core != nullptr) {
        // Test admin functions
        core->addAdmin("admin1");
        core->addAdmin("admin2");
        assert(core->isAdmin("admin1") == true);
        assert(core->isAdmin("admin2") == true);
        assert(core->isAdmin("admin3") == false);
        core->removeAdmin("admin1");
        assert(core->isAdmin("admin1") == false);

        // Test user group functions
        core->createUserGroup("group1");
        assert(core->hasUserGroup("group1") == true);
        assert(core->hasUserGroup("group2") == false);
        core->deleteUserGroup("group1");
        assert(core->hasUserGroup("group1") == false);

        // Test user functions
        core->addUserToUserGroup("group1", "user1");
        core->addUserToUserGroup("group1", "user2");
        assert(core->isUserInUserGroup("group1", "user1") == true);
        assert(core->isUserInUserGroup("group1", "user3") == false);
        core->removeUserToUserGroup("group1", "user1");
        assert(core->isUserInUserGroup("group1", "user1") == false);

        // Test permission functions
        core->addPermissionToUserGroup("group1", "permission1");
        core->addPermissionToUserGroup("group1", "permission2");
        assert(core->hasUserGroupPermission("group1", "permission1") == true);
        assert(core->hasUserGroupPermission("group1", "permission3") == false);
        core->removePermissionToUserGroup("group1", "permission1");
        assert(core->hasUserGroupPermission("group1", "permission1") == false);

        // Test public group functions
        core->addPermissionToPublicGroup("permission1");
        core->addPermissionToPublicGroup("permission2");
        assert(core->hasPublicGroupPermission("permission1") == true);
        assert(core->hasPublicGroupPermission("permission3") == false);
        core->removePermissionToPublicGroup("permission1");
        assert(core->hasPublicGroupPermission("permission1") == false);

        // Test checkUserPermission
        assert(core->checkUserPermission("user1", "permission1", true, false) == true);
        assert(core->checkUserPermission("user1", "permission1", false, false) == false);
        assert(core->checkUserPermission("admin1", "permission1", false, true) == true);
        assert(core->checkUserPermission("admin1", "permission1", true, true) == true);
    }
}
#include "Global.h"
#include <PermissionCore/PermissionCore.h>
#include <PermissionCore/PermissionManager.h>
#include <cassert>
#include <iostream>
#include <memory>

namespace test {

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
    std::cout << "getPermissionCore test value: " << (permCore == nullptr ? "Fail" : "Success") << std::endl;
}

void testPermissionCore() {
    using namespace perm;

    auto& manager = PermissionManager::getInstance();

    auto core = manager.getPermissionCore("test");

    if (core != nullptr) {
        // 测试添加删除管理员
        core->addAdmin("admin1");
        core->addAdmin("admin2");
        assert(core->isAdmin("admin1") == true);
        assert(core->isAdmin("admin2") == true);
        assert(core->isAdmin("admin3") == false);
        core->removeAdmin("admin1");
        core->removeAdmin("admin2");
        assert(core->isAdmin("admin1") == false);
        assert(core->isAdmin("admin2") == false);

        // 测试创建删除组
        core->createUserGroup("group1");
        assert(core->hasUserGroup("group1") == true);
        assert(core->hasUserGroup("group2") == false);
        core->deleteUserGroup("group1");
        assert(core->hasUserGroup("group1") == false);

        // 测试重命名
        core->createUserGroup("group2");
        assert(core->hasUserGroup("group2") == true);
        core->renameUserGroup("group2", "group1");
        assert(core->hasUserGroup("group1") == true);
        assert(core->hasUserGroup("group2") == false);

        // 测试用户添加删除
        core->addUserToUserGroup("group1", "user1");
        core->addUserToUserGroup("group1", "user2");
        assert(core->isUserInUserGroup("group1", "user1") == true);
        assert(core->isUserInUserGroup("group1", "user3") == false);
        core->removeUserToUserGroup("group1", "user1");
        core->removeUserToUserGroup("group1", "user2");
        assert(core->isUserInUserGroup("group1", "user1") == false);
        assert(core->isUserInUserGroup("group1", "user2") == false);

        // 测试权限添加删除
        core->addPermissionToUserGroup("group1", "permission1");
        core->addPermissionToUserGroup("group1", "permission2");
        assert(core->hasUserGroupPermission("group1", "permission1") == true);
        assert(core->hasUserGroupPermission("group1", "permission3") == false);
        core->removePermissionToUserGroup("group1", "permission1");
        core->removePermissionToUserGroup("group1", "permission2");
        assert(core->hasUserGroupPermission("group1", "permission1") == false);
        assert(core->hasUserGroupPermission("group1", "permission2") == false);

        // 测试公共组
        core->addPermissionToPublicGroup("permission1");
        core->addPermissionToPublicGroup("permission2");
        assert(core->hasPublicGroupPermission("permission1") == true);
        assert(core->hasPublicGroupPermission("permission3") == false);
        core->removePermissionToPublicGroup("permission1");
        core->removePermissionToPublicGroup("permission2");
        assert(core->hasPublicGroupPermission("permission1") == false);
        assert(core->hasPublicGroupPermission("permission2") == false);

        // 测试检查权限函数
        assert(core->checkUserPermission("user1", "permission1", false, false) == false);
        core->addPermissionToPublicGroup("permission1");
        assert(core->checkUserPermission("user1", "permission1", true, false) == true);
        core->addAdmin("admin1");
        assert(core->checkUserPermission("admin1", "permission1", false, true) == true);
        assert(core->checkUserPermission("admin1", "permission1", true, true) == true);
    }
}
} // namespace test
#include "Global.h"
#include <PermissionCore/Group.h>
#include <PermissionCore/PermissionCore.h>
#include <PermissionCore/PermissionManager.h>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>


namespace test {

using namespace perm;

#define groupName "TestGroup"

void testCore() {
    std::cout << "PermissionCore Testing..." << std::endl;
    auto& manager = PermissionManager::getInstance();
    auto  core    = manager.getPermissionCore("test");

    falseThrow(core != nullptr);

    falseThrow(core->hasGroup(groupName) == false);
    falseThrow(core->createGroup(groupName) == true);
    falseThrow(core->hasGroup(groupName) == true);

    falseThrow(core->getAllGroups().size() == 1);
    falseThrow(core->getAllGroupWithOpen().size() == 1);
    falseThrow(core->getAllGroupWithDisabled().size() == 0);

    falseThrow(core->deleteGroup(groupName) == true);
    falseThrow(core->hasGroup(groupName) == false);

    core->createGroup("TestGroup2");
    falseThrow(core->hasGroup("TestGroup2") == true);
    falseThrow(core->renameGroup("TestGroup2", groupName));
    falseThrow(core->hasGroup("TestGroup2") == false);
    falseThrow(core->hasGroup(groupName) == true);

    falseThrow(core->hasGroupPermission(groupName, pm::t1) == false);
    falseThrow(core->addPermissionToGroup(groupName, "t1", pm::t1));
    falseThrow(core->hasGroupPermission(groupName, pm::t1) == true);

    falseThrow(core->isUserInGroup(groupName, "aa") == false);
    falseThrow(core->addUserToGroup(groupName, "aa", "bb") == true);
    falseThrow(core->isUserInGroup(groupName, "aa") == true);
    falseThrow(core->isUserInGroup(groupName, "bb") == true);

    auto gr = core->getGroup(groupName);
    falseThrow(gr.has_value() == true);
    auto gp = *gr;
    falseThrow(gp.ignoreListType == perm::group::IgnoreListType::None);
    falseThrow(gp.status == perm::group::GroupStatus::Open);
    falseThrow(gp.findUser("aa")->realName == "aa");
    falseThrow(gp.findUser("bb")->uuid == "bb");
    falseThrow(gp.findUserWithRealName("aa")->realName == "aa");
    falseThrow(gp.findUserWithUuid("bb")->uuid == "bb");
    falseThrow(gp.findPermissionWithValue(pm::t1)->value == pm::t1);
    std::cout << "Test Group API:toString, Value: " << gp.toString(0) << std::endl;

    falseThrow(core->getGroupsOfUser("aa").size() == 1);
    falseThrow(core->getUserPermission("aa")->value.size() == 1);

    falseThrow(core->checkUserPermission("aa", pm::t1) == true);

    falseThrow(core->removeUserToGroup(groupName, "aa") == true);
    falseThrow(core->isUserInGroup(groupName, "aa") == false);
    falseThrow(core->removePermissionToGroup(groupName, pm::t1));
    falseThrow(core->hasGroupPermission(groupName, pm::t1) == false);

    std::cout << "PermissionCore Success" << std::endl;
}

} // namespace test
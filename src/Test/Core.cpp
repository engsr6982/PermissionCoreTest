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

    assert(core != nullptr);

    assert(core->hasGroup(groupName) == false);
    assert(core->createGroup(groupName) == true);
    assert(core->hasGroup(groupName) == true);

    assert(core->getAllGroups().size() == 1);
    assert(core->getAllGroupWithOpen().size() == 1);
    assert(core->getAllGroupWithDisabled().size() == 0);

    assert(core->deleteGroup(groupName) == true);
    assert(core->hasGroup(groupName) == false);

    core->createGroup("TestGroup2");
    assert(core->hasGroup("TestGroup2") == true);
    assert(core->renameGroup("TestGroup2", groupName));
    assert(core->hasGroup("TestGroup2") == false);
    assert(core->hasGroup(groupName) == true);

    assert(core->hasGroupPermission(groupName, pm::t1) == false);
    assert(core->addPermissionToGroup(groupName, "t1", pm::t1));
    assert(core->hasGroupPermission(groupName, pm::t1) == true);

    assert(core->isUserInGroup(groupName, "aa") == false);
    assert(core->addUserToGroup(groupName, "aa", "bb") == true);
    assert(core->isUserInGroup(groupName, "aa") == true);
    assert(core->isUserInGroup(groupName, "bb") == true);

    auto gr = core->getGroup(groupName);
    assert(gr.has_value() == true);
    auto gp = *gr;
    assert(gp.ignoreListType == perm::group::IgnoreListType::None);
    assert(gp.status == perm::group::GroupStatus::Open);
    assert(gp.findUser("aa")->realName == "aa");
    assert(gp.findUser("bb")->uuid == "bb");
    assert(gp.findUserWithRealName("aa")->realName == "aa");
    assert(gp.findUserWithUuid("bb")->uuid == "bb");
    assert(gp.findPermissionWithValue(pm::t1)->value == pm::t1);
    std::cout << "Test Group API:toString, Value: " << gp.toString(0) << std::endl;

    assert(core->getGroupsOfUser("aa").size() == 1);
    assert(core->getUserPermission("aa")->value.size() == 1);

    assert(core->checkUserPermission("aa", pm::t1) == true);

    assert(core->removeUserToGroup(groupName, "aa") == true);
    assert(core->isUserInGroup(groupName, "aa") == false);
    assert(core->removePermissionToGroup(groupName, pm::t1));
    assert(core->hasGroupPermission(groupName, pm::t1) == false);

    std::cout << "PermissionCore Success" << std::endl;
}

} // namespace test
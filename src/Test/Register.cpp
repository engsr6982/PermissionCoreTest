#include "Global.h"
#include <PermissionCore/Group.h>
#include <PermissionCore/PermissionRegister.h>
#include <cassert>
#include <entry/Entry.h>


namespace test {

using namespace perm;

void testRegister() {
    std::cout << "PermissionCore Testing..." << std::endl;

    auto registerInstance = PermissionRegister::getInstance();

    // registerperm
    {
        bool result1 = registerInstance.registerPermission(NAME, pm::t1, "t1");
        bool result2 = registerInstance.registerPermission(NAME, pm::t2, "t2");
        bool result3 = registerInstance.registerPermission(NAME, pm::t3, "t3");
        assert(result1 == true);
        assert(result2 == true);
        assert(result3 == true);
    }

    // test isReg
    {
        bool result1 = registerInstance.hasPermissionRegisted(NAME, pm::t1);
        bool result2 = registerInstance.hasPermissionRegisted(NAME, pm::t2);
        bool result3 = registerInstance.hasPermissionRegisted(NAME, pm::t3);
        assert(result1 == true);
        assert(result2 == true);
        assert(result3 == true);
    }

    // test getAllPerm
    {
        const std::vector<group::Permission>& result = registerInstance.getAllPermission(NAME);
        assert(result.size() == 3);
    }

    // test getPerm
    {
        const std::optional<group::Permission>& result1 = registerInstance.getPermission(NAME, pm::t1);
        assert(result1.has_value() == true);
        entry::entry::getInstance().getSelf().getLogger().info(
            "PermissionName: {}  |  PermissionValue: {}",
            result1->name,
            result1->value
        );
        assert(result1->name == "t1");
        assert(result1->value == pm::t1);

        const std::optional<group::Permission>& result2 = registerInstance.getPermission(NAME, pm::t2);
        assert(result2.has_value() == true);
        assert(result2->name == "t2");
        assert(result2->value == pm::t2);

        const std::optional<group::Permission>& result3 = registerInstance.getPermission(NAME, pm::t3);
        assert(result3.has_value() == true);
        assert(result3->name == "t3");
        assert(result3->value == pm::t3);
    }


    // test unregisterPerm
    {
        bool result = registerInstance.unRegisterPermission(NAME, pm::t1);
        assert(result == true);
        assert(registerInstance.getPermission(NAME, pm::t1).has_value() == false);
    }

    std::cout << "PermissionCore Success" << std::endl;
}

} // namespace test
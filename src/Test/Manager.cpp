#include "Global.h"
#include <PermissionCore/PermissionCore.h>
#include <PermissionCore/PermissionManager.h>
#include <cassert>

namespace test {

using namespace perm;

void testManager() {
    std::cout << "PermissionManager Testing..." << std::endl;

    auto& manager = PermissionManager::getInstance();

    auto permCore = std::make_shared<PermissionCore>(NAME);

    assert(manager.registerPermissionCore(NAME, permCore) == true);

    assert(manager.getPermissionCore(NAME) != nullptr);

    std::cout << "PermissionManager Success" << std::endl;
}

} // namespace test
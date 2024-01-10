#include "Workaround.h"
#include "Java.h"

#include "thread"
#include "chrono"

#include "Windows.h"

//
jclass getMinecraftClass1_8_9() {
    jclass cls = ct.env->FindClass("ave");
    if (cls == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    return cls;
}

jobject getMinecraft1_8_9() {
    jmethodID getMinecraftMethod = ct.env->GetStaticMethodID(getMinecraftClass1_8_9(), "A", "()Lave;");
    if (getMinecraftMethod == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    return ct.env->CallStaticObjectMethod(getMinecraftClass1_8_9(), getMinecraftMethod);
}

jobject getWorld1_8_9() {
    jclass minecraftClass = getMinecraftClass1_8_9();
    if (minecraftClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jfieldID getWorldField = ct.env->GetFieldID(minecraftClass, "f", "Lbdb;");
    if (getWorldField == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject minecraftInstance = getMinecraft1_8_9();
    if (minecraftInstance == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject world = ct.env->GetObjectField(minecraftInstance, getWorldField);
    if (world == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    return world;
}

jobject getPlayer1_8_9() {
    jclass minecraftClass = getMinecraftClass1_8_9();
    if (minecraftClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jfieldID getPlayerField = ct.env->GetFieldID(minecraftClass, "h", "Lbew;");
    if (getPlayerField == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject minecraftInstance = getMinecraft1_8_9();
    if (minecraftInstance == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject player = ct.env->GetObjectField(minecraftInstance, getPlayerField);
    if (player == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    return player;
}

void setPlayerSprint1_8_9() {
    if (!GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState(VK_LCONTROL)) return;

    jobject player = getPlayer1_8_9();
    if (player == nullptr) return;

    jclass playerClass = ct.env->GetObjectClass(player);
    if (playerClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }

    jmethodID setSprintingMethod = ct.env->GetMethodID(playerClass, "d", "(Z)V");
    if (setSprintingMethod == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }

    ct.env->CallBooleanMethod(player, setSprintingMethod, true);
    if (ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
    }
}
//

jobject getMinecraftClientInstance1_20_4() {
    jclass minecraftClientClass = ct.env->FindClass("net/minecraft/class_310");
    if (minecraftClientClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jmethodID getInstanceMethod = ct.env->GetStaticMethodID(minecraftClientClass, "method_1551", "()Lnet/minecraft/class_310;");
    if (getInstanceMethod == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject minecraftClientInstance = ct.env->CallStaticObjectMethod(minecraftClientClass, getInstanceMethod);
    if (minecraftClientInstance == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    return minecraftClientInstance;
}

jobject getPlayer1_20_4() {
    jobject minecraftClientInstance = getMinecraftClientInstance1_20_4();
    if (minecraftClientInstance == nullptr) return nullptr;

    jclass minecraftClientClass = ct.env->GetObjectClass(minecraftClientInstance);
    if (minecraftClientClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jfieldID playerFieldID = ct.env->GetFieldID(minecraftClientClass, "field_1724", "Lnet/minecraft/class_746;");
    if (playerFieldID == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject playerObject = ct.env->GetObjectField(minecraftClientInstance, playerFieldID);
    if (playerObject == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    return playerObject;
}

bool isForwardKeyPressed1_20_4() {
    jobject minecraftClientInstance = getMinecraftClientInstance1_20_4();
    if (minecraftClientInstance == nullptr) return false;

    jclass minecraftClientClass = ct.env->GetObjectClass(minecraftClientInstance);
    if (minecraftClientClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return false;
    }

    jfieldID optionsFieldID = ct.env->GetFieldID(minecraftClientClass, "field_1690", "Lnet/minecraft/class_315;");
    if (optionsFieldID == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return false;
    }

    jobject optionsObject = ct.env->GetObjectField(minecraftClientInstance, optionsFieldID);
    if (optionsObject == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return false;
    }

    jclass optionsClass = ct.env->GetObjectClass(optionsObject);
    jfieldID forwardKeyFieldID = ct.env->GetFieldID(optionsClass, "field_1894", "Lnet/minecraft/class_304;");
    if (forwardKeyFieldID == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return false;
    }

    jobject forwardKeyObject = ct.env->GetObjectField(optionsObject, forwardKeyFieldID);
    if (forwardKeyObject == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return false;
    }

    jclass keyBindingClass = ct.env->GetObjectClass(forwardKeyObject);
    jmethodID isPressedMethod = ct.env->GetMethodID(keyBindingClass, "method_1434", "()Z");
    if (isPressedMethod == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return false;
    }

    jboolean isPressed = ct.env->CallBooleanMethod(forwardKeyObject, isPressedMethod);
    if (ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return false;
    }

    return isPressed;
}

void setPlayerSprint1_20_4() {
    if (!isForwardKeyPressed1_20_4()) return;

    jobject player = getPlayer1_20_4();
    if (player == nullptr) return;

    jclass entityClass = ct.env->FindClass("net/minecraft/class_1297");
    if (entityClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }

    jmethodID setSprintingMethod = ct.env->GetMethodID(entityClass, "method_5728", "(Z)V");
    if (setSprintingMethod == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }

    ct.env->CallBooleanMethod(player, setSprintingMethod, true);
    if (ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
    }
}

void runModules()
{
    while (true) {
        setPlayerSprint1_8_9();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
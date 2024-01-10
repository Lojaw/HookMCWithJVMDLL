#include "Workaround.h"
#include "Java.h"

#include "thread"
#include "chrono"

#include "Windows.h"
#include <fstream>
#include <unordered_set>
#include <mutex>

std::unordered_set<std::string> logCache;
std::mutex logMutex;

void logMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);

    // �berpr�fen, ob die Nachricht bereits geloggt wurde
    if (logCache.find(message) != logCache.end()) {
        return; // Bereits geloggt, nichts zu tun
    }

    // Nachricht in die Datei schreiben
    std::ofstream logFile("C:\\Users\\jpsch\\Desktop\\C++\\HookMCWithJVMDLL\\logging.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }

    // Nachricht zum Cache hinzuf�gen
    logCache.insert(message);
}

void clearLogFile() {
    std::lock_guard<std::mutex> lock(logMutex);
    std::ofstream logFile("C:\\Users\\jpsch\\Desktop\\C++\\HookMCWithJVMDLL\\logging.txt", std::ios::trunc);
    logFile.close();
    logCache.clear();
}

//
jclass getMinecraftClass1_8_9() {
    jclass cls = ct.env->FindClass("ave");
    logMessage(cls != nullptr ? "found getMinecraftClass1_8_9" : "not found getMinecraftClass1_8_9");
    if (cls == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    return cls;
}

jobject getMinecraft1_8_9() {
    jmethodID getMinecraftMethod = ct.env->GetStaticMethodID(getMinecraftClass1_8_9(), "A", "()Lave;");
    logMessage(getMinecraftMethod != nullptr ? "found getMinecraftMethod1_8_9" : "not found getMinecraftMethod1_8_9");
    if (getMinecraftMethod == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    return ct.env->CallStaticObjectMethod(getMinecraftClass1_8_9(), getMinecraftMethod);
}

jobject getWorld1_8_9() {
    jclass minecraftClass = getMinecraftClass1_8_9();
    logMessage(minecraftClass != nullptr ? "found minecraftClass1_8_9" : "not found minecraftClass1_8_9");
    if (minecraftClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jfieldID getWorldField = ct.env->GetFieldID(minecraftClass, "f", "Lbdb;");
    logMessage(getWorldField != nullptr ? "found getWorldField1_8_9" : "not found getWorldField1_8_9");
    if (getWorldField == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject minecraftInstance = getMinecraft1_8_9();
    logMessage(getWorldField != nullptr ? "found minecraftInstance1_8_9" : "not found minecraftInstance1_8_9");
    if (minecraftInstance == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject world = ct.env->GetObjectField(minecraftInstance, getWorldField);
    logMessage(getWorldField != nullptr ? "found world1_8_9" : "not found world1_8_9");
    if (world == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    return world;
}

jobject getPlayer1_8_9() {
    jclass minecraftClass = getMinecraftClass1_8_9();
    logMessage(minecraftClass != nullptr ? "found minecraftClass1_8_9" : "not found minecraftClass1_8_9");
    if (minecraftClass == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jfieldID getPlayerField = ct.env->GetFieldID(minecraftClass, "h", "Lbew;");
    logMessage(getPlayerField != nullptr ? "found getPlayerField1_8_9" : "not found getPlayerField1_8_9");
    if (getPlayerField == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject minecraftInstance = getMinecraft1_8_9();
    logMessage(minecraftInstance != nullptr ? "found minecraftInstance1_8_9" : "not found minecraftInstance1_8_9");
    if (minecraftInstance == nullptr || ct.env->ExceptionCheck()) {
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jobject player = ct.env->GetObjectField(minecraftInstance, getPlayerField);
    logMessage(player != nullptr ? "found player1_8_9" : "not found player1_8_9");
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
    logMessage(setSprintingMethod != nullptr ? "found setSprintingMethod1_8_9" : "not found setSprintingMethod1_8_9");
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

// Function to get Minecraft instance
jobject getMinecraftClientInstance1_20_2() {
    jclass minecraftClientClass = ct.env->FindClass("eqv");
    if (minecraftClientClass == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: MinecraftClientClass1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    logMessage("Found: MinecraftClientClass1_20_2");

    jmethodID getInstanceMethod = ct.env->GetStaticMethodID(minecraftClientClass, "O", "()Leqv;");
    if (getInstanceMethod == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: GetInstanceMethod1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    logMessage("Found: GetInstanceMethod1_20_2");

    jobject minecraftClientInstance = ct.env->CallStaticObjectMethod(minecraftClientClass, getInstanceMethod);
    if (minecraftClientInstance == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: MinecraftClientInstance1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    logMessage("Found: MinecraftClientInstance1_20_2");

    return minecraftClientInstance;
}

// Function to get the player object
jobject getPlayer1_20_2() {
    jobject minecraftClientInstance = getMinecraftClientInstance1_20_2();
    if (minecraftClientInstance == nullptr) {
        logMessage("Error: MinecraftClientInstance1_20_2 is null in getPlayer1_20_2");
        return nullptr;
    }

    jclass minecraftClientClass = ct.env->GetObjectClass(minecraftClientInstance);
    if (minecraftClientClass == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: MinecraftClientClass not found or exception in getPlayer1_20_2");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }

    jfieldID playerFieldID = ct.env->GetFieldID(minecraftClientClass, "s", "Lfng;");
    if (playerFieldID == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: PlayerFieldID1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    logMessage("Found: PlayerFieldID1_20_2");

    jobject playerObject = ct.env->GetObjectField(minecraftClientInstance, playerFieldID);
    if (playerObject == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: PlayerObject1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return nullptr;
    }
    logMessage("Found: PlayerObject1_20_2");

    return playerObject;
}

// Function to set player's sprint status
void setPlayerSprint1_20_2() {
    jobject minecraftClientInstance = getMinecraftClientInstance1_20_2();
    if (minecraftClientInstance == nullptr) {
        logMessage("Error: MinecraftClientInstance1_20_2 is null in setPlayerSprint1_20_2");
        return;
    }

    jclass minecraftClientClass = ct.env->GetObjectClass(minecraftClientInstance);
    if (minecraftClientClass == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: MinecraftClientClass not found or exception in setPlayerSprint1_20_2");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }

    jfieldID optionsFieldID = ct.env->GetFieldID(minecraftClientClass, "m", "Leqz;");
    if (optionsFieldID == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: OptionsFieldID1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }
    logMessage("Found: OptionsFieldID1_20_2");

    jobject optionsObject = ct.env->GetObjectField(minecraftClientInstance, optionsFieldID);
    if (optionsObject == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: OptionsObject1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }
    logMessage("Found: OptionsObject1_20_2");

    jclass optionsClass = ct.env->GetObjectClass(optionsObject);
    if (optionsClass == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: OptionsClass1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }
    logMessage("Found: OptionsClass1_20_2");

    jfieldID keyUpFieldID = ct.env->GetFieldID(optionsClass, "x", "Leqt;");
    if (keyUpFieldID == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: KeyUpFieldID1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }
    logMessage("Found: KeyUpFieldID1_20_2");

    jobject keyUpObject = ct.env->GetObjectField(optionsObject, keyUpFieldID);
    if (keyUpObject == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: KeyUpObject1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }
    logMessage("Found: KeyUpObject1_20_2");

    jclass keyMappingClass = ct.env->GetObjectClass(keyUpObject);
    if (keyMappingClass == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: KeyMappingClass1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }
    logMessage("Found: KeyMappingClass1_20_2");

    jmethodID isDownMethod = ct.env->GetMethodID(keyMappingClass, "e", "()Z");
    if (isDownMethod == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: IsDownMethod1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }
    logMessage("Found: IsDownMethod1_20_2");

    jboolean isDown = ct.env->CallBooleanMethod(keyUpObject, isDownMethod);
    if (isDown) {
        jobject playerObject = getPlayer1_20_2();
        if (playerObject == nullptr) {
            logMessage("Error: PlayerObject is null in setPlayerSprint1_20_2");
            return;
        }

        jclass entityClass = ct.env->FindClass("cbu");
        if (entityClass == nullptr || ct.env->ExceptionCheck()) {
            logMessage("Error: EntityClass1_20_2 not found or exception occurred");
            ct.env->ExceptionDescribe();
            ct.env->ExceptionClear();
            return;
        }
        logMessage("Found: EntityClass1_20_2");

        jmethodID setSprintingMethod = ct.env->GetMethodID(entityClass, "g", "(Z)V");
        if (setSprintingMethod == nullptr || ct.env->ExceptionCheck()) {
            logMessage("Error: SetSprintingMethod1_20_2 not found or exception occurred");
            ct.env->ExceptionDescribe();
            ct.env->ExceptionClear();
            return;
        }
        logMessage("Found: SetSprintingMethod1_20_2");

        ct.env->CallVoidMethod(playerObject, setSprintingMethod, true);
        if (ct.env->ExceptionCheck()) {
            logMessage("Error: Exception occurred during setSprinting call");
            ct.env->ExceptionDescribe();
            ct.env->ExceptionClear();
        }
    }
}

void runModules()
{
    while (true) {
        setPlayerSprint1_8_9();
        setPlayerSprint1_20_2();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
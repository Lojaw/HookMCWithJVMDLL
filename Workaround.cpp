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

    // Überprüfen, ob die Nachricht bereits geloggt wurde
    if (logCache.find(message) != logCache.end()) {
        return; // Bereits geloggt, nichts zu tun
    }

    // Nachricht in die Datei schreiben
    std::ofstream logFile("C:\\Users\\jpsch\\Desktop\\C++\\HookMCWithJVMDLL\\logging.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }

    // Nachricht zum Cache hinzufügen
    logCache.insert(message);
}

void clearLogFile() {
    std::lock_guard<std::mutex> lock(logMutex);
    std::ofstream logFile("C:\\Users\\jpsch\\Desktop\\C++\\HookMCWithJVMDLL\\logging.txt", std::ios::trunc);
    logFile.close();
    logCache.clear();
}



// Funktion, um die Minecraft-Instanz zu erhalten
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

// Funktion, um das Spielerobjekt zu erhalten
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

    jfieldID playerFieldID = ct.env->GetFieldID(minecraftClientClass, "s", "Lfng;"); //@Nullable public LocalPlayer player;
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

// Funktion, um den Sprint-Status des Spielers zu setzen
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

    jfieldID optionsFieldID = ct.env->GetFieldID(minecraftClientClass, "m_90857_", "Lnet/minecraft/class_315;"); // isDown
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

    jmethodID isDownMethod = ct.env->GetMethodID(optionsClass, "m_90857_", "()Z"); // isDown
    if (isDownMethod == nullptr || ct.env->ExceptionCheck()) {
        logMessage("Error: IsDownMethod1_20_2 not found or exception occurred");
        ct.env->ExceptionDescribe();
        ct.env->ExceptionClear();
        return;
    }
    logMessage("Found: IsDownMethod1_20_2");

    jboolean isDown = ct.env->CallBooleanMethod(optionsObject, isDownMethod);
    if (isDown) {
        jobject playerObject = getPlayer1_20_2();
        if (playerObject == nullptr) {
            logMessage("Error: PlayerObject is null in setPlayerSprint1_20_2");
            return;
        }

        jclass entityClass = ct.env->FindClass("cbu"); // Player.java
        if (entityClass == nullptr || ct.env->ExceptionCheck()) {
            logMessage("Error: EntityClass1_20_2 not found or exception occurred");
            ct.env->ExceptionDescribe();
            ct.env->ExceptionClear();
            return;
        }
        logMessage("Found: EntityClass1_20_2");

        jmethodID setSprintingMethod = ct.env->GetMethodID(entityClass, "m_150059_", "(Z)V"); // setSprinting
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
        //setPlayerSprint1_8_9();
        setPlayerSprint1_20_2();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
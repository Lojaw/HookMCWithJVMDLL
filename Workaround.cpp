#include "Workaround.h"
#include "Java.h"

#include "thread"
#include "chrono"

#include "Windows.h"

// Definiert eine Funktion, um die Java-Klasse "ave" zu erhalten. Diese Klasse ist Teil des Minecraft-Codes.
// "ave" scheint eine obfuszierte Klasse von Minecraft zu sein, die in einer spezifischen Version des Spiels verwendet wird.
jclass getMinecraftClass() {
	// Verwendet JNI, um die Klasse "ave" zu finden und gibt einen Verweis darauf zurück.
	// ct.env ist ein Zeiger auf JNIEnv, eine Struktur, die die JNI-Schnittstelle zur JVM bereitstellt.
	return ct.env->FindClass("ave");
}

// Definiert eine Funktion, um ein Objekt der Minecraft-Klasse "ave" zu erhalten.
jobject getMinecraft() {
	// Ermittelt die Methode "A" in der Klasse "ave". Die Methode wird als statisch angenommen.
	// "()Lave;" ist die Signatur der Methode, die besagt, dass sie keine Parameter nimmt ("()")
	// und ein Objekt der Klasse "ave" zurückgibt ("Lave;").
	jmethodID getMinecraftMethod = ct.env->GetStaticMethodID(getMinecraftClass(), "A", "()Lave;");

	// Ruft die statische Methode "A" der Klasse "ave" auf und gibt das resultierende Objekt zurück.
	// Dieses Objekt repräsentiert wahrscheinlich eine Instanz der Haupt-Minecraft-Klasse.
	return ct.env->CallStaticObjectMethod(getMinecraftClass(), getMinecraftMethod);
}

jobject getWorld() {
	jfieldID getWorldField = ct.env->GetFieldID(getMinecraftClass(), "f", "Lbdb;"); //L + bdb.class + ;
	return ct.env->GetObjectField(getMinecraft(), getWorldField);
}

jobject getPlayer() {
	jfieldID getPlayerField = ct.env->GetFieldID(getMinecraftClass(), "h", "Lbew;"); //bew.class
	return ct.env->GetObjectField(getMinecraft(), getPlayerField);
}

void setPlayerSprint() {

	if (!GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState(VK_LCONTROL)) return;

	jmethodID setSprintingMethod = ct.env->GetMethodID(ct.env->GetObjectClass(getPlayer()), "d", "(Z)V");
	ct.env->CallBooleanMethod(getPlayer(), setSprintingMethod, true);
}

void runModules()
{
	while (true) {

		if (!getMinecraft()) continue;
		if (!getWorld()) continue;
		if (!getPlayer()) continue;

		setPlayerSprint();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

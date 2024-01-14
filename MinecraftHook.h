#pragma once

#include "Java.h"

class MinecraftHook {
public:
    static void InitializeHook();
    static void UninitializeHook();

private:
    static void* originalRenderMethod;
    static void HookedRenderMethod(jobject context, float tickDelta);
};
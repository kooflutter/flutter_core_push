#include "include/flutter_core_push/flutter_core_push_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_core_push_plugin.h"

void FlutterCorePushPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_core_push::FlutterCorePushPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}

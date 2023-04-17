#include "include/flutter_core_push/flutter_core_push_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>

#define FLUTTER_CORE_PUSH_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), flutter_core_push_plugin_get_type(), \
                              FlutterCorePushPlugin))

struct _FlutterCorePushPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(FlutterCorePushPlugin, flutter_core_push_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void flutter_core_push_plugin_handle_method_call(
    FlutterCorePushPlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, "getPlatformVersion") == 0) {
    struct utsname uname_data = {};
    uname(&uname_data);
    g_autofree gchar *version = g_strdup_printf("Linux %s", uname_data.version);
    g_autoptr(FlValue) result = fl_value_new_string(version);
    response = FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

static void flutter_core_push_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(flutter_core_push_plugin_parent_class)->dispose(object);
}

static void flutter_core_push_plugin_class_init(FlutterCorePushPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = flutter_core_push_plugin_dispose;
}

static void flutter_core_push_plugin_init(FlutterCorePushPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  FlutterCorePushPlugin* plugin = FLUTTER_CORE_PUSH_PLUGIN(user_data);
  flutter_core_push_plugin_handle_method_call(plugin, method_call);
}

void flutter_core_push_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  FlutterCorePushPlugin* plugin = FLUTTER_CORE_PUSH_PLUGIN(
      g_object_new(flutter_core_push_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "flutter_core_push",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}

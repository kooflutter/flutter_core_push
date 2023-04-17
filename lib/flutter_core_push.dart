
import 'flutter_core_push_platform_interface.dart';

class FlutterCorePush {
  Future<String?> getPlatformVersion() {
    return FlutterCorePushPlatform.instance.getPlatformVersion();
  }
}

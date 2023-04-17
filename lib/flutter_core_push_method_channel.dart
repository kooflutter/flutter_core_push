import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'flutter_core_push_platform_interface.dart';

/// An implementation of [FlutterCorePushPlatform] that uses method channels.
class MethodChannelFlutterCorePush extends FlutterCorePushPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_core_push');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}

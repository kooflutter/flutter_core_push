import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'flutter_core_push_method_channel.dart';

abstract class FlutterCorePushPlatform extends PlatformInterface {
  /// Constructs a FlutterCorePushPlatform.
  FlutterCorePushPlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterCorePushPlatform _instance = MethodChannelFlutterCorePush();

  /// The default instance of [FlutterCorePushPlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterCorePush].
  static FlutterCorePushPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterCorePushPlatform] when
  /// they register themselves.
  static set instance(FlutterCorePushPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}

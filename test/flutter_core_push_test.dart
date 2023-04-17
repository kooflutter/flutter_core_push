import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_core_push/flutter_core_push.dart';
import 'package:flutter_core_push/flutter_core_push_platform_interface.dart';
import 'package:flutter_core_push/flutter_core_push_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockFlutterCorePushPlatform
    with MockPlatformInterfaceMixin
    implements FlutterCorePushPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final FlutterCorePushPlatform initialPlatform = FlutterCorePushPlatform.instance;

  test('$MethodChannelFlutterCorePush is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelFlutterCorePush>());
  });

  test('getPlatformVersion', () async {
    FlutterCorePush flutterCorePushPlugin = FlutterCorePush();
    MockFlutterCorePushPlatform fakePlatform = MockFlutterCorePushPlatform();
    FlutterCorePushPlatform.instance = fakePlatform;

    expect(await flutterCorePushPlugin.getPlatformVersion(), '42');
  });
}

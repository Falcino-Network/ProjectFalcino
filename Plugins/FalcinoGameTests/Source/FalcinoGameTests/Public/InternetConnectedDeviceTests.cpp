#include "Misc/AutomationTest.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Internet/InternetConnectedDevice.h"
#include "Internet/InternetRouter.h"
#include "Internet/InternetServer.h"
#include "Tests/AutomationEditorCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInternetTests, "Project.Functional Tests.FalcinoGameTests.Tests.InternetConnectedDeviceTests.InternetTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FInternetTests::RunTest(const FString& Parameters) {

	// Create a test world
	UWorld* world = FAutomationEditorCommonUtils::CreateNewMap();
	world -> InitWorld();

	TestNotNull("Game world exists", world);

	// Spawn actors
	AActor* deviceActor1 = world -> SpawnActor<AActor>();
	UInternetConnectedDevice* deviceComponent1 = NewObject<UInternetConnectedDevice>(deviceActor1);

	AActor* deviceActor2 = world -> SpawnActor<AActor>();
	UInternetConnectedDevice* deviceComponent2 = NewObject<UInternetConnectedDevice>(deviceActor2);

	AActor* serverActor = world -> SpawnActor<AActor>();
	UInternetServer* serverComponent = NewObject<UInternetServer>(serverActor);

	TestNotNull("Actor exists", deviceActor1);
	TestNotNull("Device exists", deviceComponent1);
	TestNotNull("Actor 2 exists", deviceActor2);
	TestNotNull("Device 2 exists", deviceComponent2);
	TestNotNull("Server exists", serverActor);
	TestNotNull("Server Component Exists", serverComponent);

	// Attach the components to the actor and initialize
	deviceActor1 -> AddInstanceComponent(deviceComponent1);
	deviceComponent1 -> RegisterComponent();
	deviceActor2 -> AddInstanceComponent(deviceComponent2);
	deviceComponent2 -> RegisterComponent();
	serverActor -> AddInstanceComponent(serverComponent);
	serverComponent -> RegisterComponent();

	//Test default values
	TestNotEqual("Device Name Not Blank", deviceComponent1 -> deviceID, FString(""));
	TestFalse("IsConnected False by default", deviceComponent1 -> isConnected);
	TestEqual("ReceivedData empty at start", deviceComponent1 -> receivedData, FString(""));
	TestNull("Connected Router Null at start", deviceComponent1 -> parentRouter);

	TestNotEqual("Device Name Not Blank", deviceComponent2 -> deviceID, FString(""));
	TestFalse("IsConnected False by default", deviceComponent2 -> isConnected);
	TestEqual("ReceivedData empty at start", deviceComponent2 -> receivedData, FString(""));
	TestNull("Connected Router Null at start", deviceComponent2 -> parentRouter);

	TestNotEqual("Device Name Not Blank", serverComponent -> serverID, FString(""));
	TestTrue("Connected Devices empty at start", serverComponent -> connectedRouters.IsEmpty());	
	
	//Spawn an actor with a Router
	AActor* routerActor1 = world -> SpawnActor<AActor>();
	UInternetRouter* routerComponent1 = NewObject<UInternetRouter>();
	AActor* routerActor2 = world -> SpawnActor<AActor>();
	UInternetRouter* routerComponent2 = NewObject<UInternetRouter>();

	TestNotNull("Router Actor1 exists", routerActor1);
	TestNotNull("Router Component1 exists", routerComponent1);
	TestNotNull("Router Actor2 exists", routerActor2);
	TestNotNull("Router Component2 exists", routerComponent2);

	routerActor1 -> AddInstanceComponent(routerComponent1);
	routerComponent1 -> RegisterComponent();
	routerActor2 -> AddInstanceComponent(routerComponent2);
	routerComponent2 -> RegisterComponent();

	//Test default values
	TestNotEqual("Device Name Not Blank", routerComponent1 -> routerID, FString(""));
	TestTrue("Connected Devices empty at start", routerComponent1 -> connectedDevices.IsEmpty());	
	TestNull("Connected Server Null at start", routerComponent1 -> parentServer);
	
	TestNotEqual("Device Name Not Blank", routerComponent2 -> routerID, FString(""));
	TestTrue("Connected Devices empty at start", routerComponent2 -> connectedDevices.IsEmpty());	
	TestNull("Connected Server Null at start", routerComponent2 -> parentServer);
	
	// Register device to the Router
	routerComponent1 -> registerDevice(deviceComponent1);
	routerComponent2 -> registerDevice(deviceComponent2);
	
	// Verify registration
	TestTrue("DeviceComponent1 is connected after registration", deviceComponent1 -> isConnected);
	TestEqual("DeviceComponent1 is linked to the correct router", deviceComponent1 -> parentRouter, routerComponent1);
	TestTrue("DeviceComponent2 is connected after registration", deviceComponent2 -> isConnected);
	TestEqual("DeviceComponent2 is linked to the correct router", deviceComponent2 -> parentRouter, routerComponent2);

	serverComponent  -> registerRouter(routerComponent1);
	serverComponent  -> registerRouter(routerComponent2);

	// Verify registration
	TestEqual("RouterComponent1 is linked to the correct server", routerComponent1 -> parentServer, serverComponent);
	TestEqual("RouterComponen21 is linked to the correct server", routerComponent2 -> parentServer, serverComponent);

	// Simulate sending data
	const FString TestData = "Hello, Device 2!";
	deviceComponent1 -> sendData(deviceComponent2 -> deviceID, TestData);

	// Verify data routing and receipt
	TestEqual("DeviceComponent2 received the correct data", deviceComponent2 -> receivedData, TestData);

	// Unregister Devices
	serverComponent -> unregisterRouter(routerComponent1);
	serverComponent -> unregisterRouter(routerComponent2);
	routerComponent1 -> unRegisterDevice(deviceComponent1);
	routerComponent2 -> unRegisterDevice(deviceComponent2);

	// Verify unregistration
	TestNull("RouterComponent1 no longer has a connected server after unregistration", routerComponent1 -> parentServer);
	TestNull("RouterComponent2 no longer has a connected server after unregistration", routerComponent2 -> parentServer);
	TestFalse("DeviceComponent1 is disconnected after unregistration", deviceComponent1 -> isConnected);
	TestFalse("DeviceComponent2 is disconnected after unregistration", deviceComponent2 -> isConnected);
	TestNull("DeviceComponent1 no longer has a connected router after unregistration", deviceComponent1 -> parentRouter);
	TestNull("DeviceComponent2 no longer has a connected router after unregistration", deviceComponent2 -> parentRouter);
	
	// Cleanup
	deviceActor1 -> Destroy();
	deviceActor2 -> Destroy();
	routerActor1 -> Destroy();
	routerActor2 -> Destroy();
	serverActor -> Destroy();

	if (!HasAnyErrors()) {
		AddInfo("All InternetConnectedDevice Tests Passed");
		return true;
	} else {
		AddInfo("Test Failed");
		return false;
	}
}

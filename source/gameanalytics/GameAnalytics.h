//
// GA-SDK-CPP
// Copyright 2018 GameAnalytics C++ SDK. All rights reserved.
//

#pragma once

#if GA_SHARED_LIB && defined(_WIN32)
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "gdi32.lib")
#endif

#include <string>
#include <vector>
#include <memory>
#if USE_TIZEN || GA_SHARED_LIB
#include "GameAnalyticsExtern.h"
#endif
#if !USE_UWP && !USE_TIZEN
#include <ostream>
#endif

#if USE_LINUX
using GA_STRING = const char*;
using RETURN_GA_STRING = const char*;
#else
using GA_STRING = const std::string&;
using RETURN_GA_STRING = std::string;
#endif

namespace gameanalytics
{

    /*!
     @enum
     @discussion
     This enum is used to specify flow in resource events
     @constant GAResourceFlowTypeSource
     Used when adding to a resource currency
     @constant GAResourceFlowTypeSink
     Used when subtracting from a resource currency
     */
    enum EGAResourceFlowType
    {
        Source = 1,
        Sink = 2
    };

    /*!
     @enum
     @discussion
     his enum is used to specify status for progression event
     @constant GAProgressionStatusStart
     User started progression
     @constant GAProgressionStatusComplete
     User succesfully ended a progression
     @constant GAProgressionStatusFail
     User failed a progression
     */
    enum EGAProgressionStatus
    {
        Start = 1,
        Complete = 2,
        Fail = 3
    };

    /*!
     @enum
     @discussion
     his enum is used to specify severity of an error event
     @constant GAErrorSeverityDebug
     @constant GAErrorSeverityInfo
     @constant GAErrorSeverityWarning
     @constant GAErrorSeverityError
     @constant GAErrorSeverityCritical
     */
    enum EGAErrorSeverity
    {
        Debug = 1,
        Info = 2,
        Warning = 3,
        Error = 4,
        Critical = 5
    };

    enum EGAGender
    {
        Male = 1,
        Female = 2
    };

    class ICommandCenterListener
    {
        public:
            virtual void onCommandCenterUpdated() = 0;
    };

    class GameAnalytics
    {
     public:
        // configure calls should be used before initialize
        static void configureAvailableCustomDimensions01(const std::vector<std::string>& customDimensions);
        static void configureAvailableCustomDimensions01(GA_STRING customDimensions);
        static void configureAvailableCustomDimensions02(const std::vector<std::string>& customDimensions);
        static void configureAvailableCustomDimensions02(GA_STRING customDimensions);
        static void configureAvailableCustomDimensions03(const std::vector<std::string>& customDimensions);
        static void configureAvailableCustomDimensions03(GA_STRING customDimensions);
        static void configureAvailableResourceCurrencies(const std::vector<std::string>& resourceCurrencies);
        static void configureAvailableResourceCurrencies(GA_STRING resourceCurrencies);
        static void configureAvailableResourceItemTypes(const std::vector<std::string>& resourceItemTypes);
        static void configureAvailableResourceItemTypes(GA_STRING resourceCurrencies);
        static void configureBuild(GA_STRING build);
        static void configureWritablePath(GA_STRING writablePath);
        static void configureDeviceModel(GA_STRING deviceModel);
        static void configureDeviceManufacturer(GA_STRING deviceManufacturer);

        // the version of SDK code used in an engine. Used for sdk_version field.
        // !! if set then it will override the SdkWrapperVersion.
        // example "unity 4.6.9"
        static void configureSdkGameEngineVersion(GA_STRING sdkGameEngineVersion);
        // the version of the game engine (if used and version is available)
        static void configureGameEngineVersion(GA_STRING engineVersion);

        static void configureUserId(GA_STRING uId);

        // initialize - starting SDK (need configuration before starting)
        static void initialize(GA_STRING gameKey, GA_STRING gameSecret);

        // add events
        static void addBusinessEvent(GA_STRING currency, int amount, GA_STRING itemType, GA_STRING itemId, GA_STRING cartType);

        static void addResourceEvent(EGAResourceFlowType flowType, GA_STRING currency, float amount, GA_STRING itemType, GA_STRING itemId);

        static void addProgressionEvent(EGAProgressionStatus progressionStatus, GA_STRING progression01, GA_STRING progression02, GA_STRING progression03);

        static void addProgressionEvent(EGAProgressionStatus progressionStatus, GA_STRING progression01, GA_STRING progression02, GA_STRING progression03, int score);

        static void addDesignEvent(GA_STRING eventId);

        static void addDesignEvent(GA_STRING eventId, double value);
        static void addErrorEvent(EGAErrorSeverity severity, GA_STRING message);

        // set calls can be changed at any time (pre- and post-initialize)
        // some calls only work after a configure is called (setCustomDimension)
        static void setEnabledInfoLog(bool flag);
        static void setEnabledVerboseLog(bool flag);
        static void setEnabledManualSessionHandling(bool flag);
        static void setEnabledErrorReporting(bool flag);
        static void setEnabledEventSubmission(bool flag);
        static void setCustomDimension01(GA_STRING dimension01);
        static void setCustomDimension02(GA_STRING dimension02);
        static void setCustomDimension03(GA_STRING dimension03);
        static void setFacebookId(GA_STRING facebookId);
        static void setGender(EGAGender gender);
        static void setBirthYear(int birthYear);

        static void startSession();
        static void endSession();

        static RETURN_GA_STRING getCommandCenterValueAsString(GA_STRING key);
        static RETURN_GA_STRING getCommandCenterValueAsString(GA_STRING key, GA_STRING defaultValue);
        static bool isCommandCenterReady();
        static void addCommandCenterListener(const std::shared_ptr<ICommandCenterListener>& listener);
        static void removeCommandCenterListener(const std::shared_ptr<ICommandCenterListener>& listener);
        static RETURN_GA_STRING getConfigurationsContentAsString();

        // game state changes
        // will affect how session is started / ended
        static void onResume();
        static void onSuspend();
        static void onQuit();

#if !USE_UWP && !USE_TIZEN
        static void addCustomLogStream(std::ostream& os);
#endif

#if USE_UWP
        static void configureAvailableCustomDimensions01(const std::vector<std::wstring>& customDimensions);
        static void configureAvailableCustomDimensions02(const std::vector<std::wstring>& customDimensions);
        static void configureAvailableCustomDimensions03(const std::vector<std::wstring>& customDimensions);
        static void configureAvailableResourceCurrencies(const std::vector<std::wstring>& resourceCurrencies);
        static void configureAvailableResourceItemTypes(const std::vector<std::wstring>& resourceItemTypes);
        static void configureBuild(const std::wstring& build);
        static void configureWritablePath(const std::wstring& writablePath);
        static void configureDeviceModel(const std::wstring& deviceModel);
        static void configureDeviceManufacturer(const std::wstring& deviceManufacturer);
        static void configureSdkGameEngineVersion(const std::wstring& sdkGameEngineVersion);
        static void configureGameEngineVersion(const std::wstring& engineVersion);
        static void configureUserId(const std::wstring& uId);
        static void initialize(const std::wstring& gameKey, const std::wstring& gameSecret);
        static void addBusinessEvent(const std::wstring& currency, int amount, const std::wstring& itemType, const std::wstring& itemId, const std::wstring& cartType);
        static void addResourceEvent(EGAResourceFlowType flowType, const std::wstring& currency, float amount, const std::wstring& itemType, const std::wstring& itemId);
        static void addProgressionEvent(EGAProgressionStatus progressionStatus, const std::wstring& progression01, const std::wstring& progression02, const std::wstring& progression03);
        static void addProgressionEvent(EGAProgressionStatus progressionStatus, const std::wstring& progression01, const std::wstring& progression02, const std::wstring& progression03, int score);
        static void addDesignEvent(const std::wstring& eventId);
        static void addDesignEvent(const std::wstring& eventId, double value);
        static void addErrorEvent(EGAErrorSeverity severity, const std::wstring& message);
        static void setCustomDimension01(const std::wstring& dimension01);
        static void setCustomDimension02(const std::wstring& dimension02);
        static void setCustomDimension03(const std::wstring& dimension03);
        static void setFacebookId(const std::wstring& facebookId);
#endif

     private:
         static bool _endThread;
#if USE_UWP
        static void addBusinessEvent(const std::wstring& currency, int amount, const std::wstring& itemType, const std::wstring& itemId, const std::wstring& cartType, const std::wstring& fields);
        static void addResourceEvent(EGAResourceFlowType flowType, const std::wstring& currency, float amount, const std::wstring& itemType, const std::wstring& itemId, const std::wstring& fields);
        static void addProgressionEvent(EGAProgressionStatus progressionStatus, const std::wstring& progression01, const std::wstring& progression02, const std::wstring& progression03, const std::wstring& fields);
        static void addProgressionEvent(EGAProgressionStatus progressionStatus, const std::wstring& progression01, const std::wstring& progression02, const std::wstring& progression03, int score, const std::wstring& fields);
        static void addDesignEvent(const std::wstring& eventId, const std::wstring& fields);
        static void addDesignEvent(const std::wstring& eventId, double value, const std::wstring& fields);
        static void addErrorEvent(EGAErrorSeverity severity, const std::wstring& message, const std::wstring& fields);
#endif
        static void addBusinessEvent(GA_STRING currency, int amount, GA_STRING itemType, GA_STRING itemId, GA_STRING cartType, GA_STRING fields);
        static void addResourceEvent(EGAResourceFlowType flowType, GA_STRING currency, float amount, GA_STRING itemType, GA_STRING itemId, GA_STRING fields);
        static void addProgressionEvent(EGAProgressionStatus progressionStatus, GA_STRING progression01, GA_STRING progression02, GA_STRING progression03, GA_STRING fields);
        static void addProgressionEvent(EGAProgressionStatus progressionStatus, GA_STRING progression01, GA_STRING progression02, GA_STRING progression03, int score, GA_STRING fields);
        static void addDesignEvent(GA_STRING eventId, GA_STRING fields);
        static void addDesignEvent(GA_STRING eventId, double value, GA_STRING fields);
        static void addErrorEvent(EGAErrorSeverity severity, GA_STRING message, GA_STRING fields);

        static bool isSdkReady(bool needsInitialized);
        static bool isSdkReady(bool needsInitialized, bool warn);
        static bool isSdkReady(bool needsInitialized, bool warn, std::string message);
#if USE_UWP
        static void OnAppSuspending(Platform::Object ^sender, Windows::ApplicationModel::SuspendingEventArgs ^e);
        static void OnAppResuming(Platform::Object ^sender, Platform::Object ^args);
#endif
    };
} // namespace gameanalytics

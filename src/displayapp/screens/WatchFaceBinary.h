#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "displayapp/screens/Screen.h"
#include "components/datetime/DateTimeController.h"
#include "components/ble/BleController.h"
#include "displayapp/widgets/StatusIcons.h"

namespace Pinetime {
  namespace Controllers {
    class Settings;
    class Battery;
    class Ble;
    class NotificationManager;
    class HeartRateController;
    class MotionController;
  }

  namespace Applications {
    namespace Screens {

      class WatchFaceBinary : public Screen {
      public:
        WatchFaceBinary(DisplayApp* app,
                         Controllers::DateTime& dateTimeController,
                         Controllers::Battery& batteryController,
                         Controllers::Ble& bleController,
                         Controllers::NotificationManager& notificatioManager,
                         Controllers::Settings& settingsController,
                         Controllers::HeartRateController& heartRateController,
                         Controllers::MotionController& motionController);
        ~WatchFaceBinary() override;

        void Refresh() override;

      private:
      
        lv_color_t colorOn = lv_color_hex(0xffffff);
        lv_color_t colorOff = lv_color_hex(0x444444);
        lv_color_t background = lv_color_hex(0x000000);
      
        uint8_t displayedHourTens = 0;
        uint8_t displayedHourOnes = 0;
        uint8_t displayedMinuteTens = 0;
        uint8_t displayedMinuteOnes = 0;

        uint16_t currentYear = 1970;
        Controllers::DateTime::Months currentMonth = Pinetime::Controllers::DateTime::Months::Unknown;
        Controllers::DateTime::Days currentDayOfWeek = Pinetime::Controllers::DateTime::Days::Unknown;
        uint8_t currentDay = 0;

        DirtyValue<uint8_t> batteryPercentRemaining {};
        DirtyValue<bool> powerPresent {};
        DirtyValue<bool> bleState {};
        DirtyValue<bool> bleRadioEnabled {};
        DirtyValue<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime {};
        DirtyValue<bool> motionSensorOk {};
        DirtyValue<uint32_t> stepCount {};
        DirtyValue<uint8_t> heartbeat {};
        DirtyValue<bool> heartbeatRunning {};
        DirtyValue<bool> notificationState {};

        lv_obj_t* hourTensOne;
        lv_obj_t* hourTensTwo;
        
        lv_obj_t* hourOnesOne;
        lv_obj_t* hourOnesTwo;
        lv_obj_t* hourOnesFour;
        lv_obj_t* hourOnesEight;
        
        lv_obj_t* minuteTensOne;
        lv_obj_t* minuteTensTwo;
        lv_obj_t* minuteTensFour;
        
        lv_obj_t* minuteOnesOne;
        lv_obj_t* minuteOnesTwo;
        lv_obj_t* minuteOnesFour;
        lv_obj_t* minuteOnesEight;
        
        lv_obj_t* heartbeatIcon;
        lv_obj_t* heartbeatValue;
        lv_obj_t* stepIcon;
        lv_obj_t* stepValue;
        lv_obj_t* notificationIcon;

        Controllers::DateTime& dateTimeController;
        Controllers::NotificationManager& notificatioManager;
        Controllers::Settings& settingsController;
        Controllers::HeartRateController& heartRateController;
        Controllers::MotionController& motionController;

        lv_task_t* taskRefresh;
        Widgets::StatusIcons statusIcons;
      };
    }
  }
}

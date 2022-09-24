#include "displayapp/screens/WatchFaceBinary.h"

#include <date/date.h>
#include <lvgl/lvgl.h>
#include <cstdio>
#include "displayapp/screens/NotificationIcon.h"
#include "displayapp/screens/Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "components/ble/NotificationManager.h"
#include "components/heartrate/HeartRateController.h"
#include "components/motion/MotionController.h"
#include "components/settings/Settings.h"

using namespace Pinetime::Applications::Screens;

WatchFaceBinary::WatchFaceBinary(DisplayApp* app,
                                   Controllers::DateTime& dateTimeController,
                                   Controllers::Battery& batteryController,
                                   Controllers::Ble& bleController,
                                   Controllers::NotificationManager& notificatioManager,
                                   Controllers::Settings& settingsController,
                                   Controllers::HeartRateController& heartRateController,
                                   Controllers::MotionController& motionController)
  : Screen(app),
    currentDateTime {{}},
    dateTimeController {dateTimeController},
    notificatioManager {notificatioManager},
    settingsController {settingsController},
    heartRateController {heartRateController},
    motionController {motionController},
    statusIcons(batteryController, bleController) {

  statusIcons.Create();
  
    notificationIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_color(notificationIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_LIME);
  lv_label_set_text_static(notificationIcon, NotificationIcon::GetIcon(false));
  lv_obj_align(notificationIcon, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);


  // First Column
  hourTensOne = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(hourTensOne, 30, 30);
  lv_obj_set_style_local_bg_color(hourTensOne, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(hourTensOne, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(hourTensOne, 15, 195);
  
  hourTensTwo = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(hourTensTwo, 30, 30);
  lv_obj_set_style_local_bg_color(hourTensTwo, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(hourTensTwo, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(hourTensTwo, 15, 135);
  
  // Second column
  hourOnesOne = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(hourOnesOne, 30, 30);
  lv_obj_set_style_local_bg_color(hourOnesOne, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(hourOnesOne, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(hourOnesOne, 75, 195);
  
  hourOnesTwo = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(hourOnesTwo, 30, 30);
  lv_obj_set_style_local_bg_color(hourOnesTwo, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(hourOnesTwo, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(hourOnesTwo, 75, 135);
  
  hourOnesFour = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(hourOnesFour, 30, 30);
  lv_obj_set_style_local_bg_color(hourOnesFour, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(hourOnesFour, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(hourOnesFour, 75, 75);
  
  hourOnesEight = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(hourOnesEight, 30, 30);
  lv_obj_set_style_local_bg_color(hourOnesEight, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(hourOnesEight, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(hourOnesEight, 75, 15);
  
  //Third column
    // Second column
  minuteTensOne = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(minuteTensOne, 30, 30);
  lv_obj_set_style_local_bg_color(minuteTensOne, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(minuteTensOne, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(minuteTensOne, 135, 195);
  
  minuteTensTwo = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(minuteTensTwo, 30, 30);
  lv_obj_set_style_local_bg_color(minuteTensTwo, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(minuteTensTwo, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(minuteTensTwo, 135, 135);
  
  minuteTensFour = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(minuteTensFour, 30, 30);
  lv_obj_set_style_local_bg_color(minuteTensFour, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(minuteTensFour, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(minuteTensFour, 135, 75);
  
  // Fourth column
  minuteOnesOne = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(minuteOnesOne, 30, 30);
  lv_obj_set_style_local_bg_color(minuteOnesOne, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(minuteOnesOne, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(minuteOnesOne, 195, 195);
  
  minuteOnesTwo = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(minuteOnesTwo, 30, 30);
  lv_obj_set_style_local_bg_color(minuteOnesTwo, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(minuteOnesTwo, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(minuteOnesTwo, 195, 135);
  
  minuteOnesFour = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(minuteOnesFour, 30, 30);
  lv_obj_set_style_local_bg_color(minuteOnesFour, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(minuteOnesFour, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(minuteOnesFour, 195, 75);
  
  minuteOnesEight = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(minuteOnesEight, 30, 30);
  lv_obj_set_style_local_bg_color(minuteOnesEight, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, colorOff);
  lv_obj_set_style_local_bg_color(minuteOnesEight, LV_OBJ_PART_MAIN, LV_STATE_CHECKED, colorOn);
  lv_obj_set_pos(minuteOnesEight, 195, 15);


  heartbeatIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(heartbeatIcon, Symbols::heartBeat);
  lv_obj_set_style_local_text_color(heartbeatIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8FCE00));
  lv_obj_align(heartbeatIcon, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);


  heartbeatValue = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_color(heartbeatValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xCE1B1B));
  lv_label_set_text_static(heartbeatValue, "");
  lv_obj_align(heartbeatValue, heartbeatIcon, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

  stepValue = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_color(stepValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x00FFE7));
  lv_label_set_text_static(stepValue, "0");
  lv_obj_align(stepValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);

  stepIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_color(stepIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x00FFE7));
  lv_label_set_text_static(stepIcon, Symbols::shoe);
  lv_obj_align(stepIcon, stepValue, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  Refresh();
}

WatchFaceBinary::~WatchFaceBinary() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void WatchFaceBinary::Refresh() {
  statusIcons.Update();

  notificationState = notificatioManager.AreNewNotificationsAvailable();
  if (notificationState.IsUpdated()) {
    lv_label_set_text_static(notificationIcon, NotificationIcon::GetIcon(notificationState.Get()));
  }

  currentDateTime = dateTimeController.CurrentDateTime();

  if (currentDateTime.IsUpdated()) {
    auto newDateTime = currentDateTime.Get();

    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime - dp);
    

    uint8_t hour = time.hours().count();
    uint8_t minute = time.minutes().count();
    uint8_t second = time.seconds().count();
    
    uint8_t hourTens = hour / 10;
    uint8_t hourOnes = hour % 10;
    
    uint8_t minuteTens = minute / 10;
    uint8_t minuteOnes = minute % 10;


    if (displayedHourTens != hourTens) {
      switch (hourTens) {
        case 0:
          lv_obj_set_state(hourTensOne, LV_STATE_DEFAULT);
          lv_obj_set_state(hourTensTwo, LV_STATE_DEFAULT);
          break;
        case 1:
          lv_obj_set_state(hourTensOne, LV_STATE_CHECKED);
          lv_obj_set_state(hourTensTwo, LV_STATE_DEFAULT);
          break;
        case 2:
          lv_obj_set_state(hourTensOne, LV_STATE_DEFAULT);
          lv_obj_set_state(hourTensTwo, LV_STATE_CHECKED);
          break;
      }
      displayedHourTens = hourTens;
    }
    
    if (displayedHourOnes != hourOnes) {
      switch (hourOnes) {
        case 0:
          lv_obj_set_state(hourOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesEight, LV_STATE_DEFAULT);
          break;
        case 1:
          lv_obj_set_state(hourOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesEight, LV_STATE_DEFAULT);
          break;
        case 2:
          lv_obj_set_state(hourOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesTwo, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesEight, LV_STATE_DEFAULT);
          break;
        case 3:
          lv_obj_set_state(hourOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesTwo, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesEight, LV_STATE_DEFAULT);
          break;
        case 4:
          lv_obj_set_state(hourOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesFour, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesEight, LV_STATE_DEFAULT);
          break;
        case 5:
          lv_obj_set_state(hourOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesFour, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesEight, LV_STATE_DEFAULT);
          break;
        case 6:
          lv_obj_set_state(hourOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesTwo, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesFour, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesEight, LV_STATE_DEFAULT);
          break;
        case 7:
          lv_obj_set_state(hourOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesTwo, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesFour, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesEight, LV_STATE_DEFAULT);
          break;
        case 8:
          lv_obj_set_state(hourOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesEight, LV_STATE_CHECKED);
          break;
        case 9:
          lv_obj_set_state(hourOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(hourOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(hourOnesEight, LV_STATE_CHECKED);
          break;
      }
      displayedHourOnes = hourOnes;
    }
    
    if (displayedMinuteTens != minuteTens) {
      switch (minuteTens) {
        case 0:
          lv_obj_set_state(minuteTensOne, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteTensTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteTensFour, LV_STATE_DEFAULT);
          break;
        case 1:
          lv_obj_set_state(minuteTensOne, LV_STATE_CHECKED);
          lv_obj_set_state(minuteTensTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteTensFour, LV_STATE_DEFAULT);
          break;
        case 2:
          lv_obj_set_state(minuteTensOne, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteTensTwo, LV_STATE_CHECKED);
          lv_obj_set_state(minuteTensFour, LV_STATE_DEFAULT);
          break;
        case 3:
          lv_obj_set_state(minuteTensOne, LV_STATE_CHECKED);
          lv_obj_set_state(minuteTensTwo, LV_STATE_CHECKED);
          lv_obj_set_state(minuteTensFour, LV_STATE_DEFAULT);
          break;
        case 4:
          lv_obj_set_state(minuteTensOne, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteTensTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteTensFour, LV_STATE_CHECKED);
          break;
        case 5:
          lv_obj_set_state(minuteTensOne, LV_STATE_CHECKED);
          lv_obj_set_state(minuteTensTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteTensFour, LV_STATE_CHECKED);
          break;
      }
      displayedMinuteTens = minuteTens;
    }
    
    if (displayedMinuteOnes != minuteOnes) {
      switch (minuteOnes) {
        case 0:
          lv_obj_set_state(minuteOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesEight, LV_STATE_DEFAULT);
          break;
        case 1:  
          lv_obj_set_state(minuteOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesEight, LV_STATE_DEFAULT);
          break;
        case 2:
          lv_obj_set_state(minuteOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesEight, LV_STATE_DEFAULT);
          break;
        case 3:
          lv_obj_set_state(minuteOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesEight, LV_STATE_DEFAULT);
          break;
        case 4: 
          lv_obj_set_state(minuteOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesFour, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesEight, LV_STATE_DEFAULT);
          break;
        case 5: 
          lv_obj_set_state(minuteOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesFour, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesEight, LV_STATE_DEFAULT);
          break;
        case 6:
          lv_obj_set_state(minuteOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesFour, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesEight, LV_STATE_DEFAULT);
          break;
        case 7:
          lv_obj_set_state(minuteOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesFour, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesEight, LV_STATE_DEFAULT);
          break;
        case 8:
          lv_obj_set_state(minuteOnesOne, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesEight, LV_STATE_CHECKED);
          break;
        case 9:
          lv_obj_set_state(minuteOnesOne, LV_STATE_CHECKED);
          lv_obj_set_state(minuteOnesTwo, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesFour, LV_STATE_DEFAULT);
          lv_obj_set_state(minuteOnesEight, LV_STATE_CHECKED);
          break;
      }
      displayedMinuteOnes = minuteOnes;  
    }
  }

  heartbeat = heartRateController.HeartRate();
  heartbeatRunning = heartRateController.State() != Controllers::HeartRateController::States::Stopped;
  if (heartbeat.IsUpdated() || heartbeatRunning.IsUpdated()) {
    if (heartbeatRunning.Get()) {
      lv_obj_set_style_local_text_color(heartbeatIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8FCE00));
      lv_label_set_text_fmt(heartbeatValue, "%d", heartbeat.Get());
    } else {
      lv_obj_set_style_local_text_color(heartbeatIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x1B1B1B));
      lv_label_set_text_static(heartbeatValue, "");
    }

    lv_obj_realign(heartbeatIcon);
    lv_obj_realign(heartbeatValue);
  }

  stepCount = motionController.NbSteps();
  motionSensorOk = motionController.IsSensorOk();
  if (stepCount.IsUpdated() || motionSensorOk.IsUpdated()) {
    lv_label_set_text_fmt(stepValue, "%lu", stepCount.Get());
    lv_obj_realign(stepValue);
    lv_obj_realign(stepIcon);
  }
}


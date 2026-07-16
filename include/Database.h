#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stdint.h>
#include <Arduino.h>
#include <EEPROM.h>

#define UTILS_DEFAULT_NTP_SERVER "pool.ntp.org"
#define UTILS_CAL_SEC_GMP_OFFSET(H, M) H * 3600 + M * 60
// #define UTILS_DEFAULT_SEC_GMP_OFFSET UTILS_CAL_SEC_GMP_OFFSET(3,30)// 3 hours and 30 minutes

#define DB_DEFAULT_TZ_H                 +3
#define DB_DEFAULT_TZ_M                 +30

#define DB_DEFAULT_STA_SSID             "esp_sta"
#define DB_DEFAULT_STA_PASS             "12345678" 
#define DB_DEFAULT_AP_SSID              "esp"
#define DB_DEFAULT_AP_PASS              "12345678" 

#define DB_FIRST_RUN_KEY                0x01

typedef struct db_time_zone_tag{
  char url[64];
  int8_t hour;
  int8_t min;
}db_time_zone_t;
typedef struct db_sta_wifi_conf_tag{
  char ssid[32];
  char pass[32];
}db_sta_wifi_conf_t;
typedef struct db_ap_wifi_conf_tag{
  char ssid[32];
  char pass[32];
}db_ap_wifi_conf_t;

typedef struct {
  uint8_t FirstRunKey;
  // Device ID
  uint32_t id;
  // configurations
  db_sta_wifi_conf_t sta;
  db_ap_wifi_conf_t ap;
  db_time_zone_t timeZone;
  // user part
}Database_t;


void Database_init(void);

bool Database_isFirstRun(void);

void Database_setId(uint32_t *id);
uint32_t *Database_getId(void);

void Database_set_time_zone(db_time_zone_t *timeZone);
db_time_zone_t *Database_get_time_zone(void);

void Database_set_sta(db_sta_wifi_conf_t *sta);
db_sta_wifi_conf_t *Database_get_sta(void);

void Database_set_ap(db_ap_wifi_conf_t *ap);
db_ap_wifi_conf_t *Database_get_ap(void);

void Database_resetKey(void);

bool Database_needUpdate(void);
void Database_update(void);

#endif /* _DATABASE_H_ */


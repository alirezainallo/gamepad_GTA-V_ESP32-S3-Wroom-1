// #include <vcruntime_string.h>
#include "Database.h"

static bool isFirstRun = false;
static bool needUpdate = false;

uint32_t getUniqueID(void){
  #if defined(ESP32)
    uint64_t mac = ESP.getEfuseMac();
    return (uint32_t)(mac >> 16);
  #elif defined(ESP8266)
    uint32_t chipId = ESP.getChipId();
    return chipId;
  #else
    return 0xFFFFFFFF;
  #endif
}

void Database_init(void) {
    EEPROM.begin(sizeof(Database_t));
    Database_t* db = (Database_t*) EEPROM.getDataPtr();

    if (DB_FIRST_RUN_KEY != db->FirstRunKey) {
        db->FirstRunKey = DB_FIRST_RUN_KEY;
        // -------------- Default Config --------------
        db->id = getUniqueID();// DB_CONF_DEFAULT_ID;
        
        strcpy(db->ap.ssid, DB_DEFAULT_AP_SSID);
        strcpy(db->ap.pass, DB_DEFAULT_AP_PASS);
        
        strcpy(db->sta.ssid, DB_DEFAULT_STA_SSID);
        strcpy(db->sta.pass, DB_DEFAULT_STA_PASS);
        
        strcpy(db->timeZone.url, UTILS_DEFAULT_NTP_SERVER);
        db->timeZone.hour = DB_DEFAULT_TZ_H;
        db->timeZone.min  = DB_DEFAULT_TZ_M;

        
        // user
        
        // --------------------------------------------
        needUpdate = true;
        isFirstRun = true;
        Database_update();
    }
}
bool Database_isFirstRun(void) {
    return isFirstRun;
}

void Database_setId(uint32_t *id){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    db->id = *id;
    needUpdate = true;
}
uint32_t *Database_getId(void){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    return &db->id;
}

void Database_set_time_zone(db_time_zone_t *timeZone){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    db->timeZone = *timeZone;
    needUpdate = true;
}
db_time_zone_t *Database_get_time_zone(void){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    return &db->timeZone;
}

void Database_set_sta(db_sta_wifi_conf_t *sta){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    db->sta = *sta;
    needUpdate = true;
}
db_sta_wifi_conf_t *Database_get_sta(void){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    return &db->sta;
}

void Database_set_ap(db_ap_wifi_conf_t *ap){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    db->ap = *ap;
    needUpdate = true;
}
db_ap_wifi_conf_t *Database_get_ap(void){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    return &db->ap;
}

void Database_resetKey(void){
    Database_t *db = (Database_t*)EEPROM.getDataPtr();
    db->FirstRunKey = 0;
    needUpdate = true;
}
bool Database_needUpdate(void) {
    return needUpdate;
}
void Database_update(void) {
    if(needUpdate){
        EEPROM.commit();
        needUpdate = false;
    }
}

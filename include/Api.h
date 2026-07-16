#pragma once

#include <Arduino.h>

#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

class Api
{
public:

    /*
    ============================================================
        GET /api/keys

        Description:
            دریافت لیست تمام Macro Key ها

        Request:
            No Body

            Example:
                GET http://192.168.4.1/api/keys


        Response:
            HTTP 200

            JSON Array:

            [
                {
                    "id": 1,
                    "name": "Spawn Car",
                    "command": "comet",
                    "tabBefore": false,
                    "enterAfter": true
                },
                {
                    "id": 2,
                    "name": "Weapon",
                    "command": "toolup",
                    "tabBefore": true,
                    "enterAfter": true
                }
            ]

    ============================================================
    */
    static void getKeys(AsyncWebServerRequest *request);



    /*
    ============================================================
        POST /api/key

        Description:
            اجرای یک Macro با ID مشخص


        Request Body:

        JSON:

        {
            "id": 1
        }


        Example:

        POST /api/key

        {
            "id":5
        }


        Response Success:

        HTTP 200

        {
            "success": true
        }


        Response Error:

        HTTP 404

        {
            "success": false,
            "message": "Key not found"
        }


    ============================================================
    */
    static void executeKey(
        AsyncWebServerRequest *request,
        JsonVariant &json);




    /*
    ============================================================
        POST /api/key/add


        Description:
            ساخت یک Macro Key جدید


        Request Body:


        {
            "id": 10,

            "name": "Fast Run",

            "command": "jrtalent",

            "tabBefore": false,

            "enterAfter": true
        }



        Field Description:


        id:
            uint16_t
            Unique ID


        name:
            String
            Name shown in UI


        command:
            String
            Text sent through HID keyboard


        tabBefore:
            bool
            Send TAB before command


        enterAfter:
            bool
            Press ENTER after command



        Response Success:

        {
            "success": true
        }



        Response Error:

        {
            "success": false,
            "message": "Cannot add key"
        }


    ============================================================
    */
    static void addKey(
        AsyncWebServerRequest *request,
        JsonVariant &json);





    /*
    ============================================================
        PUT /api/key/edit


        Description:
            تغییر اطلاعات یک Macro Key


        Request Body:


        {
            "id": 10,

            "name": "Super Jump",

            "command": "hoptoit",

            "tabBefore": true,

            "enterAfter": false
        }



        Important:

            id فقط برای پیدا کردن کلید استفاده می‌شود.
            id تغییر داده نمی‌شود.



        Response Success:


        {
            "success": true
        }



        Response Error:


        {
            "success": false,

            "message": "Cannot update key"
        }



    ============================================================
    */
    static void editKey(
        AsyncWebServerRequest *request,
        JsonVariant &json);





    /*
    ============================================================
        DELETE /api/key/delete


        Description:
            حذف یک Macro Key



        Request Body:


        {
            "id":10
        }



        Response Success:


        {
            "success":true
        }



        Response Error:


        {
            "success":false,

            "message":"Key not found"
        }


    ============================================================
    */
    static void deleteKey(
        AsyncWebServerRequest *request,
        JsonVariant &json);



private:


    /*
        Internal response helper

        Output:

        {
            "success":true
        }

    */
    static void sendSuccess(
        AsyncWebServerRequest *request);



    /*
        Internal error helper


        Output:


        {
            "success":false,

            "message":"error text"
        }

    */
    static void sendError(
        AsyncWebServerRequest *request,
        const char *message,
        uint16_t code = 400);
};

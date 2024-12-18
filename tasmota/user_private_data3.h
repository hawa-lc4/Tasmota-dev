// hawa-lc4

#ifndef _USER_PRIVATE_DATA3_H_
#define _USER_PRIVATE_DATA3_H_

#ifdef STA_SSID1
#undef STA_SSID1
#endif
#define STA_SSID1              ""

#ifdef STA_PASS1
#undef STA_PASS1
#endif
#define STA_PASS1              ""

#ifdef STA_SSID2
#undef STA_SSID2
#endif
#define STA_SSID2              ""

#ifdef STA_PASS2
#undef STA_PASS2
#endif
#define STA_PASS2              ""

#ifdef WIFI_AP_PASSPHRASE
#undef WIFI_AP_PASSPHRASE
#endif
#define WIFI_AP_PASSPHRASE     "SML!reader"                // AccessPoint passphrase. For WPA2 min 8 char, for open use "" (max 63 char).

#ifdef WEB_USERNAME
#undef WEB_USERNAME
#endif
#define WEB_USERNAME            "admin"

#ifdef WEB_PASSWORD
#undef WEB_PASSWORD
#endif
#define WEB_PASSWORD            "admyn"

#endif  // _USER_PRIVATE_DATA3_H_

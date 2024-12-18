// hawa-lc4

#ifndef _USER_PRIVATE_DATA2_H_
#define _USER_PRIVATE_DATA2_H_

#ifdef WIFI_AP_PASSPHRASE
#undef WIFI_AP_PASSPHRASE
#endif
#define WIFI_AP_PASSPHRASE     "BMX!light"                // AccessPoint passphrase. For WPA2 min 8 char, for open use "" (max 63 char).

#ifdef WEB_USERNAME
#undef WEB_USERNAME
#endif
#define WEB_USERNAME            "admin"

#ifdef WEB_PASSWORD
#undef WEB_PASSWORD
#endif
#define WEB_PASSWORD            "admyn"

#endif  // _USER_PRIVATE_DATA2_H_

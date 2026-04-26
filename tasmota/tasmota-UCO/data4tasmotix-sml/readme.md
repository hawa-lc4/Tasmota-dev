Die Dateien "script.txt" und "README_FW.txt" sind für das FlashFS Dateisystem bestimmt. 
Die anderen Dateien gehören auf eine SD-Karte.
In der Datei "smlog.csv" stehen dann die Protokolleinträge.
Die neueren Versionen des SML loggers können neben den Zählerwerten
auch die Werte einer OpenDTU protokollieren.

Auf der SD-Karte dann eine der folgenden Dateien umkopieren in script.txt:
(URL:  https://tasmota.github.io/docs/Smart-Meter-Interface/)
Dateiname:                FriendlyName gesetzt auf:                 Datei gültig für Zähler:
 script.dd3	              FriendlyName1 eBz_DD3_OBIS-ASCII          eBZ DD3 mit OBIS ASCII Ausgabe
 script.ed300l	          FriendlyName1 EMH_ED300L_SML              EMH ED300L mit SML AUsgabe
 script.dtz541            FriendlyName1 Holley_DTZ541_SML           Holley DTZ541  mit SML Ausgabe
 script.LK13BE6067x9      FriendlyName1 Logarex_LK13BE_SML          Logarex LK13BE6067x9 mit SML Ausgabe
 script.Shelly-Emulator   !!! under construction / Baustelle !!!
 
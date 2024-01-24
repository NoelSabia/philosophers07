To do:
monitoring() thread erstellt -> wie viel gegessen werden soll in ein array 
reingeschrieben und jetzt muss man noch folgendes aendern:
-> monitoring bis anzahl von philos laufen lassen und wenn ALLE <= 0 sind dann abbrechen

Mutex:
Def: Mechanismus um Resourcen zeitlich gesehen nacheinander zu teilen.

Initialisierung: pthred_mutex_init(was gemutexed werden soll, NULL);
Locken(fuer eigenen Gebrauch): pthread_mutex_lock(was[welchepos], NULL);
Unlocken(damit es andere nutzen koennen): pthread_mutex_unlock(was[welchepos], NULL);
Zerstoeren: pthred_mutex_destroy(was zerstoert werden soll, NULL);


Ablauf:
- Errorchecking
- Daten richtig einlesen und vorbereiten (mutex init/ in structs)
- Philo_schleife (threads unterschiedlich starten)
- Monitoring_schleife
- Bereinigen (Mutex destroyen)

Argumente:
1. Anzahl der Philosophen
2. Zeit bis sie verhungern
3. Zeit die gebraucht wird um zu essen
4. Zeit die gebraucht wird um zu schlafen
5. (Optional) Wie oft gegessen werden soll
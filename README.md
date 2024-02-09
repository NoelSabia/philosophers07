To do:
-die zeit zwischen dem essen ist noch nicht richtig!

Mutex:
Def: Mechanismus um Resourcen zeitlich gesehen nacheinander zu teilen.

Initialisierung: pthred_mutex_init(was gemutexed werden soll, NULL);
Locken(fuer eigenen Gebrauch): pthread_mutex_lock(was[welchepos], NULL);
Unlocken(damit es andere nutzen koennen): pthread_mutex_unlock(was[welchepos], NULL);
Zerstoeren: pthred_mutex_destroy(was zerstoert werden soll, NULL);

Argumente:
1. Anzahl der Philosophen
2. Zeit bis sie verhungern
3. Zeit die gebraucht wird um zu essen
4. Zeit die gebraucht wird um zu schlafen
5. (Optional) Wie oft gegessen werden soll


timer beginnt beim beginn vom essen nicht wenn sie fertig sind!

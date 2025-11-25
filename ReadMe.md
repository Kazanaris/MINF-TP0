![mesure temps LED allumée](C:\microchip\harmony\v2_06\apps\MINF\TP\Tp0_LedAd\mesure temps LED allumée.PNG).
Sur cette image nous pouvons voir que la LED est allumée pendant 200ms.
Nous pouvons voir cela car elle est à l'état bas pendant 200ms.

![Mesure periode LED](C:\microchip\harmony\v2_06\apps\MINF\TP\Tp0_LedAd\Mesure periode LED.PNG).
Sur cette image, nous pouvons voir que la durée de la période est de 1,6s.
nous avons vu que les LEDs restent allumées pendant 200ms et nous avons 8 LEDs.
200ms * 8 = 1,6s => Le chenillard boucle comme il se doit sans latence.

![mesure 3s avant appel d'APP_TASK](C:\microchip\harmony\v2_06\apps\MINF\TP\Tp0_LedAd\mesure 3s avant appel d'APP_TASK.PNG).
Sur cette image, nous pouvons voir que le temps avant d'entrer pour la première fois dans l'état APP_TASK est de 3,06s.
Cela répond à la demande du CdC.
La raison pour laquelle CH1 met 200ms de plus a avoir un temps haut vient du fait que la LED D6 (sur laquelle la mesure est faite) 
est la première LED du chenillard a s'allumer.

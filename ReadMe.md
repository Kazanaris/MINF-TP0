![mesure temps LED allumée](https://github.com/Kazanaris/MINF-TP0/blob/main/mesure%20temps%20LED%20allum%C3%A9e.png).



Sur cette image nous pouvons voir que la LED est allumée pendant 200ms.
Nous pouvons voir cela car elle est à l'état bas pendant 200ms.




![Mesure periode LED](https://github.com/Kazanaris/MINF-TP0/blob/main/Mesure%20periode%20LED.png).



Sur cette image, nous pouvons voir que la durée de la période est de 1,6s.
nous avons vu que les LEDs restent allumées pendant 200ms et nous avons 8 LEDs.
200ms * 8 = 1,6s => Le chenillard boucle comme il se doit sans latence.




![mesure 3s avant appel d'APP_TASK](https://github.com/Kazanaris/MINF-TP0/blob/main/mesure%203s%20avant%20appel%20d'APP_TASK.png).



Sur cette image, nous pouvons voir que le temps avant d'entrer pour la première fois dans l'état APP_TASK est de 3,06s.
Cela répond à la demande du CdC.
La raison pour laquelle CH1 met 200ms de plus a avoir un temps haut vient du fait que la LED D6 (sur laquelle la mesure est faite) 
est la première LED du chenillard a s'allumer.


Pour le timer je l'ai configuréen suivant la configuration du CdC et j'ai réglé le prescaler sur 256 et pour le "compteur" du timer j'ai déterminé sa valeur avec le calcul suivant :
((temps voulu * fréquence)/prescaler) - 1 = ((100ms * 80kHz)/256) - 1 = 31249


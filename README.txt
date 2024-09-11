
<Considercaiones tecnicas y Feedback (Grupo 3, lab 01)> 



** CONSIDERACIONES TECNICAS **

    ->   "sort -n &"   (Funciona bien nada más que se pierde la referencia de la terminal cuando lo ejecutas, sin embargo cuando le das un comando nuevo sigue ejecutando)

	->	 "wc > /dev/mem"  (No dice permiso denegado y se bugea la terminal cuando lo ejecutas)
		
    ->	 "wc < /dev/mem"  (En cambio aca no se bugea al ejecutar dado que dice que es un descriptor de archivo erroneo)
				
	-> 	 "ls >"  (Aca salta por el assert dado que no existe archivo en el que incrustar la información) y luego se sale del mybash y da este mensaje zsh: IOT instruction (core dumped)  ./mybash
	
En estos 3 comandos encontramos funciones no deseadas de nuestro bash, pero con un poco mas de tiempo hubiesemos podido pulir el codigo y corregir estos problemas.


** FEEDBACKS **

  "Nehuen Emanuel Guevara":  

Mi experiencia durante el laboratorio 1 fue muy enriquecedora, dado que aprendí muchisimo en el uso de git, en temas claves del laboratorio, y sobre todo la experiencia de un trabajo grupal. Fue muy rica la colaboración en presentar codigo, e ir mejorandonos y trayendo a discusión las ideas de lo que cada uno trae. Creo que el laboratorio para mí fue verdaderamente complejo cuando me propuse en hacer un modelo funcional del execute, el cual obviamente a posteriori se fue modificando y ya es un nuevo codigo en sí, pero la experiencia en crear un flujo coherente de los datos fue bastante enriquecedora y muy gratificante. Luego fuera de mi granito de arena al proyecto creo que ocupe un rol un poco más de ir modificando cositas o pispeando algun que otro detalle, en el cual creo que no hubo tanto estrés dado que sentía que el contenido ya había sido más que nada masticado por mis compañeros y lo díficil ya estaba. En este mismo sentido también fue muy lindo ir entendiendo conceptos, en función de como mis compañeros realizaban codigo y en esto de que gracias a que ellos habían entendido, yo lograba entender también y luego a lo mejor poder aportar algo que haga que ese codigo crezca un poco más (proceso el cual también realizaban mis compañeros con mi codigo). En conclusión estoy bastante contento con mi grupo fuimos comprometidos con el proyecto y logramos llegar comodos sin tanto estres a la entrega, contentos con el resultado y sobre todo con lo vivido... ;)


  "Lautaro Deco":

En este texto voy a hablar sobre como fue mi experiencia/vivencia con el lab1, 
voy a empezar diciendo que este lab al principio no me convencia muccho, y que estaba un poco negado dado que no me llamaba al principio mucho la atencion, pero a medida que fuimos avanzando en el lab ese disgusto se fue yendo y cada vez disfrutaba mas sentarme a codear y leer cosas relacionadas al labo, con los chicos fuimos dividiendonos el trabajo en principio, pero siempre hubo mucha comunicacion entre nosostros y tratabamos de que cada cosa que ibamos avanzando o agregando todos le siguieramos el hilo al codigo, la idea era que todos entendamos todo. Como en todo trabajo "grande" por asi decir es facil sentirse a veces que el codigo te sobrepasa o que estas bastante trabado en una parte que a veces es frustrante, pero creo que tambien es importante el manejo de esa frustracion y saber sobrellevar el trabajo, dado que es grande y algunos modulos eran ccomplejos, casi nos sacamos los pelos para el execute.c , nos hizo renegar un poco, si embargo me gusto mucho como lo pudimos solucionar en conjunto. Otro tema a parte es que me propuse hacer el punto * del obfuscated, destaco que aunque me llevo bastante tiempito de leer ese codigo para entenderlo, fue unas de las partes creo que mas lindas del labo, siento que es un ejercicio muy bueno para abrir un poco la cabeza y de entendimiento de codigo. En general disfrute este lab y tambien lo fuimos llevando bastante bien con los chicos, tratando de ir todos al mismo ritmo, ayudandonos cada vez que podiamos :)


  "Tomas Torres":

Quiero empezar este feedback diciendo que este laboratorio me desafio bastante. Pero gracias a mi grupo pude no solo entender sino que aportar ideas sobre como empezar tal con codigo, ingeniarmela para hacer archivos desde cero como el builtin o proponer ideas (luego pulidas entre todos) de como podria/deberia ser la estructura del archivo mas feo y pesado (ademas de interesante) como el execute. Dentro de todo el lab me parecio ultra interesante. El tema de las "syscalls" me genero un monton de dudas y asombro de lo inmenso que es todo el trabajo que hay detras de algo tan simple como puede parecer el prender una compu y utilizar todo eso que funciona "magicamente". Note la dedicacion de mi grupo en intentar hacer todo lo que se podia hacer en el lab, incluyendo ejercicios y estrellas, la cual llevo a que intentara pensar en algun metodo para que funciones los conectores && y ;. Aunque al final no lo logre, fue enriquecedora la experiencia de intentar hacer algo que parecia imposible pero que al intentarlo varias veces no parecia ya tan lejano ese objetivo. En si esto fue con todo el lab1, al principio leer el enunciado y no entender nada, ponernos de acuerdo con los chicos, y juntos ir aportando lo que cada uno iba aprendiendo hasta poder lograr el objetivo. Me emociona saber que aun quedan mas labs por hacer que seguramente sera un desafio pero que entre nuestro grupito vamos a podre sobrellevar. :S 


  "Federico Taborda":
  
Federico Taborda: Mi experiencia en el lab01 fue una constate maduración de conceptos, hay muchas cosas que me costo entender pero yo creo que gracias al intensivo de aprender pude lograr captar muchas cosas, me gusto mucha el formato en otras palabras me sentí mas programador. Me genero un vinculo muy grande con lo que estábamos haciendo en el proyecto, al punto de quedarme horas pensando como se hacían las funcione, tads, etc. Pero me gustaba estar trabajo ya que puse todo mis esfuerzos en entender cosas que, en particular, a mi me lleva mucho tiempo en comprender, cosas que por ahí yo tuve que adquirir maduración propia en cuanto a conceptos, pero creo que me ayudo mucho puesto que al estar libre en ayd2 yo creo que después de este lab mi cerebro termino de entender los conceptos que por ahí quedaron un poco mal o no me cerraban del todo. Siempre intente ayudar lo que mas pude pero destaco que siempre hubo ese paso de frenar a explicar codigo de parte de los chicos,  cada uno aporto en lo que se sentia mas comodo o por ahi sabian mas pero siempre llevamos el proyecto bien entendido de lo que haciamo, estoy contento porque pude aportar mucho mas de lo que imaginba y todo lo que pude dar lo di asique me voy contento . En fin, me gusto mucho y me ayudo a sentirme que me gusta este tipo de cosas y que aunque me cueste mucho si le meto pasión de sentarme ver que esta pasando, investigar si se puede llevar. Y también gracias a los chicos de mi grupo que se cargaron el lab a la espalda y ayudaron mucho mas que yo que por ahí no estoy tan lucido con estas cosas.

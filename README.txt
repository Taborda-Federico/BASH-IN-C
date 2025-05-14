




** CONSIDERACIONES TECNICAS **

    ->   "sort -n &"   (Funciona bien nada más que se pierde la referencia de la terminal cuando lo ejecutas, sin embargo cuando le das un comando nuevo sigue ejecutando)

	->	 "wc > /dev/mem"  (No dice permiso denegado y se bugea la terminal cuando lo ejecutas)
		
    ->	 "wc < /dev/mem"  (En cambio aca no se bugea al ejecutar dado que dice que es un descriptor de archivo erroneo)
				
	-> 	 "ls >"  (Aca salta por el assert dado que no existe archivo en el que incrustar la información) y luego se sale del mybash y da este mensaje zsh: IOT instruction (core dumped)  ./mybash
	
En estos 3 comandos encontramos funciones no deseadas de nuestro bash, pero con un poco mas de tiempo hubiesemos podido pulir el codigo y corregir estos problemas.




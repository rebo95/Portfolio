//Rodrigo Manuel Pérez Ruiz
//Aaron Reboredo Vázquez

using System;

namespace Practica1
{
	class MainClass
	{
		public static void Main(string[] args)
		{
			
			int alto, ancho, bombaX, bombaY, jugadorX, jugadorY, enemigoX, enemigoY, balaX, balaY, i, bp, s, m, delta;
			string mov;

			Random rnd = new Random();
			// INPUT DE DATOS; SELECCIÓN DEL TAMAÑO DEL CAMPO DE BATALLA Y LA DIFICULTAD ( DELTA)


			ancho = 0;
			alto = 0;
			//inicializamos las variables que nos va a pedir que introsuzcamos 
			//las inicializamos con un valor que va a forzar al programa a entrar en el bucle en primera instancia

			while ((ancho < 10) || (ancho > 50))
			{
				Console.Write("Introducir ancho (10,50) : ");
				ancho = int.Parse(Console.ReadLine());
			}

			//si no introducimos los valores entre los establecidos nos vuelve a pedir el dato en cuestión

			while ((alto < 10) || (alto > 30))
			{
				Console.Write("Introducir alto (10,30) : ");
				alto = int.Parse(Console.ReadLine());
			}

			Console.Write
			       (@"Delta: setea velocidad de juego
Recomendado valores entre 100 (más difícil) y 300,
Introducir valor de dificultad deseado : ");

			delta = int.Parse(Console.ReadLine());
			       

			//INICIALIZACION DE VARIABLES PARA LOS CONDICIONALES CORRESPONDIENTES

			jugadorX = ancho / 2;
			jugadorY = alto - 1;
			balaX = ancho + 2;
			balaY = alto + 1;
			bp = 1;
			enemigoX = ancho / 2;
			enemigoY = (alto / 2) - 2;
			bombaX = ancho + 2;
			bombaY = 0;
			s = 0;
			m = 0;


			while (bp > 0)
			{
				//INPUT KEYBOARD

				if (Console.KeyAvailable)
				{
					//establecemos la lectura de teclado y las restricciones de disparo y movimiento pertinentes
					//de la mima manera fijamos ya el movimiento del PLAYER1
					mov = (Console.ReadKey(true)).KeyChar.ToString();
					if (mov == "a" && jugadorX > 0)
					{
						jugadorX--;
					}
					if (mov == "d" && jugadorX < ancho - 1)
					{
						jugadorX++;
					}


					if (mov == "l" && balaX == ancho + 2)
						m = 1;
					else
						m = 0;
					//FINAL DEL INPUT DE USUARIO
				}

				//MOVIMIENTO ENEMIGO, BOMBA ENEMIGA Y BALA PLAYER 1

				// POSICIONAMIENTO DEL ENEMIGO Y MOVIMIENTO POR LA PANTALLA
				//movimiento horizontal y restricciones


				if (enemigoX <= 1)
					enemigoX += rnd.Next(0, 2);
				else if (enemigoX >= (ancho - 5))
					enemigoX += rnd.Next(-1, 1);
				else
					enemigoX += rnd.Next(-1, 2);

				//movimiento veltical y restricciones

				if (enemigoY <= 2)
					enemigoY += rnd.Next(0, 2);
				else if (enemigoY >= (alto / 2))
					enemigoY += rnd.Next(-1, 1);
				else
					enemigoY += rnd.Next(-1, 2);

				//FINAL MOVIMIENTO ENEMIGO


				//MOVIMIENTO DEL PROYECTIL ENEMIGO

				//condicion de parada, desaparición de la bomba al salir del campo de juego 
				if (bombaY <= alto - 1)
					if (bombaY == 0)
					{
						bombaY = enemigoY + 1;
						bombaX = enemigoX + 1;
					}
					else
						bombaY++;
				
				//situa la bomba en el cargador enemigo 
				else {
					bombaX = ancho + 2;
					bombaY = 0;
				}

				//FINAL MOVIMIENTO PROYECTIL ENEMIGO

				//DISPARO BALA PLAYRER 1 + COMPORTAMIENTO 
				//posicionamiento de la bala tras el input en keyboard
				if (m == 1)
				{
					balaY = jugadorY - 1;
					balaX = jugadorX;
					m = 0;
				}

				//movimiento intrínseco de bala
				if (m == 0 && balaX < ancho)
					balaY--;

				//posicionamiento en espera a disparo (tras desaparecer del campo de juego )
				if (balaY <= 0)
				{
					balaY = alto + 1;
					balaX = ancho + 2;
				}

				//FINAL MOVIMIENTO DEL PRIYECIL PLAYER 1


				//MOTOR DE COLISIONES 

				//COLISIONES ENTRE BALA Y BOMBA
				if ((balaX == bombaX) && ((balaY == bombaY) || (balaY == bombaY - 1)))
				{
					//devolvemos bomba a posición cargador enemigo 
					bombaX = ancho + 2;
					bombaY = 0;
					//devolvemos bala jugador a cargador PLAYER 1
					balaX = ancho + 2;
					balaY = alto + 1;
				}

				//COLISÓN BOMBA ENEMIGA PLAYER 1


				if (((bombaY == jugadorY) && (bombaX == jugadorX)))
				{ //sale del bucle principal y imprime en pantalla "derrota"
					bp = 0; 
					Console.Clear();
					//posicionamos mensaje de derrota en la posición deseada 

					Console.SetCursorPosition((ancho / 2) - 4, alto / 2);
					Console.Write("GAME OVER");
					Console.SetCursorPosition(0, alto + 3);
					//introducción de lectura de consola; si ejecutamos con depuracion el programa no se cierra.

					Console.Write(" Pulse ENTER para cerrar el programa ");
					Console.ReadLine();

				}

				//FINAL COLISIÓN BOMBA JUGADOR Y SISTEMA DE DERROTA

				// COLISIÓN BALA Y ENEMIGO Y SISTEMA DE VICTORIA

				//Impacto de nuestra bala con el enemigo 

				//Hemos implementado que la bala pueda colisionar con el enemigo en una posición por encima suya para 
				//evitar que el enemigo traspase la bala en el cambio de frame

				if ((((balaY == enemigoY)||(balaY == enemigoY-1)) && ((balaX == enemigoX) || (balaX == (enemigoX + 1))
				                             || (balaX == enemigoX + 2))))
					
					// implementando un sistema de daño con código de colores añadimos una variable que
					//vaya recogiendo ese daño 

					{
					//la bala se destruye y vuelve al posicionamiento en espera a disparor al impactar con el enemigo 
					balaY = alto + 1;
					balaX = ancho + 2;
					//la bala se destruye y vuelve al cargador al impactar contra el enemigo 
					s++;
					//añadimos 1 a la lvariable que contabiliza el daño.
						}
					
					//FINAL COLISIONES BALA ENEMIGO Y SISTEMA DE VICTORIA 



				//RENDERIZADO GRÁFICO


				Console.SetCursorPosition(0, 0);
				Console.Clear();

				//PINTADO CAMPO DE JUEGO

				for (i = 0; i <alto; i++)
				{
					//pintamos el lateral del campo por cada salto de inea que hace el for
					//situamos el cursor en la posición deseada y escribimos.
					Console.SetCursorPosition(ancho, i);
					Console.Write("|");
						
					}

				//FIN PINTADO CAMPO DE JUEGO 

				//PINTADO DE JUGADOR, EMEMIGO, BOMBA Y BALA
				Console.ForegroundColor = ConsoleColor.Green; //color del jugador 
				Console.SetCursorPosition(jugadorX, jugadorY);
				Console.Write("@"); //dibujo del jugador


				//ESTABLECEMOS UN SISTEMA DE VIDAS PARA EL ENEMIGO. POR CADA HIT ESTE CAMBIA DE COLOR
				//TIENE TRES VIDAS. 3 HITS PARA MATARLO. CUATRO ESTADOS:
				//blanco(inicial), amarillo ( 1er hit) , rojo (2º hit), destruido - fin de partida (3er hit) */

				if (s == 0)
				{
					Console.ForegroundColor = ConsoleColor.White;
					 //color inicial enemigo 
				}
				else if (s == 1)
				{
					Console.ForegroundColor = ConsoleColor.Yellow;
					   //color secundario enemigo 
				}
				else if (s == 2)
				{
					Console.ForegroundColor = ConsoleColor.Red;
					   //color final enemigo 
				}
				//renderizamos el enemigo.
				Console.SetCursorPosition(enemigoX, enemigoY);
				Console.Write("***");

				// tras el tercer impacto el enemigo ha muerto y finaliza el juego con nuestra victoria

				if (s == 3){
					Console.Clear();
						Console.SetCursorPosition((ancho / 2) - 4, alto / 2);
						Console.Write("VICTORY");
						Console.SetCursorPosition(0, alto + 3);
					Console.Write(" Pulse ENTER para cerrar el programa ");
					bp = 0;
					Console.ReadLine();

				}

				// Pintamos el resto de integrantes, bala y bomba

				Console.ForegroundColor = ConsoleColor.White; //color bala 
				Console.SetCursorPosition(balaX, balaY);    
				Console.Write("^"); //dibujo bala

				Console.ForegroundColor = ConsoleColor.Blue; // color bomba
				Console.SetCursorPosition(bombaX, bombaY); 
				Console.Write("="); //dibujo de la bomba
				Console.ForegroundColor = ConsoleColor.White;

			//TIEMPO DE RETARDO O DIFICULTAD DEL JUEGO
				System.Threading.Thread.Sleep(delta);

			}

		}
	}
}
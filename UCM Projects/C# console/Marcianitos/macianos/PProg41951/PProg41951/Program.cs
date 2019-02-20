using System;

namespace Practica1
{
	class MainClass
	{
		public static void Main(string[] args)
		{

			int alto, ancho, bombaX, bombaY, jugadorX, jugadorY, enemigoX, enemigoY, balaX, balaY, aleatorio, i, j, bp;
			double delta;
			string mov, a, d;

			Random rnd = new Random();

			Console.Write("Introducir ancho: ");
			ancho = int.Parse(Console.ReadLine());
			Console.Write("Introducir alto: ");
			alto = int.Parse(Console.ReadLine());
			//Console.Write ("Introducir delta: ");
			//delta = double.Parse (Console.ReadLine ());
			jugadorX = ancho / 2;
			jugadorY = alto - 1;
			balaX = ancho + 2;
			balaY = alto - 2;
			bp = 1;
			enemigoX = ancho / 2;
			enemigoY = (alto / 2) - 2;
			bombaX = ancho + 2;
			bombaY = 4;

			while (bp > 0)
			{

				//INPUT USUARIO
				if (Console.KeyAvailable)
				{
					mov = (Console.ReadKey(true)).KeyChar.ToString();
					if (mov == "a" && jugadorX > 0)
					{
						jugadorX--;
					}
					if (mov == "d" && jugadorX < ancho - 1)
					{
						jugadorX++;
					}
					if (mov == "s")
					{

						if (balaY > 1)
						{
							balaY = jugadorY - 1;
							balaX = jugadorX;
						}

						else {
							balaY = (alto - 2);
							balaX = (ancho + 2);
						}
					}

				}

				//posicion en X del enemigo
				if (enemigoX <= 1)
					enemigoX = enemigoX + rnd.Next(0, 2);
				else if (enemigoX >= (ancho - 5))
					enemigoX = enemigoX + rnd.Next(-1, 1);
				else
					enemigoX = enemigoX + rnd.Next(-1, 2);

				if (enemigoY <= 2)
					enemigoY = enemigoY + rnd.Next(0, 2);
				else if (enemigoY >= (alto / 2))
					enemigoY = enemigoY + rnd.Next(-1, 1);
				else
					enemigoY = enemigoY + rnd.Next(-1, 2);




				//RENDERIZADO GRÁFICO

				Console.SetCursorPosition(0, 0);
				Console.Clear();

				i = 0;
				while (i < alto)
				{

					j = 0;
					while (j < ancho)
					{
						Console.Write(" ");
						j++;
						if (j == ancho)
						{
							Console.Write("|");
						}
					}
					Console.WriteLine();
					i++;
				}

				Console.SetCursorPosition(jugadorX, jugadorY);  //dibujo del borde, enemigo, bomba, jugador y bala
				Console.Write("@"); //dibujo del borde, enemigo, bomba, jugador y bala

				Console.SetCursorPosition(enemigoX, enemigoY); //dibujo del borde, enemigo, bomba, jugador y bala
				Console.Write("***");   //dibujo del borde, enemigo, bomba, jugador y bala
				Console.SetCursorPosition(balaX, balaY);    //dibujo del borde, enemigo, bomba, jugador y bala
				Console.Write("^"); //dibujo del borde, enemigo, bomba, jugador y bala
									/*	Console.SetCursorPosition (bombaX, bombaY);	//dibujo del borde, enemigo, bomba, jugador y bala
									Console.Write ("=");	//dibujo del borde, enemigo, bomba, jugador y bala
									Console.SetCursorPosition (jugadorX, jugadorY);	//dibujo del borde, enemigo, bomba, jugador y bala
									Console.Write ("@");	//dibujo del borde, enemigo, bomba, jugador y bala
									Console.SetCursorPosition (bombaX, bombaY);	//dibujo del borde, enemigo, bomba, jugador y bala
									Console.Write ("=");	//dibujo del borde, enemigo, bomba, jugador y bala
										*/

				//Tiempo de retardo
				System.Threading.Thread.Sleep(100);


			}
		}
	}
}


// if (bombax==balaX && balaY<bombaY)
//set cursor position balaxbalay write " "
//set cursor position bomba write " "

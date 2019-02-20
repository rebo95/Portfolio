using System;

namespace Practica1
{
	class MainClass
	{
		public static void Main(string[] args)
		{

			int alto, ancho, bombaX, bombaY, jugadorX, jugadorY, enemigoX, enemigoY, balaX, balaY, i, j, bp, p, q, s;
			string mov;

			Random rnd = new Random();

			Console.Write("Introducir ancho: ");
			ancho = int.Parse(Console.ReadLine());
			while ((ancho < 10) || (ancho > 50))
			{
				Console.Write("Introducir ancho: ");
				ancho = int.Parse(Console.ReadLine());
			}
			Console.Write("Introducir alto: ");
			alto = int.Parse(Console.ReadLine());
			while ((alto < 10) || (alto > 30))
			{
				Console.Write("Introducir alto: ");
				alto = int.Parse(Console.ReadLine());
			}
			//Console.Write ("Introducir delta: ");
			//delta = double.Parse (Console.ReadLine ());
			jugadorX = ancho / 2;
			jugadorY = alto - 1;
			balaX = ancho + 2;
			balaY = alto + 1;
			bp = 1;
			enemigoX = ancho / 2;
			enemigoY = (alto / 2) - 2;
			bombaX = ancho + 2;
			bombaY = 0;
			p = 0;
			q = 0;
			s = 0;


			while (bp > 0)
			{
				//INPUT USUARIO
				p = 0;
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
					if ((mov == "s") && (balaY == alto + 1) && (balaX == ancho + 2))
						p = 1;
				}
				if (p == 1)
				{
					q = 1;
					balaX = jugadorX;
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

				if (q == 1)
				{
					if (balaY > 0)
					{
						if (balaY >= jugadorY)
						{
							balaY = jugadorY - 1;
							balaX = jugadorX;
						}
						else
							balaY = balaY - 1;
					}
					else {
						balaX = ancho + 2;
						balaY = alto + 1;
						q = 0;
					}
				}

				//Movimiento de la bomba enemiga
				if (bombaY < (alto - 1))
				{
					if (bombaY <= enemigoY)
					{
						bombaY = enemigoY + 1;
						bombaX = enemigoX + 1;
					}
					else
						bombaY = bombaY + 1;
				}
				else {
					bombaX = ancho + 2;
					bombaY = 0;
				}


				if (((bombaX == balaX) && ((bombaY == balaY) || (bombaY == balaY + 1) || (bombaY == balaY - 1))))
				{
					bombaX = ancho + 2;
					bombaY = 0;
					balaX = ancho + 2;
					balaY = alto + 1;
					q = 0;
				}

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
				Console.ForegroundColor = ConsoleColor.Green;
				Console.SetCursorPosition(jugadorX, jugadorY);  //dibujo del borde, enemigo, bomba, jugador y bala
				Console.Write("@"); //dibujo del borde, enemigo, bomba, jugador y bala
				Console.SetCursorPosition(enemigoX, enemigoY); //dibujo del borde, enemigo, bomba, jugador y bala
				if (s == 0)
				{
					Console.ForegroundColor = ConsoleColor.White;
					Console.Write("***");   //dibujo del borde, enemigo, bomba, jugador y bala
				}
				if (s == 1)
				{
					Console.ForegroundColor = ConsoleColor.Yellow;
					Console.Write("***");   //dibujo del borde, enemigo, bomba, jugador y bala
				}
				if (s == 2)
				{
					Console.ForegroundColor = ConsoleColor.DarkYellow;
					Console.Write("***");   //dibujo del borde, enemigo, bomba, jugador y bala
				}
				if (s == 3)
				{
					Console.ForegroundColor = ConsoleColor.Red;
					Console.Write("***");   //dibujo del borde, enemigo, bomba, jugador y bala
				}
				Console.ForegroundColor = ConsoleColor.White;
				Console.SetCursorPosition(balaX, balaY);    //dibujo del borde, enemigo, bomba, jugador y bala
				Console.Write("^"); //dibujo del borde, enemigo, bomba, jugador y bala
				Console.ForegroundColor = ConsoleColor.Blue;
				Console.SetCursorPosition(bombaX, bombaY);  //dibujo del borde, enemigo, bomba, jugador y bala
				Console.Write("="); //dibujo del borde, enemigo, bomba, jugador y bala
				Console.ForegroundColor = ConsoleColor.White;
				//Tiempo de retardo
				System.Threading.Thread.Sleep(300);

				if (((bombaY == jugadorY) && (bombaX == jugadorX)))
					bp = 0;
				if (((balaY == enemigoY) && ((balaX == enemigoX) || (balaX == (enemigoX + 1)) || (balaX == enemigoX + 2))))
				{
					s = s + 1;
					if (s == 4)
						bp = 0;
				}
				if (((bombaY == jugadorY) && (bombaX == jugadorX)))
				{
					Console.SetCursorPosition((ancho / 2) - 4, alto / 2);
					Console.Write("GAME OVER");
					Console.SetCursorPosition(0, alto + 3);
				}
				if (((balaY == enemigoY) && (s == 4)) && ((balaX == enemigoX) || (balaX == (enemigoX + 1)) || (balaX == enemigoX + 2)))
				{
					Console.SetCursorPosition((ancho / 2) - 4, alto / 2);
					Console.Write("VICTORY");
					Console.SetCursorPosition(0, alto + 3);
				}
			}
		}
	}
}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace LaPracticaDeVerdad
{
    class Program
    {
        struct Coordenadas
        {
            public int cx;
            public int cy;
        }

        struct Casilla
        {
            public bool mina;
            public char estado;
        }

        struct Tablero
        {
            public Casilla[,] cas;
            public int posX, posY;
        }



        static void Main(string[] args)
        {
            Jugar();
        }

        static Tablero creaTablero(int fils, int cols, int numMinas)
        {
            Tablero tab;
            Random rnd = new Random();
            tab.cas = new Casilla[fils, cols];
            tab.posX = 0;
            tab.posY = 0;
            int ContadorDeMinas = 0;

            for (int i = 0; i < tab.cas.GetLength(0); i++)
                for (int j = 0; j < tab.cas.GetLength(1); j++)
                    tab.cas[i, j].estado = 'o';

            while (ContadorDeMinas < numMinas)
            {
                int x = rnd.Next(0, cols);
                int y = rnd.Next(0, fils);
                if (!tab.cas[y, x].mina)
                {
                    tab.cas[y, x].mina = true;
                    ContadorDeMinas++;
                }
            }
            return tab;
        }


        static void Dibuja(Tablero tab, bool bomba)
        {
            if (bomba)
            {
                for (int i = 0; i < tab.cas.GetLength(0); i++)
                {
                    for (int j = 0; j < tab.cas.GetLength(1); j++)
                    {
                        if (tab.cas[i, j].mina)
                        {
                            Console.SetCursorPosition(j, i);
                            Console.BackgroundColor = ConsoleColor.Yellow;
                            Console.ForegroundColor = ConsoleColor.White;
                            if (j == tab.posX && i == tab.posY)
                            {
                                Console.SetCursorPosition(tab.posX, tab.posY);
                                Console.BackgroundColor = ConsoleColor.Red;
                                Console.ForegroundColor = ConsoleColor.Black;
                            }
                            Console.Write("*");
                        }
                    }
                }

                Console.SetCursorPosition(tab.cas.GetLength(1), tab.cas.GetLength(0));
                Console.BackgroundColor = ConsoleColor.Black;
                Console.ForegroundColor = ConsoleColor.DarkRed;
                Console.WriteLine("Boooooom!!!");
            }
            else
                for (int i = 0; i < tab.cas.GetLength(0); i++)
                {
                    for (int j = 0; j < tab.cas.GetLength(1); j++)
                    {


                        if (i == tab.posY && j == tab.posX)
                        {
                            Console.BackgroundColor = ConsoleColor.White;
                        }
                        else
                            Console.BackgroundColor = ConsoleColor.Black;

                        if (tab.cas[i, j].estado == 'o')
                        {
                            Console.SetCursorPosition(j, i);
                            if (Console.BackgroundColor == ConsoleColor.White)
                            {
                                Console.ForegroundColor = ConsoleColor.Black;
                            }
                            else
                                Console.ForegroundColor = ConsoleColor.White;

                            Console.Write("o");
                        }

                        else if (tab.cas[i, j].estado == '0')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.Write(" ");
                        }
                        else if (tab.cas[i, j].estado == '1')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.Blue;
                            Console.Write("1");
                        }
                        else if (tab.cas[i, j].estado == '2')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.Green;
                            Console.Write("2");
                        }
                        else if (tab.cas[i, j].estado == '3')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.Write("3");
                        }
                        else if (tab.cas[i, j].estado == '4')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.DarkBlue;
                            Console.Write("4");
                        }
                        else if (tab.cas[i, j].estado == '5')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.DarkRed;
                            Console.Write("5");
                        }
                        else if (tab.cas[i, j].estado == '6')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.DarkGreen;
                            Console.Write("6");
                        }
                        else if (tab.cas[i, j].estado == '7')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.Black;
                            Console.Write("7");
                        }
                        else if (tab.cas[i, j].estado == '8')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.Gray;
                            Console.Write("8");
                        }
                        else if (tab.cas[i, j].estado == 'x')
                        {
                            Console.SetCursorPosition(j, i);
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.Write("x");
                        }

                        if (Console.BackgroundColor == ConsoleColor.White)
                            Console.ForegroundColor = ConsoleColor.Black;

                    }

                }

            Console.SetCursorPosition(tab.posX, tab.posY);
        }


        static void descubreAdyacencia(Tablero tab, int x, int y)
        {
            char est = ' ';
            string minaString;
            Coordenadas[] pendientes = new Coordenadas[tab.cas.GetLength(0) * tab.cas.GetLength(1)];
            //Creamos un vector auxiliar que vaya almacenando todas aqueyas posiciones circundantes a la que hacemos click
            //y que nos permitirán ir visitando eseas posiciones a partir de la indicada 

            int End = 1;

            pendientes[0] = new Coordenadas { cx = tab.posX, cy = tab.posY };


            int puntero = 0;

            while (puntero < End)
            {
                //vamos a ir almacenando las posiciones pendientes en un vector de coordenadas que iremos recorriendo para ir haciendo el análisis
                //de todas esas posiciones pendientes de analizar       
                int mina = 0;
                for (int i = Math.Max(0, pendientes[puntero].cy - 1); i <= Math.Min(tab.cas.GetLength(0) - 1, pendientes[puntero].cy + 1); i++)
                {
                    for (int j = Math.Max(0, pendientes[puntero].cx - 1); j <= Math.Min(tab.cas.GetLength(1) - 1, pendientes[puntero].cx + 1); j++)
                    {
                        if (tab.cas[i, j].mina)
                        {
                            mina++;
                        }
                    }
                }

                //buscamos alrededor de la posicion en la que se encuentra el puntero (casilla pendiente de analizar) y vemos cuantas minas, si las hay, hay alrededor
                if (mina != 0)
                {
                    minaString = mina.ToString();
                    est = minaString[0];
                    tab.cas[pendientes[puntero].cy, pendientes[puntero].cx].estado = est;
                }

                else
                {
                    //en caso de no haber minas alrededor el estado de esa casilla va a ser 0 y miramos de esa manera las casillas que tiene alrededor para saber 
                    //si son casillas pendientes de analizar y añadirlas de esta manera a nuestro vector de casillas por explorar 
                    tab.cas[pendientes[puntero].cy, pendientes[puntero].cx].estado = '0';
                    for (int i = Math.Max(0, pendientes[puntero].cy - 1); i <= Math.Min(tab.cas.GetLength(0) - 1, pendientes[puntero].cy + 1); i++)
                    {
                        for (int j = Math.Max(0, pendientes[puntero].cx - 1); j <= Math.Min(tab.cas.GetLength(1) - 1, pendientes[puntero].cx + 1); j++)
                        {
                            int k = 0;
                            //vamos recorriendo el vector de pendientes cada vez para que no se añadan en el mismo posiciones que ya se habían introducido
                            //anteriormete, codificamos o obligamos para las siguientes ocasiones que llamemos al método adyacencia que el estado de la casilla sea 
                            //sin destapar, de esta manera no almacenará posiciones ya analizadas en anteriores ocasiones en las que hayamos llamado al método
                            while ((i != pendientes[k].cy || j != pendientes[k].cx) && k < End && tab.cas[i, j].estado == 'o')
                            {
                                k++;
                            }
                            if (k == End)
                            {

                                pendientes[End].cx = j;
                                pendientes[End].cy = i;
                                End++;
                            }
                        }

                    }

                }
                puntero++;
            }
        }


        static char leeInput()//Lee el caracter recibido por teclado en forma de string y lo devuelve como un caracter
        {
            if (Console.KeyAvailable)
            {
                string tecla = Console.ReadKey().Key.ToString();
                //codificamos una char para el movimiento según la entrada de teclado 
                if (tecla == "LeftArrow")
                {
                    return 'l';
                }
                else if (tecla == "UpArrow")
                {
                    return 'u';
                }
                else if (tecla == "RightArrow")
                {
                    return 'r';
                }
                else if (tecla == "DownArrow")
                {
                    return 'd';
                }
                else if (tecla == "Spacebar")
                {
                    return 's';
                }
                else if (tecla == "Enter")
                {
                    return 'e';
                }
                else if (tecla == "Escape")
                {
                    return 'q';
                }

                else return ' ';
            }

            return ' ';//para cualquier otra tecla simplemente se devuelve un blanco y no cambiará nada del juego
        }


        static bool procesaInput(ref Tablero tab, char c)
        {
            bool mina = false;


            if (c == 'u')
            {
                if (tab.posY > 0)
                    tab.posY -= 1;
            }
            else if (c == 'd')
            {
                if (tab.posY < tab.cas.GetLength(0) - 1)
                    tab.posY += 1;
            }
            else if (c == 'l')
            {
                if (tab.posX > 0)
                    tab.posX -= 1;
            }
            else if (c == 'r')
            {
                if (tab.posX < tab.cas.GetLength(1) - 1)
                    tab.posX += 1;
            }
            else if (c == 'e')
            {
                if (tab.cas[tab.posY, tab.posX].estado == 'o')
                    tab.cas[tab.posY, tab.posX].estado = 'x';
                else if (tab.cas[tab.posY, tab.posX].estado == 'x')
                    tab.cas[tab.posY, tab.posX].estado = 'o';

                // nos permite marcar la casilla siempre y cuando el estado sea tapada, y nos permite desmarcar aquellas que hemos marcado con anterioridad solo
            }
            else if (c == 's')
            {
                if (tab.cas[tab.posY, tab.posX].estado == 'o')
                    mina = ClickCasilla(tab);
                //si pulsamos la tecla que nos hace de clik se llama al método click casilla solo si la casilla seleccionada está tapada 
            }

            return mina;
        }


        static bool ClickCasilla(Tablero tab)
        {
            if (tab.cas[tab.posY, tab.posX].estado == 'o')
            {
                if (tab.cas[tab.posY, tab.posX].mina)
                {
                    tab.cas[tab.posY, tab.posX].estado = '*';
                    return true;
                }
                else
                {
                    descubreAdyacencia(tab, tab.posX, tab.posY);
                    return false;
                }
            }
            else
                return false;
        }

        static bool Terminado(Tablero tab)
        {
            bool victoria = true;
            int i = 0;
            int j;
            while (victoria && i < tab.cas.GetLength(0))
            {
                j = 0;
                while (victoria && j < tab.cas.GetLength(1))
                {
                    //if ((tab.cas[i, j].estado == 'o' && !tab.cas[i, j].mina) || (tab.cas[i, j].estado == 'x' && !tab.cas[i, j].mina))
                    // con esta línea de código la victoria se produciría una vez aisladas las minas sin necesidad de que sean marcadas, 
                    //cambio interesante si queremos que la experiencia se asemeje al juego original.
                    if ((tab.cas[i, j].estado == 'o' && tab.cas[i, j].mina) || tab.cas[i, j].estado == 'o'
                       || (tab.cas[i, j].estado == 'x' && !tab.cas[i, j].mina))
                    {
                        victoria = false;
                    }
                    j++;
                }
                i++;
            }
            return victoria;

        }


        static void GuardarPartida(Tablero tab)
        {
            StreamWriter Guardado = new StreamWriter("PartidaGuardada.txt");

            for (int i = 0; i < tab.cas.GetLength(0); i++)
            {
                for (int j = 0; j < tab.cas.GetLength(1); j++)
                {
                    if (tab.cas[i, j].estado == 'o' && tab.cas[i, j].mina == true)
                        Guardado.Write('-');
                    else if (tab.cas[i, j].estado == 'o' && tab.cas[i, j].mina == false)
                        Guardado.Write('/');
                    else if (tab.cas[i, j].estado == 'x' && tab.cas[i, j].mina == false)
                        Guardado.Write('|');
                    else if (tab.cas[i, j].estado == 'x' && tab.cas[i, j].mina == true)
                        Guardado.Write('=');
                    else if (tab.cas[i, j].estado == '0')
                        Guardado.Write('ç');
                    else if (tab.cas[i, j].estado == '1')
                        Guardado.Write('%');
                    else if (tab.cas[i, j].estado == '2')
                        Guardado.Write('6');
                    else if (tab.cas[i, j].estado == '3')
                        Guardado.Write('j');
                    else if (tab.cas[i, j].estado == '4')
                        Guardado.Write('?');
                    else if (tab.cas[i, j].estado == '5')
                        Guardado.Write('(');
                    else if (tab.cas[i, j].estado == '6')
                        Guardado.Write('*');
                    else if (tab.cas[i, j].estado == '7')
                        Guardado.Write('#');
                    else if (tab.cas[i, j].estado == '8')
                        Guardado.Write(':');

                }
                Guardado.WriteLine();
            }
            Guardado.Close();
            //hemos realizado un acodificación ilegible para almacnar el estado de la partida en un txt, de tal manera que el usuario no pueda ver el estado 
            // de la partida que va a cargar de manera tan sencilla
        }

        static Tablero CargaTablero()
        {
            //realizamos una primera lectura de un archivo de texto de tal manera que se analice el número de filas y columnas que tiene nuestra partida
            // también podríamos almacenar esta información en el txt a la hora de guardar partida (dos primeras lineas con el número de fils y cols respectivamente)
            //y que este método leyese esas líneas de información para 
            // codificar la partida y tablero cargados.
            StreamReader Cargador = new StreamReader("PartidaGuardada.txt");
            StreamReader Analisis = new StreamReader("PartidaGuardada.txt");
            int i = 0;
            int fils = 1;
            int cols;

            string linea;
            string lectura;

            Tablero tab;

            tab.posX = 0;
            tab.posY = 0;

            lectura = Analisis.ReadLine();
            cols = lectura.Length;

            while (!Analisis.EndOfStream)
            {
                lectura = Analisis.ReadLine();
                fils++;

            }

            tab.cas = new Casilla[fils, cols];

            //imprimimos en pantala el tablero guardado en el txt en función de la codificación establecida 
            while (!Cargador.EndOfStream)
            {
                linea = Cargador.ReadLine();


                for (int j = 0; j < linea.Length; j++)
                {
                    if (linea[j] == '-')
                    {
                        tab.cas[i, j].estado = 'o';
                        tab.cas[i, j].mina = true;
                    }
                    else if (linea[j] == '/')
                    {
                        tab.cas[i, j].estado = 'o';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == '=')
                    {
                        tab.cas[i, j].estado = 'x';
                        tab.cas[i, j].mina = true;
                    }
                    else if (linea[j] == '|')
                    {
                        tab.cas[i, j].estado = 'x';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == 'ç')
                    {
                        tab.cas[i, j].estado = '0';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == '%')
                    {
                        tab.cas[i, j].estado = '1';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == '6')
                    {
                        tab.cas[i, j].estado = '2';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == 'j')
                    {
                        tab.cas[i, j].estado = '3';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == '?')
                    {
                        tab.cas[i, j].estado = '4';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == '(')
                    {
                        tab.cas[i, j].estado = '5';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == '*')
                    {
                        tab.cas[i, j].estado = '6';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == '#')
                    {
                        tab.cas[i, j].estado = '7';
                        tab.cas[i, j].mina = false;
                    }
                    else if (linea[j] == ':')
                    {
                        tab.cas[i, j].estado = '8';
                        tab.cas[i, j].mina = false;
                    }
                }
                i++;

            }

            Analisis.Close();
            Cargador.Close();
            return tab;
        }


        static void Jugar()
        {
            //método que nos permite que el juego se ejecute, con su menú y mensajes de repetición de partida o abandonar en caso que se quiera
            Tablero tab = new Tablero();

            bool mina = false;
            bool victoria = false;
            bool abandonar = false;

            char entrada;

            string guardar;
            string cargar;

            bool responde = false;

            int Alto = 0;
            int Ancho = 0;
            int Minas = 0;
            int min = 4;
            int max = 30;
            int maxMinas;

            while (!responde)
            {
                Console.WriteLine(" Cargar partida -> [c] ");
                Console.WriteLine(" Empezar nuevo juego -> [n] ");
                Console.Write(" ¿Qué desea hacer? : ");
                cargar = Console.ReadLine();

                if ((cargar == "c") || (cargar == "C"))
                {
                    responde = true;
                    tab = CargaTablero();
                }
                else if ((cargar == "n") || (cargar == "N"))
                {
                    Console.Clear();
                    responde = true;

                    while ((Alto < min) || (Alto > max))
                    {
                        Console.Write(" Alto [{0}-{1}] : ", min, max);
                        Alto = int.Parse(Console.ReadLine());
                    }
                    while ((Ancho < min) || (Ancho > max))
                    {
                        Console.Write("Ancho [{0}-{1}] : ", min, max);
                        Ancho = int.Parse(Console.ReadLine());
                    }
                    maxMinas = (Ancho * Alto / 3);
                    while ((Minas < 1) || (Minas > maxMinas))
                    {
                        Console.Write("Número de Minas [1-{0}] : ", maxMinas);
                        Minas = int.Parse(Console.ReadLine());
                    }

                    tab = creaTablero(Alto, Ancho, Minas);
                }
            }

            Console.Clear();
            Dibuja(tab, false);

            while (!mina && !victoria && !abandonar)
            {
                entrada = leeInput();
                if (entrada == 'q')
                    abandonar = true;
                else if (entrada != ' ')
                {
                    mina = procesaInput(ref tab, entrada);
                    Dibuja(tab, mina);
                    //si no hemos pulsado mina podemos ganar
                    if (!mina)
                        victoria = Terminado(tab);
                }
            }
            if (victoria)
            {
                Console.Clear();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Enhorabuena has ganado ");
                //si hemos ganado aparece este mensaje, y solo si hemos ganado 
            }

            else if (abandonar)
            {
                //el mensaje aparece si abandonamos y solo si abandonamos 
                Console.Clear();
                responde = false;
                while (!responde)
                {
                    Console.ForegroundColor = ConsoleColor.White;
                    Console.Write("Deseas guardar la partida? [s/n]: ");
                    guardar = Console.ReadLine();

                    if (guardar == "s")
                    {
                        responde = true;
                        GuardarPartida(tab);
                        Console.WriteLine("Partida guardada");
                    }
                    else if (guardar == "n")
                        responde = true;
                }

            }
            Console.SetCursorPosition(tab.cas.GetLength(1) + 2, tab.cas.GetLength(0) + 2);
            Console.WriteLine("Fin del juego");
            Console.WriteLine("Pulsa ENTER para cerrar el programa \n Introduzca [r] y pulse Enter para jugar otra vez");
            Console.ForegroundColor = ConsoleColor.White;
            string respuesta = Console.ReadLine();
            if (respuesta == "r" || respuesta == "R")
            {
                Console.Clear();
                Jugar();
            }
        }
    }
}

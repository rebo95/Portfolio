using System;

namespace S5E3
{
	class MainClass
	{
		public static void Main(string[] args)
		{uint n, i, p;
			
			Console.Write("introduzca el número de pisos que deseas que tenga el árbol : ");
			n =uint.Parse(Console.ReadLine());
			i = 1;
				
			while (i<=n) { 
				while (i<n) {
                    Console.Write(" ");
					i = i + 1;
				}
				p = 2*i-1;
				while (i<=p){
					Console.Write("*");
					i = i + 1;
				}
                    Console.WriteLine(); 
				i = i + 1;
			}
		}
	}
}

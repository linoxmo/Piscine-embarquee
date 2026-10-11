#include <stdio.h>
//#include <stdlib.h>

#define PI 3.14159624

#define MINI(a, b)  a<b ? a : b // mauvaise facon de definir des macros en c! attention a l'ordre des calculs

#define MAXI(a, b)  (((a)>(b)) ? (a) : (b)) // Bonne facon de definir des macros en c! Chaque chiffre est bien entre parenthese

int main(void) {

    printf("%lf\n", PI);
    int x, y, result_1, result_2;
    char c;

    x = 3;
    y = 6;
    c = 'a';
    result_1 = MINI(x,y) + 2;
    result_2 = MAXI(c,y) + 2;

    printf("result_1 == %d\n", result_1);
    printf("result_2 == %d\n", result_2);
}


/* Trois etapes de compilation:
- Le Preprocesseur: Transforme le fichier d'origine en remplancant toutes les instuctions commancant par "#" par autre chose.
On peut observer son travail avec cc/gcc fichier.c -E (compilation jusqu'a l'etape du preprocessing afficher dans le terminal. L'option > fichier.cbis redirige la sortie dans un fichier)
- Le 
*/

/*
Avantage d'une Macro par rapport a une fonction: Pas d'appelle de fonction, sur des fonctions simples, l'appel
de fonction coute plus cher que l'operation. Quand on appel des fonctions, on empile des informations sur la stack.
A la fin de la compilation, on doit depiler la stack, ce qui prends des cycles cpu.   
Deuxieme interet, dans une Macro, il n'y a pas de Typage. 
*/
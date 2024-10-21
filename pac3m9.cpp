#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
vector<string> noms; // Vector global per emmagatzemar els noms de les persones
 
vector<string> frases = {
    "es una persona molt treballadora.",
    "ha fet una feina excel·lent.",
    "té un gran sentit de l'humor.",
    "sempre està disposat a ajudar els altres.",
    "ha demostrat molta dedicació al projecte."
};
 
void addname(const string& name) {
    noms.push_back(name);
}
 
int main() {
    int N;
    cout << "Introdueix la quantitat de processos que vols crear: ";
    cin >> N;
 
    // Inicialitza el generador de nombres aleatoris amb el temps actual com a llavor
    srand(time(0));
 
    for (int i = 0; i < N; ++i) {
        pid_t pid = fork();
 
        if (pid < 0) {  // Si el fork falla
            cerr << "Error en crear el procés." << endl;
            return 1;
        } else if (pid == 0) { // Codi del procés fill
            string nom;
            cout << "Introdueix un nom per al procés " << i + 1 << ": ";
            cin >> nom;
            // Enviar el nom al procés pare a través de la consola
            cout << nom << endl; // Imprimir el nom per que el pare pugui llegir-ho
            exit(0); // El procés fill acaba aquí per evitar executar el codi del pare
        } else { // Codi del procés pare
            wait(NULL); // Espera que acabi el procés fill
            string nom;
            // Llegeix el nom que el fill ha imprès
            cout << "Introdueix el nom per al procés " << i + 1 << ": ";
            cin >> nom;
            // Afegeix el nom al vector global
            addname(nom);
        }
    }
 
    // Triar aleatòriament una persona de l'array de noms i una frase
    if (!noms.empty()) {  // Comprova que l'array de noms no estigui buit
        int idx_nom = rand() % noms.size();  // Selecciona un índex aleatori del vector de noms
        int idx_frase = rand() % frases.size();  // Selecciona un índex aleatori del vector de frases
        cout << "Menció aleatòria: " << noms[idx_nom] << " " << frases[idx_frase] << endl;
    } else {
        cout << "No s'ha pogut generar cap mencio, l'array de noms esta buit." << endl;
    }
 
    return 0; // Finalitza el programa
}
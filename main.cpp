#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


//Punto 1)
const int MAX = 1000;

struct Conductor
{
    int id;
    string nombre;
    string apellido;
    long dni;
    int zona;
};

struct Viaje
{
    string origen;
    string destino;
    long fecha;
    long horaInicio;
    int idConductor;
    float distancia;
    int calificacion;
};

struct ConductorEvaluado //Punto 3)
{
    int id;
    string nombre;
    string apellido;
    float distanciaTotal;
    float indiceCalidad;
    int zona;
};

//Punto 2)
//Busqueda binaria
int buscarConductor(Conductor v[], int n, int idBuscado)
{
    int inicio = 0, fin = n - 1;
    while (inicio <= fin) 
    {
        int medio = inicio + (fin - inicio) / 2;  //Esta formula tambien es valida
        //int medio = (inicio + fin) / 2;  //Esta formula tambien es valida
        //int medio = inicio + (inicio + fin) / 2; //Esta formula no es valida
        if (v[medio].id == idBuscado)
            return medio;
        else if (idBuscado < v[medio].id)
            fin = medio - 1;
        else
            inicio = medio + 1;
    }
    return -1;
}

//Busqueda secuencial
/*
int buscarConductor(Conductor v[], int n, int idBuscado)
{
	int i = 0;
	while(i < n && v[i].id != idBuscado)
		i++;
	return (i < n) ? i : -1;
}
*/

//Punto 3)
void generarVectorEvaluado(Conductor conductores[], int nCond,
                           Viaje viajes[], int nViajes,
                           ConductorEvaluado evaluados[], int& nEval) 
{
    int i = 0, j = 0;
    nEval = 0;
    while (i < nCond) 
    {
        int idActual = conductores[i].id;
        float sumaDistancia = 0, sumaPuntos = 0;
        while (j < nViajes && viajes[j].idConductor < idActual) 
            j++;
        while (j < nViajes && viajes[j].idConductor == idActual) 
        {
            float distancia = viajes[j].distancia;
            int puntos = viajes[j].calificacion;
            sumaDistancia += distancia;
            sumaPuntos += distancia * puntos;
            j++;
        }
        evaluados[nEval].id = conductores[i].id;
        evaluados[nEval].nombre = conductores[i].nombre;
        evaluados[nEval].apellido = conductores[i].apellido;
        evaluados[nEval].distanciaTotal = sumaDistancia;
        evaluados[nEval].indiceCalidad = (sumaDistancia > 0) ? (sumaPuntos / sumaDistancia) : 0;
        evaluados[nEval].zona = conductores[i].zona;
        nEval++;
        i++;
    }
}

//Punto 4)
//Bubble sort mejorado
void ordenarPorZona(ConductorEvaluado v[], int n)
{
    bool intercambio = true;
    int i = 0;

    while (i < n - 1 && intercambio)
    {
        intercambio = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (v[j].zona > v[j + 1].zona)
            {
                ConductorEvaluado temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;

                intercambio = true;
            }
        }
        i++;
    }
}

/*
//Bubble sort
void ordenarPorZona(ConductorEvaluado v[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - 1 - i; j++) 
        {
            if (v[j].zona > v[j + 1].zona) 
            {
                //swap(v[j], v[j + 1]);  //Esto tambien funciona
                ConductorEvaluado temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}
*/


//Punto 5)
void reportePorZona(ConductorEvaluado v[], int n) 
{
    int i = 0;
    string nombresZonas[] = {"Centro", "Norte", "Sur"};
    cout << "Reporte por Zona - Plataforma de Transporte" << endl;
    cout << "===========================================" << endl;

    while (i < n) 
    {
        int zonaActual = v[i].zona;
        float distanciaTotal = 0;
        float sumaIndices = 0;
        int cantidadConductores = 0;

        while (i < n && v[i].zona == zonaActual) 
        {
            distanciaTotal += v[i].distanciaTotal;
            sumaIndices += v[i].indiceCalidad;
            cantidadConductores++;
            i++;
        }
        cout << endl;
        //5.1)
        cout << "Zona " << zonaActual << ": " << nombresZonas[zonaActual - 1] << endl;
        cout << endl;

        //5.2)
        cout << "Total distancia recorrida: " << fixed << setprecision(1) << distanciaTotal << " km" << endl;
        if (cantidadConductores > 0)
        {
            //5.3)
    		float promedioIndice;
        	promedioIndice = sumaIndices / (float)cantidadConductores;
        	cout << "Promedio índice de calidad: " << fixed << setprecision(1) << promedioIndice << endl;
        }
        else
        {
            //5.3)
        	cout << "Promedio índice de calidad: 0.0" << endl;
        }
    }
    cout << endl;
    cout << "===========================================" << endl;
    cout << "Fin del reporte" << endl;
}


void cargarDatos(Conductor conductores[], int& nCond, Viaje viajes[], int& nViajes) 
{
    nCond = 0; 
    nViajes = 0;
    cout << "=== CARGA DE CONDUCTORES ===\n";
    while (true) {
        int id; cout << "ID del conductor (0 para terminar): "; cin >> id;
        if (id == 0) break;
        conductores[nCond].id = id;
        cout << "Nombre: "; cin.ignore(); getline(cin, conductores[nCond].nombre);
        cout << "Apellido: "; getline(cin, conductores[nCond].apellido);
        cout << "DNI: "; cin >> conductores[nCond].dni;
        cout << "Zona (1=Centro, 2=Norte, 3=Sur): "; cin >> conductores[nCond].zona;
        int cantidad; cout << "Cantidad de viajes: "; cin >> cantidad;
        for (int i = 0; i < cantidad; i++) {
            viajes[nViajes].idConductor = id;
            cout << "  Viaje " << (i+1) << " - Origen: "; cin.ignore(); getline(cin, viajes[nViajes].origen);
            cout << "  Destino: "; getline(cin, viajes[nViajes].destino);
            cout << "  Fecha (DDMMAAAA): "; cin >> viajes[nViajes].fecha;
            cout << "  Hora inicio (0-23): "; cin >> viajes[nViajes].horaInicio;
            cout << "  Distancia (km): "; cin >> viajes[nViajes].distancia;
            cout << "  Calificación (1 a 5): "; cin >> viajes[nViajes].calificacion;
            nViajes++;
        }
        nCond++;
    }
}

int main() 
{
    Conductor conductores[MAX];
    Viaje viajes[MAX];
    ConductorEvaluado evaluados[MAX];
    int nCond, nViajes, nEvaluados;
    cargarDatos(conductores, nCond, viajes, nViajes);
    generarVectorEvaluado(conductores, nCond, viajes, nViajes, evaluados, nEvaluados);
    ordenarPorZona(evaluados, nEvaluados);
    reportePorZona(evaluados, nEvaluados);
    return 0;
}
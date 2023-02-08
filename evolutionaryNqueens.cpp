// Solve nquees problem using evolutionary algorithm

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;

#define N 8
#define TABLE N*N
#define POPULATION 25
#define MUTATION_RATE 0.01

struct Individual {
    int cromossome[TABLE];
    int fitnessScore;
};

vector<Individual> population = vector<Individual>(POPULATION);
vector<Individual> newPopulation = vector<Individual>(POPULATION);
vector<Individual> mutatePopulation = vector<Individual>(POPULATION);

int currentNewPopulationCount = 0;
int currentMutatePopulationCount = 0;

int currentGeneration = 0;

bool is_board_valid(vector<Individual> population, int individual) {
    int board[N][N];
    int conflicts = 0;
    //convert to 2D array
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = population[individual].cromossome[i * N + j];
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(board[i][j] == 1) {
                //check row
                for(int k = 0; k < N; k++) {
                    if(k != j && board[i][k] == 1) {
                        conflicts++;
                    }
                }
                //check column
                for(int k = 0; k < N; k++) {
                    if(k != i && board[k][j] == 1) {
                        conflicts++;
                    }
                }
                //check diagonal
                for(int k = 0; k < N; k++) {
                    for(int l = 0; l < N; l++) {
                        if(k != i && l != j && board[k][l] == 1) {
                            if(abs(k - i) == abs(l - j)) {
                                conflicts++;
                            }
                        }
                    }
                }
            }
        }
    }


    return conflicts;
}

void printPopulation() {
    for(int i = 0; i < POPULATION; i++){
        for(int j = 0; j < TABLE; j++){
            cout << population[i].cromossome[j] << " ";
            if(j % N == N - 1){
                cout << endl;
            }
        }

        cout << endl;
        cout << "Fitness: " << population[i].fitnessScore << endl;
        cout << endl;
    }
}

void sortPopulation() {
    for (int i = 0; i < POPULATION; i++) {
        for (int j = i + 1; j < POPULATION; j++) {
            if (population[i].fitnessScore < population[j].fitnessScore) {
                Individual aux = population[i];
                population[i] = population[j];
                population[j] = aux;
            }
        }
    }
}

void sortNewPopulation() {
    for (int i = 0; i < POPULATION; i++) {
        for (int j = i + 1; j < POPULATION; j++) {
            if (newPopulation[i].fitnessScore < newPopulation[j].fitnessScore) {
                Individual aux = newPopulation[i];
                newPopulation[i] = newPopulation[j];
                newPopulation[j] = aux;
            }
        }
    }
}

void sortMutatePopulation() {
    for (int i = 0; i < POPULATION; i++) {
        for (int j = i + 1; j < POPULATION; j++) {
            if (mutatePopulation[i].fitnessScore < mutatePopulation[j].fitnessScore) {
                Individual aux = mutatePopulation[i];
                mutatePopulation[i] = mutatePopulation[j];
                mutatePopulation[j] = aux;
            }
        }
    }
}

int fitness(int individual, vector<Individual> population) {
    int countQueens = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (population[individual].cromossome[i * N + j] == 1) {
                countQueens++;
            }
        }
    }

    int conflicts = is_board_valid(population, individual);
    int fitness = countQueens - conflicts < 0 || countQueens > 8 ? -8 : countQueens - conflicts;
    return fitness;
}

void crossover(int mother, int father) {
    int cutPoint = rand() % N;

    Individual newIndividual = population[mother];

    for (int i = cutPoint; i < TABLE; i++) {
        newIndividual.cromossome[i] = population[father].cromossome[i];
    }

    newPopulation[currentNewPopulationCount] = newIndividual;
    newPopulation[currentNewPopulationCount].fitnessScore = fitness(currentNewPopulationCount, newPopulation);
    currentNewPopulationCount++;
}

void mutate(int individual) {
    Individual newIndividual = newPopulation[individual];

    for(int i = 0; i < TABLE; i++){
        if(rand() % 100 < 5){
            newIndividual.cromossome[i] = newIndividual.cromossome[i] == 1 ? 0 : 1;
        }
    }

    mutatePopulation[individual] = newIndividual;
    newPopulation[currentMutatePopulationCount].fitnessScore = fitness(individual, mutatePopulation);
    currentMutatePopulationCount++;
}

int rouletteSelecion() {
    int sum = 0;

    for(int i = 0; i < POPULATION; i++){
        sum += population[i].fitnessScore;
    }

    int random = rand() % sum;

    for(int i = 0; i < POPULATION; i++){
        if(random < population[i].fitnessScore){
            return i;
        }
        random -= population[i].fitnessScore;
    }

    return rand() % POPULATION;
}

void init() {
    for (int i = 0; i < POPULATION; i++) {
        for (int j = 0; j < N; j++) {
            int random = rand() % N;
            int index = j * N + random;
            population[i].cromossome[index] = 1;
        }
    }

    for (int i = 0; i < POPULATION; i++) {
        population[i].fitnessScore = fitness(i, population);
    }
}

int main() {
    srand(time(NULL));
    init();

    while(100000 > currentGeneration) {
        sortPopulation();

        for(int i = 0; i < 25; i++){
            crossover(rouletteSelecion(), rouletteSelecion());
        }

        for(int i = 0; i < POPULATION; i++){
            if(rand() % 100 < MUTATION_RATE * 100){
                mutate(i);
            }
        }

        currentMutatePopulationCount = 0;
        currentNewPopulationCount = 0;

        for(int i = 0; i < POPULATION; i++){
            population[i].fitnessScore = fitness(i, population);
            newPopulation[i].fitnessScore = fitness(i, newPopulation);
            mutatePopulation[i].fitnessScore = fitness(i, mutatePopulation);

            if(population[i].fitnessScore == 8){
                cout << "Generation: " << currentGeneration << endl;
                printPopulation();
                return 0;
            }
        }

        sortNewPopulation();
        sortPopulation();
        sortMutatePopulation();

        for(int i = 0; i < POPULATION; i++){
            if(i > 10 && i < 20) {
                population[i] = newPopulation[i-10];
            } else if(i >=20) {
                population[i] = mutatePopulation[i-20];
            }
        }

        currentGeneration++;
    }
    
    for(int i = 0; i < POPULATION; i++){
        population[i].fitnessScore = fitness(i, population);
    }

    sortPopulation();
    printPopulation();

    return 0;
}
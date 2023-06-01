#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

vector<float> chegada;
vector<float> duracao;

int tam = 0;

void bubbleSort(int x)
{
    if(x==0)
    {
        // Ordena de maneira crescente de acordo com a chegada
        for (int i = 0; i < tam-1; i++)
        {
            for (int j = 0; j < tam-i-1; j++)
            {
                if (chegada[j] > chegada[j+1])
                {
                    float temp = chegada[j];
                    float temp2 = duracao[j];
                    chegada[j] = chegada[j+1];
                    duracao[j] = duracao[j+1];
                    chegada[j+1] = temp;
                    duracao[j+1] = temp2;
                }
            }
        }
    }
    else
    {
        // Ordena de maneira crescente de acordo com a duracao
        for (int i = 0; i < tam-1; i++)
        {
            for (int j = 0; j < tam-i-1; j++)
            {
                if (duracao[j] > duracao[j+1])
                {
                    float temp = chegada[j];
                    float temp2 = duracao[j];
                    chegada[j] = chegada[j+1];
                    duracao[j] = duracao[j+1];
                    chegada[j+1] = temp;
                    duracao[j+1] = temp2;
                }
            }
        }
    }
}

string fcfs()
{
    float duracaoTotal = 0, tRetornoTotal = 0, tRespostaTotal = 0, tEsperaTotal = 0;
    float aux = 0;
    bool executou = false;
    bool check[tam] = {false};

    for(int i=0; i<tam; i++)
    {
        duracaoTotal += duracao[i];
    }

    // A variável aux representa o instante de execução t
    // Portanto, o while irá de t = aux = 0 até t = duracaoTotal
    while(aux < duracaoTotal)
    {
        for(int i=0; i<tam; i++)
        {
            // Aqui é feita a checagem se o elemento i já chegou no t = aux e se ele ainda não foi executado, por isso a variavel booleana check
            if(chegada[i] <= aux && check[i] == false)
            {
                tRetornoTotal += aux + duracao[i] - chegada[i];
                tRespostaTotal += aux - chegada[i];
                tEsperaTotal += aux - chegada[i];
                aux += duracao[i];
                check[i] = true; // Entrando no if, o check de i se torna verdadeiro e impossibilita uma nova entrada do elemento i nessa condição
                executou = true; // Aqui é feita uma verificação se o if foi executado
                break;
            }
        }
        // Aqui é feita uma verificação se o if anterior foi executado. Caso não tenha sido, significa que a máquina ficou ociosa
        // Logo, é feito um acréscimo no aux e no duracaoTotal para que o programa possa continuar
        if(executou == false)
        {
            aux++;
            duracaoTotal++;
        }
        executou = false;
    }

    // As variáveis ss1, ss2 e ss3 irão guardar o valor das médias do tempo de retorno, de resposta e de espera nessa ordem
    // Elas serão usadas para o retorno da função
    // Para definir a precisão de uma casa decimal, foram usados o fixed e o setprecision(1) da biblioteca iomanip
    stringstream ss1, ss2, ss3;
    ss1 << fixed << setprecision(1) << tRetornoTotal/tam;
    ss2 << fixed << setprecision(1) << tRespostaTotal/tam;
    ss3 << fixed << setprecision(1) << tEsperaTotal/tam;

    return "FCFS " + ss1.str() + " " + ss2.str() + " " + ss3.str();
}

string sjf()
{
    // A função sjf() funciona de maneira similar à função fcfs()

    float duracaoTotal = 0, tRetornoTotal = 0, tRespostaTotal = 0, tEsperaTotal = 0;
    float aux = 0;
    bool executou = false;
    bool check[tam] = {false};

    for(int i=0; i<tam; i++)
    {
        duracaoTotal += duracao[i];
    }

    while(aux < duracaoTotal)
    {
        for(int i = 0; i < tam; i++)
        {
            if(chegada[i] <= aux && check[i] == false)
            {
                tRetornoTotal += aux + duracao[i] - chegada[i];
                tRespostaTotal += aux - chegada[i];
                tEsperaTotal += aux - chegada[i];
                aux += duracao[i];
                check[i] = true;
                executou = true;
                break;
            }
        }
        if(executou == false)
        {
            aux++;
            duracaoTotal++;
        }
        executou = false;
    }

    stringstream ss1, ss2, ss3;
    ss1 << fixed << setprecision(1) << tRetornoTotal/tam;
    ss2 << fixed << setprecision(1) << tRespostaTotal/tam;
    ss3 << fixed << setprecision(1) << tEsperaTotal/tam;

    return "SJF " + ss1.str() + " " + ss2.str() + " " + ss3.str();
}

string rr()
{
    vector<float> fila;
    float duracaoTotal = 0, tRetornoTotal = 0, tRespostaTotal = 0, tEsperaTotal = 0;
    int aux = 0, contFila = 0;

    typedef struct
    {
        float tDuracaoRestante;
        float tRetorno = 0;
        float tResposta = 0;
        float tEmExecucao = 0;
        float quantum = 2;
        bool estaNaFila = false;
        bool primeiraExecucao = true;
        bool encerrou = false;
    } tempo[tam];
    tempo t;

    for(int i=0; i<tam; i++)
    {
        t[i].tDuracaoRestante = duracao[i];
        duracaoTotal += duracao[i];
    }

    while(aux < duracaoTotal)
    {
        for(int i = 0; i < tam; i++)
        {
            // Aqui se checa se algum processo entra em t = aux e se ele ainda não entrou na fila para que seja adicionado
            if(chegada[i] == aux && t[i].estaNaFila == false)
            {
                fila.push_back(i);
                t[i].estaNaFila = true;
            }
        }
        for(int i = 0; i < tam; i++)
        {
            // Aqui é feita a checagem se o processo da vez zerou o quantum
            if(t[i].quantum == 0 && i == fila[contFila])
            {
                contFila++; // Caso tenha zerado, a fila anda
                // Aqui é feita a checagem se o elemento i ainda tem tempo de duração para gastar. Caso tenha, ele retorna à fila
                if(t[i].tDuracaoRestante > 0)
                {
                    fila.push_back(i);
                    t[i].estaNaFila = true;
                    // O quantum precisa ser reestabelecido, porém é preciso verificar quanto tempo de duração restante ainda falta
                    if(t[i].tDuracaoRestante >= 2)
                    {
                        t[i].quantum = 2;
                    }
                    else
                    {
                        t[i].quantum = 1;
                    }
                }
            }
        }
        // Caso a fila esteja vazia, significa que máquina está ociosa, logo aux e duracaoTotal são incrementados para que o programa possa continuar
        // Do contrário, segue para a execução normal
        if(fila.empty())
        {
            aux++;
            duracaoTotal++;
        }
        else
        {
            for(int i = 0; i < tam; i++)
            {
                // Entra na execução o elemento que tem a vez na fila, cuja duração restante e quantum ainda não terminaram
                if(i == fila[contFila] && t[i].tDuracaoRestante > 0 && t[i].quantum > 0)
                {
                    t[i].estaNaFila = false;

                    // A variável booleana primeiraExecucao serve para marcar o momento em que o elemento i entra pela primeira vez em execução
                    if(t[i].primeiraExecucao == true)
                    {
                        t[i].tResposta = aux; // tResposta captura o valor do tempo de resposta t = aux
                        t[i].primeiraExecucao = false; // A variável primeiraExecucao se torna falsa para não entrar mais nessa condição
                    }
                    t[i].tDuracaoRestante--;
                    // Aqui o if é utilizado para checar se o tempo de duração restante chegou a zero
                    if(t[i].tDuracaoRestante == 0)
                    {
                        t[i].tRetorno = aux+1; // Caso tenha chego a zero, o tempo de retorno guarda o instante
                        t[i].encerrou = true; // A variável booleana encerrou do elemento i se torna verdadeira para que ela não entre na fila novamente
                    }
                    t[i].quantum--;
                    t[i].tEmExecucao++; // O tempo em execução do elemento i é incrimentado para fins de cálculo ao fim do programa
                    aux++;
                }
            }
        }
    }

    for(int i=0; i<tam; i++)
    {
        tRetornoTotal += (t[i].tRetorno - chegada[i]);
        tRespostaTotal += (t[i].tResposta - chegada[i]);
        tEsperaTotal += (t[i].tRetorno - t[i].tEmExecucao - chegada[i]);
    }

    stringstream ss1, ss2, ss3;
    ss1 << fixed << setprecision(1) << tRetornoTotal/tam;
    ss2 << fixed << setprecision(1) << tRespostaTotal/tam;
    ss3 << fixed << setprecision(1) << tEsperaTotal/tam;

    return "RR " + ss1.str() + " " + ss2.str() + " " + ss3.str();
}

int main()
{
    ifstream arq;
    string linha, saidaFCFS, saidaSJF, saidaRR;

    arq.open("entrada.txt");

    while(getline(arq, linha))
    {
        size_t pos = linha.find(" "); // Identifica a posição do espaço
        chegada.push_back(stoi(linha.substr(0, pos))); // Salva na variável chegada do vector o valor até a posição do espaço
        duracao.push_back(stoi(linha.substr(pos + 1))); // Salva na variável duracao do vector o valor após a posição do espaço
    }

    arq.close();

    tam = chegada.size(); // Variável global para quantidade de elementos

    bubbleSort(0); // Aqui é chamada a função bubbleSort, responsável pela ordenação. Passando 0 como parâmetro, a ordenação é pela chegada
    saidaFCFS = fcfs();
    saidaRR = rr();
    bubbleSort(1); // Aqui é chamada a função bubbleSort novamente. Passando qualquer valor como parâmetro, a ordenação é pela duração
    saidaSJF = sjf();

    cout << saidaFCFS << endl << saidaSJF << endl << saidaRR << endl;

    return 0;
}

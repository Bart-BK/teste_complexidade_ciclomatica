/* --------------------------------------------------------------------------- */
/*
    CODIFICAÇÃO INICIAL: Phillipe Kramer, Eva Maia, Sérgio Fred
    CORREÇÃO E MELHORAMENTO: Prabhát Kumar de Oliveira, Eberty Alves dos Santos
	ORITENTAÇÃO: Sérgio Fred
	Data da codificação inicial: julho-agosto/2017
    Data da correção: dezembro-janeiro/2018
    Versão: 1.1 alpha

RESTRIÇÕES DE USO DA FERRAMENTA
1 - O CÓDIGO DEVE ESTAR ESCRITO DE FORMA CORRETA
2 - DEVE ESTAR COMPLETAMENTE INDENTADO SEGUINDO O MODELO:
         if(){
         }
         else(){
         }
         while(){
         }
         for(){
     }
*/
/* --------------------------------------------------------------------------- */
 
 
/* --------------------------------------------------------------------------- */
#include <vcl.h>
#include <iostream>
#include "projeto_Prabhat_e_Eberty.h"

/* --------------------------------------------------------------------------- */
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"

/* --------------------------------------------------------------------------- */
TForm1 *Form1;
int k = 0;
int flagMain = 0;

/* Estrutura de dados responsável por armazenar o nó em que ocorre alguma abertura de chaves
    seu tipo pode ser: L - loop , F - false , I - IF , E - Else */
typedef struct {
    int no;
    char tipo;
} Tchave;

/* Estrutura de dados responsável por armazenar uma aresta, sendo pai o nó de origem e filho o nó de destino dessa aresta */
typedef struct {
    int pai;
    int filho;
} Taresta;

/* --------------------------------------------------------------------------- */
Tchave chaves[100];
Taresta arestas[100];
int nos[100];
int pai = 0;
int count = 0, count_ar = 0;
int topo = -1;
char loop = 'F';
int **adj;


/* --------------------------------------------------------------------------- */
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
    // Necessário para inicialização do form
}


/* --------------------------------------------------------------------------- */
void __fastcall TForm1::FormCreate(TObject *Sender) {
    //FILE *arq;
    ClientDataSet1->Open();
    ClientDataSet1->First();
    if (FileExists(ExtractFilePath(ParamStr(0)) + "dados.xml")) {
        ClientDataSet1->LoadFromFile("dados.xml");
    } else {
        //arq = fopen(ExtractFilePath(ParamStr(0))+"dados.xml", "w");
        ShowMessage("Não há base de dados criada...");
    }

    Memo1->Text = ClientDataSet1Programa->Value;
    init();

}

/* --------------------------------------------------------------------------- */
/* Método para ação do botão "anterior" */
void __fastcall TForm1::Button1Click(TObject *Sender) {
    ClientDataSet1->Prior();
    Memo1->Text = ClientDataSet1Programa->Value;
}

/* --------------------------------------------------------------------------- */
/* Método para ação do botão "próximo" */
void __fastcall TForm1::Button2Click(TObject *Sender) {
    ClientDataSet1->Next();
    Memo1->Text = ClientDataSet1Programa->Value;
}

/* --------------------------------------------------------------------------- */
/* Método para ação do botão "Deletar"  */
void __fastcall TForm1::Button4Click(TObject *Sender) {
    ClientDataSet1->Delete();
    ShowMessage("Programa deletado...");
}

/* --------------------------------------------------------------------------- */
/* Método para ação do botão "Salvar" */
void __fastcall TForm1::Button3Click(TObject *Sender) {
    ClientDataSet1->Edit();
    ClientDataSet1Programa->Value = Memo1->Text;
    ClientDataSet1->SaveToFile("dados.xml", dfXML);
    ShowMessage("Programa ou edição salvos com sucesso !!!");
}

/* --------------------------------------------------------------------------- */
/* Método responsável por atualizar os dados no Memo1 sempre que um célula for clicada */
void __fastcall TForm1::DBGrid1CellClick(TColumn *Column) {
    Memo1->Text = ClientDataSet1Programa->Value;
}

/* Método responsável por adicionar um novo Nó no vetor de global de Nós e incrementar o contador
    de nós, o contandor de nós sempre ficará uma unidade acima do ultimo nó adicionado no vetor. */
void add_no() {
    nos[count] = count;
    count++;
}

/* Este método irá adiconar na pilha de "chaves" o nó em que houve a ocorrencia de uma abertura
    de chave e o tipo dessa abertura, se foi um if, while, for, else... Sendo assim teremos sempre
    no topo da pilha a ultima chave aberta, que deverá ser a primeira a ser fechada. */
void add_chaves() {
    topo++;
    chaves[topo].no = count - 1;
    chaves[topo].tipo = loop;
    loop = 'F';
}

/* Este método adiciona no vetor de estruturas aresta, qual o nó originou e qual é o nó de destino
    dessa aresta, aumentando o contador de arestas e definindo que o novo pai é o nó atual(count-1) */
void add_aresta(int no_pai, int filho) {
    arestas[count_ar].pai = no_pai;
    arestas[count_ar].filho = filho;
    pai = count - 1;
    count_ar++;
}

/* Quando esse método é chamado, é verificado primeiramente se o topo não está nulo, ou seja, não há nenhuma
    chave aberta. Caso exista alguma chave aberta, o metodo irá no topo da pilha e verá qual nó originou essa chave
    juntamente com o tipo desse nó(while,for,else,nenhum), tomando uma decisão diferente para cada tipo. No final o
    topo é decrementado pois a chave foi removida e o topo passa a ter a chave mais interna após a que foi fechada. */
void removeChave() {
    if (topo != -1) {
        loop = chaves[topo].tipo;
        if (loop == 'L') {
            pai = count - 1;
            add_aresta(pai, chaves[topo].no);
            pai = chaves[topo].no;
        } else if (loop == 'I') {
            pai = count - 1;
            add_aresta(pai, count);
            pai = chaves[topo].no;

        } else if (loop == 'E') {
            pai = chaves[topo].no - 1;
            add_aresta(pai, count);
            pai = count - 1;
        }
        topo--;
    }
}

/* Este método adiciona um nó simples que não possui nenhum tipo de bifurcação no grafo. */
void simple_node() {
    add_no();
    add_aresta(pai, count - 1);
}

/* Este método faz as verificações necessárias para a insersão de um nó no grafo
    caso ele não esteja fechando uma chave e o topo seja 0, ele está nó main, que é o nó
    simples de inicio. Caso esteja fechando uma chave é feito um conjunto de procedimentos,
    caso não, outro conjunto. */
void insertNode(AnsiString str) {
    if (str == '}' && chaves[topo].no == 0) {
        simple_node();
    } else if (str == '}') {
        removeChave();
        add_no();
        add_aresta(pai, count - 1);
    } else {
        add_no();
        add_aresta(pai, count - 1);
        add_chaves();
    }
}

/* Este método verifica a situação de quando existe um else no grafo pois o else não pode ser
    executado caso o if seja verdeiro.  */
void add_else(AnsiString str) {
    removeChave();
    count_ar--;
    add_no();
    add_aresta(pai, count - 1);
    loop = 'E';
    add_chaves();
}

/* Método que lê o memo com o código a ser processado e excuta chamadas a funções de acordo com o que foi lido. */
void processo(TMemo *Memo1) {
    flagMain = 0;
    Memo1->Lines->Strings[0];
    AnsiString str;
    for (int i = 0; i < Memo1->Lines->Count; i++) {
        str = Memo1->Lines->Strings[i];
        AnsiString s_main;
        s_main = str.SubString(str.Pos("main"), 4); // ENCONTRA O main e começa a contar daqui
        if (CompareStr(" main ", str.SubString(str.Pos(" main "), 6)) == 0 || 
        CompareStr("main ", str.SubString(str.Pos("main "), 5)) == 0 || 
        CompareStr("main(", str.SubString(str.Pos("main("), 5)) == 0) {
            k = i;
            flagMain = 1;
            add_no();
            add_chaves();
            break;
        }
        
    }

    // Se não encontrou main, então estamos analisando apenas uma função
    if(flagMain == 0){
        for (int i = 0; i < Memo1->Lines->Count; i++) {
            str = Memo1->Lines->Strings[i];
            if (CompareStr("){", str.SubString(str.Pos("){"), 2)) == 0 || 
            CompareStr(") {", str.SubString(str.Pos(") {"), 3)) == 0) {
                k = i;
                add_no();
                add_chaves();
                break;
            } 
        }
    }

    for (int i = k; i < Memo1->Lines->Count; i++) { // até a última linha do Memo1
        str = Memo1->Lines->Strings[i];
        AnsiString str_while, str_for, str_if, str_ch, str_main;
        // str_while = str.SubString(str.Pos("while"), 5); // caso seja while indica o comando e a linha
        if (CompareStr(" while(", str.SubString(str.Pos("while(") -1, 7)) == 0 ||
            CompareStr(" while ", str.SubString(str.Pos("while ") -1, 7)) == 0 ||
            CompareStr("\twhile(", str.SubString(str.Pos("while(") -1, 7)) == 0 ||
            CompareStr("\twhile ", str.SubString(str.Pos("while ") -1, 7)) == 0) {
            loop = 'L';
            insertNode("while");
        } else {
            // str_for = str.SubString(str.Pos("for"), 3); // caso seja for indica o comando e a linha
            if (CompareStr(" for(", str.SubString(str.Pos("for(") -1, 5)) == 0 ||
                CompareStr(" for ", str.SubString(str.Pos("for ") -1, 5)) == 0 ||
                CompareStr("\tfor(", str.SubString(str.Pos("for(") -1, 5)) == 0 ||
                CompareStr("\tfor ", str.SubString(str.Pos("for ") -1, 5)) == 0) {
                loop = 'L';
                insertNode("for");
            } else {
                // str_if = str.SubString(str.Pos("if"), 2); // caso seja if indica o comando e a linha
                if (CompareStr(" if(", str.SubString(str.Pos("if(") -1, 4)) == 0 ||
                    CompareStr(" if ", str.SubString(str.Pos("if ") -1, 4)) == 0 ||
                    CompareStr("\tif(", str.SubString(str.Pos("if(") -1, 4)) == 0 ||
                    CompareStr("\tif ", str.SubString(str.Pos("if ") -1, 4)) == 0) {
                    loop = 'I';
                    insertNode("if");
                } else {

                    // str_ch = str.SubString(str.Pos("}else"), 5); // caso seja }else indica o comando e a linha
                    if (CompareStr(" else{", str.SubString(str.Pos("else{") -1, 6)) == 0 ||
                        CompareStr(" else ", str.SubString(str.Pos("else ") -1, 6)) == 0 ||
                        CompareStr("\telse{", str.SubString(str.Pos("else{") -1, 6)) == 0 ||
                        CompareStr("\telse ", str.SubString(str.Pos("else ") -1, 6)) == 0 ||
                        CompareStr("}else{", str.SubString(str.Pos("}else{"), 6)) == 0 ||
                        CompareStr("}else ", str.SubString(str.Pos("}else "), 6)) == 0) {
                        add_else("else");

                    } else {
                        // str_ch = str.SubString(str.Pos('}'), 1); // caso seja } indica o comando e a linha
                        if (CompareStr('}', str.SubString(str.Pos('}'), 1)) == 0) {
                            insertNode("}");
                        } else {
                            simple_node();
                        }
                    }
                }
            }
        }
    }
}

/* Método responsável por criar a matriz de adjacência, incialmente nula de Ordem sendo o número
    de nós no vetor em seguida, percorre-se o vetor de arestas adicionando as adjacências na matriz. */
void TForm1::criarMatriz(int size) {
    adj = (int **) malloc(size * sizeof (int*));
    for (int i = 0; i < size; i++) {
        adj[i] = (int *) malloc(size * sizeof (int));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < count_ar; i++) {
        adj[arestas[i].pai][arestas[i].filho] = 1;
    }
    print_matrix(size);
}

/* Carregamento de itens de interface */
void TForm1::carregaResultado() {
    Memo1->Hide();
    DBGrid1->Hide();
    Programa->Hide();
    ProgressBar1->Show();
    ProgressBar1->Position = 100;
    Button6->Show();
}

/* Calcula a complexidade cilcomática do código a partir da funçao A-N+2 */
int calculaComplexidade(int nos, int arestas) {
    return arestas - nos + 2;
}

/* Reinicia os valores para ser possivel uma nova consulta */
void resetaValores() {
    pai = 0, count = 0, count_ar = 0, topo = -1, loop = 'F';
}

/* Imprime todas as linhas e colunas da matriz de adjacência. */
void TForm1::print_matrix(int size) {
    AnsiString msg = "";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            msg += "  " + IntToStr(adj[i][j]);
        }
        Memo3->Lines->Add(msg);
        msg = "";
    }
}

/* Imprime todas os nós do grafo */
void TForm1::print_nos() {
    AnsiString msg;
    for (int i = 0; i < count; i++) {
        msg += IntToStr(nos[i]) + ", ";
    }
    Edit3->Text = msg;
}

/* Imprime todas as arestas do grafo */
void TForm1::print_arestas() {
    AnsiString msg;
    for (int i = 0; i < count_ar; i++) {
        msg += "[" + IntToStr(arestas[i].pai) + "," + IntToStr(arestas[i].filho) + "], ";
    }
    Edit4->Text = msg;
}

/* Calcula o risco do programa de acordo com o resultado da complexidade ciclomatica  */
void TForm1::calcula_risco(int complexidade) {
    if (complexidade >= 1 || complexidade <= 10) {
        Edit2->Text = "Método simples. Baixo risco.";
    } else if (complexidade >= 11 || complexidade <= 20) {
        Edit2->Text = "Método razoavelmente complexo. Moderado risco.";
    } else if (complexidade >= 21 || complexidade <= 50) {
        Edit2->Text = "Método muito complexo. Elevado risco.";
    } else if (complexidade >= 51) {
        Edit2->Text = "Método de altíssimo risco e bastante instável.";
    }
}

/* Carregamento de itens de interface  */
void __fastcall TForm1::Button5Click(TObject *Sender) {
    // Botão Analisar
    resetaValores();
    processo(Memo1);
    criarMatriz(count);
    carregaResultado();

    calcula_risco(calculaComplexidade(count, count_ar));
    Edit1->Text = calculaComplexidade(count, count_ar);

    print_nos();
    print_arestas();

    Button1->Enabled = false;
    Button2->Enabled = false;
    Button3->Enabled = false;
    Button4->Enabled = false;
    Button5->Enabled = false;
}

void __fastcall TForm1::Button6Click(TObject *Sender) {
    // Botão de Ver resultado
    ProgressBar1->Hide();
    Button6->Hide();
    Label1->Visible = true;
    Label2->Visible = true;
    Memo3->Visible = true;
    Label3->Visible = true;
    Label4->Visible = true;
    Edit1->Visible = true;
    Edit2->Visible = true;
    Button7->Visible = true;
    Edit3->Visible = true;
    Edit4->Visible = true;
    Label5->Visible = true;
    Label6->Visible = true;
}

void __fastcall TForm1::Button7Click(TObject *Sender) {
    //Botão voltar
    Label1->Visible = false;
    Label2->Visible = false;
    Memo3->Visible = false;
    Label3->Visible = false;
    Label4->Visible = false;
    Edit1->Visible = false;
    Edit2->Visible = false;
    Button7->Visible = false;

    Edit3->Visible = false;
    Edit4->Visible = false;
    Label5->Visible = false;
    Label6->Visible = false;

    enable_inicio();

    Memo3->Text = "";

    Button1->Enabled = true;
    Button2->Enabled = true;
    Button3->Enabled = true;
    Button4->Enabled = true;
    Button5->Enabled = true;
}

/* Carregamento de itens de interface */
void TForm1::enable_inicio() {
    Programa->Visible = true;
    Memo1->Visible = true;
    DBGrid1->Visible = true;
    ProgressBar1->Position = 0;
}

/* Carregamento de itens de interface */
void TForm1::init() {
    ProgressBar1->Visible = false;
    DBGrid1->Height = 321;
    DBGrid1->Width = 231;
    Button6->Visible = false;
    Label1->Visible = false;
    Label2->Visible = false;
    Memo3->Visible = false;
    Label3->Visible = false;
    Label4->Visible = false;
    Edit1->Visible = false;
    Edit2->Visible = false;
    Button7->Visible = false;
    Edit3->Visible = false;
    Edit4->Visible = false;
    Label5->Visible = false;
    Label6->Visible = false;
}

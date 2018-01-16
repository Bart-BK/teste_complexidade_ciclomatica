//---------------------------------------------------------------------------

#ifndef projeto_Prabhat_e_Eberty
#define projeto_Prabhat_e_Eberty
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Data.DB.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

class TForm1 : public TForm {
__published: // IDE-managed Components
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    TButton *Button4;
    TMemo *Memo1;
    TLabel *Programa;
    TDBGrid *DBGrid1;
    TDataSource *DataSource1;
    TClientDataSet *ClientDataSet1;
    TAutoIncField *ClientDataSet1Id;
    TStringField *ClientDataSet1Descricao;
    TMemoField *ClientDataSet1Programa;
    TButton *Button5;
    TProgressBar *ProgressBar1;
    TButton *Button6;
    TMemo *Memo3;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *Edit1;
    TEdit *Edit2;
    TButton *Button7;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *Edit3;
    TEdit *Edit4;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall DBGrid1CellClick(TColumn *Column);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
private: // User declarations
public: // User declarations
    __fastcall TForm1(TComponent* Owner);
    void carregaResultado();
    void criarMatriz(int size);
    void print_nos();
    void print_arestas();
    void print_matrix(int size);
    void calcula_risco(int complexidade);
    void enable_inicio();
    void init();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

object Form1: TForm1
  Left = 0
  Top = 0
  ActiveControl = Button1
  Caption = 'Teste De Software'
  ClientHeight = 554
  ClientWidth = 876
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Programa: TLabel
    Left = 274
    Top = 80
    Width = 46
    Height = 13
    Caption = 'Programa'
  end
  object Label1: TLabel
    Left = 83
    Top = 84
    Width = 185
    Height = 19
    Caption = 'Complexidade Ciclom'#225'tica'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 496
    Top = 84
    Width = 145
    Height = 19
    Caption = 'Matriz de Adjac'#234'ncia'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 83
    Top = 123
    Width = 139
    Height = 16
    Caption = 'Complexidade do c'#243'digo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 18
    Top = 403
    Width = 79
    Height = 16
    Caption = 'N'#237'vel de Risco'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 17
    Top = 446
    Width = 21
    Height = 16
    Caption = 'N'#243's'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 17
    Top = 490
    Width = 43
    Height = 16
    Caption = 'Arestas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object DBGrid1: TDBGrid
    Left = 18
    Top = 80
    Width = 47
    Height = 49
    DataSource = DataSource1
    TabOrder = 5
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = DBGrid1CellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'Id'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Descricao'
        Visible = True
      end>
  end
  object Button1: TButton
    Left = 18
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Anterior'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 99
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Pr'#243'ximo'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 180
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Salvar'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 261
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Deletar'
    TabOrder = 3
    OnClick = Button4Click
  end
  object Memo1: TMemo
    Left = 274
    Top = 99
    Width = 479
    Height = 302
    TabOrder = 4
  end
  object Button5: TButton
    Left = 342
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Analisar'
    TabOrder = 6
    OnClick = Button5Click
  end
  object ProgressBar1: TProgressBar
    Left = 123
    Top = 200
    Width = 550
    Height = 33
    TabOrder = 7
  end
  object Button6: TButton
    Left = 342
    Top = 256
    Width = 75
    Height = 25
    Caption = 'Ver resultado'
    TabOrder = 8
    OnClick = Button6Click
  end
  object Memo3: TMemo
    Left = 496
    Top = 122
    Width = 289
    Height = 279
    TabOrder = 9
  end
  object Edit1: TEdit
    Left = 83
    Top = 145
    Width = 38
    Height = 21
    TabOrder = 10
  end
  object Edit2: TEdit
    Left = 18
    Top = 425
    Width = 302
    Height = 21
    TabOrder = 11
  end
  object Button7: TButton
    Left = 694
    Top = 412
    Width = 75
    Height = 25
    Caption = 'Voltar'
    TabOrder = 12
    OnClick = Button7Click
  end
  object Edit3: TEdit
    Left = 17
    Top = 468
    Width = 832
    Height = 21
    TabOrder = 13
  end
  object Edit4: TEdit
    Left = 17
    Top = 512
    Width = 832
    Height = 21
    TabOrder = 14
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 656
    Top = 8
  end
  object ClientDataSet1: TClientDataSet
    PersistDataPacket.Data = {
      920000009619E0BD010000001800000003000000000003000000920002496404
      0001000200010007535542545950450200490008004175746F696E6300094465
      7363726963616F01004900000001000557494454480200020014000850726F67
      72616D6104004B00000001000753554254595045020049000500546578740001
      000C4155544F494E4356414C55450400010001000000}
    Active = True
    Aggregates = <>
    Params = <>
    Left = 712
    Top = 8
    object ClientDataSet1Id: TAutoIncField
      FieldName = 'Id'
    end
    object ClientDataSet1Descricao: TStringField
      FieldName = 'Descricao'
    end
    object ClientDataSet1Programa: TMemoField
      FieldName = 'Programa'
      BlobType = ftMemo
    end
  end
end

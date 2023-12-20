object FdodavanjeNadzor: TFdodavanjeNadzor
  Left = 0
  Top = 0
  Caption = 'FdodavanjeNadzor'
  ClientHeight = 177
  ClientWidth = 494
  Color = clBtnFace
  DragKind = dkDock
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Lprezime: TLabel
    Left = 40
    Top = 78
    Width = 37
    Height = 13
    Caption = 'prezime'
  end
  object Lime: TLabel
    Left = 40
    Top = 19
    Width = 16
    Height = 13
    Caption = 'ime'
  end
  object Lvrijeme: TLabel
    Left = 40
    Top = 131
    Width = 35
    Height = 13
    Caption = 'vrijeme'
  end
  object Eprezime: TEdit
    Left = 128
    Top = 75
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object Eime: TEdit
    Left = 128
    Top = 16
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object BpotvrdiN: TButton
    Left = 368
    Top = 126
    Width = 75
    Height = 25
    Caption = 'potvrdi'
    TabOrder = 2
    OnClick = BpotvrdiNClick
  end
  object Evrijeme: TEdit
    Left = 128
    Top = 128
    Width = 121
    Height = 21
    TabOrder = 3
  end
end

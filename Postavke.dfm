object FPostavke: TFPostavke
  Left = 0
  Top = 0
  Caption = 'Postavke'
  ClientHeight = 149
  ClientWidth = 351
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 24
    Width = 103
    Height = 13
    Caption = 'Izaberite zeljeni font:'
  end
  object Label2: TLabel
    Left = 32
    Top = 64
    Width = 64
    Height = 13
    Caption = 'Velicina fonta'
  end
  object CBFont: TComboBox
    Left = 184
    Top = 21
    Width = 145
    Height = 21
    TabOrder = 0
    Items.Strings = (
      'Arial'
      'Calibri'
      'Times New Roman')
  end
  object EVelicinaFonta: TEdit
    Left = 184
    Top = 61
    Width = 145
    Height = 21
    TabOrder = 1
  end
  object BSpremi: TButton
    Left = 268
    Top = 116
    Width = 75
    Height = 25
    Caption = 'Spremi'
    TabOrder = 2
    OnClick = BSpremiClick
  end
  object BPromjeniBoju: TButton
    Left = 176
    Top = 116
    Width = 86
    Height = 25
    Caption = 'Promjeni Boju'
    TabOrder = 3
    OnClick = BPromjeniBojuClick
  end
  object ColorDialog1: TColorDialog
    Left = 80
    Top = 104
  end
end

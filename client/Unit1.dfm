object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 378
  ClientWidth = 883
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 24
    Top = 189
    Width = 190
    Height = 13
    Caption = 'Va'#353'e posu'#273'enje knjige i datum vra'#263'anja'
  end
  object Memo1: TMemo
    Left = 24
    Top = 208
    Width = 345
    Height = 113
    Lines.Strings = (
      '')
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 16
    Width = 345
    Height = 153
    Caption = 'Upi'#353'ite va'#353'e podatke'
    TabOrder = 1
    object Label1: TLabel
      Left = 32
      Top = 35
      Width = 16
      Height = 13
      Caption = 'ime'
    end
    object Label2: TLabel
      Left = 32
      Top = 75
      Width = 37
      Height = 13
      Caption = 'prezime'
    end
    object Label3: TLabel
      Left = 32
      Top = 110
      Width = 21
      Height = 13
      Caption = 'sifra'
    end
    object Eime: TEdit
      Left = 112
      Top = 32
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object Eprezime: TEdit
      Left = 112
      Top = 72
      Width = 121
      Height = 21
      TabOrder = 1
    end
    object Esifra: TEdit
      Left = 112
      Top = 107
      Width = 121
      Height = 21
      TabOrder = 2
    end
    object Button1: TButton
      Left = 262
      Top = 105
      Width = 75
      Height = 25
      Caption = 'Posalji'
      TabOrder = 3
      OnClick = Button1Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 424
    Top = 75
    Width = 313
    Height = 186
    Caption = 'Pretra'#382'ite knjige po autoru'
    TabOrder = 2
    object Button2: TButton
      Left = 166
      Top = 30
      Width = 75
      Height = 25
      Caption = 'Pretrazi'
      TabOrder = 0
      OnClick = Button2Click
    end
    object Eautor: TEdit
      Left = 16
      Top = 32
      Width = 121
      Height = 21
      TabOrder = 1
    end
    object Memo2: TMemo
      Left = 16
      Top = 72
      Width = 225
      Height = 89
      TabOrder = 2
    end
  end
  object BgeneriranjeKljuceva: TButton
    Left = 24
    Top = 327
    Width = 190
    Height = 25
    Caption = 'GeneriranjeKljuceva'
    TabOrder = 3
    OnClick = BgeneriranjeKljucevaClick
  end
  object BposaljiKljuceve: TButton
    Left = 256
    Top = 327
    Width = 105
    Height = 25
    Caption = 'PosaljiKljuceve'
    TabOrder = 4
    OnClick = BposaljiKljuceveClick
  end
  object ComboBox1: TComboBox
    Left = 424
    Top = 16
    Width = 65
    Height = 21
    ItemIndex = 1
    TabOrder = 5
    Text = 'HR'
    OnChange = ComboBox1Change
    Items.Strings = (
      'EN'
      'HR')
  end
  object TCP_klijent: TIdTCPClient
    ConnectTimeout = 0
    Host = '127.0.0.1'
    Port = 4321
    ReadTimeout = -1
    Left = 104
    Top = 248
  end
  object UDP_klijent: TIdUDPClient
    Host = '127.0.0.1'
    Port = 5555
    Left = 488
    Top = 168
  end
  object Codec1: TCodec
    AsymetricKeySizeInBits = 1024
    AdvancedOptions2 = []
    CryptoLibrary = CryptographicLibrary1
    Left = 560
    Top = 168
    StreamCipherId = 'native.StreamToBlock'
    BlockCipherId = 'native.AES-128'
    ChainId = 'native.CBC'
  end
  object CryptographicLibrary1: TCryptographicLibrary
    Left = 512
    Top = 288
  end
  object ACodec: TCodec
    AsymetricKeySizeInBits = 1024
    AdvancedOptions2 = []
    CryptoLibrary = CryptographicLibrary1
    Left = 168
    Top = 248
    StreamCipherId = 'native.RSA'
    BlockCipherId = ''
    ChainId = 'native.CBC'
  end
  object Signatory1: TSignatory
    Codec = ACodec
    Left = 232
    Top = 248
  end
end

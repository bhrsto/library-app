object MainForm: TMainForm
  Left = 0
  Top = 0
  ActiveControl = BRegistracijaZ
  Caption = 'MainForm'
  ClientHeight = 665
  ClientWidth = 1231
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object LimePrezime: TLabel
    Left = 80
    Top = 24
    Width = 19
    Height = 13
    Caption = 'test'
  end
  object LabelPostotak: TLabel
    Left = 1053
    Top = 83
    Width = 67
    Height = 13
    Caption = 'LabelPostotak'
  end
  object LKorisnik: TLabel
    Left = 24
    Top = 24
    Width = 40
    Height = 13
    Caption = 'Korisnik:'
  end
  object SekcijaRegistracijaZaposlenika: TGroupBox
    Left = 337
    Top = 56
    Width = 264
    Height = 113
    Caption = 'Ragistracija i ure'#273'ivanje zaposlenika'
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 0
    object BRegistracijaZ: TButton
      Left = 16
      Top = 64
      Width = 75
      Height = 25
      Caption = 'Registracija'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = BRegistracijaZClick
    end
  end
  object GBIzvjestaj: TGroupBox
    Left = 24
    Top = 175
    Width = 505
    Height = 201
    Caption = 'Generiranje izvje'#353'taja po klijentu'
    TabOrder = 1
    object BIzvjestaj: TButton
      Left = 56
      Top = 56
      Width = 75
      Height = 25
      Caption = 'Izvjestaj'
      TabOrder = 0
      OnClick = BIzvjestajClick
    end
    object BPrikaziIzvjestaj: TButton
      Left = 56
      Top = 104
      Width = 75
      Height = 25
      Caption = 'Prikazi'
      TabOrder = 1
      OnClick = BPrikaziIzvjestajClick
    end
  end
  object BPostavke: TButton
    Left = 918
    Top = 576
    Width = 75
    Height = 25
    Caption = 'Postavke'
    TabOrder = 2
    OnClick = BPostavkeClick
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 56
    Width = 265
    Height = 113
    Caption = 'Ragistracija i ure'#273'ivanje korisnika'
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 3
    object BRegistracijaK: TButton
      Left = 16
      Top = 40
      Width = 75
      Height = 25
      Caption = 'Registracija'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = BRegistracijaKClick
    end
  end
  object MemoIspis: TMemo
    Left = 192
    Top = 191
    Width = 321
    Height = 185
    TabOrder = 4
  end
  object Bpreuzmi: TButton
    Left = 790
    Top = 107
    Width = 75
    Height = 25
    Caption = 'Preuzmi'
    TabOrder = 5
    OnClick = BpreuzmiClick
  end
  object ProgressBar1: TProgressBar
    Left = 790
    Top = 84
    Width = 257
    Height = 17
    TabOrder = 6
  end
  object Edit1: TEdit
    Left = 816
    Top = 37
    Width = 121
    Height = 21
    TabOrder = 7
    Text = 'https://filetransfer.io/data-package/GsUKGELp/download'
  end
  object AEditBrzina: TEdit
    Left = 655
    Top = 80
    Width = 121
    Height = 21
    TabOrder = 8
    Text = '100'
  end
  object BzamjeniBaze: TButton
    Left = 880
    Top = 107
    Width = 113
    Height = 25
    Caption = 'Zamjeni Baze'
    TabOrder = 9
    OnClick = BzamjeniBazeClick
  end
  object BzakasnjelePosudbe: TButton
    Left = 790
    Top = 351
    Width = 154
    Height = 25
    Caption = 'Zakasnjele Posudbe'
    TabOrder = 10
    OnClick = BzakasnjelePosudbeClick
  end
  object StringGridBindSourceDB1: TStringGrid
    Tag = 3
    Left = 24
    Top = 391
    Width = 1199
    Height = 114
    ColCount = 3
    FixedCols = 0
    RowCount = 2
    TabOrder = 11
    ColWidths = (
      28
      41
      1534)
    ColAligments = (
      0
      0
      0)
  end
  object BgeneriranjeKljuceva: TButton
    Left = 40
    Top = 560
    Width = 153
    Height = 25
    Caption = 'GeneriranjeKljuceva'
    TabOrder = 12
    OnClick = BgeneriranjeKljucevaClick
  end
  object ComboBox1: TComboBox
    Left = 1180
    Top = 21
    Width = 43
    Height = 22
    Style = csOwnerDrawFixed
    Color = clAppWorkSpace
    ItemIndex = 1
    TabOrder = 13
    Text = 'HR'
    OnChange = ComboBox1Change
    Items.Strings = (
      'EN'
      'HR')
  end
  object Button1: TButton
    Left = 296
    Top = 544
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 14
    OnClick = Button1Click
  end
  object TCP_server: TIdTCPServer
    Active = True
    Bindings = <
      item
        IP = '0.0.0.0'
        Port = 4321
      end>
    DefaultPort = 4321
    OnExecute = TCP_serverExecute
    Left = 564
    Top = 216
  end
  object IdUDPServer1: TIdUDPServer
    Active = True
    BroadcastEnabled = True
    Bindings = <
      item
        IP = '0.0.0.0'
        Port = 5555
      end>
    DefaultPort = 0
    ThreadedEvent = True
    OnUDPRead = IdUDPServer1UDPRead
    Left = 561
    Top = 160
  end
  object HttpClient: TNetHTTPClient
    UserAgent = 'Embarcadero URI Client/1.0'
    Left = 1032
    Top = 128
  end
  object HttpRequest: TNetHTTPRequest
    MethodString = 'GET'
    Client = HttpClient
    Left = 1120
    Top = 128
  end
  object BindingsList1: TBindingsList
    Methods = <>
    OutputConverters = <>
    Left = 212
    Top = 437
    object LinkGridToDataSourceBindSourceDB13: TLinkGridToDataSource
      Category = 'Quick Bindings'
      DataSource = BindSourceDB1
      GridControl = StringGridBindSourceDB1
      Columns = <>
    end
  end
  object RESTClient1: TRESTClient
    Accept = 'application/json, text/plain; q=0.9, text/html;q=0.8,'
    AcceptCharset = 'utf-8, *;q=0.8'
    BaseURL = 'http://localhost:8080/zakasnjelePosudbe'
    Params = <>
    Left = 104
    Top = 432
  end
  object RESTRequest1: TRESTRequest
    AssignedValues = [rvConnectTimeout, rvReadTimeout]
    Client = RESTClient1
    Params = <>
    Response = RESTResponse1
    Left = 360
    Top = 440
  end
  object RESTResponse1: TRESTResponse
    ContentType = 'application/json'
    RootElement = 'korisnici'
    Left = 528
    Top = 432
  end
  object RESTResponseDataSetAdapter1: TRESTResponseDataSetAdapter
    Active = True
    Dataset = FDMemTable1
    FieldDefs = <>
    Response = RESTResponse1
    TypesMode = Rich
    NestedElements = True
    Left = 784
    Top = 432
  end
  object FDMemTable1: TFDMemTable
    Active = True
    FieldDefs = <
      item
        Name = 'ime'
        DataType = ftWideString
        Size = 4
      end
      item
        Name = 'prezime'
        DataType = ftWideString
        Size = 5
      end
      item
        Name = 'knjige'
        DataType = ftWideString
        Size = 255
      end>
    IndexDefs = <>
    FetchOptions.AssignedValues = [evMode]
    FetchOptions.Mode = fmAll
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvUpdateChngFields, uvUpdateMode, uvLockMode, uvLockPoint, uvLockWait, uvRefreshMode, uvFetchGeneratorsPoint, uvCheckRequired, uvCheckReadOnly, uvCheckUpdatable]
    UpdateOptions.LockWait = True
    UpdateOptions.FetchGeneratorsPoint = gpNone
    UpdateOptions.CheckRequired = False
    StoreDefs = True
    Left = 1000
    Top = 432
  end
  object BindSourceDB1: TBindSourceDB
    DataSet = FDMemTable1
    ScopeMappings = <>
    Left = 1152
    Top = 432
  end
  object Codec1: TCodec
    AsymetricKeySizeInBits = 1024
    AdvancedOptions2 = []
    CryptoLibrary = CryptographicLibrary1
    Left = 672
    Top = 208
    StreamCipherId = 'native.StreamToBlock'
    BlockCipherId = 'native.AES-128'
    ChainId = 'native.CBC'
  end
  object CryptographicLibrary1: TCryptographicLibrary
    Left = 848
    Top = 208
  end
  object ACodec: TCodec
    AsymetricKeySizeInBits = 1024
    AdvancedOptions2 = []
    CryptoLibrary = CryptographicLibrary1
    Left = 552
    Top = 576
    StreamCipherId = 'native.RSA'
    BlockCipherId = ''
    ChainId = 'native.CBC'
  end
  object Signatory1: TSignatory
    Codec = ACodec
    Left = 616
    Top = 576
  end
end
